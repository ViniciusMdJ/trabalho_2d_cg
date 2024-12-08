#ifndef MATRIX_TRANSFORMATIONS_H
#define MATRIX_TRANSFORMATIONS_H

#include <bits/stdc++.h>

namespace MatrixTransformations
{
    void mtTranslatef(float x, float y, float z);
    void mtRotatef(float angle, float x, float y, float z);
    void mtScalef(float x, float y, float z);

    void mtPushMatrix();
    void mtPopMatrix();
    void mtLoadIdentity();

    void mtTransformPoint(float &x, float &y, float &z);
    std::array<std::array<float, 4>, 4> matrixMultiplication(std::array<std::array<float, 4>, 4> &a, std::array<std::array<float, 4>, 4> &b);
}

#endif//MATRIX_TRANSFORMATIONS_H