#include "rooms.h"

// goal: creates a Room struct given the description, items, and next adjacent rooms
// param description: char* representing the description of the room when 'LOOK' is used
// param items: char* representing the list items
// param north, south, east, west: Room struct pointer representing the room in the specified direction
// return: a Room struct pointer to a room with the specified fields
struct Room* room(char* name, char* description, struct Item* items, struct Room *north, struct Room *south, struct Room *east, struct Room *west) {
  //create dummy head for item's linked list;
  char *dummy = (char*) malloc(6);
  if (dummy == NULL) {
      return NULL;
  }
  strcpy(dummy, "dummy");

  struct Item* dum = (struct Item*) malloc(sizeof(items) + sizeof(dummy));
  dum->name = dummy;
  dum->next = items;

  //create room with new linked list with dummy head;
  struct Room* r = (struct Room*) malloc(2*sizeof(description) + sizeof(items) + 6 * sizeof(north));
  r->name = name;
  r->description = description;
  r->items = dum;
  r->north = north;
  r->south = south;
  r->east = east;
  r->west = west;
  return r;
};

// goal: swaps two pointers
// param a b: struct Room* to be swapped
// return: void
void swap (struct Room* a, struct Room* b) { 
    struct Room temp = *a; 
    *a = *b; 
    *b = temp; 
} 

// goal: shuffles a struct Room* array using the Fisher-Yates algorithm. 
// Credit due to GeeksforGeeks and StackOverflow for idea and implementation.
// param arr: struct Room* array to be shuffled
// return: void
void randomize (struct Room* map[]) { 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand (time(NULL)); 
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = 8; i > 0; i--) { 
        // Pick a random index from 0 to i 
        int j = rand() % (i + 1); 
        // Swap arr[i] with the element at random index 
        swap(map[i], map[j]); 
    } 
} 

// goal: links rooms together to form 3x3 board. 
// param map: struct Room* array with shuffle pointers to rooms. 0 is top left room
// return: void
void createMap(struct Room* map[]) {
  for (int i = 0; i < 9; i++) {
    switch(i) {
      case 0:
        // top left (lawful good)
        map[0]->south = map[3];
        map[0]->east = map[1];
        break;
      case 1:
        // top middle
        map[1]->south = map[4];
        map[1]->east = map[2];
        map[1]->west = map[0];
        break;
      case 2:
        // top right
        map[2]->south = map[5];
        map[2]->west = map[1];
        break;
      case 3:
      // middle left
        map[3]->north = map[0];
        map[3]->south = map[6];
        map[3]->east = map[4];
        break;
      case 4:
      // middle (True Neutral)
        map[4]->north = map[1];
        map[4]->south = map[7];
        map[4]->east = map[5];
        map[4]->west = map[3];
        break;
      case 5:
      // middle right (chaotic neutral)
        map[5]->north = map[2];
        map[5]->south = map[8];
        map[5]->west = map[4];
        break;
      case 6:
      // bottom left
        map[6]->north = map[3];
        map[6]->east = map[7];
        break;
      case 7:
      // bottom middle
        map[7]->north = map[4];
        map[7]->east = map[8];
        map[7]->west = map[6];
        break;
      case 8:
      // bottom right (chaotic evil)
        map[8]->north = map[5];
        map[8]->west = map[7];
        break;
    }

  }
}

// goal: print out rooms in each direction
// param room: current room of avatar
// return: void
void mapPrint(struct Room* room) {
  if (room->north != NULL) {
    printf("\n  - North: %s \n", room->north->name);
  }
  if (room->south != NULL) {
    printf("\n  - South: %s \n", room->south->name);
  }
  if (room->east != NULL) {
    printf("\n  - East: %s \n", room->east->name);
  }
  if (room->west != NULL) {
    printf("\n  - West: %s \n", room->west->name);
  }
}