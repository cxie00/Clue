Hello!!!

    Link to Youtube Demo: https://youtu.be/33Id0Z9RXRc
    My implementation features a main function where the initialization, input, and game loop occur. I initialize
the three main data structures: Items, Rooms, and Characters. They are defined in their respective .h and .c files
as structs with relevant functions defined. 

Files and details into the files:
    - Makefile 
        - type 'make' in the terminal to compile files and 'make clean' to remove .o files. 
    - adventure.c 
        - int main()
            - Initialization: has hard coded items, characters, and rooms that are created with . 
            - Random: I randomize the map, items, and characters with a respective randomize function. 
            - Win condition: I randomly choose an item, character, and room after all the initialization as ANSWER.
            - Loss: I keep track of guesses, and the while loop executes guesses is < 10. If >, loop breaks.
            - Input: I take in and tokenzie string inputs using fgets() and strok().
            - Commands: I strcmp the input with commands like 'help', 'look', etc in a nested if/else statement.
            - Win: If user gets 3 matches on 'clue', win message is displayed and loop breaks.
            - Free: When loop breaks, all pointers are FREED at the end of main().
    - items.c (some important functions, but not all)
        - struct Item* item defined.
        - item() contructor to create an item, some getters and setter functions.
        - drop_item(), add_item() to remove an item from a linked list and to add an item to a linked list.
        - list() lists all the items in a linked list (used to list items in room, in inventory, and characters in a room).
    - rooms.c (some important functions)
        - struct Room* room defined.
        - room() constructor to create a room with some getters and setter functions.
        - randomize() and swap(), createMap() for randomizing the rooms and connecting game board.
    - characters.c (some important functions)
        - move_character() to move any character
        - go_Dir() specifically for 'go' command of player character 
        - clue() that checks if player's room pointer is same as answer, if character is in room, 
            if room or player have answer item.

Errors checked:
    - trying to 'go' null or invalid directions 
    - trying to call 'clue' on null or invalid Characters
    - null input 
    - dropping or adding null or invalid Items
    - three or more inputs

P.S. 3 easter eggs in if/else (1 of them very useful)

9/27/20
    - added colors to make the game look better