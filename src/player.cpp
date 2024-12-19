#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/player.h"
#include "../include/vector.h"

#define BODY_WIDTH 0.04

void Player::DrawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glBegin(GL_QUADS);
      glVertex3f(-width/2, 0, z);
      glVertex3f(width/2, 0, z);
      glVertex3f(width/2, height, z);
      glVertex3f(-width/2, height, z);
    glEnd();
}

void Player::DrawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 60; i++)
        {
            float theta = (float)i * M_PI / 30.0;
            glVertex3f(radius * cos(theta), radius * sin(theta), z);
        }
    glEnd();
}

void Player::Draw(){
    glPushMatrix();
        DrawCollisionBox();
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
        DrawRect(bodyHeight, bodyWidth, 0.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawHead(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        DrawCirc(headRadius, 0.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawArm(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(armAngle, 0.0, 0.0, 1.0);
        DrawRect(armHeight, armWidth, 1.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::DrawLegs(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
        glTranslatef(x, y, z);
        glPushMatrix();
            glRotatef(leftThighAngle, 0.0, 0.0, 1.0);
            DrawRect(legsHeight, legsWidth, 1.0, 1.0, 0.0);
            glTranslatef(0.0, legsHeight, 0.0);
            glRotatef(leftShinAngle, 0.0, 0.0, 1.0);
            DrawRect(legsHeight, legsWidth, 1.0, 1.0, 0.0);
        glPopMatrix();

        glRotatef(rightThighAngle, 0.0, 0.0, 1.0);
        DrawRect(legsHeight, legsWidth, 1.0, 1.0, 0.0);
        glTranslatef(0.0, legsHeight, 0.0);
        glRotatef(rightShinAngle, 0.0, 0.0, 1.0);
        DrawRect(legsHeight, legsWidth, 1.0, 1.0, 0.0);

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
    this->armAngle = -90.0;
    this->legsHeight = height/5;
    this->legsWidth = height/20;    
    this->leftThighAngle = 195.0;
    this->rightThighAngle = 165.0;
    this->leftShinAngle = -15.0;
    this->rightShinAngle = -15.0;
    std::cout << "x " << x << " y " << y << " height " << height << std::endl;
    // std::cout << "bodyHeight " << bodyHeight << std::endl;
    // std::cout << "headRadius " << headRadius << std::endl;
    // std::cout << bodyHeight << bodyHeight << std::endl;
}

void Player::Move(Vector &direction){
    this->x += direction.getComponent(0);
    this->y += direction.getComponent(1);
    this->z += direction.getComponent(2);
}

Rectangle Player::getBoundingBox(){
    return Rectangle(
        bodyWidth,
        height,
        x - bodyWidth/2,
        y - height/2,
        z,
        1.0,
        1.0,
        1.0
    );
}

void Player::Jump(){
    // if(!isJumping){
    //     isJumping = true;
    //     jumpStartTime = time(NULL);
    // }
    // else{
    //     time_t currentTime = time(NULL);
    //     if(currentTime - jumpStartTime > 1){
    //         isJumping = false;
    //     }
    // }
}