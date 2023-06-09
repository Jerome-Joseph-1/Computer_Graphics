#ifndef MOVE_H
#define MOVE_H

void move_ship(obj*, bool*);
void move_bullet(bullet* bullets[MAX_BULLETS], bool* bulletBufferFilled);
void move_enemy_ships(obj* enemy_ships[MAX_ENEMY_SHIPS], float* angle);
void move_comets(comet* comets[MAX_COMETS]);

void move_enemy_bullet(bullet* enemy_bullets[MAX_ENEMY_BULLETS]);

#endif