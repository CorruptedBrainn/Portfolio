# This is the main script, standard execution starts and ends here.

# The script that will contain all of the functions, where calculations are performed.
# Multiple files are used for tidiness, and it helps me test specific aspects easily and efficiently.
from assistant import *

# Some global variables that I can access from anywhere
# 0 is a default value to indicate 0 objects chosen
# I stuffed them in a list for ease
costChoices = [0, 0, 0, 1, 0] # Rocket, Pilot, Passengers, Length, Cost

# Printing for loop since I always seem to be typing this
def printList(arr):
    for i in arr:
        print(i)
    return

# Defines over here will contain functions for each "page"
# This is done in functions to allow for recusrion
# The callstack is gonna go insane

# This page is the "return" page -- from here the user can navigate anywhere
def navigate(curr):
    # Clearing the screen for pretty formatting
    clearScreen()
    print(headerFormat("Page Navigation"))
    print(miscFormat("Enter the Corresponding Page Number to Navigate there"))
    print("")
    # Using arrays is better because it's faster
    options = [
        "Cancel Transaction",
        "Welcome / Home Page",
        "Rocket Selection Page",
        "Passenger / Pilot Page",
        "Trip Details Page",
        "Cost Calculation Page"
    ]
    prints = []
    for i in range(curr + 1):
        prints.append("Page " + str(i) + "       | " + options[i])
    printList(optionsFormat(prints))
    # Loop to take the user's input until it matches a valid page number
    choice = 100
    while choice == 100:
        # The sleep function will return a keypress
        choice = sleep()
        if choice.isdigit() != True or int(choice) > curr:
            choice = 100
    choice = int(choice)
    # Messy if tree that'll detect the page to go to
    if choice == 0: return kill()
    if choice == 1: 
        clearScreen()
        return welcome()
    if choice == 2: return rockets()
    if choice == 3: return people()
    if choice == 4: return days()
    if choice == 5: return final()
    print("")
    # If something goes bad this should catch it -- Shouldn't happen EVER
    printList(miscFormat("An unexpected error occured. Try again."))
    return navigate(curr)

# This page is the "welcome" page
def welcome():
    # Tiny function
    print(headerFormat("Welcome!"))
    printList(optionsFormat(["Press any key to Start"]))
    sleep()
    rockets()
    return

# This page is the rocket selection page
def rockets():
    # Just about every single function has the same or similar structure to the navigation function (row 23)
    clearScreen()
    print(headerFormat("Choose your rocket"))
    print(miscFormat(str("Current Cost: " + showCost(costChoices[4]))))
    print(miscFormat("Enter the Corresponding Option Number to Choose it"))
    print("")
    prints = []
    for i in range(len(costList[0])):
        prints.append("Rocket " + str(i + 1) + "     | " + costList[0][i][0] + ": " + showCost(costList[0][i][1]) + " / Day")
    prints.append("------------------------")
    if costChoices[0] > 0: prints.append("Enter Key   | Next Page")
    prints.append("Backspace   | Navigation")
    if costChoices[0] > 0:
        prints[costChoices[0] - 1] = prints[costChoices[0] - 1] + " (SELECTED)"
    printList(optionsFormat(prints))
    choice = 0
    while choice == 0:
        choice = sleep()
        if choice.isdigit():
            choice = int(choice)
            if 1 <= choice and choice <= 3:
                costChoices[0] = choice
                costChoices[4] = calculateCost(costChoices)
                choice = rockets()
            else:
                choice = 0
        elif choice == "\\r" and costChoices[0] > 0:
            return people()
        elif choice == "\\x08":
            return navigate(2)
        else:
            choice = 0
            continue
    return choice

# This page is the people selection page
def people():
    clearScreen()
    print(headerFormat("Choose who's Coming"))
    print(miscFormat(str("Current Cost: " + showCost(costChoices[4]))))
    print(miscFormat("Enter the Corresponding Option Key to Choose it"))
    print("")
    prints = []
    prints.append("Up / Down   | Cycle Through Passengers: $500 / Passenger / Day (" + str(costChoices[2]) + "/10)")
    prints.append("[Y] / [N]   | Choose Pilot: $500 / Day (")
    if costChoices[1] == 0: prints[1] = prints[1] + "None Selected)"
    else: prints[1] = prints[1] + "Pilot Selected)"
    prints.append("------------------------")
    prints.append("Enter Key   | Next Page")
    prints.append("Backspace   | Navigation")
    printList(optionsFormat(prints))
    choice = 0
    while choice == 0:
        choice = sleep()
        if choice == "\\r":
            return days()
        elif choice == "\\x08":
            return navigate(3)
        elif choice == "y" or choice == "Y":
            costChoices[1] = 1
        elif choice == "n" or choice == "N":
            costChoices[1] = 0
        elif choice == "\\xe0H":
            costChoices[2] += 1
            costChoices[2] %= 11
        elif choice == "\\xe0P":
            costChoices[2] += 10
            costChoices[2] %= 11
        else:
           choice = 0
           continue
        costChoices[4] = calculateCost(costChoices)
        choice = people()
    return choice

