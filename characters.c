#include "characters.h"

struct Character* character(char* name, struct Room* room, struct Item* inventory) {
    char *dummy = (char*) malloc(6);
    if (dummy == NULL) {
        return NULL;
    }
    strcpy(dummy, "dummy");

    struct Item* dum = (struct Item*) malloc(sizeof(inventory) + sizeof(dummy));
    dum->name = dummy;
    dum->next = inventory;
    
    struct Character* c = (struct Character*) malloc(sizeof(name) + sizeof(room) + sizeof(inventory));
    if (c == NULL) {
        return NULL;
    }
    c->name = name;
    c->room = room;
    c->inventory = dum;
    return c;
}

// goal: move avatar in an inputed direction by setting room to new adjacent room
// return 1 if successful, else 0.
int goDir(struct Character* character, char* noun) {
    char* oldRoom = character->room->name;
    int moved = 0;
    if (noun == NULL) {
        printf("\n \033[0;31mGo where?\033[0m Enter a direction.\n");
        return 0;
    }
    if (strcmp(noun, "north") == 0) {
        moved = move_character(character, character->room->north); 
    }
    else if (strcmp(noun, "east") == 0) {
        moved = move_character(character, character->room->east); 
    }
    else if (strcmp(noun, "south") == 0) {
        moved = move_character(character, character->room->south); 
    }
    else if (strcmp(noun, "west") == 0) {
        moved = move_character(character, character->room->west); 
    } else {
        printf("\n \033[0;31mWait, what?\033[0m \n");
        printf(" I can't go '%s'! That's not a valid direction. \n", noun);
        printf(" I can only go: north, south, east, and west. \n");
        return 0;
    }
    if (moved != 0) {
        printf("\n You \033[1;31mmoved\033[0m %s from the %s to the %s. \n", noun, oldRoom, character->room->name);
    } else {
        printf("\n \033[0;31mYou can't go that way.\033[0m There's nothing %s.\n", noun);
    }
    return 1;
}

// goal: set character's room pointer to particular room
// return: 1 if successful, else 0. 
int move_character(struct Character* character, struct Room* destination) {
    if (destination != NULL) {
        character->room = destination;  
        return 1;       
    }
    return 0;
}

// goal: check is noun is the 'name' of a valid npc
// return: bool true if successful, else false.
bool validSus(struct Character* npcList[], char* noun, struct Room* avatarRoom) {
    if (noun == NULL) {
        printf("\n \033[0;31mClue who?\033[0m You must clue a character.\n");
        return false;
    }
    for (int i = 0; i < 5; i++) {
        if (strcmp(npcList[i]->name, noun) == 0) {
            int moved = move_character(npcList[i], avatarRoom);
            printf("\n You brought %s for questioning. \n", npcList[i]->name);
            return true;
        }
    }
    printf("\n Can't do that. That's not a valid suspect.\n");
    return false;
}

// goal: randomize which room gets what item
// param itemList[]: array of item pointers
// param map[]: array of room pointers whose items field may get set
// return: void
void randomizeItem(struct Item* itemList[], struct Room* map[]) { 
  for (int i = 0; i < 6; i++) {
   // gen random number  
   srand(clock());
   int r = rand() % 9;
   while (map[r]->items->next != NULL) {
      r = rand() % 9;
   }
   map[r]->items->next = itemList[i];
   // printf("\n %s item is %s\n", map[r]->name, itemList[i]->name);
  }
}

// goal: randomize which room each character points to
// param npcList[]: array of Character pointers whose room field will get set
// param map[]: array of room pointers
// return: void
void randomizeChar(struct Character* npcList[], struct Room* map[]) {
   srand(clock());
   for (int i = 0; i < 5; i++) {
      int r = rand() % 9;
      // printf("room %s character %s\n", map[r]->name, npcList[i]->name);
      npcList[i]->room = map[r];
   }
}

// goal: prints out which character in npcList is pointing to same room as avatar, avatarRoom
// param npcList[]: array of Character pointers that will be traversed
// param avatar: char* name of room that avatar is currently in
// return: void
void roomChar(struct Character* npcList[], char* avatarRoom) {
   bool found = false;
   for (int i = 0; i < 5; i++) {
      char* npcRoom = npcList[i]->room->name;
      if (strcmp(npcRoom, avatarRoom) == 0) {
         found = true;
         printf("  - %s\n", npcList[i]->name);
      }
   }
   if (!found) {
      printf(" - Seems like \033[0;31mno one\033[0m else is in here.\n");
   }
}

// goal: compares player's guess to answer and returns and prints results
// param answer[]: array of Character pointers that will be traversed
// param avatar: struct Character representing player
// param noun: char* of name of suspect that player guessed 
// return: true if guess is correct, false if guess is incorrect
bool clue(char* answer[], struct Character* avatar, char* noun) {
   int result = 0;
   // check for room match
   if (strcmp(answer[1], avatar->room->name) == 0) {
      result++;
      printf("  - \033[1;31mRoom Match!\033[0m The murder took place in the %s.\n", answer[1]);
   }
   // check for character match
   if (strcmp(answer[0], noun) == 0) {
      result++;
      printf("  - \033[1;31mCharacter Match!\033[0m Murderer was %s.\n", answer[0]);
   }
   // check for item match
   struct Item* inRoom = drop_item(avatar->room->items, answer[2], 1);
   struct Item* inBag = drop_item(avatar->inventory, answer[2], 1);
   if (inRoom != NULL || inBag != NULL) {
      result++;
      printf("  - \033[1;31mItem Match!\033[0m Item was %s.\n", answer[2]);
   } 
   if (result == 3) {
      // three matches, game won
      printf(" \n That's it! %s used %s in the %s.\n", answer[0], answer[2], answer[1]);
      return true;
   }
   // not enough correct matches, game continue or lost
   return false;
}