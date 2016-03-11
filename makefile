
CC=gcc
CFLAGS= -g -std=c11

main: solve_cube.o cube_search_tree.o cube.o

solve_cube.o: solve_cube.h cube_search_tree.o

cube_search_tree.o: cube_search_tree.h cube.o

cube.o: cube.c cube.h

scratch: cube.c

clean :
	rm -rf *.o
