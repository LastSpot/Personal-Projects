#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ITEMS_H
#define ITEMS_H

// Declaring the struct Item with its attributes
struct Item {
    char* name;
    struct Item* nextItem;
    struct Item* prevItem;
};

// Initializing and allocating memory for an Item object
// Parameter: a string as the name of the item
// Return: an object with attributes of struct Item
struct Item* item(char* name);

// Deallocate memory
// Parameter: an Item object
// Return: nothing
void itemFree(struct Item* object);

// Get an item's name
// Parameter: an Item object
// Return: a string that is the item's name
char* getName(struct Item* object);

// Get the next item in the linked list
// Parameter: an Item object
// Return: the next Item object within the linked list
struct Item* getNext(struct Item* object);

// Get the previous item in the linked list
// Parameter: an Item object
// Return: the previous Item object within the linked list
struct Item* getPrev(struct Item* object);

// Set the item's name
// Parameter: an Item object and a string as its new name
// Return: nothing
void setName(struct Item* object, char* newName);

// Set the next Item in the linked list
// Parameter: an Item object as the current head of the linked list and another Item object to set as the new head
// Return: nothing
void setNext(struct Item* object, struct Item* next);

// Set the previous Item in the linked list
// Parameter: an Item object as the current head of the linked list and another Item object as the Item previous to the current head
// Return: nothing
void setPrev(struct Item* object, struct Item* prev);

#endif