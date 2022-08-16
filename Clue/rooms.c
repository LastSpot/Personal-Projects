#include "rooms.h"
#include "items.h"
#include "characters.h"

struct Room* createRoom(char* name) {
    struct Room* room = (struct Room *)malloc(sizeof(struct Room));
    if (room == NULL) {
        return NULL;
    }
    room -> name = name;
    room -> north = NULL;
    room -> south = NULL;
    room -> east = NULL;
    room -> west = NULL;
    room -> itemList = NULL;
    room -> charIndex = 0;
    room -> character;
    return room;
}

void roomFree(struct Room* place) {
    free(place);
}

char* getRoomName(struct Room* place) {
    return place -> name;
}

struct Room* getNorthRoom(struct Room* place) {
    return place -> north;
}

struct Room* getSouthRoom(struct Room* place) {
    return place -> south;
}

struct Room* getEastRoom(struct Room* place) {
    return place -> east;
}

struct Room* getWestRoom(struct Room* place) {
    return place -> west;
}

void setNorthRoom(struct Room* place, struct Room* newNorth) {
    place -> north = newNorth;
}

void setSouthRoom(struct Room* place, struct Room* newSouth) {
    place -> south = newSouth;
}

void setEastRoom(struct Room* place, struct Room* newEast) {
    place -> east = newEast;
}

void setWestRoom(struct Room* place, struct Room* newWest) {
    place -> west = newWest;
}

void showItem(struct Room* place) {
    struct Item* reset = place -> itemList;
    if (place -> itemList == NULL) {
        printf("\tThere are no items in the room\n");
        return;
    }
    while (place -> itemList != NULL) {
        printf("\t%s\n", getName(place -> itemList));
        place -> itemList = getPrev(place -> itemList);
    }
    place -> itemList = reset;
}

void addItem(struct Room* place, struct Item* newItem) {
    if (place -> itemList == NULL) {
        place -> itemList = newItem;
    }
    else {
        setNext(place -> itemList, newItem);
        setPrev(newItem, place -> itemList);
        place -> itemList = getNext(place -> itemList);
    }
}

int removeItem(struct Room* place, struct Item* target) {
    int removed = 0;
    struct Item* next;
    struct Item* prev;
    struct Item* reset = place -> itemList;
    while (place -> itemList != NULL && removed == 0) {
        next = getNext(place -> itemList);
        prev = getPrev(place -> itemList);
        if (place -> itemList == target && next == NULL && prev == NULL) {
            place -> itemList = NULL;
            removed = 1;
        }
        else if (place -> itemList == target && next == NULL) {
            setNext(prev, NULL);
            setPrev(place -> itemList, NULL);
            place -> itemList = prev;
            removed = 1;
        }
        else if (place -> itemList == target && prev == NULL) {
            setPrev(next, NULL);
            setNext(place -> itemList, NULL);
            place -> itemList = next;
            while (getNext(place -> itemList) != NULL) {
                place -> itemList = getNext(place -> itemList);
            }
            removed = 1;
        }
        else if (place -> itemList == target) {
            setNext(prev, next);
            setPrev(next, prev);
            setNext(place -> itemList, NULL);
            setPrev(place -> itemList, NULL);
            place -> itemList = next;
            while (getNext(place -> itemList) != NULL) {
                place -> itemList = getNext(place -> itemList);
            }
            removed = 1;
        }
        else {
            place -> itemList = prev;
        }
    }
    if (removed == 0) {
        place -> itemList = reset;
        return 0;
    }
    return 1;
}

void showChar(struct Room* place) {
    if (place -> charIndex == 0) {
        printf("\tNo character in this room\n");
    }
    else {
        for (int i = 0; i < place -> charIndex; ++i) {
            printf("\t%s\n", getCharName(place -> character[i]));
        }
    }
}

void addChar(struct Room* place, struct Character* newCharacter) {
    int inRoom = 0;
    for (int i = 0; i < place -> charIndex; ++i) {
        if (place -> character[i] == newCharacter) {
            inRoom = 1;
        }
    }
    if (inRoom == 0) {
        place -> character[place -> charIndex] = newCharacter;
        place -> charIndex += 1;
    }
}

void removeChar(struct Room* place, struct Character* charRemove) {
    for (int i = 0; i < place -> charIndex; ++i) {
        if (place -> character[i] == charRemove) {
            place -> character[i] = NULL;
            for (int j = i; j < 5; ++j) {
                place -> character[j] = place -> character[j + 1];
            }
            place -> character[5] = NULL;
            place -> charIndex -= 1;
            break;
        }
    }
}

int itemEmpty(struct Room* place) {
    if (place -> itemList == NULL) {
        return 1;
    }
    return 0;
}

int clueSearchRoom(struct Room* place, struct Item* item) {
    struct Item* reset = place -> itemList;
    while (place -> itemList != NULL) {
        if (place -> itemList == item) {
            return 1;
        }
        place -> itemList = getPrev(place -> itemList);
    }
    place -> itemList = reset;
    return 0;
}

int charInRoom(struct Room* place, struct Character* chosenChar) {
    for (int i = 0; i < place -> charIndex; ++i) {
        if (place -> character[i] == chosenChar) {
            return 1;
        }
    }
    return 0;
}