#include<iostream>
#include<GL/glut.h>

void init(){
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,300,0,300);
}

void drawLine(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int x1, x2, y1, y2;
    x1 = 50; x2 = 200; y1 = 40; y2 = 100;
    ///std::cin >>x1>>y1>>x2>>y2;
    int m = 2*(y2 - y1);
    int err = m - (x2-x1);
    for(int x = x1, y = y1; x <= x2; x++){
        std::cout << x <<", " << y<< std::endl;
        glVertex2i(x,y);
        err += m;
        if(err >= 0){
            y++;
            err -= 2*(x2-x1);
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,900);
    glutInitWindowPosition(500,0);

    glutCreateWindow("Bresenham Line drawing Algo");
    init();
    glutDisplayFunc(drawLine);
    glutMainLoop();

    return 0;
}