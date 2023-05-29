#ifndef DRAW_H
#define DRAW_H

//function prototypes of draw_*

void draw_ship(obj *point);
void draw_menu();
void draw_background();
void draw_enemy_ship(obj* enemy_ship);
void draw_bullets(bullet* bullets[MAX_BULLETS]);

// functions to load textures
void set_up_images();


#endif