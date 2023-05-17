#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"
void draw_ship(obj *point)
{
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(point->x+(SIZE/3.0f),point->y-(2.0*(SIZE/3.0f)));
	glVertex2f(point->x-(SIZE/3.0f),point->y+(SIZE/3.0f));
	glVertex2f(point->x+(2.0f*(SIZE/3.0f)),point->y+(SIZE/3.0f));
	glEnd();
}