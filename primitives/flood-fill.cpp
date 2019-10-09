//PROBLEM IN SELF CONSTRUCTOR TAKING UP ARGUMENTS AND == OVERLOADING

#include<math.h>
#include "setup.h"

class Color{
    public:
        float r , g , b;
        //SELF-CONSTRUCTOR
        //without parameters
        //with parameters--OVERLOADED
        Color(GLfloat r, GLfloat g, GLfloat b){
            r = r;
            g = g;
            b = b;
        }
        Color(){}
        //OPERATOR OVERLOADING
        //to chk if new and old color are same

        //bool operator==(Color c){
        //    std::cout << "checking if the colors of pixel match" << std:: endl;
        //    if(r == c.r && g == c.g && b == c.b) {
        //        std::cout << "old and new pixel matched" << std::endl;
        //        return 1;
        //    }
        //    else return 0;
        //}

};

class Point{
    public:
        GLint x, y;
        Point(GLint xcor, GLint ycor){
            xcor = x;
            ycor = y;
        }
};

//Dimensions of the circle to be drawn
Point pt(300, -420);//centre co-ordinates
GLfloat radius = 200;

Color oldColor(0.0f ,0.0f ,0.0f); //background color
Color newColor(1.0f ,0.85f ,0.73f);//color to set

void draw_circle(){
    GLfloat step = 1/radius;
    GLfloat x, y;

    for(GLfloat theta = 0; theta <= 360; theta += step){
        x = pt.x + radius*cos(theta);
        y = pt.y + radius*sin(theta);
        glVertex2i(x,y);
    }
}

void setPixelColor(GLint x, GLint y, Color color){
    std::cout << "setting color in pixel" << std::endl;
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

Color getPixelColor(GLint x, GLint y){
    Color color;
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT, &color);
    std::cout << "In get pixel funct" << std::endl;
    return color;
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor){
    Color color = getPixelColor(x,y);

    std::cout << color.r << " " << oldColor.r <<std::endl;
    std::cout << color.g << " " << oldColor.g <<std::endl;
    std::cout << color.b << " " << oldColor.b <<std::endl;
    if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b){
        setPixelColor(x,y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
    return;
}

void draw(){
    //will display a circle in the beggining
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
        //draw circle
        draw_circle();
    glEnd();
    glFlush();
}

void onMouseClick(int btn, int state, int x, int y){
    //start floodfill
    floodFill(pt.x, pt.y, oldColor, newColor);
}