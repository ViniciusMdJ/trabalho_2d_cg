#ifndef ARENA_H
#define ARENA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "rectangle.h"
#include "player.h"
#include "bullet.h"

class Arena{
    Rectangle* backgroud;
    std::vector<Rectangle> obstacles;
    std::list<Bullet> bullets;
    std::list<Player> enemies;

public:
    Arena(GLfloat width, GLfloat height, GLfloat x, GLfloat y);
    void addObstacles(Rectangle rect);
    void Draw();
    void verifyCollision(Player &player);
    void addBullet(Bullet bullet);
    void addEnemy(Player enemy);
    bool bulletCheck(const Bullet& value, Player &player);
    void updateArena(Player &player, GLdouble timeDiff);
};

#endif//ARENA_H