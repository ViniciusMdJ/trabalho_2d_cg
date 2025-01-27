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

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

int keyStatus[256];
bool drawCollisionBox = false;
bool clearBullet = false;
bool moveEnemies = true;

//Componentes do mundo virtual sendo modelado
Arena* arena;
Arena* currentArena;

Text statusMsg;
Text restartMsg("Press R to restart");

Text gameOverMessage("Game Over Press R to restart");
Text winMessage("You Win Press R to restart");
Text initialMessage("Press R to start");

// inicializar com valor diferente de START
GameStatus gameStatus = GAME_OVER;
void (*screenDraw)(void);
GameStatus (*updateGame)(GLdouble timeDiff, GLdouble currentTime);

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    
    (*screenDraw)();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void drawRunningScreen(void){
    currentArena->Draw();
}

void drawMessageScreen(void){
    // glColor3f(1.0, 1.0, 1.0);
    // glBegin(GL_LINES);
    //     glVertex2f(-1, 1);
    //     glVertex2f(1, -1);
    //     glVertex2f(1, 1);
    //     glVertex2f(-1, -1);
    // glEnd();

    //verificar pq não desenha as duas mensagens
    statusMsg.drawTextCentered(0, 0);
    // restartMsg.drawTextCentered(0, -0.05);
}

GameStatus dontUpdate(GLdouble timeDiference, GLdouble currentTime){
    return gameStatus;
}

GameStatus updateRunning(GLdouble timeDiference, GLdouble currentTime){
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
    return currentArena->updateArena(direction, timeDiference, currentTime);
}

void setGameStatus(GameStatus gs){
    if(gs == gameStatus) return;
    gameStatus = gs;
    switch(gs){
        case GAME_OVER:
            screenDraw = drawMessageScreen;
            statusMsg = gameOverMessage;
            updateGame = dontUpdate;
            break;
        case WIN:
            screenDraw = drawMessageScreen;
            statusMsg = winMessage;
            updateGame = dontUpdate;
            break;
        case START:
            screenDraw = drawMessageScreen;
            statusMsg = initialMessage;
            updateGame = dontUpdate;
            break;
        case RUNNING:
            screenDraw = drawRunningScreen;
            currentArena = new Arena(*arena);
            updateGame = updateRunning;
            break;
        default:
            break;
    }
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
    if(key == 'b'){
        Player::setDrawCollisionBox(drawCollisionBox = !drawCollisionBox);
    }
    if(key == 'c'){
        Arena::setClearBullet(clearBullet = !clearBullet);
    }
    if(key == 'r' && gameStatus != RUNNING){
        setGameStatus(RUNNING);
    }
    if(key == 'm'){
        Arena::setMoveEnemies(moveEnemies = !moveEnemies);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void init(void)
{
    srand(time(NULL));
    ResetKeyStatus();
    Player::setDrawCollisionBox(drawCollisionBox);
    Arena::setClearBullet(clearBullet);
    Arena::setMoveEnemies(moveEnemies);
    setGameStatus(START);
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

    if(gameStatus != RUNNING) return;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        currentArena->playerShoot();
    }

    if(button == GLUT_RIGHT_BUTTON){
        bool isJumping;
        if(state == GLUT_DOWN) isJumping = true;
        else if(state == GLUT_UP) isJumping = false;

        currentArena->playerJump(isJumping, currentTime);
    }
}

void motionMouse(int x, int y){
    if(gameStatus != RUNNING) return;
    // ajustar o braço do player
    GLfloat relativeX = (x - Width/2) / (float)Width;
    GLfloat relativeY = (Height/2 - y) / (float)Height;

    currentArena->updatePlayerArm(relativeX, relativeY);
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

    setGameStatus((*updateGame)(timeDiference, currentTime));

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    
    if(argc < 2){
        cout << "Eh necessario passar o caminho do arquivo xml" << endl;
        exit(1);
    }

    parserXmlFile(argv[1], arena);

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
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