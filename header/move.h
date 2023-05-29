#ifndef MOVE_H
#define MOVE_H

void move_ship(obj*, bool*);
void move_bullet(bullet* bullets[MAX_BULLETS], bool* bulletBufferFilled);
void move_enemy_ships(obj* enemy_ships[MAX_ENEMY_SHIPS], float* angle);

#endif