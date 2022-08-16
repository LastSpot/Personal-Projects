To play the game, compile the following file using gcc: adventure.c, rooms.c, items.c, characters.c
To compile the code: gcc adventure.c rooms.c items.c characters.c
An optional flag to compile the code to name the combined file: -o main

Each of the 9 rooms were individually created with a name. They are then randomly put into each index in an array using a random number generator.
The layout of the building with 9 rooms: 0 | 1 | 2
                                         3 | 4 | 5
                                         6 | 7 | 8
Each room is connected to their top, down, right, and left room.
The rooms are connected through pointers. Each room has a pointer pointing to the north, south, west, and east room. 
If the room does not have a direction, the room in that direction is NULL.
Items are put into their designated rooms at the beginning of the game.
There is a total of 6 items in the game.
Also, besides the player, there are a total of 5 characters

For each of the input, there will be a scanf function to take the input and assign it to a variable. 
If a command has a secondary function, there will be another scanf to take its input.
For example, the take command has a secondary function to take the name of an item. There will be another scanf to take the name of the item and assign it to another variable. The scanf function would scan strings within the user input to look for matched command/target within the game. The game has instruction on how the user should type the input and such. Any other cases would be regard as invalid and prompt the user to retype.

The first user input would be their name to set as their avatar's name.
After that, the game would require commands as the user input.
As explained above, some commands require further user input.
If any commands or input is regard as invalid within the game, the user would have to retype the input.