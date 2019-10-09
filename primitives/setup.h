//TO DO---ADD mouseClickFunct only in bound and flood
//Function redefined in color filling algo and not defined in others
#include<iostream>
#include<GL/glut.h>


void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(1.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-800,800,-800,800);
}

void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void draw();
//void onMouseClick(int btn, int state,int x, int y);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    //bitmask(data usedfoe bitwise operations) to select a single buffered mode
    //rgb is the color mode selected--ALPHA and LUMINANCE can also be chosen
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,900);
    glutInitWindowPosition(500,0);
    glutCreateWindow("Pixel Drawing");
    init();
    glutDisplayFunc(draw);
    //glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;
}