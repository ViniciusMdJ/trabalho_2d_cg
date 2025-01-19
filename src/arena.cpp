#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/rectangle.h"
#include "../include/arena.h"
#include "../include/utils.h"

Arena::Arena(Player* player, GLfloat width, GLfloat height, GLfloat x, GLfloat y){
    // std::cout << width << " " << height << " " << x << " " << y << std::endl;

    this->player = player;
    backgroud = new Rectangle(width, height, x, y, 0.0, 0.0, 0.0, 1.0);
}

void Arena::addObstacles(Rectangle rect){
    obstacles.push_back(rect);
}

void Arena::addEnemy(Player enemy){
    enemies.push_back(enemy);
}

void Arena::Draw(){
    GLfloat playerX, playerY;
    player->getCordinates(playerX, playerY);

    glPushMatrix();
        glTranslatef(-playerX, 0, 0);
        backgroud->Draw();
        for(auto i : obstacles){
            i.Draw();
        }
        for(auto i : bullets){
            i.Draw();
        }
        for(auto i : enemies){
            i.Draw();
        }
        player->Draw();
    glPopMatrix();
}

void Arena::verifyCollision(){
    Rectangle rect = player->getBoundingBox();

    Vector move = backgroud->moveInside(rect);
    player->Move(move);

    Vector v;
    for(auto i : obstacles){
        v += i.Collides(rect);
    }
    for(auto i : enemies){
        v += i.getBoundingBox().Collides(rect);
    }

    // std::cout << v.getComponent(0) << " " << v.getComponent(1) << std::endl;
    player->Move(v); 
}

void Arena::addBullet(Bullet bullet){
    bullets.push_back(bullet);
}

bool Arena::bulletCheck(const Bullet& value){
    for(auto i : obstacles){
        if(checkColision(value, i)){
            return true;
        }
    }
    auto i = enemies.begin();
    while(i != enemies.end()){
        if(checkColision(value, i->getBoundingBox())){
            enemies.erase(i);
            return true;
        }
        i++;
    }
    if(checkColision(value, player->getBoundingBox())){
        return true;
    }
    return !checkColision(value, *backgroud);
}

void Arena::updateEnemies(GLdouble timeDiff){
    GLfloat playerX, playerY;
    player->getCordinates(playerX, playerY);
    for(auto &i : enemies){
        i.setArmAngle(playerX, playerY);
        if(rand() / (double)RAND_MAX < CHANCE_TO_SHOOT){
            bullets.push_back(i.shoot());
        }
    }
}

void Arena::updateArena(Vector direction, GLdouble timeDiff, GLdouble currentTime){
    player->updatePlayer(direction, currentTime, timeDiff);
    updateEnemies(timeDiff);
    for(auto &i : bullets){
        i.Move(timeDiff * 2 * INC_MOVE);
    }
    bullets.remove_if([this](const Bullet& value) { return bulletCheck(value); });
    verifyCollision();
}

void Arena::playerShoot(){
    addBullet(player->shoot());
}

void Arena::playerJump(bool jump, GLdouble currentTime){
    player->Jump(jump, currentTime);
}

void Arena::updatePlayerArm(GLfloat x, GLfloat y){
    GLfloat playerX, playerY;
    player->getCordinates(playerX, playerY);

    player->setArmAngle(x + playerX, y);
}