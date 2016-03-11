
typedef enum {TOP, LEFT, FRONT, RIGHT, BACK, BOTTOM} side;
typedef enum {CW, CCW, HALF} direction;
typedef struct cube_face_tag { char face[3][3]; } cube_face;
typedef struct cube_tag { cube_face sides[6]; char state[54]; } cube;

void print_cube(cube *c);
void turn_side(cube *c, side s, direction d); 
