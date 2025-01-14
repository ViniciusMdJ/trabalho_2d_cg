#include <bits/stdc++.h>

#include "../include/bullet.h"
#include "../include/rectangle.h"

void doNothing(void) {}

bool checkColision(const Bullet& value, const Rectangle& rect) {
    float rectX, rectY, rectW, rectH, circX, circY, circR;
    value.getCoordinates(circX, circY, circR);
    circR = value.getRadius();
    rect.getCoordinates(rectX, rectY);
    rect.getDimensions(rectW, rectH);
    rectX += rectW/2;
    rectY -= rectH/2;

    double distanceX = std::abs(circX - rectX);
    double distanceY = std::abs(circY - rectY);

    if (distanceX > (rectW/2.0 + circR)) { return false; }
    if (distanceY > (rectH/2.0 + circR)) { return false; }

    if (distanceX <= (rectW/2.0)) { return true; } 
    if (distanceY <= (rectH/2.0)) { return true; }

    double cornerDistance_sq = pow((distanceX - rectW/2.0), 2) +
                               pow((distanceY - rectH/2.0), 2);

    return (cornerDistance_sq <= (circR * circR));
}

void DrawRectBaseCenter(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glBegin(GL_QUADS);
      glVertex3f(-width/2, 0, 0);
      glVertex3f(width/2, 0, 0);
      glVertex3f(width/2, height, 0);
      glVertex3f(-width/2, height, 0);
    glEnd();
}

void DrawRectTopLeft(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -height, 0);
        glVertex3f(width, -height, 0);
        glVertex3f(width, 0, 0);
    glEnd();
}

void DrawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 60; i++)
        {
            float theta = (float)i * M_PI / 30.0;
            glVertex3f(radius * cos(theta), radius * sin(theta), 0);
        }
    glEnd();
}

bool updateAndCheckAngles(GLfloat &angle, GLfloat direction, GLfloat increment, GLfloat minAngle, GLfloat maxAngle)
{
    angle += increment * direction;
    if (angle > maxAngle){
        angle = maxAngle;
        return true;
    }
    else if (angle < minAngle){
        angle = minAngle;
        return true;
    }
    return false;
}