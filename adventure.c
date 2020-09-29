#include <stdio.h>
#include <string.h>
#include "characters.h"

// typedef to make my life easier :)
typedef struct Item* Item;
typedef struct Character* Character;
typedef struct Room* Room;

// ------------------------------------------------------------------------------------------------
// GAME!!!!!!!
int main() {
   // initialize items using item constructor in items.c
   Item desktop = item("desktop", NULL);
   Item goose = item("goose", NULL);
   Item projector = item("projector", NULL);
   Item spoon = item("spoon", NULL);
   Item detergent = item("detergent", NULL);
   Item knife = item("knife", NULL);
   // create array to store Items. makes it easy to traverse
   Item masterItem[6] = {desktop, goose, projector, spoon, detergent, knife};
   
   // initialize rooms using room constructor in rooms.c
   Room room1 = room("dorm room", "This reminds you of your dorm when you were a student. Are those inscriptions written in blood on the wall??", NULL, NULL, NULL, NULL, NULL);
   Room room2 = room("stairwell", "It's hard to see anything in the dark, but the steps are...sticky?", NULL, NULL, NULL, NULL, NULL);
   Room room3 = room("laundry room", "There's some dirty laundry strewn across the floor. Some of the machines have been knocked over.", NULL, NULL, NULL, NULL, NULL);
   Room room4 = room("lounge", "The TV is still on, illuminating the lounge partly. The furniture is in disarray and damaged.", NULL, NULL, NULL, NULL, NULL);
   Room room5 = room("elevator", "You press the buttons, but the door won't budge. A putrid smell emanates from the elevator.", NULL, NULL, NULL, NULL, NULL);
   Room room6 = room("bathroom","After your first step, you notice the floor is covered in water. Yikes.", NULL, NULL, NULL, NULL, NULL);
   Room room7 = room("hallway","Most of the doors are slightly ajar, but it's too dark to see anything else.", NULL, NULL, NULL, NULL, NULL);
   Room room8 = room("kitchen","The fridge is running! It's empty, sadly.", NULL, NULL, NULL, NULL, NULL);
   Room room9 = room("lobby","The vending machines look tempting!...but the prices are outrageous.", NULL, NULL, NULL, NULL, NULL);
   // create array to store Rooms. makes it easy to traverse
   Room map[9] = {room1, room2, room3, room4, room5, room6, room7, room8, room9};

   randomize(map); // shuffle map array to give rooms different positions
   createMap(map); // link rooms
   randomizeItem(masterItem, map); // randomize location of items

   // create player
   Character avatar = character("\033[1;31mSubbaswammy\033[0m", room1, NULL);

   // initialize characters using character constructor in characters.c
   Character violet = character("Violet", NULL, NULL);
   Character brick = character("Brick", NULL, NULL);
   Character rose = character("Rose", NULL, NULL);
   Character mustard = character("Mustard", NULL, NULL);
   Character teal = character("Teal", NULL, NULL);

   // create array to store Characters. makes it easy to traverse
   Character npcList[5] = {violet, brick, rose, mustard, teal};
   
   randomizeChar(npcList, map); // place characters in random rooms 
   srand(clock());
   int avatarRm = rand() % 9; // place avatar in random room
   avatar->room = map[avatarRm];
   
   // create answer using randomly-generated ints
   srand(clock());
   int npcIndex = rand() % 5;
   int roomIndex = rand() % 9;
   int itemIndex = rand() % 6;
   char* answer[3] = {npcList[npcIndex]->name, map[roomIndex]->name, masterItem[itemIndex]->name};
   
   // ----------------------------------------------------------------------
   // FOR GRADER: UNCOMMENT LINE BELOW TO SEE ANSWER TO GAME
   // printf("Answer: %s, %s, %s\n", answer[0], answer[1], answer[2]);
   // ----------------------------------------------------------------------

   // GAME START
   // Exposition
   printf("\n\033[0;31mCLUE\033[0m by Chloe for 230\n");
   printf("\nYou are %s.\n", avatar->name);
   printf("\nYou've been told to investigate an \033[0;31malum reunion party gone awry\033[0m at Dickinson.\n");
   printf("To be honest, you're surprised people were there. Dickinson's been \033[0;31mempty\033[0m for months.\n");
   printf("The doors are \033[0;31mlocked\033[0m, but you climb in from a half-opened window.\n");
   printf("Something about being in an \033[0;31mabandoned dormitory\033[0m creeps you out.\n"); 
   
   // instructions
   static int numGuesses = 0;
   printf("\nThere's 5 suspects: %s, %s, %s, %s, and %s.\n",violet->name, brick->name, rose->name, mustard->name, teal->name);
   printf("You have \033[0;31m10 tries\033[0m to guess the murderer correctly before word gets out and tarnishes UMass's reputation.\n");
   printf("\nType \033[0;31m'help'\033[0m to see the list of commands.\n"); 

   // main game loop
   while (numGuesses < 10) {
      // take input and tokenize
      char input[100];
      printf("\n--> ");
      if (fgets(input, sizeof(input), stdin) == NULL) {
         return 1;
      }
      // tokenize 3 inputs
      char *verb = strtok(input, " \n");
      char *noun = strtok(NULL, " \n");
      char *noun2 = strtok(NULL, " \n");

      // the if/else nest of commands
      if (noun2 == NULL) { 
         if (verb != NULL) {
            if (strcmp(verb, "clue") == 0) {
               //  clue command
               bool result = false;
               if (validSus(npcList, noun, avatar->room)) {
                  numGuesses++;
                  result = clue(answer, avatar, noun);
               }
               if (result) {
                  printf("\n \033[0;31mCongrats! You solved the murder!\033[0m \n");
                  break;
               } else {
                  printf("\n \033[0;31mYou didn't get all 3 matches.\033[0m\n");
                  printf("\n You have %i guesses remaining.\n", 10 - numGuesses);
               }
               if (numGuesses == 10) {
                  printf("\n That was your last guess. \n \033[0;31mGAME OVER.\033[0m\n");
                  break;
               }
            }
            else if (strcmp(verb, "help") == 0 && noun == NULL) {
               // help command
               printf("\n\033[1;31mHere's 5 suspects:\033[0m Violet, Brick, Rose, Mustard, and Teal.\n");
               printf("\n\033[1;31mHere's a map:\033[0m\n %s, %s, %s\n %s, %s, %s\n %s, %s, %s \n", map[0]->name, map[1]->name, map[2]->name, map[3]->name, map[4]->name, map[5]->name, map[6]->name, map[7]->name, map[8]->name);
               printf("\n\033[1;31mList of commands:\033[0m \n");
               printf("\n  - '\033[1;33mlook\033[0m' to see the room you are in.\n");
               printf("\n  - '\033[1;33minventory\033[0m' to see what you currently have in your inventory. \n");
               printf("\n  - '\033[1;33mclue CHARACTER\033[0m' to bring a character for questioning.\n");
               printf("\n  - '\033[1;33mtake ITEM\033[0m' to take an ITEM from the room. \n");
               printf("\n  - '\033[1;33mdrop ITEM\033[0m' to drop an ITEM into the room. \n");
               printf("\n  - '\033[1;33mgo DIRECTION\033[0m' to go north, south, east, or west.\n"); 
            }
            else if (strcmp(verb, "look") == 0 && noun == NULL) {
               printf("\n You are in the\033[1;31m %s.\033[0m \n %s\n", avatar->room->name, avatar->room->description);
               // print out the list of items
               // print out the list of characters
               printf("\n You \033[1;31mlook\033[0m around the %s and you see: \n", avatar->room->name);
               if (avatar->room->items->next != NULL) {
                  list(avatar->room->items);
               } else {
                  printf("  - No suspicious items. \n");
               }
               printf("\n \033[1;31mOther people\033[0m in the room: \n");
               // iterate through npcList, if npcList[i]->room->name strncmp with avatar room, print npcList[i]->name
               roomChar(npcList, avatar->room->name);
               printf("\n \033[1;31mYou can go:\033[0m");
               mapPrint(avatar->room);
            }
            else if (strcmp(verb, "go") == 0) {
               // goto will return the room to the specified direction
               char* oldRoom = avatar->room->name;
               goDir(avatar, noun);
            }
            else if (strcmp(verb, "Chloe") == 0) {
               // easter egg to reveal answer
               printf(" Answer: %s, %s, %s\n", answer[0], answer[1], answer[2]);
            }
            else if (strcmp(verb, "inventory") == 0 && noun == NULL) {
               //print out avatar's inventory
               printf("\n \033[0;31mYou decide to check inside your backpack.\033[0m \n");
               printf(" You have: \n");
               list(avatar->inventory);
            }
            else if (strcmp(verb, "scream") == 0 && noun == NULL) {
               // easter egg
               printf("\n \033[0;31mYou shout at the top of your lungs.\033[0m It echoes throughout the room.\n Are you okay?\n");
            }
            else if (strcmp(verb, "chicken") == 0) {
               // easter chicken
               printf("\n You pull \033[1;33m3 chicken tendies\033[0m from your pocket and eat them.\n Delicious. #1 dining, baby! \n");
            }         
            else if (strcmp(verb, "take") == 0 && noun != NULL) {
               // take command
               bool wasExchanged = exchange(avatar->inventory, avatar->room->items, noun);
               if (wasExchanged) {
                  printf("\n You added the\033[1;31m %s\033[0m to your backpack. \n", noun);
               } else {
                  printf("\n '%s' \033[0;31misn't in the room\033[0m. You didn't take anything.\n", noun);
               }
            }
            else if (strcmp(verb, "drop") == 0 && noun != NULL) {
               // drop command
               bool wasExchanged = exchange(avatar->room->items, avatar->inventory, noun);
               if (wasExchanged) {
                  printf("\n You dropped the\033[1;31m %s\033[0m from your backpack. \n", noun);
               } else {
                  printf("\n '%s' \033[0;31misn't in your bag\033[0m. You didn't drop anything.\n", noun);
               }
            } else {
               // for bad noun input
               printf("\n \033[0;31mYou can't do that.\033[0m\n");
            }
         } else {
            // for null verb
            printf("\n \033[0;31mSpeechless?\033[0m\nTake your time. Solving a mystery is hard.\n");
         }
      } else {
         // for bad third input
         printf("\n \033[0;31mYou can't have a third input.\033[0m\n");
      }
   }
   // free all items
   for (int i = 0; i < 6; i++) {
      free(masterItem[i]);
   }
   // free all rooms
   for (int i = 0; i < 9; i++) {
      free(map[i]);
   }
   // free all characters
   for (int i = 0; i < 5; i++) {
      free(npcList[i]);
   }
   // free yourself from text-adventure prison:)
   free(avatar);
   printf("\n Thanks for playing!\n");
   return 0;
}
