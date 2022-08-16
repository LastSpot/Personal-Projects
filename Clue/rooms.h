#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ROOMS_H
#define ROOMS_H

// Declaring the struct Room with its attributes
struct Room {
    char* name;
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Item* itemList;
    struct Character* character[6];
    int charIndex;
};

// Initialize the Room object while allocating memory using malloc
// Parameter: a string as the room's name
// Return: an Room object with all of its attributes
struct Room* createRoom(char* name);

// Deallocate memory
// Parameter: a Room object
// Return: nothing
void roomFree(struct Room* place);

// Get the name of the room
// Parameter: a Room object
// Return: a string
char* getRoomName(struct Room* place);

// Get the room at the north direction
// Parameter: a Room Object
// Return: a Room Object
struct Room* getNorthRoom(struct Room* place);

// Get the room at the south direction
// Parameter: a Room Object
// Return: a Room Object
struct Room* getSouthRoom(struct Room* place);

// Get the room at the east direction
// Parameter: a Room Object
// Return: a Room Object
struct Room* getEastRoom(struct Room* place);

// Get the room at the west direction
// Parameter: a Room Object
// Return: a Room Object
struct Room* getWestRoom(struct Room* place);

// Set the north room of a Room Object
// Parameter: a Room object as the room to add on and a Room object as the room to be add on
// Return: nothing
void setNorthRoom(struct Room* place, struct Room* newNorth);

// Set the south room of a Room Object
// Parameter: a Room object as the room to add on and a Room object as the room to be add on
// Return: nothing
void setSouthRoom(struct Room* place, struct Room* newSouth);

// Set the east room of a Room Object
// Parameter: a Room object as the room to add on and a Room object as the room to be add on
// Return: nothing
void setEastRoom(struct Room* place, struct Room* newEast);

// Set the west room of a Room Object
// Parameter: a Room object as the room to add on and a Room object as the room to be add on
// Return: nothing
void setWestRoom(struct Room* place, struct Room* newWest);

// Show all the items in a room
// Parameter: a Room object
// Return: nothing
void showItem(struct Room* place);

// Add item to the room
// Parameter: a Room object as the room to add the item in and an Item object as the item to be add in
// Return: nothing
void addItem(struct Room* place, struct Item* newItem);

// Remove item from the room
// Parameter: a Room object as the room to remove the item and an Item object as the item to be remove
// Return: an int to indicate if the item was removed
int removeItem(struct Room* place, struct Item* target);

// Show all the characters in the room
// Parameter: a Room object
// Return: nothing
void showChar(struct Room* place);

// Add a character to the room
// Parameter: a Room object as the room to add the character and a Character object as the character to be add in to the room
// Return: nothing
void addChar(struct Room* place, struct Character* newCharacter);

// Remove a character from the room
// Parameter: a Room object to remove the character from and a Character object as the character to be remove
void removeChar(struct Room* place, struct Character* charRemove);

// Check if the room has items or not
// Parameter: a Room object
// Return: an int to indicate if the room is items or not
int itemEmpty(struct Room* place);

// Search for the chosen item in the room
// Parameter: a Room object to be search in and an Item object as the target of the search
// Return: an int to indicate if the room contains the specific item
int clueSearchRoom(struct Room* place, struct Item* item);

// Search for the chosen character in the room
// Parameter: a Room object and a Character object
// Return: an int to indicate if the character is in the room
int charInRoom(struct Room* place, struct Character* chosenChar);

#endif