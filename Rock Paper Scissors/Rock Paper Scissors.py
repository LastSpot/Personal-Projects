# Game of Rock Paper Scissors.

from random import randint

order = ("Rock","Paper","Scissors")
computer = order[randint(0,2)]

player = False

print("This is a game of Rock Paper Scissors.")

while player == False:

    player = input("Rock, Paper, Scissors: ")

    if player == "stop":
        break    

    elif player != "stop":

        if player == "rock":
            print("Computer chose", computer + "!")
            if computer == "Scissors":
                print("You won!", player, "crushes", computer + ".")
            elif computer == "Rock":
                print("Tie!")
            else:
                print("You lose!", computer, "covers", player + ".")

        elif player == "scissors":
            print("Computer chose", computer + "!")
            if computer == "Paper":
                print("You won!", player, "cuts", computer + ".")
            elif computer == "Scissors":
                print("Tie!")
            else:
                print("You lose!", computer, "crushes", player + ".")

        elif player == "paper":
            print("Computer chose", computer + "!")
            if computer == "Rock":
                print("You won!", player, "covers", computer + ".")
            elif computer == "Paper":
                print("Tie!")
            else:
                print("You lose!", computer, "cuts", player + ".")
        else:
            print("You don't even know how to play Rock Paper Scissors?! Shame on you!")

    player = False
    computer = order[randint(0,2)]