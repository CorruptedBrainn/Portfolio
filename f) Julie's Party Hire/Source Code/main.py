from tkinter import *
from tkinter import Tk as tk
from tkinter import ttk
from tkinter import messagebox as mb
from tkinter import font
from functools import partial
import os
import re
# My imports for the program
#   Tkinter manages the GUI aspect
#   Functools allowes me to bypass the tkinter command restrictions
#       and pass values through to other functions  run by a button
#   os is the operating system, it allows me to shut down the program
#       and other things such as current filepath location (for running
#       on other devices)
#   re allows me to do things such as splitting to an array

root = tk()
style = ttk.Style()
# Define the root (main window) and style (main styling used)

"""
    Cooper Black - Jokerman - Magneto

    PaleGreen1 PaleGreen2 PaleGreen3
    SteelBlue1 SteelBlue2 SteelBlue3
    MediumOrchid1 MediumOrchid2 MediumOrchid3
"""
# My colour and font options, I copied and pasted from this list

"""
    ICONS MADE BY:
    Smashicons      -   www.flaticon.com
    Icon Place      -   www.flaticon.com
    Abdul-Aziz      -   www.flaticon.com
    manshagraphics  -   www.flaticon.com
    freepik         -   www.flaticon.com

    VectorPortal    -   www.flaticon.com
"""
# Credits to the people who made the icons I used
# All icons were pulled from www.flaticon.com

fontFamily = "Jokerman"
# A variable as my font, so I can change this line and all my fonts automatically update

imgDir = os.getcwd()
genDir = os.getcwd()
# A variable that gets the local filepath of the program, so I can pull the location of icons
# imgDir is Image Directory :D
# genDir is the general directory, it's the same as above however different name for naming purposes

mainIcon = PhotoImage(file = fr"{imgDir}\ICONS\MainMenuIcon.png")
createIcon = PhotoImage(file = fr"{imgDir}\ICONS\CreateMenuIcon.png")
deleteIcon = PhotoImage(file = fr"{imgDir}\ICONS\DeleteMenuIcon.png")
editIcon1 = PhotoImage(file = fr"{imgDir}\ICONS\EditMenuIcon1.png")
editIcon2 = PhotoImage(file = fr"{imgDir}\ICONS\EditMenuIcon2.png")

quitBtnIcon = PhotoImage(file = fr"{imgDir}\ICONS\QuitIcon.png")
actionIcon = PhotoImage(file = fr"{imgDir}\ICONS\ActionIcon.png")
createBtnIcon = PhotoImage(file = fr"{imgDir}\ICONS\CreateItemsIcon.png")
listBtnIcon = PhotoImage(file = fr"{imgDir}\ICONS\ListItemsIcon.png")
deleteBtnIcon = PhotoImage(file = fr"{imgDir}\ICONS\DeleteItemsIcon.png")
editBtnIcon = PhotoImage(file = fr"{imgDir}\ICONS\EditItemsIcon.png")

firstNameIcon = PhotoImage(file = fr"{imgDir}\ICONS\FirstNameIcon.png")
lastNameIcon = PhotoImage(file = fr"{imgDir}\ICONS\LastNameIcon.png")
itemIcon = PhotoImage(file = fr"{imgDir}\ICONS\ItemsIcon.png")
numberItemsIcon = PhotoImage(file = fr"{imgDir}\ICONS\NumberItemsIcon.png")
receiptIcon = PhotoImage(file = fr"{imgDir}\ICONS\ReceiptIcon.png")
# Create all of my icons as variables to use later on

mbgColour = "SteelBlue1"
genColour = "SteelBlue2"
selColour = "SteelBlue3"
# 3 variables as my colours, so I can change these lines and all my colours automatically update
# mbgColour is Main Background Colour, genColour is General Colour, and selColour is Select Colour

style.theme_use("alt")
# Set the theme to visually change some things such as buttons
# This was done because tkinter fucking sucks with their themes
# And the vista theme has issues with changing the colour of buttons

style.configure("TFrame", background = mbgColour)
style.configure("TLabel", background = mbgColour)
style.configure("TButton", bordercolor = "black")
style.configure("TSpinbox", arrowcolor = "black", arrowsize = 15)
style.configure("TCombobox", arrowcolor = "black", arrowsize = 15)
style.map("TButton", 
          background = [("!active", genColour), ("active", selColour)],
          relief = [("!active", "raised"), ("active", "solid")],
          borderwidth = [("!active", 1), ("active", 2)]
          )
style.map("TEntry",
          fieldbackground = [("!focus", genColour), ("focus", selColour)])
style.map("TCombobox",
          fieldbackground = [("!focus", genColour), ("focus", selColour)])
style.map("TSpinbox",
          fieldbackground = [("!focus", genColour), ("focus", selColour)])
