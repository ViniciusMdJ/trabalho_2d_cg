#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/rectangle.h"
#include "../include/arena.h"
#include "../include/utils.h"

Arena::FuncPtrClearBullet Arena::fpClearBullet = &Arena::doNothing;

void Arena::clearBullet(){
    bullets.clear();
}

Arena::Arena(Player* player, GLfloat width, GLfloat height, GLfloat x, GLfloat y){
    // std::cout << width << " " << height << " " << x << " " << y << std::endl;

    this->player = player;
    backgroud = new Rectangle(width, height, x, y, 0.0, 0.0, 0.0, 1.0);
}

void Arena::addObstacles(Rectangle rect){
    obstacles.push_back(rect);
    float min, max;
    rect.getHorizontalLimits(min, max);
    std::cout << "new obstacle " << min << " " << max << std::endl;
}

void Arena::addEnemy(Player enemy){
    float min, max, minUpDistance = 500, upDistance;
    // seta os limites como os limites do background
    backgroud->getHorizontalLimits(min, max);
    
    for(auto i : obstacles){
        if(i.isBetweenLimitsAndUp(enemy.getBoundingBox(), upDistance) && std::abs(upDistance) < minUpDistance){
            minUpDistance = std::abs(upDistance);
            i.getHorizontalLimits(min, max);            
        }
    }

    // std::cout << "new enemy " << min << " " << max << std::endl;
    enemies.push_back(mp(enemy, std::make_tuple(min, max, 1)));
}

void Arena::Draw(){
    (this->*fpClearBullet)();
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
            i.first.Draw();
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
        for(auto& j : enemies){
            Vector move = i.Collides(j.first.getBoundingBox());
            j.first.Move(move);
            if(move.getComponent(0) != 0) std::get<2>(j.second) *= -1;
        }
    }
    for(auto i : enemies){
        v += i.first.getBoundingBox().Collides(rect);
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
        if(checkColision(value, i->first.getBoundingBox())){
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
    for(auto& i : enemies){
        moveEnemy(i, timeDiff);
        i.first.setArmAngle(playerX, playerY);
        if(rand() / (double)RAND_MAX < CHANCE_TO_SHOOT){
            bullets.push_back(i.first.shoot());
        }
    }
}

void Arena::moveEnemy(std::pair<Player, std::tuple<float, float, int>>& enemy, GLdouble timeDiff){
    float increment = std::get<2>(enemy.second) * INC_MOVE * timeDiff / 4.0;
    Vector moveEnemy(increment, 0, 0);
    enemy.first.Move(moveEnemy);

    float enemyX, enemyY;
    enemy.first.getCordinates(enemyX, enemyY);

    Vector v;
    float min = std::get<0>(enemy.second);
    float max = std::get<1>(enemy.second);

    // std::cout << "before " << min << " " << max << " " << std::get<2>(enemy.second) << std::endl;
    if(enemyX < min){
        v = Vector(min - enemyX, 0, 0);
        std::get<2>(enemy.second) *= -1;
    }
    else if(enemyX > max){
        v = Vector(max - enemyX, 0, 0);
        std::get<2>(enemy.second) *= -1;
    }

    // std::cout << "after " << min << " " << max << " " << std::get<2>(enemy.second) << std::endl;
    enemy.first.Move(v);
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

void Arena::setClearBullet(bool clear){
    if(clear){
        fpClearBullet = &Arena::clearBullet;
    }
    else{
        fpClearBullet = &Arena::doNothing;
    }
}