# The main execution function
def main():

    # Define the clubCriteriaDict
    # This dictionary will store the fail/pass reasons, such as if they fail for age or not
    # Uses Boolean (bool) variable types with String (str) keys, True is pass, False is fail
    clubCriteriaDict = {"age":False, "income":False, "experience":False}
    # Initialise the userName variable to start
    # This gives it a value to make sure the user doesn't press enter for their name
    # Uses a String (str) variable type
    userName = " "
    # Define the membershipEligible variable
    # This variable will be the variable that stores if the user passes or fails
    # While the dictionary stores the fail reasons and each key is False by default,
    # This variable is True by default and the moment a fail criteria is reached it becomes False
    # Uses a Boolean (bool) variable type, True is pass, False is fail
    membershipEligible = True
    # Define the listOfNumbers variable
    # This is used to ensure that numbers are used instead of letters or vice versa
    # Uses a variable type of Integers (int)
    # Will use a for loop nested in a for loop to execute this
    listOfNumbers = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    # This function will compare the values a user inputs to their limits and will decide if they pass or fail
    # criteria (int) is the value that the user inputted, is either their Age, Income, Experience
    # comparison1 (int) is the upper limit of a comparison, eg userAge has to be more than comparison1
    # comparison2 (int) is the lower limit of a comparison, eg userYearlyIncome has to be less than comparison2
    # The return values will go to the dictionary as a boolean value
    def criteriaDictEntry(criteria, comparison1, comparison2):
        if criteria >= comparison1 and comparison1 != 0:
            return False
        
        elif criteria <= comparison2:
            return False
        
        else:
            return True


    # This function will compare the input and check if it is a number or not
    # numberToCheck is a string and will be compared to make sure that there are no letters in the input
    # The return value is an integer
    def numberChecker(numberToCheck):

        if numberToCheck.count("-") > 1:
            numberToCheck = 999
        elif numberToCheck.count("-") == 1 and (numberToCheck[0] != "-" or len(numberToCheck) == 1):
            numberToCheck = 999
        else:
            for x in numberToCheck:
                for y in listOfNumbers:
                
                    if str(x) == str(y) or str(x) == "-":
                        break

                    elif y == 9:
                        numberToCheck = 999
                        break
                
                if numberToCheck == 999:
                    break
          
        return int(numberToCheck)

        
    # This function will inform the user why their membership was not accepted based on the dictionary values
    # It uses a for loop with the dictionary keys and values, and if a value is false then it uses the key to determine why the user was failed
    # This will loop for all keys in the dictionary
    # This is only called when the user has failed, after all questions have been answered
    def criteriaFailReason():
        print(f"\n\nSorry {userName}, you're not eligible for club membership.")
        print(f"Name: {userName}")
        print(f"Age: {userAge} years")
        print(f"Annual Income: ${userYearlyIncome}")
        print(f"Experience: {userExperience}\n")

        # x represents the key names for the dictionary, y represents the values for each key in the dictionary
        for x, y in clubCriteriaDict.items():
            # Check if the user failed for that key
            if y == False:
                print(f"Your {x} was invalid.")

                # If they failed, then use the key to determine why they failed
                if x == "age":
                    # This if tree determines why the user's age was invalid
                    # Only userAge has the tree like this, since userAge is the only criteria with an upper and lower limit
                    if userAge <= 15:
                        print("\nAt our club, we have a high membership fee due to our prestige. This means you need to be working to join.")
                        print(f"The minimum legal age to get a job is 16, and you are {userAge} years old. Try again when you have a job.")
                        
                    else:
                        print("\nAt our club, we're looking for young, passionate skiiers to join us.")
                        print(f"Our maximum join age is 25, your age ({userAge}) is too high. Sorry!")
                        
                elif x == "income":
                    print("\nOur club has extremely high costs due to the high quality of our equipment.")
                    print(f"Unfortunately, your income of ${userYearlyIncome} can't cover the $40,000 required a year. Come back when you have more money!")

                elif x == "experience":
                    print("\nAt the Snowbloa Extreme Skis Club, we look for experienced skiiers to join us.")
                    print(f"Beginners here must have at least 5 years of experience. You have {userExperience} years. Sorry!")

        
    # Print the welcome text to the user
    print("Welcome to the Snowbloa Extreme Skis Club Membership Survey.")
    print("This survey will determine if you are elibigle to join the club by asking you some questions.")
    
    # Get the user to input their name
    userName = str(input("\nTo start, enter your name. Name: "))

    # Use an infinite loop to allow me to individually check for two criteria in the same loop
    # Allows for less lines of code and faster runtime
    while True:
        # Use a loop to get the characters in the user's name
        for x in userName:
            # Use a loop to get the numbers in the number list
            for y in listOfNumbers:
                # If a character in the user's name is a number, set their name to an error code
                if str(x) == str(y) or (str(x).isalpha() == False and str(x) != "-" and str(x) != "'"):
                    userName = "00"
                    break
            # Breaks out of loop because error code
            if userName == "00":
                break;
        # Gives user the error, then prompts them to re-enter their name
        if userName == "00":
            userName = str(input("Please remove the characters that aren't letters from your name. Name: "))
            continue
        # Second condition
        elif userName.strip() == "":
            # If the user enters whitespace (enter, tab, space, ect) the .strip() function deals with it
            # Then it gives a message prompting the user to enter a valid name
            userName = str(input("Please enter a proper name instead of whitespaces. Name: "))
            continue
        # If user's name passed all conditionals
        else:
            break
    
    # Welcome the user with their name
    print(f"\nWelcome, {userName}!")
    
    # The while True loop is used to allow the code to loop back to age question when required
    while True:
        userAge = str(input("\nNow enter your age. Age: "))
        # Use an infinite loop to allow me to individually check for two criteria in the same loop
        # Allows for less lines of code and faster runtime
        while True:
            if userAge.strip() == "":
            # If the user enters whitespace (enter, tab, space, ect) the .strip() function deals with it
            # Then it gives a message prompting the user to enter a valid age
                userAge = str(input("Please enter a valid age instead of whitespaces. Age: "))
                continue
            # Calls function
            userAge = numberChecker(userAge)
            # If name is error prompt user to enter age again
            if userAge == 999:
                userAge = str(input("Make sure your age contains only numbers. Age: "))
                continue
            # If the age is below 1 or above 109 then it prompts the user to enter a valid age
            elif userAge <= 0 or 110 <= userAge:
                userAge = str(input("Your age should be an integer between 0 and 110. Age: "))
                continue
            # If user's age passed all conditionals
            else:
                break
    
        # This line calls the criteriaDictEntry function and assigns the return value (True/False) to the dict
        # The value being assigned to has the key of "age"
        # The criteria value is the user's age
        # The 25 is the upper limit of age (has to be below 25)
        # The 15 is the lower limit of age (has to be above 15)
        clubCriteriaDict["age"] = criteriaDictEntry(userAge, 25, 15)
        
        userYearlyIncome = str(input("\nPlease enter your annual (yearly) income. Income: $"))
        # Use an infinite loop to allow me to individually check for two criteria in the same loop
        # Allows for less lines of code and faster runtime
        while True:
            if userYearlyIncome.strip() == "":
            # If the user enters whitespace (enter, tab, space, ect) the .strip() function deals with it
            # Then it gives a message prompting the user to enter a valid income
                userYearlyIncome = str(input("Please enter a valid income instead of whitespaces. Income: $"))
                continue
            # Calls function
            userYearlyIncome = numberChecker(userYearlyIncome)
            # If the income is less than 0 it prompts the user to enter again (because negative income is not income, it's debt)
            if userYearlyIncome < 0:
                userYearlyIncome = str(input("Negative incomes are called debt. If you're in debt, enter in 0 as your yearly income. Income: $"))
                continue
            # If name is error prompt user to enter income again
            elif userYearlyIncome == 999:
                userYearlyIncome = str(input("Make sure your income contains only numbers. Income: $"))
                continue
            # If user's income passed all conditionals
            else:
                break
        
        # This line is the same as the clubCriteriaDict["age"] line
        # 0 tells the code to skip the criteria
        # 40000 is the lower limit of income (has to be above 40000)
        clubCriteriaDict["income"] = criteriaDictEntry(userYearlyIncome, 0, 40000)
        
        userExperience = str(input("\nHow many years of experience do you have of skiing? Experience: "))
        # Use an infinite loop to allow me to individually check for two criteria in the same loop
        # Allows for less lines of code and faster runtime
        while True:
            if userExperience.strip() == "":
            # If the user enters whitespace (enter, tab, space, ect) the .strip() function deals with it
            # Then it gives a message prompting the user to enter a valid experience
                userExperience = str(input("Please enter a valid age instead of whitespaces. Experience: "))
                continue
            # Calls function
            userExperience = numberChecker(userExperience)
            # If experience is less than 0, prompt user to enter valid number above 0
            if userExperience < 0:
                userExperience = str(input("Please make sure you enter a positive amount of years. Experience: "))
                continue
            # If name is error prompt user to enter experience again
            elif userExperience == 999:
                userExperience = str(input("Make sure your experience contains only numbers. Experience: "))
                continue
            # If user's experience passed all conditionals
            else:
                break
        
        # If age is less or equal to experience then jump back to the age question using the while loop
        if userAge <= userExperience:
            print("Your age cannot be less than your experience. Enter your age again.")
            continue
    
        # Same as the other function calling lines
        # 4 means experience has to be 5 or above
        clubCriteriaDict["experience"] = criteriaDictEntry(userExperience, 0, 4)
        break
    
    # Check that there are no dictionary values that are false
    for x in clubCriteriaDict.values():
        if x == False:
            # If a dictionary value is false, then the Boolean variable gets set to false
            membershipEligible = False
            break
    
    
    # If the user passed, then they are welcomed with this statement
    if membershipEligible == True:
        print(f"\n\nWelcome to the Snowbloa Extreme Skis Club, {userName}!")
        print("Confirmation Statement:")
        print(f"Name: {userName}")
        print(f"Age: {userAge} years")
        print(f"Annual Income: ${userYearlyIncome}")
        print(f"Experience: {userExperience}")
    
    # If user didn't pass, they get looped through the fail reason function  
    else:
        criteriaFailReason()
    return userName


# Loop to call forever
while True:
    userName = main()
    # Will wait until enter is pressed, prevents program from closing instantly when ran through the .py or .exe file
    # After feedback allow user to redo survey if wanted
    confirm = input("\nPress any key to close the survey. To redo the survey, type \"redo\".\nOption: ")
    if confirm.lower().strip() != "redo":
        print("\n")
        break
    else:
        continue

# Farewell user
print(f"Farewell, {userName}!")
