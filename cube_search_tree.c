#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cube_search_tree.h"

void insert_one_move(node_t * tree, side s, direction d) {

   node_t * new_node = malloc(sizeof(node_t));
   new_node -> cube_state = malloc(sizeof(cube));
   strcpy(new_node -> move_taken, "test test");
   memcpy(new_node -> cube_state, tree -> cube_state, sizeof(cube));
   new_node -> parent = tree;

   switch(d){
   case CW: {
      switch (s) {
      case FRONT: { strcpy(new_node -> move_taken, "FRONT CW"); break; }
      case TOP: { strcpy(new_node -> move_taken, "TOP CW"); break; }
      case BACK: { strcpy(new_node -> move_taken, "BACK CW"); break; }
      case BOTTOM: { strcpy(new_node -> move_taken, "BOTTOM CW"); break; }
      case RIGHT: { strcpy(new_node -> move_taken, "RIGHT CW"); break; }
      case LEFT: { strcpy(new_node -> move_taken, "LEFT CW"); break; }
      } break;
   }
   case CCW: {
      switch (s) {
      case FRONT: { strcpy(new_node -> move_taken, "FRONT CCW"); break; }
      case TOP: { strcpy(new_node -> move_taken, "TOP CCW"); break; }
      case BACK: { strcpy(new_node -> move_taken, "BACK CCW"); break; }
      case BOTTOM: { strcpy(new_node -> move_taken, "BOTTOM CCW"); break; }
      case RIGHT: { strcpy(new_node -> move_taken, "RIGHT CCW"); break; }
      case LEFT: { strcpy(new_node -> move_taken, "LEFT CCW"); break; }
      } break;
   }
   case HALF: {
      switch (s) {
      case FRONT: { strcpy(new_node -> move_taken, "FRONT HALF"); break; }
      case TOP: { strcpy(new_node -> move_taken, "TOP HALF"); break; }
      case BACK: { strcpy(new_node -> move_taken, "BACK HALF"); break; }
      case BOTTOM: { strcpy(new_node -> move_taken, "BOTTOM HALF"); break; }
      case RIGHT: { strcpy(new_node -> move_taken, "RIGHT HALF"); break; }
      case LEFT: { strcpy(new_node -> move_taken, "LEFT HALF"); break; }
      }
   } break;
   }
   
   turn_side(new_node -> cube_state, s, d);
   if (d == CW) {
      tree -> cw_moves[s] = new_node;
   } else if (d == CCW) {
      tree -> ccw_moves[s] = new_node;
   } else if (d == HALF) {
      tree -> half_moves[s] = new_node;
   }
}

void insert_every_CCW_move(node_t * tree) {
   for (side s = TOP; s <= BOTTOM; s++) { insert_one_move(tree, s, CCW); }
}
void insert_every_CW_move(node_t * tree) {
   for (side s = TOP; s <= BOTTOM; s++) { insert_one_move(tree, s, CW); }
}
void insert_every_HALF_move(node_t * tree) {
   for (side s = TOP; s <= BOTTOM; s++) { insert_one_move(tree, s, HALF); }
}

void insert_every_move(node_t * tree) {
   
   insert_every_HALF_move(tree);
   insert_every_CCW_move(tree);
   insert_every_CW_move(tree);
}

node_t * instantiate_cube_tree(cube * c) {

   node_t * new_root = malloc(sizeof(node_t));
   new_root -> cube_state = c;
   strcpy(new_root -> move_taken,"Initial Cube\n");
   
   return new_root;
}

void print_tree(node_t * tree) {

   if (tree == NULL) { return; }
   printf("%s %s\n", tree -> cube_state -> state, tree -> move_taken);
   for (int i = 0; i < 6; i++) { print_tree(tree -> cw_moves[i]); }
   for (int i = 0; i < 6; i++) { print_tree(tree -> ccw_moves[i]); }
   for (int i = 0; i < 6; i++) { print_tree(tree -> half_moves[i]); }
}
/*
int main() {

   node_t * node = malloc(sizeof(node_t));
   node -> cube_state = malloc(sizeof(cube));
   for (int k = 0; k < 6; k++) {
      for (int i = 0; i < 3; i++){
	 for (int j = 0; j < 3; j++){
	    node -> cube_state -> sides[k].face[i][j] = k + 'A';
	 }
      }
   }
   
   insert_every_move(node);
   print_tree(node);
   return EXIT_SUCCESS;
}
*/
