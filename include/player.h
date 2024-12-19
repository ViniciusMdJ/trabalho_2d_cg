#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include "../include/vector.h"
#include "../include/rectangle.h"

class Player{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat height;
    GLfloat bodyHeight;
    GLfloat bodyWidth;
    GLfloat headRadius;
    GLfloat armHeight;
    GLfloat armWidth;
    GLfloat armAngle;
    GLfloat legsHeight;
    GLfloat legsWidth;    
    GLfloat leftThighAngle;    
    GLfloat rightThighAngle;    
    GLfloat leftShinAngle;    
    GLfloat rightShinAngle;

    bool isJumping;
    time_t jumpStartTime;
    time_t lastJumpUpdate;

    void DrawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void DrawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawBody(GLfloat x, GLfloat y, GLfloat z);
    void DrawHead(GLfloat x, GLfloat y, GLfloat z);
    void DrawArm(GLfloat x, GLfloat y, GLfloat z);
    void DrawLegs(GLfloat x, GLfloat y, GLfloat z);
    void DrawCollisionBox();

public:
    Player(GLfloat x, GLfloat y, GLfloat z, GLfloat height);
    void Draw();
    void getCordinates(GLfloat &x, GLfloat &y);
    void Move(Vector &direction);
    Rectangle getBoundingBox();
    void Jump(bool jump, GLdouble time);
    void UpdateJump(GLdouble time);
};

#endif//PLAYER_H