# Use map and configure commands to set the default styles / options of tkinter / GUI widgets
# The maps are used to change the visuals of a widget when it has different states
# For example, if an entry (TEntry) is selected, it's background will be changed to selColour

titleFont = font.Font(family = fontFamily, name = "titleFont", size = 28, weight = "bold")
headerFont = font.Font(family = fontFamily, name = "headerFont", size = 21, weight = "bold")
mainFont = font.Font(family = fontFamily, name = "mainFont", size = 19)
italFont = font.Font(family = fontFamily, name = "italFont", size = 11, slant = "italic")
subFont = font.Font(family = fontFamily, name = "subFont", size = 15)
entryFont = font.Font(family = fontFamily, name = "entryFont", size = 13, slant = "italic")
# Define all my fonts for use

style.configure("Title.TLabel", font = titleFont, padding = 5)
style.configure("Header.TLabel", font = headerFont, padding = 3)
style.configure("Main.TLabel", font = mainFont, padding = 3)
style.configure("Main.TButton", font = mainFont, padding = 5, width = 40)
style.configure("Sub.TButton", font = italFont, padding = 2, width = 5, height = 1.5)
style.configure("Input.TLabel", font = subFont, padding = 3)
# Configure all my custom labels and buttons that are used for different purposes

root.title("Julie's Party Hire Store")
root.configure(bg = mbgColour)
# Set the title of the root window (main window) and it's background

mainFrame = ttk.Frame(root, padding = 6, width = 300, height = 300)
secondaryFrame = ttk.Frame(mainFrame, padding = 5)
actionFrame = ttk.Frame(mainFrame, padding = 9)
titleLabel = ttk.Label(mainFrame, style = "Title.TLabel")
titleImage1 = ttk.Label(root, style = "Title.TLabel", image = mainIcon)
titleImage2 = ttk.Label(root, style = "Title.TLabel", image = mainIcon)
secondaryLabel = ttk.Label(secondaryFrame, style = "Header.TLabel")
quitButton = ttk.Button(root, style = "Sub.TButton", image = quitBtnIcon, compound = "left")
createButton = ttk.Button(secondaryFrame, style = "Main.TButton", image = createBtnIcon, compound = "left")
listButton = ttk.Button(secondaryFrame, style = "Main.TButton", image = listBtnIcon, compound = "left")
deleteButton = ttk.Button(secondaryFrame, style = "Main.TButton", image = deleteBtnIcon, compound = "left")
editButton = ttk.Button(secondaryFrame, style = "Main.TButton", image = editBtnIcon, compound = "left")
firstNameEntry = ttk.Entry(actionFrame, font = entryFont, width = 30)
lastNameEntry = ttk.Entry(actionFrame, font = entryFont, width = 30)
rentedItemEntry = ttk.Combobox(actionFrame, font = entryFont, width = 30, style = "Input.TCombobox")
numberItemsEntry = ttk.Spinbox(actionFrame, from_ = 1, to = 1000, increment = 1, font = entryFont, width = 30)
receiptEntry = ttk.Entry(actionFrame, font = entryFont, width = 30)
firstNameLabel = ttk.Label(actionFrame, style = "Input.TLabel", image = firstNameIcon, compound = "left")
lastNameLabel = ttk.Label(actionFrame, style = "Input.TLabel", image = lastNameIcon, compound = "left")
rentedItemLabel = ttk.Label(actionFrame, style = "Input.TLabel", image = itemIcon, compound = "left")
numberItemsLabel = ttk.Label(actionFrame, style = "Input.TLabel", image = numberItemsIcon, compound = "left")
receiptLabel = ttk.Label(actionFrame, style = "Input.TLabel", image = receiptIcon, compound = "left")
actionButton = ttk.Button(mainFrame, style = "Main.TButton", image = actionIcon, compound = "right")
# Define literally all the widgets I use here, give them values (these ones are constant and never change)

mainFrame.grid(row = 1, column = 1, sticky = "news")
secondaryFrame.grid(row = 2, columnspan = 1, sticky = "news")
actionFrame.grid(row = 3, columnspan = 1, sticky = "news")
titleLabel.grid(row = 0, column = 0, columnspan = 1)
titleImage1.grid(row = 1, column = 0, sticky = "ne")
titleImage2.grid(row = 1, column = 2, sticky = "nw")
secondaryLabel.grid(row = 0, columnspan = 1)
quitButton.grid(row = 0, column = 2, sticky = "ne")
createButton.grid(row = 1, column = 0)
listButton.grid(row = 2, column = 0)
deleteButton.grid(row = 3, column = 0)
editButton.grid(row = 4, column = 0)
# This chunk uses the grid manager to create the main menu, and it positions the elements needed to form the main menu
# It also makes the widets become visible to the user

