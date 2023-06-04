#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

#include "header/draw.h"
#include "header/create.h"
#include "header/move.h"
#include "header/collision.h"

void initialize_all_objects();

GAME_STATE gameState;


// Bullet Variables
int bulletNumber = 0;
bool bulletBufferFilled = false;   
bullet* bullets[MAX_BULLETS];

int enemyBulletNumber = 0;
bullet* enemy_bullets[MAX_ENEMY_BULLETS];

// Ship Variables
bool keyStates[256];
obj* ship; // space_ship [ controlled by user ]

// Enemy Ship Variables
obj* enemy_ships[MAX_ENEMY_SHIPS]; // An array that contains pointers to enemy ships
float enemy_ship_angle = 0.0;

// Comet Variables
comet* comets[MAX_COMETS];

void init(){
    glClearColor(0, 0, 0, 1);
    glMatrixMode( GL_PROJECTION );
    // gluOrtho2D(0, WINDOW_X, 0, WINDOW_Y);
    glLoadIdentity();
    glOrtho(0, WINDOW_X, 0, WINDOW_Y, 0, 100.0);
    glEnable(GL_DEPTH_TEST);
}

void display(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Display code goes here

    // TODO: Use a for loop to display the enemy ships individually
    // or pass the array of enemy ships to a function and draw each enemy ship
    draw_background();
    if(gameState == GAME_START) {
        draw_ship(ship);
        for(int i = 0; i < MAX_ENEMY_SHIPS; i++) {
            if(enemy_ships[i]) {
                draw_enemy_ship(enemy_ships[i]);
            }
        }
        draw_bullets(bullets);
        draw_enemy_bullets(enemy_bullets);
        for(int i=0;i<MAX_COMETS;i++){
            if(comets[i]){
                draw_comet(comets[i]);
            }
        }
    }
    else if(gameState == MAIN_MENU) {
        // Implement Main Menu
        draw_menu();
    }
    else {
        // Game Over 
        draw_game_over();
        // Display Score
    }

    glutSwapBuffers();
}

void createObjects(){
    ship = create_ship();
    printf("Ship Created At [%f, %f]\n", ship->x, ship->y);

    // INITIALIZATION
    for(int i = 0; i < MAX_ENEMY_SHIPS; i++) enemy_ships[i] = NULL; // Initialize all enemy ships to NULL
    for(int i = 0; i < MAX_ENEMY_BULLETS; i++) enemy_bullets[i] = NULL; // Initialize all enemy bullets to NULL
    for(int i = 0; i < MAX_BULLETS; i++) bullets[i] = NULL;
    // CREATION

    for(int i = 0; i < ENEMY_COUNT; i++){
        enemy_ships[i] = create_enemy_ship(i); // 'i' is passed as a parameter denoting the count of the enemy ship, this is used to determine in which row the enemy ship is placed 
        // printf("%f %f\n", enemy_ships[i]->x, enemy_ships[i]->y);
    }

    for(int i=0;i< MAX_COMETS;i++){
        comets[i] = create_comet();
    }    
}

void create_enemy_bullets_helper(){
    if(gameState == GAME_START) {
        create_enemy_bullets(enemy_ships, enemy_bullets, &enemyBulletNumber);
        glutTimerFunc(1000, create_enemy_bullets_helper, 0);
    }
}

void keyPress(unsigned char key, int x, int y){
    keyStates[key] = 1;

    if(gameState == GAME_OVER && (key == 'p' || key == 'P')) { 
        initialize_all_objects();
    }

    else if(gameState != GAME_START && (key == 'p' || key == 'P') ) {
        gameState = GAME_START;
        glutTimerFunc(1000, create_enemy_bullets_helper, 0);
    }
}

void keyRelease(unsigned char key, int x, int y){
    keyStates[key] = 0;
}

void mouseClick(int btn, int state, int x, int y){
    if(gameState == GAME_START ) {
        // Implement Bullet Functions
        if(btn == 0 && !bulletBufferFilled && state) {
            bullet* b = create_bullet(ship);
            bullets[bulletNumber] = b;
            bulletNumber = ++bulletNumber % MAX_BULLETS;
        }
    } else if(gameState == MAIN_MENU) {
        if(btn == 0 && state == GLUT_DOWN) {
            if(x >= 900 && x <= 1000 && y >= 500 && y <= 599){
                // Start Game
                gameState = GAME_START;
                glutTimerFunc(1000, create_enemy_bullets_helper, 0);
            }
            else if(x >= 900 && x <= 1000 && y >= 600 && y <= 710) 
                exit(0); // Exit the Game 
        }
    } else {
        // Implement Game Over Page Mouse clicks
    }
}

void refresh(){
    // Update Position of space ships / enemy ships etc... 
    move_ship(ship, keyStates);
    move_bullet(bullets, &bulletBufferFilled);
    move_enemy_bullet(enemy_bullets);
    move_enemy_ships(enemy_ships, &enemy_ship_angle);
    move_comets(comets);

    check_ship_bullet_collision(bullets, enemy_ships, comets);
    check_enemy_bullet_collision(ship, enemy_bullets, comets);

    glutPostRedisplay();
    glutTimerFunc(16, refresh, 0);
}

void initialize_all_objects(){
    gameState = MAIN_MENU;
    createObjects();
    set_up_images(); // Present in draw.c 
}

int main(int argc, char** argv){
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow("SPACE INVADERS");

    init();
    initialize_all_objects();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    
    glutMouseFunc(mouseClick);

    glutTimerFunc(0, refresh, 0);

    glutMainLoop();
}