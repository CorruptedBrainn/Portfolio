"""
Name: cpp_wrapper.py
Version: 0.0.3-alpha
Description: This file contains the classes that allow me to call functions within my C++ DLLs easier
Author: Nicolas Martens
"""

from math import ceil
import os, ctypes

# Load the DLL with some filepath magic
scriptDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
dllDir = os.path.join(scriptDir, "bin\\vs-2022\\x64\\Release DLL")
script = ctypes.CDLL(dllDir + "\\Cpp Functions.dll", winmode=0)

# This class represents generating a polygon within the game environment
class GamePolygon(object):
    # Some variables and function metadata
    polygon = list[list[float]]()
    ptr = ctypes.POINTER(ctypes.POINTER(ctypes.c_double))
    size = int()
    script.createPolygon.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_double))
    script.createPolygon.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double,
                                     ctypes.c_double, ctypes.c_double, ctypes.c_int]
    script.deletePolygon.argtypes = [ctypes.POINTER(ctypes.POINTER(ctypes.c_double)), ctypes.c_int]

    # Create the polygon
    def __init__(self, x, y, r, i, s, f):
        self.size = ceil(5 * f * ceil(r / 100));
        self.ptr = script.createPolygon(x, y, r, i, s, self.size) # Returns a list of points
        self.polygon = []
        for i in range(self.size):
            self.polygon.append([self.ptr[i][0], self.ptr[i][1]])
        return

    # Delete the polgyon
    def delete(self):
        return script.deletePolygon(self.ptr, self.size)