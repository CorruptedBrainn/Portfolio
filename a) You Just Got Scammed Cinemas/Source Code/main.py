from turtle import*
import random

#Space for turtle define if needed

movies = ["Python Is Weird", "Life of Pi: Piscine Molitor", "Finding Doris II", "Minions: The Fall of Bob's Teddy", "Thomas The Useless Engine", "Ready Player 17"] #Lists for the movies and prices
prices = ["C++ Is Better", "12", "20", "13", "19", "8"]
loop = 1 #Loop for the y/n

print ("Welcome to YJGS Cinemas Booking. Please log in using your name.")
name = input ("Please enter your name to continue: ") #Input name
print ("\nWelcome, ", name, "! Your name will be printed on your movie ticket along with your row numbers.\n")

while loop == 1:
    print ("\nRight now we have 5 movies planned for the next 10 days. They are:")
    print (movies[1]) #List movies for customer
    print (movies[2])
    print (movies[3])
    print (movies[4])
    print (movies[5])
    movie_selection = int (input ("\nWhich movie would you like to watch? (Answer between 1 and 5): "))
    while movie_selection < 1 or movie_selection > 5: #Make sure input is between 1 and 5
        print ("Sorry, ", movie_selection, "is not a valid input. Please try again.")
        movie_selection = int (input ("\nWhich movie would you like to watch? (Answer between 1 and 5): "))
    print ("You have chosen to watch", movies[movie_selection], ". The price of tickets for", movies[movie_selection], "is $", prices[movie_selection])
    count = int (input ("How many people are you booking for today? (Max is 20) ")) #Buy amount of tickets
    while count < 1 or count > 20:
        print ("Sorry,", count, "is more than the allowed amount of people per group. The maximum amount of people per group is 20.")
        count = int (input ("How many people are you booking for today? (Max is 20) ")) #Limit max and min on tickets
    total = int (prices[movie_selection]) * count
    discount = total * 0.75
    if count >= 8:
        print ("\nYour total cost is $", total, ", however because you have more than 8 people in your group, you have a 25% off discount!")
        print ("Your price is now $", discount) #Add the 25% discount if more than 7 (More or equal to 8)
        turtle_payment = "$" + str(discount)
    else:
        print ("\nYour total cost is $", total)
        turtle_payment = "$" + str(total) #If discount is illegal
    message = input ("\nWould you like to proceed to checkout? (y/n) If not, you will be redirected to movie selection again. ")
    if "y" in message:
        loop = 2
    else: #Loop if y not in message
        loop = 1

room = random.randint(1,8) #Create the room and row num
row = random.randint(1,30)

print ("Thank you for buying", count, "tickets to", movies[movie_selection], ". Your room will be", room, " and your row(s) will be around row ", row)
print ("Your ticket will be printed soon. Thanks for buying at YouJustGotScammedCinemasBooking.com") #Output code

turtle_room = "Room: " + str(room)
turtle_row = "Row: " + str(row) #Define strings to print
ticket_count = "Tickets Bought: " + str(count)


tck = Turtle() #Define the ticket drawing man
win = Screen() #Define the screen

tck.shape("turtle")

win.screensize(1000, 500)

tck.penup()
tck.setposition(-250, 125)
tck.begin_fill() #All of this is the turtle to print the ticket
tck.pendown()
tck.fillcolor("#C89D7C")

tck.forward(250)
tck.circle(-5, 180)
tck.circle(5, 180)
tck.forward(250)
tck.right(90)
tck.forward(250)
tck.right(90)

tck.forward(250)
tck.circle(-5, 90)
tck.forward(15)
tck.right(270)
tck.forward(245)
tck.right(90)
tck.forward(250)
tck.right(90)

tck.forward(250)
tck.circle(-5, 90)
tck.forward(15)
tck.right(90)
tck.forward(5)
tck.circle(-5, 90)
tck.right(180)
tck.forward(235)

tck.end_fill()
tck.penup()

tck.right(270)
tck.setposition(-125, 95)
tck.write("You Just Got Scammed Cinemas", True, align="center", font=("arial", 12, "normal"))
tck.setposition(20, 75)
tck.write(turtle_room, True, align="left", font=("arial", 11, "normal"))
tck.setposition(20, 60)
tck.write(turtle_row, True, align="left", font=("arial", 11, "normal"))
tck.setposition(235, 60)
tck.write("Movie:", True, align="right", font=("arial", 13, "normal"))
tck.setposition(235, 40)
tck.write(movies[movie_selection], True, align="right", font=("arial", 13, "normal"))
tck.setposition(20, -125)
tck.write(ticket_count, True, align="left", font=("arial", 11, "normal"))
tck.setposition(-125, 70)
tck.write(name, True, align="center", font=("arial", 11, "normal"))
tck.setposition(100, -10)
tck.write("Paid? (YES)", True, align="center", font=("arial", 12, "normal"))
tck.setposition(100, -25)
tck.write(turtle_payment, True, align="center", font=("arial", 12, "normal"))

tck.ht()

cir = Turtle()
cir.penup()
cir.setposition(-175, -10)

cir.shape("arrow")

cir.color("orange")
cir.fillcolor("red")
cir.speed(10)
cir.begin_fill()
cir.pendown()
for i in range (36):
    cir.forward(100)
    cir.left(170)
cir.end_fill()
cir.ht()

input ("\n\nPress enter to exit. Hope you enjoyed getting scammed.")
