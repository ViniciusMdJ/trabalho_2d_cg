#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/player.h"
#include "../include/vector.h"
#include "../include/utils.h"
#include "../include/matrixTranformations.h"

#define BODY_WIDTH 0.04
#define JUMP_TOTAL_TIME 4000

#define THIGH_MIN_ANGLE 160.0f
#define THIGH_MAX_ANGLE 200.0f
#define SHIN_MIN_ANGLE 0.0f
#define SHIN_MAX_ANGLE 90.0f

#define THIGH_ANGLE_INC (THIGH_MAX_ANGLE - THIGH_MIN_ANGLE) / 800.0
#define SHIN_ANGLE_INC (SHIN_MAX_ANGLE - SHIN_MIN_ANGLE) / 800.0

#define LEFT_WALK 0
#define RIGHT_WALK 1
#define STOP_WALK 2

const Vector vectorLimitUpRight = Vector(1.0, 1.0, 0.0).normalize();
const Vector vectorLimitUpLeft = Vector(-1.0, 1.0, 0.0).normalize();
const Vector vectorLimitDownRight = Vector(1.0, -1.0, 0.0).normalize();
const Vector vectorLimitDownLeft = Vector(-1.0, -1.0, 0.0).normalize();

void Player::Draw(){
    glPushMatrix();
        // DrawCollisionBox();
        glTranslatef(this->x, this->y - this->headRadius, 0.0);
        DrawBody(0.0, 0.0, 0.0);
        DrawHead(0.0, bodyHeight + headRadius, 0.0);
        DrawArm(0.0, bodyHeight/2.0, 0.0);
        DrawLegs(0, 0, 0);
    glPopMatrix();

}

