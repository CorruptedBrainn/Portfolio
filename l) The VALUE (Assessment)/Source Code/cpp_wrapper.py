"""
Name: cpp_wrapper.py
Version: 0.0.3-alpha
Description: This file contains the classes that allow me to call functions within my C++ DLLs easier
Author: Nicolas Martens
"""

import os, ctypes
from random import shuffle
from re import S

# Load the DLL with some filepath magic
scriptDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
dllDir = os.path.join(scriptDir, "bin\\vs-2022\\x64\\Debug DLL")
script = ctypes.CDLL(dllDir + "\\Cpp Functions.dll", winmode=0)

class question: ...

class Generator(object):
	class question(ctypes.Structure):
		_fields_ = [
			("question", ctypes.c_wchar_p),
			("answer", ctypes.c_int * 6),
			("optionA", ctypes.c_int * 6),
			("optionB", ctypes.c_int * 6),
			("optionC", ctypes.c_int * 6),
			("type", ctypes.c_int)
			]

	script.create.restype = question
	script.create.argtypes = [ctypes.c_int]
	script.clean.restype = ctypes.c_int
	script.clean.argtypes = [ctypes.c_int]

	def create(difficulty:int = -1, buffer:int = 10)->question:
		ret:question = script.create(difficulty)
		script.clean(buffer)
		return ret

class question:
	def __init__(self, obj:Generator.question):
		self.question = str(obj.question)
		self.answer = []
		opA = []
		opB = []
		opC = []
		numzero = 0
		azero = 0
		bzero = 0
		czero = 0
		for ans in obj.answer:
			self.answer.append(str(ans))
			if str(ans) == str(0): numzero += 1
		for ans in obj.optionA:
			opA.append(str(ans))
			if str(ans) == str(0): azero += 1
		for ans in obj.optionB:
			opB.append(str(ans))
			if str(ans) == str(0): bzero += 1
		for ans in obj.optionC:
			opC.append(str(ans))
			if str(ans) == str(0): czero += 1
		numzero = 6 - min(numzero, azero, bzero, czero)
		self.answer = ", ".join(self.answer[:numzero])
		opA = opA[:numzero]
		opB = opB[:numzero]
		opC = opC[:numzero]
		self.type = obj.type
		options = [self.answer, ", ".join(opA), ", ".join(opB), ", ".join(opC)]
		shuffle(options)
		self.optionTR = options[0]
		self.optionTL = options[1]
		self.optionBR = options[2]
		self.optionBL = options[3]
		return

	def __repr__(self)->str:
		ret:str = "--QUESTION OBJ--\n"
		ret += " | Question: " + self.question + "\n | Answer: " + self.answer
		ret += "\n\nOptions:\n\t | " + self.optionTL
		ret += "\n\t | " + self.optionTR
		ret += "\n\t | " + self.optionBL
		ret += "\n\t | " + self.optionBR
		return ret

	def __str__(self)->str:
		return "Question: " + self.question + "\nAnswer: " + self.answer