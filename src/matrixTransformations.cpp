#include "../include/matrixTranformations.h"

namespace MatrixTransformations
{
    std::array<std::array<float, 4>, 4> matrixStack[32];

    int matrixStackPointer = 0;

    std::array<std::array<float, 4>, 4> currentMatrix;

    void mtTranslatef(float x, float y, float z){
        currentMatrix[3][0] = currentMatrix[0][0] * x + currentMatrix[1][0] * y + currentMatrix[2][0] * z + currentMatrix[3][0];
        currentMatrix[3][1] = currentMatrix[0][1] * x + currentMatrix[1][1] * y + currentMatrix[2][1] * z + currentMatrix[3][1];
        currentMatrix[3][2] = currentMatrix[0][2] * x + currentMatrix[1][2] * y + currentMatrix[2][2] * z + currentMatrix[3][2];
        currentMatrix[3][3] = currentMatrix[0][3] * x + currentMatrix[1][3] * y + currentMatrix[2][3] * z + currentMatrix[3][3];
    }

    void mtRotatef(float angle, float x, float y, float z){
        angle = angle * M_PI / 180.0;
        float c = cos(angle);
        float s = sin(angle);
        float t = 1 - c;

        float nx = x / sqrt(x * x + y * y + z * z);
        float ny = y / sqrt(x * x + y * y + z * z);
        float nz = z / sqrt(x * x + y * y + z * z);

        std::array<std::array<float, 4>, 4> rotationMatrix = {{
            {t * nx * nx + c, t * nx * ny - s * nz, t * nx * nz + s * ny, 0},
            {t * nx * ny + s * nz, t * ny * ny + c, t * ny * nz - s * nx, 0},
            {t * nx * nz - s * ny, t * ny * nz + s * nx, t * nz * nz + c, 0},
            {0, 0, 0, 1}
        }};

        currentMatrix = matrixMultiplication(rotationMatrix, currentMatrix);
    }

    void mtScalef(float x, float y, float z){
        for (int i = 0; i < 4; ++i) {
            currentMatrix[i][0] *= x;
            currentMatrix[i][1] *= y;
            currentMatrix[i][2] *= z;
        }
    }

    void mtPushMatrix(){
        matrixStack[matrixStackPointer] = currentMatrix;
        matrixStackPointer++;
    }

    void mtPopMatrix(){
        if (matrixStackPointer > 0)
        {
            matrixStackPointer--;
            currentMatrix = matrixStack[matrixStackPointer];
        }
    }

    void mtLoadIdentity(){
        currentMatrix = {{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }};
    }

    std::array<std::array<float, 4>, 4> matrixMultiplication(std::array<std::array<float, 4>, 4> &a, std::array<std::array<float, 4>, 4> &b){
        std::array<std::array<float, 4>, 4> result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

    void mtTransformPoint(float &x, float &y, float &z){
        float tx = x;
        float ty = y;
        float tz = z;

        x = tx * currentMatrix[0][0] + ty * currentMatrix[1][0] + tz * currentMatrix[2][0] + currentMatrix[3][0];
        y = tx * currentMatrix[0][1] + ty * currentMatrix[1][1] + tz * currentMatrix[2][1] + currentMatrix[3][1];
        z = tx * currentMatrix[0][2] + ty * currentMatrix[1][2] + tz * currentMatrix[2][2] + currentMatrix[3][2];
    }
}