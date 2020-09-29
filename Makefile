rule1: adventure.o items.o rooms.o characters.o
	gcc -std=c99 adventure.o items.o rooms.o characters.o -o play

adventure.o: adventure.c
	gcc -std=c99 adventure.c -c

items.o: items.c
	gcc -std=c99 items.c -c

rooms.o: rooms.c
	gcc -std=c99 rooms.c -c

clean: 
	rm *.o