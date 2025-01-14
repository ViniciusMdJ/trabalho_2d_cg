#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "../include/bullet.h"
#include "../include/vector.h"
#include "../include/utils.h"

Bullet::Bullet(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, Vector direction){
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->direction = direction;
}

void Bullet::Draw() const {  
    glPushMatrix();
        glTranslatef(x, y, z);
        DrawCirc(radius, 1.0, 1.0, 1.0);
    glPopMatrix();
}

void Bullet::getCoordinates(GLfloat &x, GLfloat &y, GLfloat &z) const {
    x = this->x;
    y = this->y;
    z = this->z;
}

float Bullet::getRadius() const {
    return radius;
}

void Bullet::Move(GLdouble increment){
    Vector v = direction * increment;
    x += v.getComponent(0);
    y += v.getComponent(1);
    z += v.getComponent(2);
}