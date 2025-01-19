#ifndef UTILS_H
#define UTILS_H

#include "rectangle.h"
#include "bullet.h"

#define INC_MOVE 0.0005
#define CHANCE_TO_SHOOT 0.005

typedef void (*func)(void);

void doNothing(void);

bool checkColision(const Bullet& value, const Rectangle& rect);

void DrawRectBaseCenter(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);

void DrawRectTopLeft(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);

void DrawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);

bool updateAndCheckAngles(GLfloat &angle, GLfloat direction, GLfloat increment, GLfloat minAngle, GLfloat maxAngle);

#endif//UTILS_H