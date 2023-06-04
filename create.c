#include "header/includeHeaders.h"
#include "header/customTypes.h"
#include "header/constants.h"

bullet** original_enemy_bullets_pointer;
obj**    original_enemy_ship_pointer;
int*     last_enemy_bullet;

obj* create_ship(){
    obj* ship = (obj*)malloc(sizeof(obj));
    ship->x = WINDOW_X / 2;
    ship->y = WINDOW_Y / 2 - WINDOW_Y / 4;

    ship->shape = SPACE_SHIP;
    return ship;
}

obj* create_enemy_ship(int count) {
    // Calculate the row and column based on the count
    int row = count / MAX_PER_ROW;
    int col = count % MAX_PER_ROW;

    // Define initial positions and offsets
    float initial_x = 1920 / 4;
    float initial_y = WINDOW_Y - 150;
    float offset_x = 100;
    float offset_y = 100;

    // Allocate memory for the enemy ship object
    obj* enemy_ship = (obj*) malloc(sizeof(obj));

    // Set the shape
    enemy_ship->shape = ENEMY_SHIP;

    // Calculate and set the position of the enemy ship
    if(row % 2 == 0) {
        enemy_ship->x = initial_x + offset_x * col;
        enemy_ship->y = initial_y - offset_y * row;
    }

    else {
        offset_x = 112;
        enemy_ship->x = initial_x - 50 + offset_x * col ;
        enemy_ship->y = initial_y - offset_y * row;
    }
    enemy_ship->initialX = enemy_ship->x;
    enemy_ship->initialY = enemy_ship->y;    
    return enemy_ship;
}

bullet* create_bullet(obj* ship){
    bullet* b = (bullet *)malloc(sizeof(bullet));
    b->x = ship->x;
    b->y = ship->y;
    b->present = true;

    return b;
}

//Comet object
comet* create_comet() {
    comet* c = (comet*)malloc(sizeof(comet));
    c->x = rand() % WINDOW_X; // Spawn at a random x position
    c->y = WINDOW_Y + COMET_HEIGHT; // Spawn just outside the top of the window
    c->speed = 1.0f + ((float)rand() / RAND_MAX) * 3.0f; // Random speed between 1 and 4
    return c;
}

// Enemy Bullet creation

void add_bullet_to_buffer(int enemy_ship_number){
    if(original_enemy_ship_pointer[enemy_ship_number]) {
        original_enemy_bullets_pointer[*last_enemy_bullet] = create_bullet(original_enemy_ship_pointer[enemy_ship_number]);
        *last_enemy_bullet = (*last_enemy_bullet + 1) % MAX_ENEMY_BULLETS;
    }
}

void create_enemy_bullets(obj* enemy_ships[MAX_ENEMY_SHIPS], bullet* enemy_bullets[MAX_ENEMY_BULLETS], int* total_enemy_bullets) {
    original_enemy_bullets_pointer = enemy_bullets;
    original_enemy_ship_pointer = enemy_ships;
    last_enemy_bullet = total_enemy_bullets;
    for(int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        if(enemy_ships[i]) {
            float rand_num = (float)rand() / RAND_MAX;
            
            // Define the firing probability threshold
            float firingThreshold = 0.3;

            if (rand_num < firingThreshold) {
                glutTimerFunc(rand() % 1000, add_bullet_to_buffer, i);
            }
        }
    }
}

