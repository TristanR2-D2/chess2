#pragma once

#include "../gl/glut.h"

typedef unsigned long COLORREF;
void DrawBox(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    int colorR, int colorG, int colorB, bool bTexture);
void DrawCylinder(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture = false);
void DrawCone(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture = false);
void DrawSphere(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture = false);