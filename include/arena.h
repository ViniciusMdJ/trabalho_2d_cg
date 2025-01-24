#ifndef ARENA_H
#define ARENA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "rectangle.h"
#include "player.h"
#include "bullet.h"
#include "vector.h"

class Arena{
    Rectangle* backgroud;
    Player* player;
    std::vector<Rectangle> obstacles;
    std::list<Bullet> bullets;
    std::list<std::pair<Player, std::tuple<float, float, int>>> enemies;

public:
    Arena(Player* player, GLfloat width, GLfloat height, GLfloat x, GLfloat y);
    void addObstacles(Rectangle rect);
    void Draw();
    void verifyCollision();
    void addBullet(Bullet bullet);
    void addEnemy(Player enemy);
    bool bulletCheck(const Bullet& value);
    void updateEnemies(GLdouble timeDiff);
    void moveEnemy(std::pair<Player, std::tuple<float, float, int>>& enemy, GLdouble timeDiff);
    void updateArena(Vector direction, GLdouble timeDiff, GLdouble currentTime);
    void playerShoot();
    void playerJump(bool jump, GLdouble currentTime);
    void updatePlayerArm(GLfloat x, GLfloat y);
};

#endif//ARENA_H