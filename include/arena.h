#ifndef ARENA_H
#define ARENA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

#include "rectangle.h"

class Arena{
    Rectangle* backgroud;
    std::vector<Rectangle> obstacles;

public:
    Arena(GLfloat width, GLfloat height, GLfloat x, GLfloat y);
    void addObstacles(Rectangle rect);
    void Draw();
};

#endif//ARENA_H