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
      // big old segfault right here mhmm
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

void make_one_layer(cube * initial) {

   node_t * new_cube_tree = instantiate_cube_tree(initial);
   insert_every_move(new_cube_tree);
   print_tree(new_cube_tree);
}

void brute_force(cube * initial_state, cube * solution_state) {

   node_t * tree_root = instantiate_cube_tree(initial_state);
   node_t * node_pointer = tree_contains_cube(tree_root, solution_state);
   while (node_pointer == NULL) {
      insert_every_move(tree_root);
      node_pointer = tree_contains_cube(tree_root, solution_state);
   }
   print_moveset(node_pointer);
}
