#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

#include "header/draw.h"
#include "header/create.h"
#include "header/move.h"
obj* ship; // space_ship [ controlled by user ]
bool keyStates[256];

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


    // Demo [ JUST TO TEST display() func ]  
    glColor3f(1, 0, 0);
    draw_ship(ship);

    glutSwapBuffers();
}

void createObjects(){
    ship = create_ship();
    printf("Ship Created At [%f, %f]\n", ship->x, ship->y);
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

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow("SPACE INVADERS");

    init();
    createObjects();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    
    glutTimerFunc(0, refresh, 0);

    printf("\n");

    printf("Added by user1\n");


    glutMainLoop();
}