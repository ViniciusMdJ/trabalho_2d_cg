#ifndef TEXT_H
#define TEXT_H

#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class Text {
    string value;
    static void *font;
    static int fontHeightPx;

    float getWidthNormalized();
    float getHeightNormalized();

public:
    Text();
    Text(string value);
    void setValue(string value);
    void drawText(GLfloat x, GLfloat y);
    void drawTextCentered(GLfloat x, GLfloat y);
};

#endif//TEXT_H