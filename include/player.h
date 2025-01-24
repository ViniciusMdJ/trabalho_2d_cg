#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include "../include/vector.h"
#include "../include/rectangle.h"
#include "../include/bullet.h"

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
    Vector armAngle;
    GLfloat legsHeight;
    GLfloat legsWidth;
    GLfloat rotationAngleOfLegs;
    GLfloat leftThighAngle;
    GLfloat leftShinAngle;
    GLfloat leftLegDirection;
    GLfloat rightThighAngle;
    GLfloat rightShinAngle;
    GLfloat rightLegDirection;

    bool isJumping;
    time_t jumpStartTime;
    time_t lastJumpUpdate;
    GLfloat incJumpPerMilli;
    int walkDirection;

    void DrawBody(GLfloat x, GLfloat y, GLfloat z);
    void DrawHead(GLfloat x, GLfloat y, GLfloat z);
    void DrawArm(GLfloat x, GLfloat y, GLfloat z);
    void DrawLegs(GLfloat x, GLfloat y, GLfloat z);
    void DrawCollisionBox();
    void UpdateJump(GLdouble time);
    void gravityEffect(GLdouble deltaTIme);
    void updateLegs(GLdouble deltaTime);
    void doNothing(){};

    using FuncPtr = void (Player::*)();
    static FuncPtr fpDrawCollisionBox;

public:
    Player(GLfloat x, GLfloat y, GLfloat z, GLfloat height);
    void Draw();
    void getCordinates(GLfloat &x, GLfloat &y);
    void Move(Vector &direction);
    Rectangle getBoundingBox();
    void Jump(bool jump, GLdouble time);
    void setArmAngle(GLfloat x, GLfloat y);
    void updatePlayer(Vector direction, GLdouble time, GLdouble deltaTime);
    Bullet shoot();
    static void setDrawCollisionBox(bool draw);
};

#endif//PLAYER_H