firstNameLabel.grid(row = 0, column = 0, sticky = "sew")
firstNameEntry.grid(row = 1, column = 0, sticky = "new")
lastNameLabel.grid(row = 2, column = 0, sticky = "sew")
lastNameEntry.grid(row = 3, column = 0, sticky = "new")
rentedItemLabel.grid(row = 4, column = 0, sticky = "sew")
rentedItemEntry.grid(row = 5, column = 0, sticky = "new")
numberItemsLabel.grid(row = 6, column = 0, sticky = "sew")
numberItemsEntry.grid(row = 7, column = 0, sticky = "new")
receiptLabel.grid(row = 8, column = 0, sticky = "sew")
receiptEntry.grid(row = 9, column = 0, sticky = "new")
actionButton.grid(row = 4, columnspan = 1, sticky = "news")
# This chunk is non-visible widgets that aren't part of the main menu so don't need to be seen instantly
# The grid command gives them coordinates, and it does make them visible

firstNameLabel.grid_remove()
firstNameEntry.grid_remove()
lastNameLabel.grid_remove()
lastNameEntry.grid_remove()
rentedItemLabel.grid_remove()
rentedItemEntry.grid_remove()
numberItemsLabel.grid_remove()
numberItemsEntry.grid_remove()
receiptLabel.grid_remove()
receiptEntry.grid_remove()
actionButton.grid_remove()
# The grid_remove() command removes the above chunk of widgets
# I defined their location early so I wouldn't have to redefine in a random place in the code

root.columnconfigure(0, weight = 1)
root.rowconfigure(0, weight = 1)
mainFrame.columnconfigure(0, weight = 1)
mainFrame.columnconfigure(1, weight = 1)
mainFrame.rowconfigure(0, weight = 1)
mainFrame.rowconfigure(1, weight = 1)
mainFrame.rowconfigure(2, weight = 1)
mainFrame.rowconfigure(3, weight = 1)
mainFrame.rowconfigure(3, weight = 1, pad = 4)
secondaryFrame.columnconfigure(0, weight = 1, pad = 12)
secondaryFrame.columnconfigure(1, weight = 1, pad = 12)
secondaryFrame.rowconfigure(0, weight = 1, pad = 8)
secondaryFrame.rowconfigure(1, weight = 1, pad = 8)
secondaryFrame.rowconfigure(2, weight = 1, pad = 8)
secondaryFrame.rowconfigure(3, weight = 1, pad = 8)
secondaryFrame.rowconfigure(4, weight = 1, pad = 8)
actionFrame.columnconfigure(0, weight = 1, pad = 6)
actionFrame.rowconfigure(0, weight = 1, pad = 7)
actionFrame.rowconfigure(1, weight = 1, pad = 7)
actionFrame.rowconfigure(2, weight = 1, pad = 7)
actionFrame.rowconfigure(3, weight = 1, pad = 7)
actionFrame.rowconfigure(4, weight = 1, pad = 7)
actionFrame.rowconfigure(5, weight = 1, pad = 7)
actionFrame.rowconfigure(6, weight = 1, pad = 7)
actionFrame.rowconfigure(7, weight = 1, pad = 7)
actionFrame.rowconfigure(8, weight = 1, pad = 7)
actionFrame.rowconfigure(9, weight = 1, pad = 7)
# Configure all the rows and columns used, so that there's a little spacing between them and they all have the same scaling importance

