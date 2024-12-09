
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <bits/stdc++.h>
#include <iostream>

#include "../include/matrixTranformations.h"
#include "../include/tinyxml2.h"
#include "../include/arena.h"
#include "../include/arenaParser.h"
#include "../include/player.h"

using namespace std;

// Window dimensions
const GLint Width = 850;
const GLint Height = 850;

int keyStatus[256];

//Componentes do mundo virtual sendo modelado
Arena* arena;
Player* player;

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat playerX, playerY;
    player->getCordinates(playerX, playerY);

    glPushMatrix();
        glTranslatef(-playerX, 0, 0);
        arena->Draw();
        player->Draw();
    glPopMatrix();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++) 
        keyStatus[i] = 0; 
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    float sizeX = 0.5;
    float sizeY = 0.5;
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-sizeX,     // X coordinate of left edge             
            sizeX,     // X coordinate of right edge            
            -sizeY,     // Y coordinate of bottom edge             
            sizeY,     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();

    MatrixTransformations::mtLoadIdentity(); 
}

void mouse(int button, int state, int x, int y){
   printf("button %d - state %d - x %d - y %d\n", button, state, x, y);
}

void idle(void){
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    parserXmlFile("/mnt/d/UFES/10-periodo/cg/trabalho_2d_cg/arena_teste.svg", arena, player);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Tranformations 2D");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    // glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    // glutKeyboardUpFunc(keyup);
    
    init();
 
    glutMainLoop();
 
    return 0;
}