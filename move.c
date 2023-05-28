#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

void move_ship(obj* ship, bool* keyStates) {
    if(keyStates['w']) ship->y = fmin(ship->y + SPACE_SHIP_SPEED, WINDOW_X / 4);
    if(keyStates['a']) ship->x = fmax(ship->x - SPACE_SHIP_SPEED, SPACE_SHIP_WIDTH);
    if(keyStates['s']) ship->y = fmax(ship->y - SPACE_SHIP_SPEED, SPACE_SHIP_HEIGHT);
    if(keyStates['d']) ship->x = fmin(ship->x + SPACE_SHIP_SPEED, WINDOW_X - SPACE_SHIP_WIDTH);
}

void move_bullet(bullet* bullets[MAX_BULLETS], bool* bulletBufferFilled){
    int count = 0;
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i]) {
            if(bullets[i]->present) {
                bullets[i]->y += SPACE_SHIP_BULLET_SPEED;
                count++;
                if(bullets[i]->y >= WINDOW_Y) free(bullets[i]), bullets[i] = NULL;
            } else {
                free(bullets[i]);
                bullets[i] = NULL;
            }
        }
    }
    if(count >= MAX_BULLETS) *bulletBufferFilled = true;
    else *bulletBufferFilled = false;
}