def fileAccess(mode, row):
    # This function handles everything related to accessing the files
    # It has it's own seperate function due to the need of having something that runs in order
    #   however tkinter commands execute instantly then return to the infinite loop, so putting
    #   this in the create function (for example) means that this executes instantly instead of on command
    # Mode is the mode to run, it tells the function what to execute
    # Row is dependant on what's calling it, however because of global variables it's not needed much

    global firstName, lastName, rentedItem, numberItems, receiptNumber
    # Pull a few global variables out of nowhere (other functions) for this function

    match mode:
        case "d":
            # If the mode is delete

            confirm = mb.askyesnocancel(title = "Julie's Party Hire Store", message = "Are you sure you want to continue?", detail = "Press No to go back, and Cancel to return to main menu.")
            # Give the user a popup to make sure that they want to proceed

            if confirm == False:
                # If they decide to go back, nothing happens

                return

            elif confirm == True and numberItemsEntry.get() != "" and receiptEntry.get() != "":
                # If they decide to continue, the code below is executed
                # The code also runs a check to make sure that the integers aren't full
                # This check is needed due to placeholder values being set to a noninteger value, which will give errors

                firstName = str(firstName.get()).title().replace(" ","").replace(",","")
                lastName = str(lastName.get()).title().replace(" ","").replace(",","")
                rentedItem = str(rentedItem.get()).title().replace(",","")
                numberItems = int(numberItems.get())
                receiptNumber = int(receiptNumber.get())
                # Get the values from our StringVar and IntVar

                rowNum = float(receiptNumber / len(firstName) / len(lastName) / len(rentedItem) / numberItems / ord(firstName[0]) / ord(lastName[0]))
                # Receipt numbers are generated using a multiplication operation, using the inverse process allows us to get the row number
                # Since receipts will get large quickly, there's a low chance of duplicates
                # And even if two entries have the same receipt, they'll always have one different value, since row numbers are unique
                # This means that duplicate receipt numbers are still not an isssue

                if str(int(rowNum)) in firstRow and rowNum.is_integer():
                    # Make sure the row number is in the list of rows
                    # Make sure that the division is a valid integer
                    # If it wasn't an integer, that means that some entered data is wrong

                    rowNum = str(int(rowNum))

                    rowFile = open(fr"{genDir}\ROW_FILE.txt","w")
                    firstRow.remove(rowNum)
                    rowNum = ""
                    for i in firstRow:
                        rowNum = rowNum + " " + str(i)
                    rowFile.write(rowNum.strip())
                    rowFile.close()
                    # This block will remove the row number from the list of rows
                    # It doesn't remove the entry, however the entry still won't be printed
                    # The entry is kept so that the dynamic list of items can still use that item

                else:
                    # If the check failed

                    mb.showerror(title = "Julie's Party Hire Store", message = "The data you entered is incorrect. Please double check all your information is accurate.")
                    firstName = StringVar(value = firstName)
                    lastName = StringVar(value = lastName)
                    rentedItem = StringVar(value = rentedItem)
                    numberItems = IntVar(value = numberItems)
                    receiptNumber = IntVar(value = receiptNumber)
                    # Return an error message and replaces the stringvar

                    return

                mb.showinfo(title = "Julie's Party Hire Store", message = "Your delete has been recorded.")
                # Pass a confirmation message to inform the user that everything worked well
            
            firstNameLabel.grid_remove()
            firstNameEntry.grid_remove()
            lastNameLabel.grid_remove()
            lastNameEntry.grid_remove()
            rentedItemLabel.grid_remove()
            rentedItemEntry.grid_remove()
            numberItemsLabel.grid_remove()
            numberItemsEntry.grid_remove()
            receiptLabel.grid_remove()
            receiptEntry.grid_remove()
            actionButton.grid_remove()
            secondaryLabel.configure(text = "Commands to run")
            titleImage1.configure(image = mainIcon)
            titleImage2.configure(image = mainIcon)
            createButton.grid()
            listButton.grid()
            deleteButton.grid()
            editButton.grid()
            # Restore the menu widgets and remove the delete widgets

            return
        case "a":
            # If the mode is create

            confirm = mb.askyesnocancel(title = "Julie's Party Hire Store", message = "Are you sure you want to continue?", detail = "Press No to go back, and Cancel to return to main menu.")
            # Give the user a popup to make sure that they want to proceed

            if confirm == False:
                # If they decide to go back, nothing happens

                return

            elif confirm == True and numberItemsEntry.get() != "":
                # If they decide to continue, the code below is executed
                # The code also runs a check to make sure that the integers aren't full
                # This check is needed due to placeholder values being set to a noninteger value, which will give errors

                firstName = str(firstName.get()).title().replace(" ","").replace(",","")
                lastName = str(lastName.get()).title().replace(" ","").replace(",","")
                rentedItem = str(rentedItem.get()).title().replace(",","")
                numberItems = int(numberItems.get())
                # Get the values from our StringVar and IntVar

                receiptNumber = int(row) * len(firstName) * len(lastName) * len(rentedItem) * numberItems * ord(firstName[0]) * ord(lastName[0])
                # Get the receipt number from a multiplication operator

                dataFile = open(fr"{genDir}\DATA_FILE.txt",mode)
                localVar = firstName + "," + lastName + "," + rentedItem + "," + str(numberItems) + "," + str(receiptNumber) + "\n"
                dataFile.write(localVar)
                dataFile.close()
            
                rowFile = open(fr"{genDir}\ROW_FILE.txt",mode)
                row = " "+str(int(row) + 1)
                rowFile.write(str(row))
                rowFile.close()
                # Add the data to the data files

                mb.showinfo(title = "Julie's Party Hire Store", message = str("Your entry has been recorded. Receipt: " + str(receiptNumber)))
                # Pass a confirmation message to inform the user that everything worked well
                
            firstNameLabel.grid_remove()
            firstNameEntry.grid_remove()
            lastNameLabel.grid_remove()
            lastNameEntry.grid_remove()
            rentedItemLabel.grid_remove()
            rentedItemEntry.grid_remove()
            numberItemsLabel.grid_remove()
            numberItemsEntry.grid_remove()
            actionButton.grid_remove()
            secondaryLabel.configure(text = "Commands to run")
            titleImage1.configure(image = mainIcon)
            titleImage2.configure(image = mainIcon)
            createButton.grid()
            listButton.grid()
            deleteButton.grid()
            editButton.grid()
            # Restore the menu widgets and remove the delete widgets

            return

        case "r":
            # If the mode is list

            message = "List of Hired Items:\n\n"
            # Start with a variable to display the whole list of items

            dataFile = open(fr"{genDir}\DATA_FILE.txt",mode)

            i = 0
            # ITERATOR VARIABLE!!!!!

            for x in range(int(row[-1])):
                # This will pull every value in the list of current row hires

                dataPrint = dataFile.readline().split(",")
                # Split the row into each component

                if str(x) not in row:
                    continue
                # Check that the current row being read is in the valid list

                i += 1
                # I love my iterator

                message = message + "Hire " + str(i) + "\t|\tFull Name: " + dataPrint[0] + " " + dataPrint[1] + "\n"
                message = message + "\t|\tItems Rented: " + dataPrint[3] + " " + dataPrint[2] + "\n"
                message = message + "\t|\tReceipt: " + dataPrint[4] + "\n"
                # Add the current row to my variable list to print

            mb.showinfo(title = "Julie's Party Store", message = message)
            # Print the final list

            dataFile.close()
            return

        case "w":
            # If the mode is edit

            confirm = mb.askyesnocancel(title = "Julie's Party Hire Store", message = "Are you sure you want to continue?", detail = "Press No to go back, and Cancel to return to main menu.")
            # Check if the user wants to continue

            if confirm == False:
                # If they don't want to continue, go back to previous interface

                return

            elif confirm == True and numberItemsEntry.get() != "":
                # If the user continued and there aren't any blank integers

                firstName = str(firstName.get()).title().replace(" ","").replace(",","")
                lastName = str(lastName.get()).title().replace(" ","").replace(",","")
                rentedItem = str(rentedItem.get()).title().replace(",","")
                numberItems = int(numberItems.get())
                # Get the values from the StringVar and IntVar variables

                receiptNumber = int(row) * len(firstName) * len(lastName) * len(rentedItem) * numberItems * ord(firstName[0]) * ord(lastName[0])
                # Generate the new receipt number

                dataString = ""
                dataFile = open(fr"{genDir}\DATA_FILE.txt","r")
                dataArray = dataFile.read()
                dataArray = re.split("\n", dataArray)
                dataArray[int(row)] = firstName + "," + lastName + "," + rentedItem + "," + str(numberItems) + "," + str(receiptNumber)
                dataFile.close()
                for x in dataArray:
                    dataString = dataString + x + "\n"
                    # Loop through the array and add newlines to them
                dataFile = open(fr"{genDir}\DATA_FILE.txt",mode)
                dataFile.write(dataString)
                dataFile.close()
                # Paste new value to text file

                mb.showinfo(title = "Julie's Party Hire Store", message = str("Your edit has been recorded. Receipt: " + str(receiptNumber)))
                # Let the user know eveything went fine
            
            firstNameLabel.grid_remove()
            firstNameEntry.grid_remove()
            lastNameLabel.grid_remove()
            lastNameEntry.grid_remove()
            rentedItemLabel.grid_remove()
            rentedItemEntry.grid_remove()
            numberItemsLabel.grid_remove()
            numberItemsEntry.grid_remove()
            actionButton.grid_remove()
            secondaryLabel.configure(text = "Commands to run")
            titleImage1.configure(image = mainIcon)
            titleImage2.configure(image = mainIcon)
            createButton.grid()
            listButton.grid()
            deleteButton.grid()
            editButton.grid()
            # Delete widgets and restore menu

            return

