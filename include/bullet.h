#ifndef BULLET_H
#define BULLET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "vector.h"

#define BULLET_RADIUS 0.005

class Bullet{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat radius;
    Vector direction;

public:
    Bullet(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, Vector direction);
    void Draw() const ;
    void getCoordinates(GLfloat &x, GLfloat &y, GLfloat &z) const ;
    float getRadius() const ;
    void Move(GLdouble increment);
};

#endif//BULLET_H