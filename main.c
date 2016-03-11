#include <stdlib.h>
#include <stdio.h>
#include "solve_cube.h"

int main(){
   printf("flag 0");
   // Sets up a solved cube, and a cube to solve
   cube *c1 = malloc(sizeof(cube));
   cube *c2 = malloc(sizeof(cube));
   for (int k = 0; k < 6; k++) {
      for (int i = 0; i < 3; i++){
	 for (int j = 0; j < 3; j++){
	    c1 -> sides[k].face[i][j] = k + 'A';
	    c2 -> sides[k].face[i][j] = k + 'A';
	 }
      }
   }
   printf("flag 3");
   turn_side(c2, FRONT, CW);
   brute_force(c2, c1);
   return EXIT_SUCCESS;
}
