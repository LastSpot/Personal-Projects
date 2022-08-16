#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"
#include "characters.h"

// Start of the game
int start() {
    printf("\n\n------------------------------------------------------\n");
    printf("Welcome to Clue! A text adventure game!\n");
    printf("------------------------------------------------------\n");
    printf("Use command 'help' to display all available commands\n");
    printf("\n");
    printf("\n");
    return 0;
}

// Help command
int help() {
    printf("\n");
    printf("------------------------------------------------------\n");
    printf("List of commands:\n");
    printf("\n");
    printf("\thelp: display all commands and the list of directions\n");
    printf("\tlist: lookup the list of items, rooms, and characters\n");
    printf("\tgo: move to another room using directions (north/south/west/east)\n");
    printf("\tlook: see rooms in each direction and see objects/characters in the room\n");
    printf("\ttake: pick up items\n");
    printf("\tdrop: drop items\n");
    printf("\tinventory: check items in  the avatar's inventory\n");
    printf("\tclue: make a guess\n");
    printf("\n");
    printf("List of directions:\n");
    printf("\n");
    printf("\tnorth: move to the north room (if applicable)\n");
    printf("\tsouth: move to the north room (if applicable)\n");
    printf("\twest: move to the north room (if applicable)\n");
    printf("\teast: move to the north room (if applicable)\n");
    printf("------------------------------------------------------\n");
    printf("\n");
    return 0;
}

