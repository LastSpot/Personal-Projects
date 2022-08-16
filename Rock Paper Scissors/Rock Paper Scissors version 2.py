# Game of Rock Paper Scissors version 2. The improved version compared to the first one.

from random import randint

order = ("Rock","Paper","Scissors")
computer = order[randint(0,2)]

player = False
# Put as False by default so that when an input is given, it turns to True.

print("This is a game of Rock Paper Scissors. To make it easier, for I am such an awesome person, I have simiplified the typing for rock, paper, and scissors to r (rock), p (paper), and s (scissors).")

while player == False:

    player = input("Rock, Paper, Scissors: ")
    # The input.

    if player == "stop":
        break    
    elif player != "stop":
    
        if player == "Rock" or player == "r":
            print("Computer chose", computer + "!")
            if computer == "Scissors":
                print("You won! Rock crushes", computer + ".")
            elif computer == "Rock":
                print("Tie!")
            else:
                print("You lose!", computer, "covers Rock.")

        elif player == "Scissors" or player == "s":
            print("Computer chose", computer + "!")
            if computer == "Paper":
                print("You won! Scissors cuts", computer + ".")
            elif computer == "Scissors":
                print("Tie!")
            else:
                print("You lose!", computer, "crushes Scissors.")

        elif player == "Paper" or player == "p":
            print("Computer chose", computer + "!")
            if computer == "Rock":
                print("You won! Paper covers", computer + ".")
            elif computer == "Paper":
                print("Tie!")
            else:
                print("You lose!", computer, "cuts Paper.")
        else:
            print("You don't even know how to play Rock Paper Scissors?! Shame on you!")

    player = False
    # So that when the conditional statements have passed, it will repeat the loop.

    computer = order[randint(0,2)]
    # To randomize the word that will come out again to have different results.