#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

class Rectangle{
    GLfloat width;
    GLfloat height;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat R; 
    GLfloat G;
    GLfloat B;

public:
    Rectangle(
        GLfloat width,
        GLfloat height,
        GLfloat x,
        GLfloat y,
        GLfloat z,
        GLfloat R, 
        GLfloat G,
        GLfloat B
    );

    void Draw();
};

#endif//RECTANGLE_H