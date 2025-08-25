# Imports to allow me to test everything
import assistant as funcs
import unittest

# Imports to allow me to modify standard input / output (I/O) streams and manipulate them for easier testing
import sys
import io

# A way to calculate the costs that I know will work
rCosts = [0, 10000, 5000, 8000]
piCosts = 500
paCosts = 500

# This runs default testing, using for loops to simulate calculating the cost with each possible value
# It compares and returns false if one of the options is false
# I know the cost it's attempting to calculate is correct because the two methods of comparing return the same value
def calcOptionsCall():
    ret = True
    for i in range(1, 4):
            for j in range(2):
                for k in range(11):
                    for l in range(1, 31):
                        ret = (funcs.calculateCost([i, j, k, l]) == (rCosts[i] + (piCosts * j) + (paCosts * k)) * l)
                        if ret == False:
                            return False
    return True

def letterCode(letter):
    if letter == "ENTER":
        return ["\r"]
    elif letter == "BACKSPACE":
        return ["\x08"]
    elif letter == "UP":
        return ["\xe0", "H"]
    elif letter == "DOWN":
        return ["\xe0", "P"]
    elif letter == "LEFT":
        return ["\xe0", "K"]
    elif letter == "RIGHT":
        return ["\xe0", "M"]
    else: return [letter]

def setupSleepTest(letter):
    oldstdin = sys.stdin
    funcs.testingVar = True
    # where letter is an array
    letter = letterCode(letter)
    res = ""
    for i in letter:
        res = res + "b'" + i + "'\n"
    sys.stdin = io.StringIO(res)


class test_Math(unittest.TestCase):
    # Test against all calculation options
    # 1914 tests run -- if one returns false they all fail
    def test_AllCalcOptions(self):
        self.assertEqual(calcOptionsCall(), True)

    # Calculate an arbitrary daily cost with:
        # Rocket 2 (Cost: 5000)
        # Pilot (Cost: 500)
        # 7 Passengers (Cost: 3500)
    def test_CalculateADailyCost_A(self):
        self.assertEqual(funcs.calculateIndividualCosts([2, 1, 7]), [5000, 500, 3500, 9000])
    
    # Calculate an arbitrary daily cost with 0 options chosen
    # Should calculate 0 dollars cose for all
    def test_CalculateADailyCost_B(self):
        self.assertEqual(funcs.calculateIndividualCosts([0, 0, 0]), [0, 0, 0, 0])

class test_CostFormatting(unittest.TestCase):
    # The next 10 tests will calculate my formatting of numerical values to money
    # The script should theoretically only use up to sizes under 10^7
    # Run up to (including) 10^9 to check it'll work
    def test_Money1dig_A(self):
        self.assertEqual(funcs.showCost(0), "$0")
    
    def test_Money1dig_B(self):
        self.assertEqual(funcs.showCost(9), "$9")
    
    def test_Money2dig_A(self):
        self.assertEqual(funcs.showCost(78), "$78")
    
    def test_Money3dig_A(self):
        self.assertEqual(funcs.showCost(501), "$501")
    
    def test_Money4dig_A(self):
        self.assertEqual(funcs.showCost(1000), "$1,000")
    
    def test_Money5dig_A(self):
        self.assertEqual(funcs.showCost(99999), "$99,999")
    
    def test_Money6dig_A(self):
        self.assertEqual(funcs.showCost(101010), "$101,010")
    
    def test_Money7dig_A(self):
        self.assertEqual(funcs.showCost(7654321), "$7,654,321")
    
    def test_Money8dig_A(self):
        self.assertEqual(funcs.showCost(12345678), "$12,345,678")

    def test_Money9dig_A(self):
        self.assertEqual(funcs.showCost(123789456), "$123,789,456")

class test_GenericFormatting(unittest.TestCase):
    # This class is used to test my generic string formatting functions
    def test_Banner_A(self):
        self.assertEqual(funcs.beginEndBanner("A Generic Message of Length N"), [
            "+-------------------------------+",
            "| A Generic Message of Length N |",
            "+-------------------------------+"
        ])
    
    def test_Banner_B(self):
        self.assertEqual(funcs.beginEndBanner("Ten Chars"), [
            "+-----------+",
            "| Ten Chars |",
            "+-----------+"
        ])
    
    def test_Header_A(self):
        self.assertEqual(funcs.headerFormat("HWEFOWQ FWF* (@NYF@W@NUF)"), "==== HWEFOWQ FWF* (@NYF@W@NUF) ====")
    
    def test_Header_B(self):
        self.assertEqual(funcs.headerFormat("2"), "==== 2 ====")

    def test_Options_A(self):
        self.assertEqual(funcs.optionsFormat(["Only 1 Lonely Option"]), ["--< Only 1 Lonely Option >--"])
    
    def test_Options_B(self):
        self.assertEqual(funcs.optionsFormat(["Stress Testing A",
                                              "Stress Testing B",
                                              "Stress Testing C",
                                              "Tress Stesting D",
                                              "Testing Stress E",
                                              "Outsider F"]), [
                                                  "--< Stress Testing A >--",
                                                  "--< Stress Testing B >--",
                                                  "--< Stress Testing C >--",
                                                  "--< Tress Stesting D >--",
                                                  "--< Testing Stress E >--",
                                                  "--< Outsider F >--"
                                              ])
    
    def test_Misc_A(self):
        self.assertEqual(funcs.miscFormat("HWEFOWQ FWF* (@NYF@W@NUF)"), " | HWEFOWQ FWF* (@NYF@W@NUF) | ")

    def test_Misc_B(self):
        self.assertEqual(funcs.miscFormat("2"), " | 2 | ")

    def test_Misc_C(self): # Where \t is the tab character, because it jumps to a set position I'm setting the answer with the tab character too
        self.assertEqual(funcs.miscFormat("\t"), " | \t | ")

    def test_Misc_D(self):
        self.assertEqual(funcs.miscFormat("\tNumber of Passengers: " + str(10)), " | \tNumber of Passengers: 10 | ")

class test_Sleeps(unittest.TestCase):
    # Small tests to allow me to check my sleep functions return the correct output
    # I use special commands such as "ENTER" or "UP" to simulate the keypresses
    def test_Sleep_A(self):
        setupSleepTest("E")
        self.assertEqual(funcs.sleep(), "E")

    def test_Sleep_B(self):
        setupSleepTest("3")
        self.assertEqual(funcs.sleep(), "3")

    def test_Sleep_C(self):
        setupSleepTest("0")
        self.assertEqual(funcs.sleep(), "0")

    def test_Sleep_D(self):
        setupSleepTest("~")
        self.assertEqual(funcs.sleep(), "~")

    def test_Sleep_E(self):
        setupSleepTest("ENTER")
        self.assertEqual(funcs.sleep(), "\r")

if __name__ == '__main__':
    unittest.main()