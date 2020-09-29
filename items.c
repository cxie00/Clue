#include "items.h"

// constructor for item
struct Item* item(char* name,  struct Item* next) {
  struct Item* i = (struct Item*) malloc(sizeof(next) + sizeof(name));
  if (i == NULL) {
    return NULL;
  }
  i->name = name;
  i->next = next;
  return i;
};

char* item_name(struct Item* item) {
  return item -> name;
}

struct Item* item_next(struct Item* item) {
  return item -> next;
}

// goal: removes an item from inventory if finder is 0
// param items: struct Item* linked list of items to traverse
// param str: char* representing name of item to search for
// param finder: int representing whether to modify linked list or not
//  can be 0 for modify mode, 1 for finder mode(used in clue() in adventure.c)
// return: a pointer to the item taken or NULL if item not found
struct Item* drop_item(struct Item* items, char* str, int finder) {
  // If first item, set the item to the second struct
  struct Item* first_p = items;
  struct Item* second_p = item_next(items);
  while (second_p != NULL) {
    if (strcmp(item_name(second_p), str) == 0) {
      break;
    }
    // iterate through linked list to next two pointers
    first_p = item_next(first_p);
    second_p = item_next(second_p);
  }
  if (second_p != NULL && finder == 0) {
    first_p->next = item_next(second_p);
  }
  return second_p;
}

// goal: add an item to linked list
// param itemList: linked list of struct Item* to add to
// param itemToAdd: struct Item* to add
// return: void
void add_item(struct Item* itemList, struct Item* itemToAdd) {
  // If first item, set the item to the second struct
  struct Item* second_p = item_next(itemList);
  itemList->next = itemToAdd;
  itemToAdd->next = second_p;
}

// goal: removes an item from a linked list and adds it to another
// return: true if an item was exchanged
bool exchange(struct Item* toAddto, struct Item* toDropFrom, char* itemName) {
  struct Item* taken = drop_item(toDropFrom, itemName, 0);
  if (taken != NULL) {
    add_item(toAddto, taken);
    return true;
  } else {
    // item was not found in toDropFrom, return false
    return false;
  }
}

// goal: print out the name of each item in the linked list
// param item: pointer to item list
// return: void
void list(struct Item* item) {
  struct Item* second_p = item_next(item);
  if (second_p == NULL) {
    printf(" - Nothing. Your bag is empty.\n");
  }
  while (second_p != NULL) {
    printf("  - a %s\n", second_p->name);
    // iterate through linked list to next two pointers
    second_p = item_next(second_p);
  }
}