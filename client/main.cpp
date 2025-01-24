
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
#include "../include/vector.h"
#include "../include/utils.h"
#include "../include/text.h"
#include "../include/gameStatus.h"

using namespace std;

GameStatus gameStatus = START;

// Window dimensions
const GLint Width = 850;
const GLint Height = 850;

int keyStatus[256];
bool drawCollisionBox = false;
bool clearBullet = false;

//Componentes do mundo virtual sendo modelado
Arena* arena;

Text statusMsg;
Text restartMsg("Press R to restart");

Text gameOver("Game Over");
Text win("You Win");

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    
    arena->Draw();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void initScreen(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(-1, 1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glVertex2f(-1, -1);
    glEnd();

    //verificar pq não desenha as duas mensagens
    statusMsg.drawTextCentered(0, 0);
    restartMsg.drawTextCentered(0, -0.05);

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++) 
        keyStatus[i] = 0; 
}

void keyPress(unsigned char key, int x, int y)
{
    keyStatus[key] = 1;
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    if(key == 'b'){
        Player::setDrawCollisionBox(drawCollisionBox = !drawCollisionBox);
    }
    if(key == 'c'){
        Arena::setClearBullet(clearBullet = !clearBullet);
    }
    glutPostRedisplay();
}

void init(void)
{
    srand(time(NULL));
    ResetKeyStatus();
    Player::setDrawCollisionBox(drawCollisionBox);
    Arena::setClearBullet(clearBullet);
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
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;

    // printf("button %d - state %d - x %d - y %d\n", button, state, x, y);

    // x = x - Width/2;
    // y = Height/2 - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        arena->playerShoot();
    }

    if(button == GLUT_RIGHT_BUTTON){
        bool isJumping;
        if(state == GLUT_DOWN) isJumping = true;
        else if(state == GLUT_UP) isJumping = false;

        arena->playerJump(isJumping, currentTime);
    }
}

void motionMouse(int x, int y){
    // ajustar o braço do player
    GLfloat relativeX = (x - Width/2) / (float)Width;
    GLfloat relativeY = (Height/2 - y) / (float)Height;

    arena->updatePlayerArm(relativeX, relativeY);
}

void idle(void){
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;

    Vector direction;

    //Treat keyPress
    if(keyStatus[(int)('a')]){
        direction.setComponent(0, direction.getComponent(0) - 1);
    }
    if(keyStatus[(int)('d')]){
        direction.setComponent(0, direction.getComponent(0) + 1);
    }
    // if(keyStatus[(int)('w')]){
    //     direction.setComponent(1, direction.getComponent(1) + 1);
    // }
    // if(keyStatus[(int)('s')]){
    //     direction.setComponent(1, direction.getComponent(1) - 1);
    // }


    direction = direction.normalize() * (INC_MOVE * timeDiference);
    arena->updateArena(direction, timeDiference, currentTime);

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    parserXmlFile("./arena_teste.svg", arena);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Trabalho 2D Vinicius");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motionMouse);
    glutPassiveMotionFunc(motionMouse);
    
    init();
 
    glutMainLoop();
 
    return 0;
}