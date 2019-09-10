#include<iostream>
#include<GL/glut.h>

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1,1,1);
    glPointSize(1.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);
}

void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void draw();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    //bitmask(data usedfoe bitwise operations) to select a single buffered mode
    //rgb is the color mode selected--ALPHA and LUMINANCE can also be chosen
    glutInitDisplayMode(GLUT_SINGLE | GLUT_LUMINANCE);
    glutInitWindowSize(1000,900);
    glutInitWindowPosition(500,0);
    glutCreateWindow("Pixel Drawing");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}