# This page is the trip length / details page
def days():
    clearScreen()
    print(headerFormat("Choose how long your Trip is"))
    print(miscFormat(str("Current Cost: " + showCost(costChoices[4]))))
    print(miscFormat("Enter the Corresponding Option Key to Choose it"))
    print("")
    prints = []
    prints.append("Each Day will Cost " + showCost(calculateIndividualCosts(costChoices)[3]))
    prints.append("Trip Length: " + str(costChoices[3]) + " Days (min-max: 1-30)")
    prints.append("------------------------")
    prints.append("Up Arrow    | Increase Trip Length by 1 Day")
    prints.append("Down Arrow  | Decrease Trip Length by 1 Day")
    prints.append("Left Arrow  | Increase Trip Length by 5 Days")
    prints.append("Right Arrow | Decrease Trip Length by 5 Days")
    prints.append("------------------------")
    prints.append("Enter Key   | Next Page")
    prints.append("Backspace   | Navigation")
    printList(optionsFormat(prints))
    choice = 0
    while choice == 0:
        choice = sleep()
        if choice == "\\r":
            return final()
        elif choice == "\\x08":
            return navigate(4)
        elif choice == "\\xe0H":
            costChoices[3] += 1
        elif choice == "\\xe0P":
            costChoices[3] += 29
        elif choice == "\\xe0M":
            costChoices[3] += 10
        elif choice == "\\xe0K":
            costChoices[3] += 20
        else:
            choice = 0
            continue
        costChoices[3] -= 1
        costChoices[3] %= 30
        costChoices[3] += 1
        costChoices[4] = calculateCost(costChoices)
        choice = days()
    return choice

# This page is the final cost calculation page
def final():
    clearScreen()
    print(headerFormat("Final Cost Details"))
    arr = calculateIndividualCosts(costChoices)
    print(miscFormat(str("Cost of Rocket (" + costList[0][costChoices[0] - 1][0] + "): " + showCost(arr[0]) + " per Day")))
    if costChoices[1] == 1:
        print(miscFormat(str("Cost of a Pilot: " + showCost(arr[1]) + " per Day")))
    if costChoices[2] > 1:
        print(miscFormat(str("Cost of a Passenger: " + showCost(costList[2]) + " per Day")))
        print(miscFormat("\tNumber of Passengers: " + str(costChoices[2])))
        print(miscFormat(str("\tTotal Passenger Cost: " + showCost(arr[2]) + " per Day")))
    print(miscFormat(str("Daily Cost: " + showCost(arr[3]))))
    print(headerFormat(str("Total Cost: " + showCost(costChoices[4]))))
    print("")
    print(miscFormat("Enter the Corresponding Option Key to Choose it"))
    print("")
    printList(optionsFormat(["Enter Key   | Next Page",
                                    "Backspace   | Navigation"]))
    choice = 0
    while choice == 0:
        choice = sleep()
        if choice == "\\r":
            clearScreen()
            print(headerFormat("Thank you!"))
            print(miscFormat("Final Cost: " + showCost(costChoices[4]) + " for " + str(costChoices[3]) + " days"))
            print("")
            return
        elif choice == "\\x08":
            return navigate(5)
        else:
            choice = 0
            continue
    return choice

# This page is where the user is directed when they cancel the transaction
def kill():
    clearScreen()
    return

# The main function, where function calling happens.
def main():
    printList(beginEndBanner("Mars Trip Rocket Planning"))
    print("")
    welcome()
    printList(beginEndBanner("Farewell, and Safe Trip!"))
    printList(optionsFormat(["Press any key to End"]))
    sleep()
    return

# Code execution begins and ends here. This will make sure that for the script to run, code execution has to start from this file.
if __name__ == '__main__':
    # This block will run the main function, and if a fatal error is caught it won't kill the prorgam execution
    # Instead, it goes to the except block, and it will continue execution from there.
    try:
        main()
    except:
        # I don't know what the formatting looks like for this
        # Ideally this segment of code will NEVER run
        # It serves as a just in case something does happen
        clearScreen()
        print(headerFormat("An unexpected error occurred."))
        printList(optionsFormat(["Please Restart the Program."]))
        print("")
        printList(beginEndBanner("Farewell, we Apologise for any Inconvenience"))