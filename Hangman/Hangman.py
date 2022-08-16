import random
from time import sleep

HANGMAN = (
"""
 ------
 |    |
 |
 |
 |
 |
 |
 |
 |
----------
""",
"""
 ------
 |    |
 |    O
 |
 |
 |
 |
 |
 |
----------
""",
"""
 ------
 |    |
 |    O
 |   -+-
 | 
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-
 |   
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |   
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |    |
 |   | 
 |   | 
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |    |
 |   | |
 |   | |
 |  
----------
""")

wrong = 0
WORDS = ["APPLE","LAPTOP","MR.BEAN","TEDDY","TELEVISION","TIME","ADMIN"]
word = random.choice(WORDS)
maxWrong = len(HANGMAN) - 1
wordUsed = []
progress = ("-") * len(word)
print()
print()
print("Welcome to the game of Hangman.")
print("This is a remake of the classic version of the Hangman.")
print("The rules of a regular Hangman applies here.")
print()
print()
input("Press ENTER to start: ")
print()
print()
print("Before we start, I will be giving out a hint to what the word is.")
print()
print("The hint is: ")

if word == "APPLE":
    hint = ("Which fruit falls on Isaac Newton?")

elif word == "LAPTOP":
    hint = ("What is a macBook?")

elif word == "MR.BEAN":
    hint = ("One of Rowan Atkinson's most famous role. Mainly appealing to kids.")

elif word == "TEDDY":
    hint = ("What does Mr.Bean always have with him?")

elif word == "TELEVISION":
    hint = ("One of the daily object of our modern time. An electronic digital cinema at home.")

elif word == "TIME":
    hint = ("Non stop, irreversible and absolute measurement.")

elif word == "ADMIN":
    hint = ("The highest authority position in a system.")

while wrong < maxWrong and progress != word:
    print()
    print(HANGMAN[wrong])
    print("Your hint:", hint)
    print()
    print("Word so far: ", progress)
    print("Letters used: ", wordUsed)

    player = input("Guess a letter: ").upper()
    sleep(0.5)
    print()

    while player in wordUsed:
        wrong += 1
        print(HANGMAN[wrong])
        print()
        print("You have already tried this letter.")
        print()
        print("Your hint:", hint)
        print()
        print("Word so far: ", progress)
        print("Letters used: ", wordUsed)


        player = input("Guess a letter: ").upper()
        sleep(0.5)
        print()
    
    wordUsed.append(player)

    if player in word:

        new = ""
        
        for x in range(len(word)):
            if player == word[x]:
                new += player

            else:
                new += progress[x]
        progress = new

    else:
        print("Incorrect! That letter is not within the word.")
        wrong += 1

print("Your result... ")
sleep(0.5)
if wrong == maxWrong:
    print("You are out of guesses. Better next time!")

else:
    print("You have guess the word correctly and within the alotted number of guesses!")
    print("The word is", word + ".")

print()
print()
input("Press Enter to exit.")