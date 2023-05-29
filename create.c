#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

obj* create_ship(){
    obj* ship = (obj*)malloc(sizeof(obj));
    ship->x = WINDOW_X / 2;
    ship->y = WINDOW_Y / 2 - WINDOW_Y / 4;

    ship->shape = SPACE_SHIP;
    ship->sizeX = SPACE_SHIP_WIDTH;
    ship->sizeY = SPACE_SHIP_HEIGHT;
    return ship;
}

obj* create_enemy_ship(int count) {
    // Calculate the row and column based on the count
    int row = count / MAX_PER_ROW;
    int col = count % MAX_PER_ROW;

    // Define initial positions and offsets
    float initial_x = 500;
    float initial_y = WINDOW_Y - 300;
    float offset_x = ENEMY_SHIP_WIDTH;
    float offset_y = ENEMY_SHIP_HEIGHT;

    // Allocate memory for the enemy ship object
    obj* enemy_ship = (obj*) malloc(sizeof(obj));

    // Set the shape and dimensions of the enemy ship
    enemy_ship->shape = ENEMY_SHIP;
    enemy_ship->sizeX = ENEMY_SHIP_WIDTH;
    enemy_ship->sizeY = ENEMY_SHIP_HEIGHT;

    // Calculate and set the position of the enemy ship
    enemy_ship->x = initial_x + offset_x * col;
    enemy_ship->y = initial_y - offset_y * row;
    
    return enemy_ship;
}

bullet* create_bullet(obj* ship){
    bullet* b = (bullet *)malloc(sizeof(bullet));
    b->x = ship->x;
    b->y = ship->y;
    b->present = true;

    return b;
}