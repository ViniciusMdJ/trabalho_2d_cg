#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "vector.h"

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

    void Draw() const ;
    Vector Collides(Rectangle &rect) const ;
    void getCoordinates(GLfloat &x, GLfloat &y) const ;
    void getDimensions(GLfloat &width, GLfloat &height) const ;
    Vector moveInside(Rectangle &rect) const ;
};

#endif//RECTANGLE_H