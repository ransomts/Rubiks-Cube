#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cube_search_tree.h"

bool cubes_equal(cube * c1, cube * c2) {

   return strcmp(c1 -> state, c2 -> state) == 0;
}

node_t * tree_contains_cube(node_t * tree, cube * solution_state){

   if (tree == NULL) { return NULL; }
   if (cubes_equal(tree -> cube_state, solution_state)) { return tree; }

   for (int i = 0; i < 6; i++) {
      cube * cw_move = tree -> cw_moves[i] -> cube_state;
      if (cubes_equal(cw_move, solution_state)) { return tree -> cw_moves[i]; }
      cube * ccw_move = tree -> ccw_moves[i] -> cube_state;
      if (cubes_equal(ccw_move, solution_state)) { return tree -> ccw_moves[i]; }
      cube * half_move = tree -> half_moves[i] -> cube_state;
      if (cubes_equal(half_move, solution_state)) { return tree -> half_moves[i]; }
   }

   return NULL;
}

void print_moveset(node_t * bottom_node) {

   node_t * node_pointer = bottom_node;
   while (node_pointer != NULL) {
      printf("%s\n", node_pointer -> move_taken);
      node_pointer = node_pointer -> parent;
   }
}

void brute_force(cube * initial_state, cube * solution_state) {

   printf("flag 1");
   
   node_t * initial_condition = malloc(sizeof(node_t));
   initial_condition -> cube_state = initial_state;
   strcpy(initial_condition -> move_taken, "Start State");

   printf("flag 2");

   node_t * node_pointer = tree_contains_cube(initial_condition, solution_state);
   while (node_pointer == NULL) {
      insert_every_move(initial_condition);
   }
   print_moveset(node_pointer);
}

