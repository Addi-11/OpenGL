//TO DO -- REPLACE STRUCT WITH CLASSES
#include "setup.h"

struct Point{
	GLint x;
	GLint y;
};
//inheritence..to do
struct Line{
	//starting points of line
	struct Point p1;
	//ending points of line
	struct Point p2;
};


void translate(struct Line oldpt, struct Point chgpt){
	oldpt.x1 += chgpt.x;
	oldpt.y += chgpt.y; 
	drawLine();
}

void drawLine(struct Line pt1, struct Line pt2){
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(pt1.x,pt1.y);
	glVertex2i(pt2.x,pt2.y);
    glEnd();
    glFlush();
}

void draw(){
	//draw a line
	struct  Point pt1 = {-50,100};
	struct Point pt2 = {60,200};
	drawLine( pt1, pt2);
}