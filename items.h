#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Item {
  char* name;
  struct Item* next;
};

// constructor for item
struct Item* item(char* name, struct Item* next);

// basic getters and setters
char* item_name(struct Item* item);
char* item_description(struct Item* item);
struct Item* item_next(struct Item* item);

// goal: removes an item from inventory if finder is 0
// return: a pointer to the item taken or NULL if item not found
struct Item* drop_item(struct Item* items, char* str, int finder);

// goal: add an item to linked list
// return: void
void add_item(struct Item* itemList, struct Item* itemToAdd);

// goal: removes an item from a linked list and adds it to another
// return: true if an item was exchanged
bool exchange(struct Item* toAddto, struct Item* toDropFrom, char* itemName);

// goal: print out the name of each item in the linked list
void list(struct Item* item);