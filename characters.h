#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rooms.h"

struct Character {
    char* name;
    struct Room* room;
    struct Item* inventory;
};
// constructor for Character
struct Character* character(char* name, struct Room* room, struct Item* inventory);

// goal: move avatar in an inputed direction by setting room to new adjacent room
// return: int 1 if successful, else 0.
int goDir(struct Character* character, char* noun);

// goal: set character's room pointer to particular room
// return: int 1 if successful, else 0. 
int move_character(struct Character* character, struct Room* room);

// goal: check is noun is the 'name' of a valid npc
// return: bool true if successful, else false.
bool validSus(struct Character* npcList[], char* noun, struct Room* avatarRoom);


// goal: randomize which room gets what item
// param itemList[]: array of item pointers
// param map[]: array of room pointers whose items field may get set
// return: void
void randomizeItem(struct Item* itemList[], struct Room* map[]);

// goal: randomize which room each character points to
// param npcList[]: array of Character pointers whose room field will get set
// param map[]: array of room pointers
// return: void
void randomizeChar(struct Character* npcList[], struct Room* map[]);

// goal: prints out which character in npcList is pointing to same room as avatar, avatarRoom
// param npcList[]: array of Character pointers that will be traversed
// param avatar: char* name of room that avatar is currently in
// return: void
void roomChar(struct Character* npcList[], char* avatarRoom);

// goal: compares player's guess to answer and returns and prints results
// param answer[]: array of Character pointers that will be traversed
// param avatar: struct Character representing player
// param noun: char* of name of suspect that player guessed 
// return: true if guess is correct, false if guess is incorrect
bool clue(char* answer[], struct Character* avatar, char* noun);