int main() {

    // Initializing the 9 rooms
    struct Room* kitchen = createRoom("Kitchen");
    struct Room* livingRoom = createRoom("Living room");
    struct Room* studyRoom = createRoom("Study room");
    struct Room* bathroom = createRoom("Bathroom");
    struct Room* guestRoom = createRoom("Guest room");
    struct Room* pool = createRoom("Pool");
    struct Room* greenhouse = createRoom("Greenhouse");
    struct Room* library = createRoom("Library");
    struct Room* bedroom = createRoom("Bedroom");

    // Initializing the 6 items
    struct Item* knife = item("Knife");
    struct Item* key = item("Key");
    struct Item* pillow = item("Pillow");
    struct Item* book = item("Book");
    struct Item* laptop = item("Laptop");
    struct Item* clock = item("Clock");

    // Initializing the 5 characters
    struct Character* npc1 = character("kevin");
    struct Character* npc2 = character("tintin");
    struct Character* npc3 = character("nitit");
    struct Character* npc4 = character("angel");
    struct Character* npc5 = character("lexi");

    // Set location for each character at the beginning
    setLocation(npc1, studyRoom);
    setLocation(npc2, livingRoom);
    setLocation(npc3, bedroom);
    setLocation(npc4, library);
    setLocation(npc5, greenhouse);

    // Add each character to a room
    addChar(studyRoom, npc1);
    addChar(livingRoom, npc2);
    addChar(bedroom, npc3);
    addChar(library, npc4);
    addChar(greenhouse, npc5);

    // Add each item to a room
    addItem(kitchen, knife);
    addItem(bedroom, pillow);
    addItem(library, book);
    addItem(livingRoom, key);
    addItem(studyRoom, laptop);
    addItem(guestRoom, clock);

    // Put all rooms into an array
    struct Room* roomList[9];
    roomList[0] = kitchen;
    roomList[1] = livingRoom;
    roomList[2] = studyRoom;
    roomList[3] = bathroom;
    roomList[4] = guestRoom;
    roomList[5] = pool;
    roomList[6] = greenhouse;
    roomList[7] = library;
    roomList[8] = bedroom;

    // Put all items into an array
    struct Item* items[6];
    items[0] = knife;
    items[1] = key;
    items[2] = pillow;
    items[3] = book;
    items[4] = laptop;
    items[5] = clock;

    // Put all characters into an array
    struct Character* characterList[5];
    characterList[0] = npc1;
    characterList[1] = npc2;
    characterList[2] = npc3;
    characterList[3] = npc4;
    characterList[4] = npc5;

    // Randomizing the position of each room
    struct Room* building[9];
    for (int i = 0; i < 9; ++i) {
        building[i] = NULL;
    }
    srand(time(0));
    for (int i = 0; i < 9; ++i) {
        int index = rand() % 9;
        if (building[index] != NULL) {
            while (building[index] != NULL) {
                ++index;
                if (index > 8) {
                    index = 0;
                }
            }
            building[index] = roomList[i];
        }
        else {
            building[index] = roomList[i];
        }
    }

    // Linking each room in the building based on their index
    // The layout of the building:
    // 0 | 1 | 2
    // 3 | 4 | 5
    // 6 | 7 | 8
    setEastRoom(building[0], building[1]);
    setSouthRoom(building[0], building[3]);

    setWestRoom(building[1], building[0]);
    setEastRoom(building[1], building[2]);
    setSouthRoom(building[1], building[4]);

    setWestRoom(building[2], building[1]);
    setSouthRoom(building[2], building[5]);

    setNorthRoom(building[3], building[0]);
    setEastRoom(building[3], building[4]);
    setSouthRoom(building[3], building[6]);

    setNorthRoom(building[4], building[1]);
    setWestRoom(building[4], building[3]);
    setEastRoom(building[4], building[5]);
    setSouthRoom(building[4], building[7]);

    setNorthRoom(building[5], building[2]);
    setWestRoom(building[5], building[4]);
    setSouthRoom(building[5], building[8]);

    setNorthRoom(building[6], building[3]);
    setEastRoom(building[6], building[7]);

    setNorthRoom(building[7], building[4]);
    setWestRoom(building[7], building[6]);
    setEastRoom(building[7], building[8]);

    setNorthRoom(building[8], building[5]);
    setWestRoom(building[8], building[7]);

    // Randomly choosing a room, item, and a character as the answer
    struct Character* chosenChar = characterList[rand() % 5];
    struct Room* chosenRoom = roomList[rand() % 9];
    struct Item* chosenItem = items[rand() % 6];
    // Representing the number of object matched within a single clue
    int chosenAnswer = 0;

    // Creating the player's avatar
    struct Character* player;

    // Main while loop
    int end = 0;
    // The total amount of clue used
    int numClue = 0;
 
    // Indicate if the command is valid
    int valid;

    // Start the introduction of the game
    start();

    // Array to store the player's name
    char playerName[100];
    // Taking the input for the player's name
    printf("Enter player's name: ");
    scanf("%s", &playerName);
    player = character(playerName);
    // Randomly placing the player within the 9 rooms
    setLocation(player, building[rand() % 9]);
    printf("------------------------------------------------------\n");
    printf("\n");

    while (end == 0) {
        // Array to store the command input
        char commandInput[10];
        printf("------------------------------------------------------\n");
        printf("Enter command: ");
        // Taking the command input
        scanf("%s", &commandInput);
        printf("\n");
        printf("------------------------------------------------------\n");
        printf("\n");
        // Check if the command is "help"
        if (strcmp(commandInput, "help") == 0) {
            help();
        }
        // Check if the command is "list"
        else if (strcmp(commandInput, "list") == 0) {
            // Showing all the rooms, items, and characters (except for the player)
            printf("------------------------------------------------------\n");
            printf("Items:\n");
            for (int i = 0; i < 6; ++i) {
                printf("\t%s\n", getName(items[i]));
            }
            printf("Rooms:\n");
            for (int i = 0; i < 9; ++i) {
                printf("\t%s\n", getRoomName(building[i]));
            }
            printf("Characters:\n");
            for (int i = 0; i < 5; ++i) {
                printf("\t%s\n", getCharName(characterList[i]));
            }
            printf("------------------------------------------------------\n");
            printf("\n");
        }
        // Check if the command is "look"
        else if (strcmp(commandInput, "look") == 0) {
            printf("------------------------------------------------------\n");
            // Displaying the current room
            printf("The room you are currently in is: %s\n\n", getRoomName(getLocation(player)));
            // Showing the room in each direction
            // If there is no room in a direction, the direction is not displayed
            printf("Rooms in each direction:\n");
            // Showing the north room
            if (getNorthRoom(getLocation(player)) != NULL) {
                printf("\tNorth: %s\n", getRoomName(getNorthRoom(getLocation(player))));
            }
            // Showing the south room
            if (getSouthRoom(getLocation(player)) != NULL) {
                printf("\tSouth: %s\n", getRoomName(getSouthRoom(getLocation(player))));
            }
            // Showing the west room
            if (getWestRoom(getLocation(player)) != NULL) {
                printf("\tWest: %s\n", getRoomName(getWestRoom(getLocation(player))));
            }
            // Showing the east room
            if (getEastRoom(getLocation(player)) != NULL) {
                printf("\tEast: %s\n", getRoomName(getEastRoom(getLocation(player))));
            }
            printf("\n");
            // Showing all the characters in the current room
            printf("Characters in this room:\n");
            showChar(getLocation(player));
            printf("\n");
            // Showing all the items in the current room
            printf("Items in the room:\n");
            showItem(getLocation(player));
            printf("------------------------------------------------------\n");
            printf("\n");
        }
        // Check if the command is "go"
        else if (strcmp(commandInput, "go") == 0) {
            valid = 0;
            // Array to store the direction input
            char direction[10];
            // Loop until a receive valid direction
            while (valid == 0) {
                struct Room* move;
                printf("------------------------------------------------------\n");
                printf("Enter direction: ");
                // Taking the direction input
                scanf("%s", &direction);
                printf("\n");
                printf("------------------------------------------------------\n");
                printf("\n");
                // Check if the direction is north
                if (strcmp(direction, "north") == 0) {
                    move = getNorthRoom(getLocation(player));
                    // Check if there is a north room
                    if (move == NULL) {
                        printf("Invalid direction\n");
                        printf("Please enter another direction\n\n");
                    }
                    else {
                        setLocation(player, move);
                        printf("Moved to %s\n\n", getRoomName(getLocation(player)));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Check if the direction is south
                else if (strcmp(direction, "south") == 0) {
                    move = getSouthRoom(getLocation(player));
                    // Check if there is a south room
                    if (move == NULL) {
                        printf("Invalid direction\n");
                        printf("Please enter another direction\n\n");
                    }
                    else {
                        setLocation(player, move);
                        printf("Moved to %s\n\n", getRoomName(getLocation(player)));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Check if the direction is east
                else if (strcmp(direction, "east") == 0) {
                    move = getEastRoom(getLocation(player));
                    // Check if there is a south room
                    if (move == NULL) {
                        printf("Invalid direction\n");
                        printf("Please enter another direction\n\n");
                    }
                    else {
                        setLocation(player, move);
                        printf("Moved to %s\n\n", getRoomName(getLocation(player)));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Check if the direction is west
                else if (strcmp(direction, "west") == 0) {
                    move = getWestRoom(getLocation(player));
                    // Check if there is a west room
                    if (move == NULL) {
                        printf("Invalid direction\n");
                        printf("Please enter another direction\n\n");
                    }
                    else {
                        setLocation(player, move);
                        printf("Moved to %s\n\n", getRoomName(getLocation(player)));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Case for when an invalid direction is given
                else {
                    printf("Invalid direction\n");
                    printf("Please enter north/south/west/east as your direction\n\n");
                }
            }
        }
        // Check if the command is "take"
        else if (strcmp(commandInput, "take") == 0) {
            int roomEmpty = itemEmpty(getLocation(player));
            valid = 0;
            while (valid == 0) {
                // Check if the room is empty
                if (roomEmpty == 1) {
                    printf("The room is empty\n\n");
                    break;
                }
                // Condition to check if the item is removed from the room
                int take;
                // Array to store the item's name
                char itemName[10];
                printf("------------------------------------------------------\n");
                // Taking input for the item
                printf("Enter item(no CAPS): ");
                scanf("%s", &itemName);
                printf("\n");
                printf("------------------------------------------------------\n");
                printf("\n");
                // Check if the item is knife
                if (strcmp(itemName, "knife") == 0) {
                    take = removeItem(getLocation(player), knife);
                    // Check if knife is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(knife));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, knife);
                        printf("%s added to inventory\n\n", getName(knife));
                        valid = 1;
                    }
                }
                // Check if the item is key
                else if (strcmp(itemName, "key") == 0) {
                    take = removeItem(getLocation(player), key);
                    // Check if key is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(key));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, key);
                        printf("%s added to inventory\n\n", getName(key));
                        valid = 1;
                    } 
                }
                // Check if the item is pillow
                else if (strcmp(itemName, "pillow") == 0) {
                    take = removeItem(getLocation(player), pillow);
                    // Check if pillow is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(pillow));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, pillow);
                        printf("%s added to inventory\n\n", getName(pillow));
                        valid = 1;
                    }
                }
                // Check if the item is book
                else if (strcmp(itemName, "book") == 0) {
                    take = removeItem(getLocation(player), book);
                    // Check if book is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(book));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, book);
                        printf("%s added to inventory\n\n", getName(book));
                        valid = 1;
                    }
                }
                // Check if the item is laptop
                else if (strcmp(itemName, "laptop") == 0) {
                    take = removeItem(getLocation(player), laptop);
                    // Check if laptop is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(laptop));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, laptop);
                        printf("%s added to inventory\n\n", getName(laptop));
                        valid = 1;
                    }
                }
                // Check if the item is clock
                else if (strcmp(itemName, "clock") == 0) {
                    take = removeItem(getLocation(player), clock);
                    // Check if clock is in the room
                    if (take == 0) {
                        printf("%s is not in this room\n\n", getName(clock));
                        // Showing the items in the room
                        printf("Items in the room:\n");
                        showItem(getLocation(player));
                        printf("\n");
                    }
                    else {
                        addInventory(player, clock);
                        printf("%s added to inventory\n\n", getName(clock));
                        valid = 1;
                    }
                }
                // Case for invalid item input
                else {
                    printf("Invalid item\n");
                    printf("Please enter another name\n\n");
                }
            }
        }
        // Check if the command is "drop"
        else if (strcmp(commandInput, "drop") == 0) {
            // Check if the iventory is empty
            int playerEmpty = inventoryEmpty(player);
            valid = 0;
            if (playerEmpty == 1) {
                printf("Inventory is empty\n\n");
                valid = 1;
            }
            // Loop until a valid item input is given
            while(valid == 0) {
                int removed;
                // Array to store item's name
                char itemName[10];
                printf("------------------------------------------------------\n");
                printf("Enter item(no CAPS): ");
                // Taking item's name input
                scanf("%s", &itemName);
                printf("\n");
                printf("------------------------------------------------------\n");
                printf("\n");
                // Checking if the item is knife
                if (strcmp(itemName, "knife") == 0) {
                    removed = removeInventory(player, knife);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(knife));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), knife);
                        printf("%s removed from the inventory\n\n", getName(knife));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Checking if the item is key
                else if (strcmp(itemName, "key") == 0) {
                    removed = removeInventory(player, key);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(key));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), key);
                        printf("%s removed from the inventory\n\n", getName(key));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Checking if the item is pillow
                else if (strcmp(itemName, "pillow") == 0) {
                    removed = removeInventory(player, pillow);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(pillow));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), pillow);
                        printf("%s removed from the inventory\n\n", getName(pillow));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Checking if the item is book
                else if (strcmp(itemName, "book") == 0) {
                    removed = removeInventory(player, book);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(book));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), book);
                        printf("%s removed from the inventory\n\n", getName(book));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Checking if the item is laptop
                else if (strcmp(itemName, "laptop") == 0) {
                    removed = removeInventory(player, laptop);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(laptop));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), laptop);
                        printf("%s removed from the inventory\n\n", getName(laptop));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Checking if the item is clock
                else if (strcmp(itemName, "clock") == 0) {
                    removed = removeInventory(player, clock);
                    // Checking if the item is in the inventory
                    if (removed == 0) {
                        printf("%s is not in the inventory\n\n", getName(clock));
                        // Showing items in the inventory
                        printf("The items in your inventory are:\n");
                        showInventory(player);
                        printf("\n");
                    }
                    else {
                        addItem(getLocation(player), clock);
                        printf("%s removed from the inventory\n\n", getName(clock));
                        // Condition to end the loop
                        valid = 1;
                    }
                }
                // Case for invalid item input
                else {
                    printf("Invalid item\n");
                    printf("Please enter another name\n\n");
                }
            }
        }
        // Check if the command is "inventory"
        else if (strcmp(commandInput, "inventory") == 0) {
            // Showing items in the inventory
            printf("The items in your inventory are:\n");
            showInventory(player);
            printf("\n");
        }
        // Check if the command is "clue"
        else if (strcmp(commandInput, "clue") == 0) {
            // Incrementing numClue
            ++numClue;
            // Array to store character's name
            char charInput[10];
            // Condition to end the loop
            int charValid = 0;
            // Loop until a valid character name is given
            while (charValid == 0) {
                // Array to store the character name input
                char input[10];
                printf("------------------------------------------------------\n");
                printf("Enter a character's name (except for the player's name and no CAPS):\n");
                // Taking the character name input
                scanf("%s", &input);
                printf("\n");
                printf("------------------------------------------------------\n");
                printf("\n");
                // Check if the name is kevin
                if (strcmp(input, "kevin") == 0) {
                    for (int i = 0; i < 10; ++i) {
                        charInput[i] = input[i];
                    }
                    charValid = 1;
                }
                // Check if the name is tintin
                else if (strcmp(input, "tintin") == 0) {
                    for (int i = 0; i < 10; ++i) {
                        charInput[i] = input[i];
                    }
                    charValid = 1;
                }
                // Check if the name is nitit
                else if (strcmp(input, "nitit") == 0) {
                    for (int i = 0; i < 10; ++i) {
                        charInput[i] = input[i];
                    }
                    charValid = 1;
                }
                // Check if the name is angel
                else if (strcmp(input, "angel") == 0) {
                    for (int i = 0; i < 10; ++i) {
                        charInput[i] = input[i];
                    }
                    charValid = 1;
                }
                // Check if the name is lexi
                else if (strcmp(input, "lexi") == 0) {
                    for (int i = 0; i < 10; ++i) {
                        charInput[i] = input[i];
                    }
                    charValid = 1;
                }
                // Case for invalid character name
                else {
                    printf("Character name not valid\n");
                    printf("Please enter a valid name\n\n");
                }
            }
            // Finding the match character to their name
            struct Character* selectedChar;
            for (int i = 0; i < 5; ++i) {
                if (strcmp(getCharName(characterList[i]), charInput) == 0) {
                    selectedChar = characterList[i];
                }
            }
            // Removing the character from their room
            removeChar(getLocation(selectedChar), selectedChar);
            // Set their new location to be at the player's location
            setLocation(selectedChar, getLocation(player));
            // Add the character to the room
            addChar(getLocation(player), selectedChar);
            printf("------------------------------------------------------\n");
            // Hint about the room
            if (getLocation(player) == chosenRoom) {
                // Increment chosenAnswer
                ++chosenAnswer;
                printf("Room Match\n");
            }
            else {
                printf("Wrong Room\n");
            }
            // Hint about the character
            // Check if the chosen character is in the room
            if (charInRoom(getLocation(player), chosenChar) == 1) {
                // Increment chosenAnswer
                ++chosenAnswer;
                printf("Character Match\n");
            }
            else {
                printf("Wrong Character\n");
            }
            // Hint about the item
            // Check if the item is in the room or in the inventory
            if (clueSearchRoom(getLocation(player), chosenItem) == 1 ||  clueSearchCharacter(player, chosenItem) == 1) {
                // Increment chosenAnswer
                ++chosenAnswer;
                printf("Item Match\n");
            }
            else {
                printf("Wrong Item\n");
            }
            // Indicating the amount of clue remaining
            printf("\nThe number of clue left is: %i\n", 10 - numClue);
            printf("------------------------------------------------------\n");
            // Player won the game
            if (chosenAnswer >= 3) {
                printf("You have won the game!!\n\n");
                end = 1;
            }
            // Player lost the game
            if (numClue >= 10 && chosenAnswer < 3) {
                end = 1;
                printf("You have lost.\n\n");
                printf("The answer was:\n");
                printf("\t%s\n", getCharName(chosenChar));
                printf("\t%s\n", getRoomName(chosenRoom));
                printf("\t%s\n", getName(chosenItem));
            }
            // Reseting the chosenAnswer to 0
            chosenAnswer = 0;
        }
        // Case for invalid command input
        else {
            printf("Invalid command\n");
            printf("Please enter a valid command or type 'help'\n");
            printf("\n");
        }
    }
    // Deallocating memory for the rooms
    for (int i = 0; i < 9; ++i) {
        roomFree(roomList[i]);
    }
    // Deallocating memory for the items
    for (int i = 0; i < 6; ++i) {
        itemFree(items[i]);
    }
    // Deallocating memory for the characters
    for (int i = 0; i < 5; ++i) {
        characterFree(characterList[i]);
    }
    // End of the game
    printf("------------------------------------------------------\n");
    printf("\n\n");
    printf("Congrats %s! You have finished the game!\n", getCharName(player));
    printf("The End\n\n");
    printf("------------------------------------------------------\n");
    return 0;
}