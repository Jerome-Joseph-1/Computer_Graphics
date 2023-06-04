#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

bool bullet_hits_enemy(int x, int y, obj* enemy) {
    if( x >= enemy->x - ENEMY_SHIP_WIDTH / 2  && x <= enemy->x + ENEMY_SHIP_WIDTH / 2 && y >= enemy->y - ENEMY_SHIP_HEIGHT / 2  && y <= enemy->y + ENEMY_SHIP_HEIGHT / 2)
        return true;
    return false;
}

bool bullet_hits_ship(int x, int y, obj* ship) {
    if( x >= ship->x - SPACE_SHIP_WIDTH / 2  && x <= ship->x + SPACE_SHIP_WIDTH / 2 && y >= ship->y - SPACE_SHIP_HEIGHT / 2  && y <= ship->y + SPACE_SHIP_HEIGHT / 2)
        return true;
    return false;
}

void check_ship_bullet_collision(bullet* bullets[MAX_BULLETS], obj* enemy_ships[MAX_ENEMY_SHIPS], comet* comets[MAX_COMETS]) {
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i]) {
            for(int j = 0; j < MAX_ENEMY_SHIPS; j++) {
                if(enemy_ships[j]) {
                    if(bullet_hits_enemy(bullets[i]->x, bullets[i]->y, enemy_ships[j])) {
                        bullets[i]->present = false;
                        enemy_ships[j]->hp--;
                    }
                }
            }
        }
    }
}
void check_enemy_bullet_collision(obj* ship, bullet* enemy_bullets[MAX_ENEMY_BULLETS]) {
    for(int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if(enemy_bullets[i]) {
            if(bullet_hits_ship(enemy_bullets[i]->x, enemy_bullets[i]->y, ship)) {
                enemy_bullets[i]->present = false;
                ship->hp--;
            }
        }        
    }
}
