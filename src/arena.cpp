#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/rectangle.h"
#include "../include/arena.h"
#include "../include/utils.h"

Arena::Arena(GLfloat width, GLfloat height, GLfloat x, GLfloat y){
    // std::cout << width << " " << height << " " << x << " " << y << std::endl;

    backgroud = new Rectangle(width, height, x, y, 0.0, 0.0, 0.0, 1.0);
}

void Arena::addObstacles(Rectangle rect){
    obstacles.push_back(rect);
}

void Arena::addEnemy(Player enemy){
    enemies.push_back(enemy);
}

void Arena::Draw(){
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
}

void Arena::verifyCollision(Player &player){
    Rectangle rect = player.getBoundingBox();

    Vector move = backgroud->moveInside(rect);
    player.Move(move);

    Vector v;
    for(auto i : obstacles){
        v += i.Collides(rect);
    }
    for(auto i : enemies){
        v += i.getBoundingBox().Collides(rect);
    }

    // std::cout << v.getComponent(0) << " " << v.getComponent(1) << std::endl;
    player.Move(v); 
}

void Arena::addBullet(Bullet bullet){
    bullets.push_back(bullet);
}

bool Arena::bulletCheck(const Bullet& value, Player &player){
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
    if(checkColision(value, player.getBoundingBox())){
        return true;
    }
    return !checkColision(value, *backgroud);
}

void Arena::updateArena(Player &player, GLdouble timeDiff){
    for(auto &i : bullets){
        i.Move(timeDiff * 2 * INC_MOVE);
    }
    bullets.remove_if([this, &player](const Bullet& value) { return bulletCheck(value, player); });
    verifyCollision(player);
}