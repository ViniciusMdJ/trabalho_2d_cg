#include "../include/rectangle.h"
#include "../include/utils.h"
#include <GL/gl.h>
#include <GL/glu.h>

void Rectangle::Draw() const { 
    glPushMatrix();
        glTranslatef(x, y, 0);
        DrawRectTopLeft(height, width, R, G, B);
    glPopMatrix();
}

Rectangle::Rectangle(GLfloat width, GLfloat height, GLfloat x, GLfloat y, GLfloat z, GLfloat R, GLfloat G, GLfloat B){
    // std::cout <<  " width " << width <<  " height " << height <<  " x " << x <<  " y " << y <<  " z " << z << std::endl;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->z = z;
    this->R = R;
    this->G = G;
    this->B = B;
}

Vector Rectangle::Collides(Rectangle &rect) const {
    Vector v;
    GLfloat w, h, multiplierX, multiplierY;

    if(this->x > rect.x){
        w = rect.width;
        multiplierX = -1;
    }
    else{
        w = this->width;
        multiplierX = 1;
    }

    if(this->y > rect.y){
        h = this->height;
        multiplierY = -1;
    }
    else{
        h = rect.height;
        multiplierY = 1;
    }

    GLfloat delta_x = std::abs(rect.x - this->x);
    GLfloat delta_y = std::abs(rect.y - this->y);
    GLfloat intersection_x = w - delta_x;
    GLfloat intersection_y = h - delta_y;
    if(delta_x < w && delta_y < h){
        if(intersection_x < intersection_y){
            v.setComponent(0, intersection_x * multiplierX);
        }
        else{
            v.setComponent(1, intersection_y * multiplierY);
        }
        std::cout << "Collided" << std::endl;
    }

    return v;
}

void Rectangle::getCoordinates(GLfloat &x, GLfloat &y) const {
    x = this->x;
    y = this->y;
}

void Rectangle::getDimensions(GLfloat &width, GLfloat &height) const {
    width = this->width;
    height = this->height;
}

Vector Rectangle::moveInside(Rectangle &rect) const {
    Vector v;
    if(rect.x < this->x ){
        v.setComponent(0, this->x - rect.x);
    }
    else if((rect.x + rect.width) > (this->x + this->width)){
        v.setComponent(0, (this->x + this->width) - (rect.x + rect.width));
    }

    if(rect.y > this->y){
        v.setComponent(1, this->y - rect.y);
    }
    else if((rect.y - rect.height) < (this->y - this->height)){
        v.setComponent(1, (this->y - this->height) - (rect.y - rect.height));
    }
    return v;
}