#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

obj* create_ship(){
    obj* ship = (obj*)malloc(sizeof(obj));
    ship->x = WINDOW_X / 2;
    ship->y = WINDOW_Y / 2 - WINDOW_Y / 4;

    ship->shape = SPACE_SHIP;
    return ship;
}

obj* create_enemy_ship(int count) {
    // Calculate the row and column based on the count
    int row = count / MAX_PER_ROW;
    int col = count % MAX_PER_ROW;

    // Define initial positions and offsets
    float initial_x = 1920 / 4;
    float initial_y = WINDOW_Y - 150;
    float offset_x = 100;
    float offset_y = 100;

    // Allocate memory for the enemy ship object
    obj* enemy_ship = (obj*) malloc(sizeof(obj));

    // Set the shape
    enemy_ship->shape = ENEMY_SHIP;

    // Calculate and set the position of the enemy ship
    if(row == 0) {
        enemy_ship->x = initial_x + offset_x * col;
        enemy_ship->y = initial_y - offset_y * row;
    }

    if(row == 1) {
        offset_x = 112;
        enemy_ship->x = initial_x - 50 + offset_x * col ;
        enemy_ship->y = initial_y - offset_y * row;
    }
    enemy_ship->initialX = enemy_ship->x;
    enemy_ship->initialY = enemy_ship->y;    
    return enemy_ship;
}

bullet* create_bullet(obj* ship){
    bullet* b = (bullet *)malloc(sizeof(bullet));
    b->x = ship->x;
    b->y = ship->y;
    b->present = true;

    return b;
}



//Comet object
comet* create_comet() {
    comet* c = (comet*)malloc(sizeof(comet));
    c->x = rand() % WINDOW_X; // Spawn at a random x position
    c->y = WINDOW_Y + COMET_HEIGHT; // Spawn just outside the top of the window
    c->speed = 1.0f + ((float)rand() / RAND_MAX) * 3.0f; // Random speed between 1 and 4
    return c;
}
