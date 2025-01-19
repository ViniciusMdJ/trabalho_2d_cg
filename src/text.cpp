#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "../include/text.h"

using namespace std;

void *Text::font = GLUT_BITMAP_HELVETICA_18;
int Text::fontHeightPx = 10;

Text::Text() {
    this->value = "";
}

Text::Text(string value) {
    this->value = value;
}

void Text::setValue(string value) {
    this->value = value;
}

void Text::drawText(GLfloat x, GLfloat y) {
    glRasterPos2f(x, y);
    for (int i = 0; i < value.length(); i++) {
        glutBitmapCharacter(font, this->value[i]);
    }
}

void Text::drawTextCentered(GLfloat x, GLfloat y) {
    int length = value.length();
   
    float normalizedWidth = getWidthNormalized();
    // std::cout << "largura " << normalizedWidth << std::endl;

    // Calcula a posição inicial para centralizar
    float startX = x - (normalizedWidth / 2.0f);
    float startY = y - (getHeightNormalized() / 2.0f);
    // std::cout << "cordenadas " << startX << " " << y << std::endl;

    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
        glRasterPos2f(startX, startY);
        for (int i = 0; i < length; i++) {
            glutBitmapCharacter(font, value[i]);
        }
    glPopMatrix();
}

float Text::getHeightNormalized() {
    return fontHeightPx / (float)glutGet(GLUT_WINDOW_HEIGHT);
}

float Text::getWidthNormalized() {
    int maxPx = 0, current = 0;
    for(int i = 0; i < value.length(); i++) {
        if(value[i] == '\n') {
            maxPx = std::max(maxPx, current);
            current = 0;
        } else {
            current += glutBitmapWidth(font, value[i]);
        }
    }
    maxPx = std::max(maxPx, current);

    return maxPx / (float)glutGet(GLUT_WINDOW_WIDTH);
}