def checkNum(val):
    # Function to check if a value is an integer or not

    return re.match(r"^[0-9]*$", val) is not None
    # This returns false if the value is not a number

checkNumWrapper = (root.register(checkNum), "%P")

def checkStr(val):
    # Function to check if a value is a string or space

    return re.match(r"^([A-z]|\s)*$", val) is not None
    # This returns false if the value is not a space and not a letter

checkStrWrapper = (root.register(checkStr), "%P")

def checkSpin(val):
    # This checks if a value is an integer and if it's less than 1001

    if re.match(r"^[0-9]*$", val) is not None and val != "":
        return int(val) <= 1000
    elif val == "":
        return True
    return False
    # This returns false if the value is not a number or it's greater than 1000

checkSpinWrapper = (root.register(checkSpin), "%P")
# Group of functions to return true or false depending on a set criteria
# Used for data validation every time something has been typed in an entry

def createItem():
    # Function to run when creating an item

    global firstRow, firstName, lastName, rentedItem, numberItems, receiptNumber, itemsList

    firstName = StringVar()
    lastName = StringVar()
    rentedItem = StringVar()
    numberItems = IntVar(value = "")
    # Define some StringVar and IntVars, asign the Integer Vars a default value so we don't have a random default 0

    createFunc = partial(fileAccess, "a", firstRow[-1])
    # The partial (function) created to pass values through buttons
    # The partial is assigned a variable called createFunc
    # The partial leads to the file access function
    
    secondaryLabel.configure(text = "Item Rental | Logging a Hired Item")
    titleImage1.configure(image = createIcon)
    titleImage2.configure(image = createIcon)
    createButton.grid_remove()
    listButton.grid_remove()
    deleteButton.grid_remove()
    editButton.grid_remove()
    firstNameEntry.configure(textvariable = firstName, validate = "key", validatecommand = checkStrWrapper)
    lastNameEntry.configure(textvariable = lastName, validate = "key", validatecommand = checkStrWrapper)
    rentedItemEntry.configure(values = itemsList, validate = "all", textvariable = rentedItem, validatecommand = checkStrWrapper)
    numberItemsEntry.configure(textvariable = numberItems, validate = "all", validatecommand = checkSpinWrapper)
    firstNameLabel.configure(text = "Customer's First name:")
    lastNameLabel.configure(text = "Customer's Last name:")
    rentedItemLabel.configure(text = "Item that has been hired:")
    numberItemsLabel.configure(text = "How many items have been hired:")
    actionButton.configure(text = "Confirm Changes", command = createFunc)
    # Configure everything to have the right settings and remove the menu layout

    firstNameLabel.grid()
    firstNameEntry.grid()
    lastNameLabel.grid()
    lastNameEntry.grid()
    rentedItemLabel.grid()
    rentedItemEntry.grid()
    numberItemsLabel.grid()
    numberItemsEntry.grid()
    actionButton.grid()
    # Display the create layout

    return

