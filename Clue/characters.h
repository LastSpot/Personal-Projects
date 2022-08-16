#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CHARACTERS_H
#define CHARACTERS_H    

// Declaring the struct Character with its attributes
struct Character {
    char* name;
    struct Room* location;
    struct Item* inventory;
};

// Initializing and allocating memory for an Character object
// Parameter: a string as the character's name
// Return: a Character object
struct Character* character(char* name);

// Deallocating memory
// Parameter: a Character object
// Return: nothing
void characterFree(struct Character* avatar);

// Get a character's name
// Parameter: a Character object
// Return: a string as the character's name
char* getCharName(struct Character* avatar);

// Get location of a character
// Parameter: a Character object
// Return: a Room object as the location of the Character object
struct Room* getLocation(struct Character* avatar);

// Set a character's location
// Parameter: a Character object and a Room object as the new location
// Return: nothing
void setLocation(struct Character* avatar, struct Room* newLocation);

// Show a character's inventory
// Parameter: a Character Object
// Return: nothing
void showInventory(struct Character* avatar);

// Add an item to a character's inventory
// Parameter: a Character object and an Item object as the item to add
// Return: nothing
void addInventory(struct Character* avatar, struct Item* newItem);

// Remove an item from a character's inventory
// Parameter: a Character object and an Item object as the item to be remove
// Return: an int to indicate if the item was removed from the inventory
int removeInventory(struct Character* avatar, struct Item* removeItem);

// Check if a character's inventory is empty
// Parameter: a Character object
// Return: an int to indicate if the inventory is empty
int inventoryEmpty(struct Character* avatar);

// Check if the character has the chosen item
// Parameter: a Character object and an Item object as the chosen item
// Return: an int to indicate if the character has the chosen item in the inventory
int clueSearchCharacter(struct Character* avatar, struct Item* item);

#endif