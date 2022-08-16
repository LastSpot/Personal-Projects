#include "items.h"

struct Item* item(char* name) {
    struct Item* item = (struct Item *)malloc(sizeof(struct Item));
    if (item == NULL) {
        return NULL;
    }
    item -> name = name;
    item -> nextItem = NULL;
    item -> prevItem = NULL;
    return item;
}

void itemFree(struct Item* object) {
    free(object);
}

char* getName(struct Item* object) {
    return object -> name;
}

struct Item* getNext(struct Item* object) {
    return object -> nextItem;
}

struct Item* getPrev(struct Item* object) {
    return object -> prevItem;
}

void setName(struct Item* object, char* newName) {
    object -> name = newName;
}

void setNext(struct Item* object, struct Item* next) {
    object -> nextItem = next;
}

void setPrev(struct Item* object, struct Item* prev) {
    object -> prevItem = prev;
}