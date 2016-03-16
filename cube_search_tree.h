#include "cube.h"

typedef struct node {
   char move_taken[16];
   cube * cube_state;
   struct node * parent;
   struct node * cw_moves[6];
   struct node * ccw_moves[6];
   struct node * half_moves[6];
} node_t;

node_t * instantiate_cube_tree(cube * c);
void insert_every_CW_move(node_t *);
void insert_every_CCW_move(node_t *);
void insert_every_HALF_move(node_t *);
void insert_one_move(node_t *, side, direction);
void insert_every_move(node_t *);
void print_tree(node_t *);
