#include<iostream>
#include<GL/glut.h>
#include<unistd.h>

void init(){
    glClearColor(0 ,0, 0, 1.0);
    glColor3f(255,255,255);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-780,780,-420,420);
}
int abs(int x){
    return (x > 0) ? x: (x*-1);
}

void drawLine(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    //DDA ALgo
    int dx, dy, i, len;
    float Xinc, Yinc, X, Y;
    
    int X0, X1, Y0, Y1;
    std::cin >> X0 >> Y0 >> X1 >>Y1;
    dx = X1 - X0;
    dy = Y1 - Y0;
    len = abs(dx) > abs(dy) ? abs(dx):abs(dy);
    Xinc = dx / (float)len;
    Yinc = dy / (float)len;
    X = X0; Y = Y0;

    for(i = 0; i <= len; i++){
        //delays printing of output not the displaying of pixels
        //usleep(1000000); // in ms
        glVertex2f(X,Y);
        X += Xinc;
        Y += Yinc;
        std::cout <<X<<", "<<Y<<std::endl;
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(1000,900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("DDA Algorithm");
    init();
    glutDisplayFunc(drawLine);
    glutMainLoop();
    return 0;
}