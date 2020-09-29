#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

struct Room {
  char* name;
  char* description;
  struct Item* items;
  struct Room* north;
  struct Room* south;
  struct Room* east;
  struct Room* west;
};

// goal: creates a Room struct given the description, items, and next adjacent rooms
// param description: char* representing the description of the room when 'LOOK' is used
// param items: char* representing the list items
// param north, south, east, west: Room struct pointer representing the room in the specified direction
// return: a Room struct pointer to a room with the specified fields
struct Room* room(char* name, char* description, struct Item* items, struct Room *north, struct Room *south, struct Room *east, struct Room *west);

// goal: swaps two pointers
// param a b: struct Room* to be swapped
// return: void
void swap (struct Room* a, struct Room* b);

// goal: shuffles a struct Room* array using the Fisher-Yates algorithm. 
// Credit due to GeeksforGeeks and StackOverflow for idea and implementation.
// param arr: struct Room* array to be shuffled
// return: void
void randomize (struct Room* map[]);

// goal: links rooms together to form 3x3 board. 
// param map: struct Room* array with shuffle pointers to rooms. 0 is top left room
// return: void
void createMap(struct Room* map[]);

// goal: print out rooms in each direction
// param room: current room of avatar
// return: void
void mapPrint(struct Room* room);