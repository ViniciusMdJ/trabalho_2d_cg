#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/rectangle.h"
#include "../include/arena.h"

Arena::Arena(GLfloat width, GLfloat height, GLfloat x, GLfloat y){
    std::cout << width << " " << height << " " << x << " " << y << std::endl;

    backgroud = new Rectangle(width, height, x, y, 0, 0.0, 0.0, 1.0);
}

void Arena::addObstacles(Rectangle rect){
    obstacles.push_back(rect);
}

void Arena::Draw(){
    backgroud->Draw();
    for(auto i : obstacles){
        i.Draw();
    }
}