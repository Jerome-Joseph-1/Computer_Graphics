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