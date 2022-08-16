#This is a mini calculator
from time import sleep
def my_addition(a,b):
    x = a + b
    print("\t =", x)
    print()
def my_subtraction(a,b):
    x = a - b
    print("\t =", x)
    print()
def my_multiplication(a,b):
    x = a*b
    print("\t =", x)
    print()
def my_division(a,b):
    x = a/b
    print("\t =", x)
    print()
def my_quadratic(a,b,c):
    x = (-b + (b**2 - 4*a*c)**(1/2))/(2*a)
    y = (-b - (b**2 - 4*a*c)**(1/2))/(2*a)
    print("\t x =", x)
    print()
    print("\t x =", y)
    print()
def my_roots(a,b):
    x = a**(1/b)
    print("\t =", x)
    print()
def my_power(a,b):
    x = a**b
    print("\t =", x)
    print()

print()
print("\t What type of calculation would you like to use?")
print()
print("\t This calculator supports addition, subtraction, multiplication, division, quadratic expression, finding roots, and finding power of a number.")
sleep(1)
print()
print()
player = False
while player == False:
    user = input("\t Enter your choice for calculation here: ")
    sleep(1)
    print()
    print()
    if user == "add" or user == "addition" or user == "plus" or user == "+" or user == "a":
        a = float(input("\t Enter your first number: "))
        print()
        b = float(input("\t Enter your second number: "))
        sleep(2)
        print()
        my_addition(a,b)
    elif user == "minus" or user == "subtraction" or user == "subtract" or user == "-" or user == "s":
        a = float(input("\t Enter your first number: "))
        print()
        b = float(input("\t Enter your second number: "))
        sleep(2)
        print()
        my_subtraction(a,b)
    elif user == "time" or user == "multiplication" or user == "multiple" or user == "*" or user == "m":
        a = float(input("\t Enter your first number: "))
        print()
        b = float(input("\t Enter your second number: "))
        sleep(2)
        print()
        my_multiplication(a,b)
    elif user == "divid" or user == "division" or user == "/" or user == "d":
        a = float(input("\t Enter your first number (numerator): "))
        print()
        b = float(input("\t Enter your second number (denominator): "))
        sleep(2)
        print()
        my_division(a,b)
    elif user == "quadratic equation" or user == "quadratic" or user == "q":
        print("\t Use the following form: ax**2 + bx + c = 0.")
        print()
        a = float(input("\t Enter value for 'a': "))
        print()
        b = float(input("\t Enter value for 'b': "))
        print()
        c = float(input("\t Enter value for 'c': "))
        sleep(2)
        print()
        my_quadratic(a,b,c)
    elif user == "root" or user == "roots" or user == "r":
        print("\t Use the following form: x**(1/y) = y roots of x")
        print()
        a = float(input("\t Enter value for x: "))
        print()
        b = float(input("\t Enter value for y: "))
        sleep(2)
        print()
        my_roots(a,b)
    elif user == "power" or user == "powers" or user == "p":
        print("\t Use the following form: x**y (x to the power of y)")
        print()
        a = float(input("\t Enter value for x: "))
        print()
        b = float(input("\t Enter value for y: "))
        sleep(2)
        print()
        my_power(a,b)
    else:
        print("\t Your answer is invalid.")
    print()
    sleep(1)
    print("\t Do you want to use the program again?")
    sleep(1)
    print()
    playerTwo = input("\t Your answer: ")
    if playerTwo == "y" or playerTwo == "yes":
        player = False
        print()
    elif playerTwo == "n" or playerTwo == "no":
        player = True
print("\t Bye.")
sleep(2)