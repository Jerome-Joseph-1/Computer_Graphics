#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

extern GAME_STATE gameState;
extern int score;

void move_ship(obj* ship, bool* keyStates) {
    if(ship->hp > 0) {
        if(keyStates['w']) ship->y = fmin(ship->y + SPACE_SHIP_SPEED, WINDOW_X / 4);
        if(keyStates['a']) ship->x = fmax(ship->x - SPACE_SHIP_SPEED, SPACE_SHIP_WIDTH);
        if(keyStates['s']) ship->y = fmax(ship->y - SPACE_SHIP_SPEED, SPACE_SHIP_HEIGHT);
        if(keyStates['d']) ship->x = fmin(ship->x + SPACE_SHIP_SPEED, WINDOW_X - SPACE_SHIP_WIDTH);
    } else {
        gameState = GAME_OVER;
    }
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

void move_enemy_ships(obj* enemy_ships[MAX_ENEMY_SHIPS], float* theta){
    int major_axis = 250, minor_axis = 100;
    for(int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        if(enemy_ships[i]) {
            if(enemy_ships[i]->hp > 0) {
                enemy_ships[i]->x = enemy_ships[i]->initialX + major_axis * cos(*theta);
                enemy_ships[i]->y = enemy_ships[i]->initialY + minor_axis * sin(*theta);
            } else {
                score++;
                free(enemy_ships[i]);
                enemy_ships[i] = NULL;
            }
        }
    }
    *theta -= ENEMY_SHIP_SPEED;

    if(*theta < -6.248) *theta = 0;
}

//move comets
void move_comets(comet* comets[MAX_COMETS]) {
    for (int i = 0; i < MAX_COMETS; i++) {
        if(comets[i]){
        comets[i]->y -= comets[i]->speed;

        if (comets[i]->y < 0) {
            comets[i]->y = WINDOW_Y;  // Set comet y-coordinate to the top of the window
        }
    }}
}

// Move enemy bullets 

void move_enemy_bullet(bullet* enemy_bullets[MAX_ENEMY_BULLETS]) {
    for(int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if(enemy_bullets[i]) {
            if(enemy_bullets[i]->present) {
                enemy_bullets[i]->y -= ENEMY_SHIP_BULLET_SPEED;
                if(enemy_bullets[i]->y < 0) free(enemy_bullets[i]), enemy_bullets[i] = NULL;
            } else {
                free(enemy_bullets[i]);
                enemy_bullets[i] = NULL;
            }
        } 
    }
}