def listItems():
    # This function lists all currently rented items

    global firstRow

    fileAccess("r",firstRow)
    # It then runs the file access function with the correct valus

    return

def deleteItem():
    # This function is for deleting items

    global firstRow, firstName, lastName, rentedItem, numberItems, receiptNumber

    firstName = StringVar()
    lastName = StringVar()
    rentedItem = StringVar()
    numberItems = IntVar(value = "")
    receiptNumber = IntVar(value = "")
    # Create StringVars and IntVars and assign placeholder values
    # The placeholder values also have some importance in error checking - the code can check if an empty value is present or not

    delFunc = partial(fileAccess, "d", "0")
    # Create the partials leading to the file access function, assign it as delFunc
    
    secondaryLabel.configure(text = "Item Rental | Logging a Returned Item")
    titleImage1.configure(image = deleteIcon)
    titleImage2.configure(image = deleteIcon)
    createButton.grid_remove()
    listButton.grid_remove()
    deleteButton.grid_remove()
    editButton.grid_remove()
    firstNameEntry.configure(textvariable = firstName, validate = "key", validatecommand = checkStrWrapper)
    lastNameEntry.configure(textvariable = lastName, validate = "key", validatecommand = checkStrWrapper)
    rentedItemEntry.configure(values = itemsList, textvariable = rentedItem, validate = "all", validatecommand = checkStrWrapper)
    numberItemsEntry.configure(textvariable = numberItems, validate = "all", validatecommand = checkSpinWrapper)
    receiptEntry.configure(textvariable = receiptNumber, validate = "key", validatecommand = checkNumWrapper)
    firstNameLabel.configure(text = "Customer's First name:")
    lastNameLabel.configure(text = "Customer's Last name:")
    rentedItemLabel.configure(text = "Item that has been returned:")
    numberItemsLabel.configure(text = "How many items have been returned:")
    receiptLabel.configure(text = "The receipt number of the transaction:")
    actionButton.configure(text = "Confirm Changes", command = delFunc)
    # Configure all my tkinter widgets and remove the current main menu

    firstNameLabel.grid()
    firstNameEntry.grid()
    lastNameLabel.grid()
    lastNameEntry.grid()
    rentedItemLabel.grid()
    rentedItemEntry.grid()
    numberItemsLabel.grid()
    numberItemsEntry.grid()
    receiptLabel.grid()
    receiptEntry.grid()
    actionButton.grid()
    # Show all the delete menu widgets
    # All of their grid locations are saved from when they were defined initially

    return

