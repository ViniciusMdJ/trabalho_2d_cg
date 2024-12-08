#include "../include/rectangle.h"
#include <GL/gl.h>
#include <GL/glu.h>

void Rectangle::Draw(){
    glColor3f(R, G, B);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glBegin(GL_QUADS);
            glVertex3f(0, 0, z);
            glVertex3f(0, -height, z);
            glVertex3f(width, -height, z);
            glVertex3f(width, 0, z);
        glEnd();
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