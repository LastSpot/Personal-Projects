#include "characters.h"
#include "rooms.h"
#include "items.h"

struct Character* character(char* name) {
    struct Character* character = (struct Character *)malloc(sizeof(struct Character));
    if(character == NULL) {
        return NULL;
    }
    character -> name = name;
    character -> location = NULL;
    character -> inventory = NULL;
    return character;
}

void characterFree(struct Character* avatar) {
    free(avatar);
}

char* getCharName(struct Character* avatar) {
    return avatar -> name;
}

struct Room* getLocation(struct Character* avatar) {
    return avatar -> location;
}

void setLocation(struct Character* avatar, struct Room* newLocation) {
    avatar -> location = newLocation;
}

void showInventory(struct Character* avatar) {
    struct Item* reset = avatar -> inventory;
    if (avatar -> inventory == NULL) {
        printf("\tYour inventory is empty\n");
    }
    while (avatar -> inventory != NULL) {
        printf("\t%s\n", getName(avatar -> inventory));
        avatar -> inventory = getPrev(avatar -> inventory);
    }
    avatar -> inventory = reset;
}

void addInventory(struct Character* avatar, struct Item* newItem) {
    if (avatar -> inventory == NULL) {
        avatar -> inventory = newItem;
    }
    else {
        setNext(avatar -> inventory, newItem);
        setPrev(newItem, avatar -> inventory);
        avatar -> inventory = getNext(avatar -> inventory);
    }
}

int removeInventory(struct Character* avatar, struct Item* removeItem) {
    int removed = 0;
    struct Item* next;
    struct Item* prev;
    struct Item* reset = avatar -> inventory;
    while (avatar -> inventory != NULL && removed == 0) {
        next = getNext(avatar -> inventory);
        prev = getPrev(avatar -> inventory);
        if (avatar -> inventory == removeItem && next == NULL && prev == NULL) {
            avatar -> inventory = NULL;
            removed = 1;
        }
        else if (avatar -> inventory == removeItem && next == NULL) {
            setNext(prev, NULL);
            setPrev(avatar -> inventory, NULL);
            avatar -> inventory = prev;
            removed = 1;
        }
        else if (avatar -> inventory == removeItem && prev == NULL) {
            setPrev(next, NULL);
            setNext(avatar -> inventory, NULL);
            avatar -> inventory = next;
            while (getNext(avatar -> inventory) != NULL) {
                avatar -> inventory = getNext(avatar -> inventory);
            }
            removed = 1;
        }
        else if (avatar -> inventory == removeItem) {
            setNext(prev, next);
            setPrev(next, prev);
            setNext(avatar -> inventory, NULL);
            setPrev(avatar -> inventory, NULL);
            avatar -> inventory = next;
            while (getNext(avatar -> inventory) != NULL) {
                avatar -> inventory = getNext(avatar -> inventory);
            }
            removed = 1;
        }
        else {
            avatar -> inventory = prev;
        }
    }
    if (removed == 0) {
        avatar -> inventory = reset;
        return 0;
    }
    return 1;
}

int inventoryEmpty(struct Character* avatar) {
    if (avatar -> inventory == NULL) {
        return 1;
    }
    return 0;
}

int clueSearchCharacter(struct Character* avatar, struct Item* item) {
    struct Item* reset = avatar -> inventory;
    while (avatar -> inventory != NULL) {
        if (avatar -> inventory == item) {
            return 1;
        }
        avatar -> inventory = getPrev(avatar -> inventory);
    }
    avatar -> inventory = reset;
    return 0;
}