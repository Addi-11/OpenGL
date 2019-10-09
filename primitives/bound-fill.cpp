#include <math.h>
#include <GL/glut.h>
#include<iostream>

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init() {
	glClearColor(0, 0, 0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void bfill(GLint x, GLint y, Color boundColor, Color newColor){

    //to get the current pixel color
    Color color = getPixelColor(x,y);

    //stop filling as soon as getpixel color == boundary color
    if(color.r != boundColor.r && color.g != boundColor.g && color.b != boundColor.b){
        setPixelColor(x, y, newColor);
        bfill(x+1, y, boundColor, newColor);
        bfill(x, y+1, boundColor, newColor);
        bfill(x-1, y, boundColor, newColor);
        bfill(x, y-1, boundColor, newColor);
    }
    return;
}

void onMouseClick(int button, int state, int x, int y)
{
	Color newColor = {1.0f, 0.07f, 0.85f};
	Color boundColor = {1.0f, 1.0f, 1.0f};//white of the boundary

	bfill(100, 100, boundColor, newColor);
}

void display(void) {
	Point pt = {320, 240};
	GLfloat radius = 100;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
        glVertex2i(200,406);
        glVertex2i(20,56);
        glVertex2i(20,56);
        glVertex2i(300,96);
        glVertex2i(300,96);
        glVertex2i(200,406);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}