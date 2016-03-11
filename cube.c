#include <stdlib.h>
#include <stdio.h>

typedef enum {TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM} side;
typedef enum {CW, CCW, HALF} direction;
typedef struct cube_face_tag { char face[3][3]; } cube_face;
typedef struct cube_tag { cube_face sides[6]; char state[54]; } cube;

void update_cube_state(cube *c) {

   for (side s = TOP; s <= BOTTOM; s++) {
      for (int i = 0; i < 3; i++) {
	 for (int j = 0; j < 3; j++) {
	    c -> state[s*9 + i*3 + j] = c -> sides[s].face[i][j];
	 }
      }
   }   
}

void print_cube(cube *c){

   int char_count = 0;
   int i,j;
   // print top side
   for (i = 0; i < 3; i++) {
      printf("        ");
      for (j = 0; j < 3; j++) {
	 //printf("%d ",c -> sides[TOP].face[i][j]);
	 printf("%c ",c -> sides[TOP].face[i][j]);
	 char_count += 2;
      }
      char_count++;
      printf("\n");
   }
   printf("\n");
   char_count++;
   // print middle four sides
   for (i = 0; i < 3; i++) {
      for (int side = LEFT; side <= BACK; side++){
	 for (j = 0; j < 3; j++) {
	    printf("%c ", c -> sides[side].face[i][j]);
	    char_count += 2;
	 }
	 char_count++;
	 printf("\t");
      }
      char_count++;
      printf("\n");
   }
   char_count++;
   printf("\n");
   // print bottom side
   for (i = 0; i < 3; i++) {
      char_count += 9;
      printf("        ");
      for (j = 0; j < 3; j++) {
	 //printf("%d ",c -> sides[BOTTOM].face[i][j]);
	 printf("%c ",c -> sides[BOTTOM].face[i][j]);
	 char_count += 2;
      }
      char_count++;
      printf("\n");
   }
   printf("----------------------------------------\n");
} 

void swap_two_numbers(cube *c, side s1, side s2, int ax, int ay, int bx, int by) {

   int temp = c -> sides[s1].face[ax][ay];
   c -> sides[s1].face[ax][ay] = c -> sides[s2].face[bx][by];
   c -> sides[s2].face[bx][by] = temp;
}

void flip_side_vert(cube *c, side s) {
   // Flips Vertically
   swap_two_numbers(c, s, s, 0, 0, 0, 2);
   swap_two_numbers(c, s, s, 1, 0, 1, 2);
   swap_two_numbers(c, s, s, 2, 0, 2, 2);

}
void flip_side_horiz(cube *c, side s) {
   // Flips Vertically
   swap_two_numbers(c, s, s, 0, 0, 2, 0);
   swap_two_numbers(c, s, s, 0, 1, 2, 1);
   swap_two_numbers(c, s, s, 0, 2, 2, 2);

}
void flip_side_diag(cube *c, side s) {

   swap_two_numbers(c, s, s, 1, 0, 0, 1);
   swap_two_numbers(c, s, s, 2, 1, 1, 2);
   swap_two_numbers(c, s, s, 0, 2, 2, 0);
}

void turn_side_only_clock(cube *c, side s) {

   flip_side_vert(c, s);
   flip_side_diag(c, s);
}
void turn_side_only_counter(cube *c, side s) {

   turn_side_only_clock(c, s);
   turn_side_only_clock(c, s);
   turn_side_only_clock(c, s);
}

void swap_sides(cube *c, side a_side, side b_side) {
   int temp;
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
	 temp = c -> sides[a_side].face[i][j];
	 c -> sides[a_side].face[i][j] = c -> sides[b_side].face[i][j];
	 c -> sides[b_side].face[i][j] = temp;
      }
   } 
}

void turn_top_counter(cube *c) {

   // store one adjacent side 
   int a = c -> sides[BACK].face[0][0];
   int b = c -> sides[BACK].face[0][1];
   int d = c -> sides[BACK].face[0][2];

   for (int i = 0; i < 3; i++) {
      swap_two_numbers(c, RIGHT, FRONT, 0, i, 0, i);
      swap_two_numbers(c,  BACK, FRONT, 0, i, 0, i);
      swap_two_numbers(c,  LEFT, FRONT, 0, i, 0, i);
   }

   //swap_two_numbers(c, BACK, 0, 0, 0, 2);

   c -> sides[LEFT].face[0][0] =  a;
   c -> sides[LEFT].face[0][1] =  b;
   c -> sides[LEFT].face[0][2] =  d;

   turn_side_only_clock(c, TOP);
}
void turn_top_clock(cube *c) {
   
   turn_top_counter(c);
   turn_top_counter(c);
   turn_top_counter(c);
}

void turn_cube_up(cube *c) {

   swap_sides(c, FRONT, BOTTOM);
   swap_sides(c, TOP, BOTTOM);
   swap_sides(c, BACK, BOTTOM);

   /* update the left and right */
   turn_side_only_counter(c, RIGHT);
   turn_side_only_clock(c, LEFT);

   flip_side_vert(c, BACK);
   flip_side_horiz(c, BACK);
   flip_side_vert(c, BOTTOM);
   flip_side_horiz(c, BOTTOM);
}
void turn_cube_down(cube *c) {

   turn_cube_up(c);
   turn_cube_up(c);
   turn_cube_up(c);
}
void turn_cube_clock(cube *c){

   swap_sides(c, FRONT, RIGHT);
   swap_sides(c, LEFT, RIGHT);
   swap_sides(c, BACK, RIGHT);

   // update the top and bottom
   turn_side_only_counter(c, TOP);
   turn_side_only_clock(c, BOTTOM);

}
void turn_cube_counter(cube *c) {

   turn_cube_clock(c);
   turn_cube_clock(c);
   turn_cube_clock(c);
}

void turn_side_clock(cube *c, side s) {

   switch (s) {

   case TOP: { turn_top_clock(c); break; }
   case FRONT : {
      turn_cube_up(c);
      turn_top_clock(c);
      turn_cube_down(c);
      break;
   }
   case BOTTOM : {
      turn_cube_up(c);
      turn_cube_up(c);
      turn_top_clock(c);
      turn_cube_down(c);
      turn_cube_down(c);
      break;
   }
   case BACK :  {
      turn_cube_down(c);
      turn_top_clock(c);
      turn_cube_up(c);
      break;
   }  
   case LEFT :  {
      turn_cube_counter(c);
      turn_side_clock(c, FRONT);
      turn_cube_clock(c);
      break;
   }
   case RIGHT : {
      turn_cube_clock(c);
      turn_side_clock(c, FRONT);
      turn_cube_counter(c);
      break;
   }
   }
}
void turn_side_counter(cube *c, side s) {

   turn_side_clock(c, s);
   turn_side_clock(c, s);
   turn_side_clock(c, s);
}

void turn_side(cube *c, side s, direction d) {

   if (d == CW) {
      turn_side_clock(c, s);
   } else if (d == CCW) {
      turn_side_counter(c, s);
   } else {
      turn_side_clock(c, s);
      turn_side_clock(c, s);
   }
   update_cube_state(c);
}
