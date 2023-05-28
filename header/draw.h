#ifndef DRAW_H
#define DRAW_H

//function prototype of draw_ship

void draw_ship(obj *point);
void draw_menu();
void draw_background();

// functions to load textures
void set_up_images();

void draw_bullets(bullet* bullets[MAX_BULLETS]);


#endif