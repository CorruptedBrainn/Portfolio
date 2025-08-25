# This script will contain all of the functions called by the main script

# This import will allow me to use some extra math functions
from math import *

# These imports will allow me to detect the operating system so I can sleep execution
import os
import sys

testingVar = False

# A global variable storing every single cost
costList = [
    [ # List of rockets
        ["Rocket Lab Photon", 10000], # Name, cost per day
        ["SpaceX Falcon 9", 5000],
        ["Blue Origin New Shepard", 8000]
    ],
    500, # Cost of a pilot per day
    500 # Cost of each passenger per day
] # Indexing kinda hits hard ngl

# The sleep function -- grabbed from an installable module instead of downloading it online
def sleep():
    if os.name == "nt":
        import msvcrt as ms
        # Testing Var logic to allow me to modify the standard input stream (sys.stdin) and simulate inputs
        if testingVar == True: res = input()
        else: res = ms.getch()
        if str(res)[2:-1] == "\\xe0":
            if testingVar == True:
                dump = input()
                res = res[:-1]
                res += dump[2:]
            else: res += ms.getch()

    else:
        import termios as tr
        fd = sys.stdin.fileno()
        oldterm = tr.tcgetattr(fd)
        newattr = tr.tcgetattr(fd)
        newattr[3] = newattr[3] & ~tr.ICANON & ~tr.ECHO
        tr.tcsetattr(fd, tr.TCSANOW, newattr)
        try:
            res = sys.stdin.read(1)
        except IOError:
            pass
        finally:
            tr.tcsetattr(fd, tr.TCSAFLUSH, oldterm)
    return str(res)[2:-1]

# The clear screen function -- will allow me to clear the terminal for tidiness
def clearScreen():
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")
    return

# The function to make the banner at the start and end of the program -- It's dynamically sized based on the message
# This uses a 2D array (an array of strings, which is an array of characters) to store the output message
# O(n) -- Linear Time & Space Complexity where n is the length of the message
def beginEndBanner(message):
    message = str(message)
    arr = ["", "", ""]
    arr[0] = "+"
    arr[1] = "| "
    arr[2] = "+"
    for i in range(len(message) + 2):
        arr[0] = arr[0] + "-"
        arr[2] = arr[2] + "-"
    arr[1] = arr[1] + message
    arr[0] = arr[0] + "+"
    arr[1] = arr[1] + " |"
    arr[2] = arr[2] + "+"
    return arr

# The function to create "page" or "section" headers
# O(1) -- Constant Time & Space Complexity
def headerFormat(message):
    message = str(message)
    return "==== " + message + " ===="

# The function to create page options / commands
# This uses a 2D array (Like at the beginning, a 1D array of strings) to store the message
# O(n) -- Linear Time & Space Complexity where n is the amount of options
def optionsFormat(options):
    arr = []
    for i in options:
        arr.append("--< " + str(i) + " >--")
    return arr

# Another formatting function
# O(1) -- Constant Time & Space Complexity
def miscFormat(message):
    message = str(message)
    return " | " + message + " | "

# This function will display the costs in a pretty way for me
# Uses a 1D array (string) to space the numbers properly
# O(n) -- Linear Time & Space Complexity where n is the length of the string
def showCost(cost):
    cost = str(cost)
    ret = "$"
    length = len(cost)
    mod = length % 3
    if mod == 0: mod = 3
    ret = ret + cost[:mod]
    for i in range(length - mod):
        if i % 3 == 0: ret = ret + ","
        ret = ret + cost[i + mod]
    return ret

# This will return the cost calculated from the list given
# O(1) -- Constant Time & Space Complexity
def calculateCost(arr):
    ret = 0
    if arr[0] > 0:
        ret += costList[0][arr[0] - 1][1]
    ret += costList[1] * arr[1]
    ret += costList[2] * arr[2]
    ret *= arr[3]
    return ret

# This will return an array of each cost component
# O(1) -- Constant Time & Space Complexity
def calculateIndividualCosts(arr):
    ret = []
    if arr[0] > 0:
        ret.append(costList[0][arr[0] - 1][1])
    else: ret.append(0)
    ret.append(costList[1] * arr[1])
    ret.append(costList[2] * arr[2])
    ret.append(sum(ret))
    return ret