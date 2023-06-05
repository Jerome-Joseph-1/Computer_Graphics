#ifndef CONSTANT_S
#define CONSTANT_S

#define WINDOW_X 1920
#define WINDOW_Y 1080


// HP CONSTANTS
#define SHIP_HP 4
#define ENEMY_SHIP_HP 7
#define SENTRY_HP 10

// SHAPE CONSTANTS
#define SPACE_SHIP 1
#define ENEMY_SHIP 2 
#define SENTRY 3

// SIZE CONSTANTS
#define SPACE_SHIP_WIDTH 50
#define SPACE_SHIP_HEIGHT 95

#define ENEMY_SHIP_WIDTH 75
#define ENEMY_SHIP_HEIGHT 75


#define BULLET_WIDTH 18
#define BULLET_HEIGHT 70

#define SENTRY_WIDTH 133
#define SENTRY_HEIGHT 200

//SIZE
#define SIZE 5

// SPEED CONSTANTS
#define SPACE_SHIP_SPEED 5
#define SPACE_SHIP_BULLET_SPEED 15
#define ENEMY_SHIP_SPEED 0.0095
#define ENEMY_SHIP_BULLET_SPEED 10


// MAX COUNT CONSTANTS 
#define MAX_ENEMY_SHIPS 100
#define ENEMY_COUNT 16
#define MAX_PER_ROW 8 // Denotes the number of enemy ships per row

#define MAX_BULLETS 5 // Denotes max number of bullets that can be present on screen
#define MAX_ENEMY_BULLETS 100 // Denotes max number of `enemy` bullets that can be present on screen

//COMETS
#define MAX_COMETS 5
#define COMET_WIDTH 75
#define COMET_HEIGHT 150
#define MAX_SENTRIES 2

#endif