#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cube.h"

typedef struct node {
   cube * cube_state;
   struct node * parent;
   struct node * cw_moves[6];
   struct node * ccw_moves[6];
   struct node * half_moves[6];
} node_t;

void insert_one_move(node_t *, side, direction);
void insert_every_move(node_t *);
void print_tree(node_t * );

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
   turn_side(node -> cube_state, FRONT, CW);
   
   insert_every_move(node);
   print_tree(node);
   return EXIT_SUCCESS;
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

void insert_one_move(node_t * tree, side s, direction d) {
   
   node_t * new_node = malloc(sizeof(node_t));
   new_node -> cube_state = malloc(sizeof(cube));
   memcpy(new_node -> cube_state, tree -> cube_state, sizeof(cube));
   new_node -> parent = tree;
   
   turn_side(new_node -> cube_state, s, d);
   if (d == CW) {
      tree -> cw_moves[s] = new_node;
   } else if (d == CCW) {
      tree -> ccw_moves[s] = new_node;
   } else if (d == HALF) {
      tree -> half_moves[s] = new_node;
   }
}

void print_tree(node_t * tree) {

   if (tree == NULL) { return; }
   printf("%s\n", tree -> cube_state -> state);
   for (int i = 0; i < 6; i++) { print_tree(tree -> cw_moves[i]); }
   for (int i = 0; i < 6; i++) { print_tree(tree -> ccw_moves[i]); }
   for (int i = 0; i < 6; i++) { print_tree(tree -> half_moves[i]); }
}
