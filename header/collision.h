#ifndef COLLISION_H
#define COLLISION_H

void check_ship_bullet_collision(bullet* bullets[MAX_BULLETS], obj* enemy_ships[MAX_ENEMY_SHIPS], comet* comets[MAX_COMETS]);
void check_enemy_bullet_collision(obj* ship, bullet* enemy_bullets[MAX_ENEMY_BULLETS]);

#endif 