#Welcome banners for online store - to be printed at beginning and end of transaction / program
#Allows me to copy paste different banner messages and also banner does not clog up program
def banner_welcome():
    print("-------------------------------------------")
    print("-------------------------------------------")
    print("||||| Welcome to Jim's Computer Store |||||")
    print("-------------------------------------------")
    print("-------------------------------------------")

def banner_farewell():
    print("----------------------------------------------")
    print("----------------------------------------------")
    print("||||| Farewell from Jim's Computer Store |||||")
    print("----------------------------------------------")
    print("----------------------------------------------")

#Lists to store the computer and price, can have calculations done but mainly for printing purposes
#Note after testing: prices is only used twice (print prices at beginning, check user entered the correct price)
computers = ["Home Basic", "Office Computer", "Gaming Computer", "Studio Computer"]
prices = [900, 1200, 1500, 2200]

#Give the input variables default values to ensure a value is inputted
#These 5 variables are all for input statements
#name is the user's name
#age represents the user's age
#money is their money
#price is the price of the computer the user would like to purchase
#confirm makes sure the inputted information is correct
name = ""
age = 121
money = 50001
price = 0
confirm = ""

#My variable to be used for looping
#Is used in a loop to print a list of computers & prices
#Is also used to get the user's chosen computer for print statements. Done with a loop
i = 0

#Start the interaction
banner_welcome()

print("\n\nHere is a list of computers sold at our store and their prices:\n")

#Prints out the list of computers for the user
#i += 1 replaces i = i + 1
while i < len(computers):
    print("Computer", i + 1, ":", computers[i], "priced at $", prices[i])
    i += 1

#Gives user option to cancel. Makes sure a name does get entered.
name = input("\n\nPlease enter your name to proceed. Else, press enter to cancel.\nName: ")

if name != "":
    print("Welcome to Jim's Computer Store,", name, "!")
    age = int(input("\nPlease enter your age for the program.\nAge: "))
    #Make sure age is between 0 and 120 (0 is not accepted, 120 is accepted but 121 is not). If not loop again.
    
    while age <= 0 or age > 120:
        print("\nPlease ensure you enter your correct age.")
        age = int(input("Age: "))
        
    #The while statement for the confirmation below
    while confirm != "y" and confirm != "Y" and confirm != "yes" and confirm != "Yes":
        print("\nPlease enter the money you have and are willing to spend on the computer.")
        money = int(input("Budget for Computer: $"))
        
        #Make sure that user's money is between 0 and 50,000 including 50,000. If not loop again
        while money <= 0 or money >= 50000:
            print("\nPlease enter a budget value between $0 and $50,000.")
            money = int(input("Budget for Computer: $"))
            
        print("\nAbove is a list of computers sold at our store. Please enter the price of the computer you wish to buy.")
        price = int(input("Price of chosen computer: $"))
        
        #Makes sure that the price entered matches the prices available. If not loop again
        while price != prices[0] and price != prices[1] and price != prices[2] and price != prices[3]:
            print("\nPlease ensure you enter the price of a computer from the list above. Other values are not accepted.")
            price = int(input("Price of chosen Computer: $"))
            
        #i = 0, allows for another loop
        i = 0
        
        #Sets i to the value to make flexible printed statements (eg if price entered was 1200 make i 1)
        while price != prices[i]:
            i += 1
            
        #The confirmation question
        print("\n\nPlease make sure the following is correct.\nYou have $", money, "and are looking to buy the", computers[i], "for $", price, ".")
        confirm = input("\nPlease confirm with (Y/y/Yes/yes) to proceed to the closing statement. If an error was made, enter something else to re-enter info past the budget.\nConfirm (Y/y/Yes/yes): ")

    print("\n")
    
    #This IF tree prints the output
    if money >= price:
        #If the user has the funds to buy the computer they will be printed this
        print("You have the funds to buy the", computers[i], "for $", price, ".\nPlease visit Jim's Computer Store and purchase your computer, or talk to a specialist for more information.")
        print("\n\nClosing Statement:\nName:", name, "\nAge:", age, "\nBudget: $", money, "\nComputer:", computers[i], "for $", prices[i], "\nCan buy: Yes")

    else:
        
        #If not:
        if age >= 18:
            #If they are 18 or above they are offered alternate finance options
            print("You do not have the funds to buy the", computers[i], "for $", price, ".\nPlease visit Jim's Computer Store and talk to a finance specialist about our finance options.")
            print("\n\nClosing Statement:\nName:", name, "\nAge:", age, "\nBudget: $", money, "\nComputer:", computers[i], "for $", prices[i], "\nCan buy: No, visit our store for options.")

        else:
            #Else if they are under 18 they will be told to save until they have the money
            print("You do not have the funds to buy the", computers[i], "for $", price, ".\nAs you are underage our finance options are not available to you.\nKeep saving, and when you have enough money visit our store then.")
            print("\n\nClosing Statement:\nName:", name, "\nAge:", age, "\nBudget: $", money, "\nComputer:", computers[i], "for $", prices[i], "\nCan buy: No, keep saving until you have enough money.")

#If user cancelled (in name statement) they get printed this
else:
    print("Transaction Closed... Farewell from Jim's Computer Store.")
    print("\n\nClosing Statement:\nTransaction Closed by user.")
    
print("\n")

#Print the closing banner
banner_farewell()
