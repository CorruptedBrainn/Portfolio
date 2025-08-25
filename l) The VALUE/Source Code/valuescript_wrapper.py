"""
Name: valuescript_wrapper.py
Version: 0.0.3-alpha
Description: This script wraps the Valuescript DLL so I can call functions with ease
Author: Nicolas Martens
"""

import os, ctypes

# Get the directories with some filepath magic
scriptDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
dllDir = os.path.join(scriptDir, "bin\\vs-2022\\x64\\Release DLL")

# A variable change structure
class call(ctypes.Structure):
    _fields_ = [("unit", ctypes.c_wchar_p),
                ("var", ctypes.c_wchar_p),
                ("value", ctypes.c_double)]

class request(ctypes.Structure):
    _fields_ = [("unit", ctypes.c_wchar_p),
                ("var", ctypes.c_wchar_p)]

# The class that contains functions for me to use
class VSProgramObject(object):
    # Load the DLLs
    dep = ctypes.CDLL(dllDir + "\\antlr4-runtime.dll", winmode=0)
    script = ctypes.CDLL(dllDir + "\\ANTLR4_GENERATION.dll", winmode=0)
    script.readExportPipeline.restype = ctypes.c_void_p
    script.readRequestPipeline.restype = ctypes.c_void_p

    # Initialise
    def __init__(self):
        self.obj = self.script.createStorage()
        return

    # Delete (for memory safety)
    def __del__(self):
        return self.script.deleteStorage(self.obj)

    # Add a new program
    def add(self, name: str, text: str):
        return self.script.addProgram(self.obj, name, text)

    # Delete a program
    def remove(self, name: str):
        return self.script.removeProgram(self.obj, name)

    # Execute the programs in parallel
    def run(self):
        return self.script.executePrograms(self.obj)

    # Grab next variable change
    def grab(self):
        w = self.script.readExportPipeline(self.obj)
        x = call.from_address(w)
        return [x.unit, x.var, x.value]

    def clean(self):
        return self.script.killExportPipeline(self.obj)

    def update(self, unit:str, name:str, value):
        return self.script.updateImportPipeline(self.obj, unit, name, int(value))

    def get(self):
        w = self.script.readRequestPipeline(self.obj)
        x = request.from_address(w)
        return [x.unit, x.var]

    def put(self, unit:str, var:str):
        return self.script.addRequestPipeline(self.obj, unit, var)

    # Call for the programs to all stop running
    def kill(self):
        return self.script.killPrograms(self.obj)