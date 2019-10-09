//SHITTY CODE--NOT WORTHY OF BEING READ

#include "setup.h"
#include<math.h>

struct Color{
	GLint r;
	GLint g;
	GLint b;
};

void drawCircle(GLint xc,float yc, int radius) {
	GLfloat step = 1/radius;
	GLfloat x, y;
	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = xc + (radius * cos(theta));
		y = yc + (radius * sin(theta));
		glVertex2i(x, y);
	}
}

void drawLine(float r, float th){
	GLint x1 = 0, y1 = 0, x2, y2;
	float m = tan(th);
	x2 = sqrt(pow(r,2)/(1+pow(m,2)));
	y2 = m*x2;
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	std::cout<<th;
}

void draw_pi(float th1, float th2, float th3, float th4, float th5){
	GLint radius = 200;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		drawCircle(0,0,radius);
		drawLine(radius, th1);
		drawLine(radius, th1+th2);
		drawLine(radius, th1+th2+th3);
		drawLine(radius, th1+th2+th3+th4);
		drawLine(radius, th1+th2+th3+th4 +th5);
	glEnd();
	glFlush();
}

float convertPerc(float p){
	return p*360;
}
/*
Color getColor(){
	Color temp;
	temp.r = rand();
	temp.g = rand();
	temp.b = rand();
	return temp;
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


void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

void color(float th, Color c){
	Color bgColor = {0,0,0}; //black screen color
	//x and y are points in btw pi's
	GLint x,y;	
	GLint x1 = 0, y1 = 0, x2, y2;
	float m = tan(th), r = 200;
	x2 = sqrt(pow(r,2)/(1+pow(m,2)));
	y2 = m*x2;
	x = (x1+x2)/2;
	y = (y1 + y2)/2;

	floodFill(x,y,bgColor,c);
}*/

void draw(){
	//displaying the pi Chart
	//portions of pie chart
	float p1 = 0.08, p2 = 0.32, p3 = 0.1, p4 = 0.30, p5 = 0.20;
	float th1, th2, th3, th4, th5;
	//obtaining angles from percentages
	th1 = convertPerc(p1);
	th2 = convertPerc(p2);	
	th3 = convertPerc(p3);
	th4 = convertPerc(p4);
	th5 = convertPerc(p5);
	draw_pi(th1,th2,th3,th4,th5);

	//obtaining colors to fill the pi chart
	/*Color c[5];
	for(int i = 0; i < 5; i++){
		c[i] = getColor();
	}
	//color pi chart
	color(th1, c[1]);
	color(th2, c[2]);
	color(th3, c[3]);
	color(th4, c[4]);
	color(th5, c[5]);*/
}