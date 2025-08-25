# Imports to allow me to test everything
from os import read
import main
import assistant as funcs
import unittest

# Imports to allow me to modify standard input / output (I/O) streams and manipulate them for easier testing
import sys
import io

def letterCode(letter):
    if letter == "ENTER":
        return ["\\r"]
    elif letter == "BACKSPACE":
        return ["\\x08"]
    elif letter == "UP":
        return ["\\xe0", "H"]
    elif letter == "DOWN":
        return ["\\xe0", "P"]
    elif letter == "LEFT":
        return ["\\xe0", "K"]
    elif letter == "RIGHT":
        return ["\\xe0", "M"]
    else: return [letter]

def setupIOTest(stringArr):
    oldstdin = sys.stdin
    funcs.testingVar = True
    # where letter is an array
    letter = []
    for i in stringArr:
        letter += letterCode(i)
    res = ""
    for i in letter:
        res = res + "b'" + i + "'\n"
    sys.stdin = io.StringIO(res)

def startTest(function):
    main.costChoices = [0, 0, 0, 1, 0]
    oldstdout = sys.stdout
    f = open("tests.txt", 'w')
    sys.stdout = f
    function()
    f.close()
    return readAllLines("tests.txt")

def readAllLines(fileName):
    f = open(fileName, "a")
    f.close()
    f = open(fileName, "r")
    ret = f.readlines()
    f.close()
    return ret

class test_StressTesting(unittest.TestCase):
    # These tests will run through the program as usual
    def test_BasicTest_A(self):
        setupIOTest(["ENTER"])
        arr = readAllLines("BasicTestA.txt")
        self.assertEqual(startTest(main.final), arr)

    # From now on, these tests will simulate through the whole program
    # They will test specific aspects of functions and the recursion idea of the program
    # I created the expected outputs based on individual function outputs
    # This is because manually writing them all would've been a mess

    def test_BasicTest_B(self):
        setupIOTest(["UP",
                     "ENTER", "3", "1", "ENTER",
                     "DOWN", "DOWN", "N", "Y", "UP", "ENTER",
                     "DOWN", "ENTER",
                     "BACKSPACE",
                     "0",
                     "P"])
        arr = readAllLines("BasicTestB.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_BasicTestC(self):
        setupIOTest(["R",
                     "Q", "F", "@", "c", "p", "e", "2", "9", "0", "[","BACKSPACE",
                     "9", "8", "1",
                     "BACKSPACE",
                     "BACKSPACE", "0",
                     "R"])
        arr = readAllLines("BasicTestC.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_BasicTestD(self):
        setupIOTest(["D",
                     "3", "2", "1", "3", "2", "1", "BACKSPACE",
                     "P", "3", "2",
                     "2", "1", "ENTER",
                     "Y", "N", "UP", "y", "n", "UP", "DOWN", "UP", "UP", "UP", "DOWN", "ENTER",
                     "UP", "DOWN", "3", "LEFT", "RIGHT", "RIGHT", "RIGHT", "LEFT", "DOWN", "BACKSPACE",
                     "5", "2",
                     "ENTER",
                     "ENTER",
                     "ENTER",
                     "BACKSPACE",
                     "5",
                     "ENTER",
                     "H"])
        arr = readAllLines("BasicTestD.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_Breaker_A(self):
        setupIOTest(["F",
                     "4", "5", "6", "0", "d", "UP", "DOWN", "LEFT", "RIGHT", "Q", "~", "+", "ENTER", "BACKSPACE",
                     "1",
                     "ENTER",
                     "BACKSPACE",
                     "0",
                     "E"])
        arr = readAllLines("BreakTestA.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_Breaker_B(self):
        setupIOTest(["G",
                     "3", "ENTER",
                     "D", "UP", "DOWN", "UP", "J", "P", "S", "W", "Q", "K", "d", "p", "1", "2", "3", "4", "5", "9", "UP", "y", "y", "n", "y", "BACKSPACE",
                     "0",
                     "g"])
        arr = readAllLines("BreakTestB.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_Breaker_C(self):
        setupIOTest(["H",
                     "2", "ENTER",
                     "ENTER",
                     "UP", "DOWN", "RIGHT", "LEFT", "LEFT", "RIGHT", "LEFT", "UP", "DOWN", "DOWN", "DOWN", "Y", "N", "P", "1", "0", "2", "D", "W", "Q", "S", "R", "T", "ENTER",
                     "BACKSPACE",
                     "3",
                     "Y", "ENTER",
                     "ENTER",
                     "BACKSPACE",
                     "5",
                     "ENTER",
                     "P"])
        arr = readAllLines("BreakTestC.txt")
        self.assertEqual(startTest(main.main), arr)

    def test_Breaker_D(self):
        setupIOTest(["I",
                     "ENTER", "1", "ENTER",
                     "Y", "UP", "UP", "ENTER",
                     "LEFT", "ENTER",
                     "BACKSPACE",
                     "2",
                     "3", "BACKSPACE",
                     "5", "2",
                     "ENTER",
                     "ENTER",
                     "ENTER",
                     "ENTER",
                     "K"])
        arr = readAllLines("BreakTestD.txt")
        self.assertEqual(startTest(main.main), arr)

if __name__ == '__main__':
    unittest.main()