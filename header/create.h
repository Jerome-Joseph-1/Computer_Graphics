#ifndef CREATE_H
#define CREATE_H

obj* create_ship();
obj* create_enemy_ship(int count);
bullet* create_bullet(obj* ship);
comet* create_comet();
obj* create_sentry(float x, float y);
void create_enemy_bullets(obj* enemy_ships[MAX_ENEMY_SHIPS], bullet* enemy_bullets[MAX_ENEMY_BULLETS], int* enemyBulletNumber);

#endif