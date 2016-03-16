#include <stdlib.h>
#include <stdio.h>
#include "solve_cube.h"

int main(){
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
   //printf("flag 3\n");
   
   node_t * t = instantiate_cube_tree(c1);
   make_one_layer(t);
   make_one_layer(t -> cw_moves[0]);
   print_tree(t);
   //brute_force(c2, c1);
   return EXIT_SUCCESS;
}
