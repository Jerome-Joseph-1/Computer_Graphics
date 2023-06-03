#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"
comet comets[MAX_COMETS];
int numComets = 0;
int spawnTimer = 0;

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

void move_enemy_ships(obj* enemy_ships[MAX_ENEMY_SHIPS], float* theta){
    int major_axis = 250, minor_axis = 100;
    for(int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        if(enemy_ships[i]) {
            enemy_ships[i]->x = enemy_ships[i]->initialX + major_axis * cos(*theta);
            enemy_ships[i]->y = enemy_ships[i]->initialY + minor_axis * sin(*theta);
        }
    }
    *theta -= ENEMY_SHIP_SPEED;
<<<<<<< HEAD
    if(*theta < -(2 * 3.141598)) *theta = 0;
}
=======
    if(*theta < -6.248) *theta = 0;
}




//move comets
void move_comets() {
    for (int i = 0; i < numComets; i++) {
        comets[i].y -= comets[i].speed;

        if (comets[i].y < 0) {
            for (int j = i; j < numComets - 1; j++) {
                comets[j] = comets[j + 1];
            }
            numComets--;
            i--;
        }
    }

    // Check if there's space to spawn a new comet
    if (numComets < MAX_COMETS && spawnTimer <= 0) {
        // Generate random x-coordinate for the comet spawn
        float spawnX = rand() % WINDOW_X;

        // Create a new comet at the top of the screen
        comet newComet;
        newComet.x = spawnX;
        newComet.y = WINDOW_Y;
        newComet.speed = 2.0; // Adjust the speed as desired

        comets[numComets] = newComet;
        numComets++;

        // Reset spawn timer
        spawnTimer = SPAWN_DELAY;
    }

    // Decrease the spawn timer
    spawnTimer--;
}
>>>>>>> 3a12695 (changes made in order to implement comets)
