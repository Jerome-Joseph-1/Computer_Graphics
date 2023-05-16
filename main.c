#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

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
    glBegin(GL_POLYGON);
        glVertex2f(10, 10);
        glVertex2f(100, 10);
        glVertex2f(100, 100);
        glVertex2f(10, 100);
    glEnd();

    glutSwapBuffers();
}

void refresh(){

    // Update Position of space ships / enemy ships etc... 

    glutTimerFunc(16, refresh, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow("SPACE INVADERS");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, refresh, 0);

    glutMainLoop();
}