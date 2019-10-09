// g++ basic.cpp -lGL -lGLU -lglut -lm
#include<iostream>
#include<GL/glut.h>

//initialization
void init()
{
    //background colour
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //colour of the pixel
    //f--color in float :: i--int :: s--short
    glColor3f(0.98, 0.7, 0.); //rgba in floats
    glPointSize(5.0);
    //specifeis matrix stack for current operations
    //MODELVIEW, TEXTURE, COLOR
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //setting axis range in both directions
    gluOrtho2D(-780,780,-420,420);
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT); //here bitmask is performed AND-ing to clear screen
    //Triangles
    glBegin(GL_POINTS);

    glVertex2i(0,0);
    glVertex2i(90,400);
    glVertex2i(230,100);

    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    //bitmask(data usedfoe bitwise operations) to select a single buffered mode
    //rgb is the color mode selected--ALPHA and LUMINANCE can also be chosen
    glutInitDisplayMode(GLUT_SINGLE | GLUT_LUMINANCE);
    glutInitWindowSize(1000,900);
    glutInitWindowPosition(500,0);

    //name to window
    glutCreateWindow("Pixel Drawing");
    init();

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}