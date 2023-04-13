OPT = -Wall
OBJ = main.o deque.o fighter.o thread_stuff.o scenario.o stats.o

piratewars:	$(OBJ)
	gcc $(OPT) -o piratewars $(OBJ) -lpthread

main.o: main.c defs.h
	gcc $(OPT) -c main.c

thread_stuff.o: thread_stuff.c defs.h
	gcc $(OPT) -c thread_stuff.c

stats.o: stats.c defs.h
	gcc $(OPT) -c stats.c

scenario.o: scenario.c defs.h
	gcc $(OPT) -c scenario.c

deque.o:	deque.c defs.h
	gcc $(OPT) -c deque.c

fighter.o:	fighter.c defs.h
	gcc $(OPT) -c fighter.c

clean:
	rm -f $(OBJ) piratewars

