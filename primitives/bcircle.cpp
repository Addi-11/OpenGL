#include"setup.h"

//BRESENHAM CIRCLE DRAWING ALGORITHM

void drawCircle(int xc, int yc, int x, int y){
    setPixel(xc + x , yc + y);
    setPixel(xc - x , yc + y);
    setPixel(xc + x , yc - y);
    setPixel(xc - x , yc - y);
    setPixel(xc + y , yc + x);
    setPixel(xc - y , yc + x);
    setPixel(xc + y , yc - x);
    setPixel(xc - y , yc - x);
}

void circleBres(int xc, int yc, int r){
    int x = 0, y = r;
    int d = 3 - 2*r;
    drawCircle(xc, yc, x, y);
    while( y >= x){
        x++;
        if(d > 0){
            y--;
            d += 4*(x-y) + 10;
        }
        else{
            d += 4*x + 6;
        }
        drawCircle(xc,yc,x,y);
    }
}

void draw(){
    circleBres(250,-100,200);
    glFlush();
}
