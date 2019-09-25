#include "setup.h"

//MID POINT CIRCLE ALGORITHM

void midPointCircleDraw(int xc, int yc, int r){
    int x = r, y = 0;
    setPixel(x + xc, y + yc);
    if(r > 0){
        setPixel(x + xc, -y + yc);
        setPixel(y + xc, x + yc);
        setPixel(-y + xc, x + yc);
    }
    int P = 1-r;
    while(x >y){
        
        y++; 
          
        if (P <= 0) 
            P += 2*y + 1; 
        else
        { 
            x--; 
            P += 2*y - 2*x + 1; 
        } 
          
        if (x < y) 
            break; 
          
        // Printing the generated point and its reflection in the other octants after translation 
        setPixel(x + xc, y + yc); 
        setPixel(-x + xc, y + yc); 
        setPixel(x + xc, -y + yc); 
        setPixel( -x + xc, -y + yc); 
          
        // If the generated point is on the line x = y then  
        // the perimeter points have already been printed 
        if (x != y) 
        { 
            setPixel(y + xc, x + yc); 
            setPixel(-y + xc, x + yc); 
            setPixel(y + xc, -x + yc); 
            setPixel( -y + xc, -x + yc); 
        } 
    }
}

void draw(){
    midPointCircleDraw(0,0,200);
    glFlush();
}