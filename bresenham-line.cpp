#include<iostream>
#include<GL/glut.h>

//sign function
#define sign(x) ((x>0)?1:((x<0)?-1:0))

void init(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500,0);
    glutInitWindowSize(1000,900);
    glutCreateWindow("Breseham Line Algo");
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glPointSize(1.5);
    gluOrtho2D(-500,500,-500,500);
}

//function to plot points
void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
int abs(int a){
    return ((a>0)?a:(-1*a));
}

//GENERALISED BRESENHAM
void bres_general(int x1,int y1, int x2, int y2){
    int dx, dy, x, y, d, s1, s2, swap = 0, temp;
    dx = abs(x2-x1);
    dy = abs(y2-y1);
    s1 = sign(x2-x1);
    s2 = sign(y2-y1);

    //swap if dy > dx ie slope > 1
    if(dy > dx){temp = dx; dx = dy; dy = temp; swap = 1;}

    d = 2*dy - dx;
    x = x1;
    y = y1;
    for(int i = 1; i <= dx; i++){
        setPixel(x,y);
        while( d >= 0){
            //if dy > dx
            if(swap) x += s1;
            else{
                y += s2;
                d -= 2*dx;
            }
        }
        if(swap) y += s2;
        else x += s1;
        d += 2*dy;
    }
    glFlush();
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    bres_general(20,-240,-320,40);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}