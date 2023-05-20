#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

void move_ship(obj* ship, bool* keyStates) {
    if(keyStates['w']) ship->y += SPACE_SHIP_SPEED;
    if(keyStates['a']) ship->x -= SPACE_SHIP_SPEED;
    if(keyStates['s']) ship->y -= SPACE_SHIP_SPEED;
    if(keyStates['d']) ship->x += SPACE_SHIP_SPEED;
}