def editItemCont():
    # This is the function to run when the user is inputting new edit values

    global firstRow, firstName, lastName, rentedItem, numberItems, receiptNumber
    # firstRow is the array that holds the row numbers of current hires
    # firstName, lastName, rentedItem, numberItems, receiptNumber are all the StringVar / IntVar variables
    # These get linked to the entry fields, so when an edit is made these get updated

    confirm = mb.askyesnocancel(title = "Julie's Party Hire Store", message = "Are you sure you want to continue?", detail = "Press No to go back, and Cancel to return to main menu.")
    # Ask the user if they want to continue

    if confirm == False:
        # If no, return to previous menu

        return

    elif confirm == True and numberItemsEntry.get() != "" and receiptEntry.get() != "":
        # If yes and both IntVars aren't strings (otherwise error), run this code

        firstName = str(firstName.get()).title().replace(" ","").replace(",","")
        lastName = str(lastName.get()).title().replace(" ","").replace(",","")
        rentedItem = str(rentedItem.get()).title().replace(",","")
        numberItems = int(numberItems.get())
        receiptNumber = int(receiptNumber.get())
        # Get the values from the String and IntVars, format them properly

        if len(firstName) != 0 and len(lastName) != 0 and len(rentedItem) != 0 and numberItems != 0:
            # Error protection to make sure we don't get a divide by zero error

            rowNum = float(receiptNumber / len(firstName) / len(lastName) / len(rentedItem) / numberItems / ord(firstName[0]) / ord(lastName[0]))
            # Use the division operator do to validation with row number

        else:
            # We have an empty field somewhere - length is - and not possible

            rowNum = 0.5
            # Set rowNum to 0.5 as an error - it'll fail the next error check
    
        if str(int(rowNum)) in firstRow and rowNum.is_integer():
            # Check that the row number is valid AND we have a full integer

            editFunc = partial(fileAccess, "w", rowNum)
            # Create the partial to run to fileAccess
        
            firstName = StringVar()
            lastName = StringVar()
            rentedItem = StringVar()
            numberItems = IntVar(value = "")
            # New StringVars and IntVars

            titleImage1.configure(image = editIcon2)
            titleImage2.configure(image = editIcon2)
            firstNameEntry.configure(textvariable = firstName, validate = "key", validatecommand = checkStrWrapper)
            lastNameEntry.configure(textvariable = lastName, validate = "key", validatecommand = checkStrWrapper)
            rentedItemEntry.configure(values = itemsList, textvariable = rentedItem, validate = "all", validatecommand = checkStrWrapper)
            numberItemsEntry.configure(textvariable = numberItems, validate = "all", validatecommand = checkSpinWrapper)
            firstNameLabel.configure(text = "Customer's new First name:")
            lastNameLabel.configure(text = "Customer's new Last name:")
            rentedItemLabel.configure(text = "The new item that was hired:")
            numberItemsLabel.configure(text = "The new amount of items hired:")
            actionButton.configure(text = "Confrm Changes", command = editFunc)
            receiptLabel.grid_remove()
            receiptEntry.grid_remove()
            # Update the texts to show the new edit fields
            # Receipt isn't needed here so it's removed

        else:
            # If the non-integer or not valid number error happened

            mb.showerror(title = "Julie's Party Hire Store", message = "The data you entered is incorrect. Please double check all your information is accurate.")
            firstName = StringVar(value = firstName)
            lastName = StringVar(value = lastName)
            rentedItem = StringVar(value = rentedItem)
            numberItems = IntVar(value = numberItems)
            receiptNumber = IntVar(value = receiptNumber)
            # Return an error message and replaces the stringvar
            
    else:
        # If they cancelled, send to main menu
        firstNameLabel.grid_remove()
        firstNameEntry.grid_remove()
        lastNameLabel.grid_remove()
        lastNameEntry.grid_remove()
        rentedItemLabel.grid_remove()
        rentedItemEntry.grid_remove()
        numberItemsLabel.grid_remove()
        numberItemsEntry.grid_remove()
        receiptLabel.grid_remove()
        receiptEntry.grid_remove()
        actionButton.grid_remove()
        secondaryLabel.configure(text = "Commands to run")
        titleImage1.configure(image = mainIcon)
        titleImage2.configure(image = mainIcon)
        createButton.grid()
        listButton.grid()
        deleteButton.grid()
        editButton.grid()

    return