void Player::DrawBody(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        DrawRectBaseCenter(bodyHeight, bodyWidth, 0.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawHead(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        DrawCirc(headRadius, 0.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawArm(GLfloat x, GLfloat y, GLfloat z){
    double angle = armAngle.getAngleXY() - 90.0;
    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(angle, 0.0, 0.0, 1.0);
        DrawRectBaseCenter(armHeight, armWidth, 1.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawLegs(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(rotationAngleOfLegs, 0.0, 1.0, 0.0);
        glPushMatrix();
            glRotatef(leftThighAngle, 0.0, 0.0, 1.0);
            DrawRectBaseCenter(legsHeight, legsWidth, 1.0, 0.0, 0.0);
            glTranslatef(0.0, legsHeight, 0.0);
            glRotatef(leftShinAngle, 0.0, 0.0, 1.0);
            DrawRectBaseCenter(legsHeight, legsWidth, 1.0, 0.0, 0.0);
        glPopMatrix();

        glRotatef(rightThighAngle, 0.0, 0.0, 1.0);
        DrawRectBaseCenter(legsHeight, legsWidth, 1.0, 0.0, 0.0);
        glTranslatef(0.0, legsHeight, 0.0);
        glRotatef(rightShinAngle, 0.0, 0.0, 1.0);
        DrawRectBaseCenter(legsHeight, legsWidth, 1.0, 0.0, 0.0);

    glPopMatrix();
}

void Player::DrawCollisionBox(){
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(x, y, z);
        glBegin(GL_LINE_LOOP);
            glVertex3f(-bodyWidth/2, -height/2.0, z+1);
            glVertex3f(bodyWidth/2, -height/2.0, z+1);
            glVertex3f(bodyWidth/2, height/2.0, z+1);
            glVertex3f(-bodyWidth/2, height/2.0, z+1);
        glEnd();
    glPopMatrix();
}

void Player::getCordinates(GLfloat &x, GLfloat &y){
    x = this->x;
    y = this->y;
}

Player::Player(GLfloat x, GLfloat y, GLfloat z, GLfloat height){
    this->x = x;
    this->y = y;
    this->z = z;
    this->height = height;
    this->bodyHeight = height/5*2;
    this->bodyWidth = height/5;
    this->headRadius = height/10;

    this->armHeight = height/4;
    this->armWidth = height/20;
    this->armAngle = Vector(1.0, 0.0, 0.0);

    this->walkDirection = STOP_WALK;
    this->legsHeight = height/5;
    this->legsWidth = height/20;
    this->leftThighAngle = 180.0;
    this->leftShinAngle = 0;
    this->leftLegDirection = 1.0;
    this->rightThighAngle = 180.0;
    this->rightShinAngle = 0;
    this->rightLegDirection = -1.0;

    this->isJumping = false;
    this->incJumpPerMilli = (height * 6) / (float)JUMP_TOTAL_TIME;
    this->rotationAngleOfLegs = 0.0;
    // std::cout << "x " << x << " y " << y << " height " << height << std::endl;
    // std::cout << "incJumpPerMilli " << incJumpPerMilli << std::endl;
    // std::cout << "bodyHeight " << bodyHeight << std::endl;
    // std::cout << "headRadius " << headRadius << std::endl;
    // std::cout << bodyHeight << bodyHeight << std::endl;
}

void Player::Move(Vector &direction){
    this->x += direction.getComponent(0);
    this->y += direction.getComponent(1);
    this->z += direction.getComponent(2);
}

void Player::UpdateJump(GLdouble time){
    if(!isJumping) return;

    time_t deltaTime = std::min(JUMP_TOTAL_TIME, (int)(time - jumpStartTime));
    GLfloat movement = 0.0;

    if(deltaTime < JUMP_TOTAL_TIME/2){
        movement += (deltaTime - (lastJumpUpdate - jumpStartTime)) * incJumpPerMilli;
    }else if(lastJumpUpdate - jumpStartTime < JUMP_TOTAL_TIME/2){
        movement += (JUMP_TOTAL_TIME/2 - (lastJumpUpdate - jumpStartTime)) * incJumpPerMilli;
        movement -= (deltaTime - (JUMP_TOTAL_TIME/2)) * incJumpPerMilli;
    }else{
        movement -= (deltaTime - (lastJumpUpdate - jumpStartTime)) * incJumpPerMilli;
    }

    Vector v(0.0, movement, 0.0);
    Move(v);
    
    lastJumpUpdate = time;
    if(time - jumpStartTime > JUMP_TOTAL_TIME){
        isJumping = false;
        return;
    }
}

Rectangle Player::getBoundingBox(){
    return Rectangle(
        bodyWidth,
        height,
        x - bodyWidth/2,
        y + height/2,
        z,
        1.0,
        1.0,
        1.0
    );
}

void Player::Jump(bool jump, GLdouble time){
    if(jump && !isJumping){
        jumpStartTime = time;
        lastJumpUpdate = time;
    }
    isJumping = jump;
    std::cout << "pulo " << jump << " " << time << std::endl;
}

void Player::gravityEffect(GLdouble deltaTime){
    if(isJumping) return;
    Vector v(0.0, -(incJumpPerMilli * deltaTime), 0.0);
    Move(v);
}

void Player::setArmAngle(GLfloat x, GLfloat y){
    Vector newV = Vector(x - this->x, y - this->y, 0.0).normalize();

    double mag = newV.magnitude();
    if(mag == 0.0) return;

    Vector vUp, vDown;
    double dotUp, dotDown;
    
    double newVAngle = std::abs(newV.getAngleXY());
    if(newVAngle > 90.0){
        vUp = vectorLimitUpLeft;
        vDown = vectorLimitDownLeft;
    }else{
        vUp = vectorLimitUpRight;
        vDown = vectorLimitDownRight;
    }

    dotUp = newV * vUp;
    dotDown = newV * vDown;

    if(dotUp >= 0.0 && dotDown >= 0.0){
        armAngle = newV;
    }else if(dotUp < dotDown){
        armAngle = vDown;
    }else{
        armAngle = vUp;
    }
}

Bullet Player::shoot(){
    using namespace MatrixTransformations;
    float myX = 0, myY = 0, myZ = 0;
    mtPushMatrix();
        mtTranslatef(this->x, this->y - this->headRadius, 0.0);
        mtTranslatef(0.0, bodyHeight/2.0, 0.0);
        mtRotatef(-armAngle.getAngleXY() + 90.0, 0.0, 0.0, 1.0);
        mtTranslatef(0.0, armHeight, 0.0);
        mtTransformPoint(myX, myY, myZ);
    mtPopMatrix();
    return Bullet(myX, myY, myZ, BULLET_RADIUS, armAngle);
}

void Player::updateLegs(GLdouble deltaTime){
    if(walkDirection != STOP_WALK){
        bool swap;
        swap = updateAndCheckAngles(leftThighAngle, leftLegDirection, THIGH_ANGLE_INC * deltaTime, THIGH_MIN_ANGLE, THIGH_MAX_ANGLE);
        swap &= updateAndCheckAngles(leftShinAngle, leftLegDirection, SHIN_ANGLE_INC * deltaTime, SHIN_MIN_ANGLE, SHIN_MAX_ANGLE);
        if(swap) leftLegDirection *= -1;
        swap = updateAndCheckAngles(rightThighAngle, rightLegDirection, THIGH_ANGLE_INC * deltaTime, THIGH_MIN_ANGLE, THIGH_MAX_ANGLE);
        swap &= updateAndCheckAngles(rightShinAngle, rightLegDirection, SHIN_ANGLE_INC * deltaTime, SHIN_MIN_ANGLE, SHIN_MAX_ANGLE);
        if(swap) rightLegDirection *= -1;
    }

    // std::cout << "perna esquerda " << leftThighAngle << " " << leftShinAngle << std::endl;
    // std::cout << "perna direita " << rightThighAngle << " " << rightShinAngle << std::endl;
}

void Player::updatePlayer(Vector direction, GLdouble time, GLdouble deltaTime){
    if(direction.getComponent(0) > 0.0){
        walkDirection = RIGHT_WALK;
        rotationAngleOfLegs = 180.0;
    }
    else if(direction.getComponent(0) < 0.0){
        walkDirection = LEFT_WALK;
        rotationAngleOfLegs = 0.0;
    }
    else{
        walkDirection = STOP_WALK;
    }
    
    Move(direction);
    updateLegs(deltaTime);
    UpdateJump(time);
    gravityEffect(deltaTime);
}