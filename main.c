#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

#include "header/draw.h"
#include "header/create.h"
#include "header/move.h"

GAME_STATE gameState;

bool keyStates[256];
obj* ship; // space_ship [ controlled by user ]
obj* enemy_ships[MAX_ENEMY_SHIPS]; // An array that contains pointers to enemy ships

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
    if(gameState == GAME_START) {
        draw_ship(ship);
    }
    else if(gameState == MAIN_MENU) {
        // Implement Main Menu
        glColor3f(1, 1, 1);

        // Define the titles and their positions
        const char* titles[] = {"SPACE INVADERS", "START", "EXIT"};
        const int numTitles = sizeof(titles) / sizeof(titles[0]);
        const float yOffset[] = {WINDOW_X / 4 + WINDOW_Y / 2, WINDOW_Y / 2 - WINDOW_Y / 30, WINDOW_Y / 2 - WINDOW_Y / 10};

        void* font = GLUT_BITMAP_HELVETICA_18;

        for (int i = 0; i < numTitles; i++) {
            const char* title = titles[i];
            int titleWidth = 0;
            if(i != 0) 
                glColor3f(0, 1, 0);
            for (int j = 0; title[j] != '\0'; j++) {
                titleWidth += glutBitmapWidth(font, title[j]);
            }

            glRasterPos2i(WINDOW_X / 2 - titleWidth / 2, yOffset[i]);

            for (int j = 0; title[j] != '\0'; j++) {
                glutBitmapCharacter(font, title[j]);
            }
        }

        // Reset the text color
        glColor3f(1, 1, 1);
    }
    else {
        // Game Over 
        // Display Score
    }

    glutSwapBuffers();
}

void createObjects(){
    ship = create_ship();
    printf("Ship Created At [%f, %f]\n", ship->x, ship->y);

    // INITIALIZATION
    for(int i = 0; i < MAX_ENEMY_SHIPS; i++) enemy_ships[i] = NULL; // Initialize all enemy ships to NULL

    // CREATION

    for(int i = 0; i < ENEMY_COUNT; i++){
        enemy_ships[i] = create_enemy_ship(i); // 'i' is passed as a parameter denoting the count of the enemy ship, this is used to determine in which row the enemy ship is placed 
        // printf("%f %f\n", enemy_ships[i]->x, enemy_ships[i]->y);
    }

    
}

void keyPress(unsigned char key, int x, int y){
    keyStates[key] = 1;
}

void keyRelease(unsigned char key, int x, int y){
    keyStates[key] = 0;
}

void refresh(){

    // Update Position of space ships / enemy ships etc... 
    move_ship(ship, keyStates);
    glutPostRedisplay();
    glutTimerFunc(16, refresh, 0);
}

void initialize_all_objects(){
    gameState = MAIN_MENU;
    createObjects();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow("SPACE INVADERS");

    init();
    initialize_all_objects();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    
    glutTimerFunc(0, refresh, 0);

    printf("\n");

    printf("Added by user1\n");


    glutMainLoop();
}