def editItem():
    # The function to run when editing an item
    # This one gets the entry that the user might want to edit

    global firstRow, firstName, lastName, rentedItem, numberItems, receiptNumber

    firstName = StringVar()
    lastName = StringVar()
    rentedItem = StringVar()
    numberItems = IntVar(value = "")
    receiptNumber = IntVar(value = "")
    # Same process as above
    
    secondaryLabel.configure(text = "Item Rental | Editing a hired Item")
    titleImage1.configure(image = editIcon1)
    titleImage2.configure(image = editIcon1)
    createButton.grid_remove()
    listButton.grid_remove()
    deleteButton.grid_remove()
    editButton.grid_remove()
    firstNameEntry.configure(textvariable = firstName, validate = "key", validatecommand = checkStrWrapper)
    lastNameEntry.configure(textvariable = lastName, validate = "key", validatecommand = checkStrWrapper)
    rentedItemEntry.configure(values = itemsList, textvariable = rentedItem, validate = "all", validatecommand = checkStrWrapper)
    numberItemsEntry.configure(textvariable = numberItems, validate = "all", validatecommand = checkSpinWrapper)
    receiptEntry.configure(textvariable = receiptNumber, validate = "key", validatecommand = checkNumWrapper)
    firstNameLabel.configure(text = "Customer's First name:")
    lastNameLabel.configure(text = "Customer's Last name:")
    rentedItemLabel.configure(text = "Item that was hired:")
    numberItemsLabel.configure(text = "The amount of items hired:")
    receiptLabel.configure(text = "The receipt number of the transaction:")
    actionButton.configure(text = "Continue", command = editItemCont)
    # Same process as above
    # There is no partial needed since it'll just run editItemCont, which holds the error validation
    # This is the same as fileAccess handling most of the error validation for other functions

    firstNameLabel.grid()
    firstNameEntry.grid()
    lastNameLabel.grid()
    lastNameEntry.grid()
    rentedItemLabel.grid()
    rentedItemEntry.grid()
    numberItemsLabel.grid()
    numberItemsEntry.grid()
    receiptLabel.grid()
    receiptEntry.grid()
    actionButton.grid()
    # Show all the fields

    return

def quitProgram():
    # Function to end the program

    if mb.askyesno(title = "Julie's Party Hire Store", message = "Are you sure you want to quit?") == True:
        # Give them a popup asking them to confirm
        # If they click yes, run code below

        root.destroy()
        os._exit(os.EX_OK)
        # root.destroy() will kill the main window and everything inside it
        # os._exit(os.EX_OK) will kill the program, since it runs on an infinite loop and needs a way to exit

    return
    # If the program didn't die, return

def main():
    # The main function - initial execution is here and so is the infinite loop

    global firstRow, itemsList
    # Global variables to avoid passing through partials as much as possible

    titleLabel.configure(text = "Julie's Hire Database")
    secondaryLabel.configure(text = "Commands to run")
    quitButton.configure(text = "Quit", command = quitProgram)
    createButton.configure(text = "Log a rented item", command = createItem)
    listButton.configure(text = "Show all currently rented items", command = listItems)
    deleteButton.configure(text = "Log a returned item", command = deleteItem)
    editButton.configure(text = "Edit a rented item log", command = editItem)
    # Initial configuration of widgets
    
    if os.path.exists(fr"{genDir}\ROW_FILE.txt") == False:
        # This checks if the ROW_FILE file exists
        # The file is used to store all the valid rows - row numbers will be deleted from here

        rowFile = open(fr"{genDir}\ROW_FILE.txt", "a")
        rowFile.write("1")
        rowFile.close()
        # Write "1" as an initial value - this shows the next free spot to edit in

    if os.path.exists(fr"{genDir}\DATA_FILE.txt") == False:
        # This checks if the DATA_FILE file exists
        # The file is used to store every single entry - values here are never deleted, only added and edited

        dataFile = open(fr"{genDir}\DATA_FILE.txt", "a")
        dataFile.write("FIRST NAME,LAST NAME,HIRED ITEM,NUM HIRES,RECEIPT\n")
        dataFile.close()
        # Write header files as initial values - These are never read but they're there to avoid
        #   division by zero errors due to 0 based indexing

    while True:
        # This code replaces root.mainloop()
        # root.mainloop() functions as an infinite loop and is an inbuilt function
        # I don't use it because I have my own dynamic things I want updated - and
        #   I can't access the underlying code in the mainloop() function

        rowFile = open(fr"{genDir}\ROW_FILE.txt","r")
        firstRow = rowFile.readline().split()
        rowFile.close()
        # This will make sure the row numbers are always updated

        dataFile = open(fr"{genDir}\DATA_FILE.txt", "r")
        tempArray = dataFile.read().replace("\n",",").strip(",").split(",")
        dataFile.close()
        # This will pull the values from the data and put everything into an array
        
        itemsList = ["placeholder"]
        itemsList.clear()
        # Define the itemsList array and clear it - the data type will be an array now
        
        for i in range(len(tempArray)):
            # Loop through everythign in tempArray
            # This will be the laggiest component to the program

            if i % 5 == 2 and i > 5:
                # If it is a valid item (Column 3, use modulus operator to find this)

                itemsList.append(tempArray[i])
                # Add this to the itemsList array

        itemsList = list(dict.fromkeys(itemsList))
        # This does a little conversion magic to bypass some errors I was having
        
        root.update_idletasks()
        root.update()
        # The two functions to make up the mainloop() purpose - they'll update the tkinter
        #   widgets automatically

if __name__ == "__main__":
    # Check that the start of execution was this file and not another file
    # Best practice purposes - not entirely valid here but good to have anyway

    main()
    # Run the main function