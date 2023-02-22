#include "primitive.h"
#include <math.h>

#define M_2PI 360
#define M_PI  90
#define MIN(x,y) (x>y)?y:x 


int getRValue(COLORREF color) { return ((color >> 16) & 0x0FF); };
int getGValue(COLORREF color) { return ((color >> 8) & 0x0FF); };
int getBValue(COLORREF color) { return ((color >> 0) & 0x0FF); };

void DrawBox(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    int colorR, int colorG, int colorB, bool bTexture)
{
    // -- FRONT
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(0.0f, 0.0f, +1.0f);
    if (bTexture)
        ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    ::glEnd();

    // -- BACK
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(0.0f, 0.0f, -1.0f);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    ::glEnd();

    // -- LEFT
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(-1.0f, 0.0f, 0.0f);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    ::glEnd();

    // -- RIGHT
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(+1.0f, 0.0f, 0.0f);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + +zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    ::glEnd();

    // -- TOP
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(0.0f, +1.0f, 0.0f);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, +fHeightHalf + zCord, +fDepthHalf + yCord);
    ::glEnd();

    // BOTTOM
    ::glBegin(GL_TRIANGLES);
    ::glNormal3f(0.0f, -1.0f, 0.0f);
    if (bTexture) ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);

    if (bTexture) ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(-fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, -fDepthHalf + yCord);
    if (bTexture) ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(+fWidthHalf + xCord, -fHeightHalf + zCord, +fDepthHalf + yCord);
    ::glEnd();
}

void DrawCylinder(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture)
{
    float fReciprocalPrecisition = (float)(dAngleStep / M_2PI);

    // Cylinder top
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));

    int iSectorCount = 0;
    ::glBegin(GL_POLYGON);  // ? TRIANGLE_FAN ?

    for (double dTopAngle = M_2PI; dTopAngle > 0.0; dTopAngle -= dAngleStep)
    {
        // face normal
        ::glNormal3f(0.0F, +1.0F, 0.0F);
        double c = cos(dTopAngle);
        double s = sin(dTopAngle);

        // relative texture coordinates
        float fTextureOffsetS = 0.5F + (float)(0.5F * c);
        float fTextureOffsetT = 0.5F + (float)(0.5F * s);

        if (bTexture) ::glTexCoord2f(fTextureOffsetS, fTextureOffsetT);
        ::glVertex3f((float)(fWidthHalf * cos(dTopAngle) + xCord),
            fHeightHalf + zCord,
            (float)(fDepthHalf * sin(dTopAngle) + yCord));

    }
    ::glEnd();

    // Cylinder cover
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    iSectorCount = 0;
    ::glBegin(GL_TRIANGLES);
    for (double dCoverAngle1 = 0; dCoverAngle1 < M_2PI; dCoverAngle1 += dAngleStep)
    {
        double dCoverAngle2 = dCoverAngle1 + dAngleStep;
        float  fWidthPart1 = (float)(fWidthHalf * cos(dCoverAngle1) + xCord);
        float  fWidthPart2 = (float)(fWidthHalf * cos(dCoverAngle2) + xCord);
        float  fDepthPart1 = (float)(fDepthHalf * sin(dCoverAngle1) + yCord);
        float  fDepthPart2 = (float)(fDepthHalf * sin(dCoverAngle2) + yCord);

        // face normal
        ::glNormal3f((float)(1.0F * cos(dCoverAngle1 + dAngleStep / 2)),
            0.0F,
            (float)(1.0F * sin(dCoverAngle1 + dAngleStep / 2)));

        // relative texture coordinates
        float fTextureOffsetS1 = (float)(iSectorCount)*fReciprocalPrecisition;
        float fTextureOffsetT1 = 0.0F;
        float fTextureOffsetS2 = (float)(iSectorCount + 1) * fReciprocalPrecisition;
        float fTextureOffsetT2 = 1.0F;

        if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT1);
        ::glVertex3f(fWidthPart1, -fHeightHalf + zCord, fDepthPart1);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT2);
        ::glVertex3f(fWidthPart1, fHeightHalf + zCord, fDepthPart1);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT2);
        ::glVertex3f(fWidthPart2, fHeightHalf + zCord, fDepthPart2);

        if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT2);
        ::glVertex3f(fWidthPart2, fHeightHalf + zCord, fDepthPart2);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT1);
        ::glVertex3f(fWidthPart2, -fHeightHalf + zCord, fDepthPart2);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT1);
        ::glVertex3f(fWidthPart1, -fHeightHalf + zCord, fDepthPart1);
        iSectorCount++;

    }
    ::glEnd();

    // Cylinder bottom
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    iSectorCount = 0;
    ::glBegin(GL_POLYGON);  

    for (double dBottotmAngle = 0; dBottotmAngle < M_2PI; dBottotmAngle += dAngleStep)
    {
        // face normal
        ::glNormal3f(0.0F, -1.0F, 0.0F);

        double c = cos(dBottotmAngle);
        double s = sin(dBottotmAngle);

        // relative texture coordinates
        float fTextureOffsetS = 0.5F + (float)(0.5F * c);
        float fTextureOffsetT = 0.5F + (float)(0.5F * s);

        if (bTexture) ::glTexCoord2f(fTextureOffsetS, fTextureOffsetT);
        ::glVertex3f((float)(fWidthHalf * cos(dBottotmAngle) + xCord),
            -fHeightHalf + zCord,
            (float)(fDepthHalf * sin(dBottotmAngle) + yCord));

    }
    ::glEnd();
}

void DrawCone(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture)
{
    float fReciprocalPrecisition = (float)(dAngleStep / M_2PI);

    // Cone "Cover"
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    int iSectorCount = 0;
    ::glBegin(GL_TRIANGLES);
    for (double dCoverAngle1 = 0.0F; dCoverAngle1 < M_2PI; dCoverAngle1 += dAngleStep)
    {
        double dCoverAngle2 = dCoverAngle1 + dAngleStep;
        float  fWidthPart1 = (float)(fWidthHalf * cos(dCoverAngle1) + xCord);
        float  fWidthPart2 = (float)(fWidthHalf * cos(dCoverAngle2) + xCord);
        float  fDepthPart1 = (float)(fDepthHalf * sin(dCoverAngle1) + yCord);
        float  fDepthPart2 = (float)(fDepthHalf * sin(dCoverAngle2) + yCord);

        // face normal
        ::glNormal3f((fWidthPart1 + fWidthPart2) / 2, 0.0F, (fDepthPart1 + fDepthPart2) / 2);

        // relative texture coordinates
        float fTextureOffsetS1 = iSectorCount * fReciprocalPrecisition;
        float fTextureOffsetS2 = (iSectorCount + 1) * fReciprocalPrecisition;

        if (bTexture) ::glTexCoord2f(fTextureOffsetS1, 1.0);
        ::glVertex3f(0.0F + xCord, fHeightHalf + zCord, 0.0F + yCord);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS2, 0.0);
        ::glVertex3f(fWidthPart2, -fHeightHalf + zCord, fDepthPart2);
        if (bTexture) ::glTexCoord2f(fTextureOffsetS2, 0.0);
        ::glVertex3f(fWidthPart1, -fHeightHalf + zCord, fDepthPart1);

        iSectorCount++;
    }
    ::glEnd();

    // Cone Bottom
    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    iSectorCount = 0;
    ::glBegin(GL_POLYGON); 
    for (double dBottomAngle = 0; dBottomAngle < M_2PI; dBottomAngle += dAngleStep)
    {
        // face normal
        ::glNormal3f(0.0F, -1.0F, 0.0F);

        double c = cos(dBottomAngle);
        double s = sin(dBottomAngle);

        // relative texture coordinates
        float fTextureOffsetS = 0.5F + (float)(0.5F * c);
        float fTextureOffsetT = 0.5F + (float)(0.5F * s);

        if (bTexture) ::glTexCoord2f(fTextureOffsetS, fTextureOffsetT);
        ::glVertex3f((float)(fWidthHalf * c + xCord), -fHeightHalf + zCord, (float)(fDepthHalf * s + yCord));
    }
    ::glEnd();
}

void DrawSphere(float fWidthHalf, float fHeightHalf, float fDepthHalf, float xCord, float yCord, float zCord,
    double dAngleStep, int colorR, int colorG, int colorB, bool bTexture)
{
    float f1_10thPi = (float)(M_PI * 0.1f);
    float f2_10thPi = (float)(M_PI * 0.2f);
    float f3_10thPi = (float)(M_PI * 0.3f);
    float f7_10thPi = (float)(M_PI * 0.7f);
    float f8_10thPi = (float)(M_PI * 0.8f);
    float f9_10thPi = (float)(M_PI * 0.9f);

    float fPiQuarter = (float)(M_PI * 0.25f);
    float fPiHalf = (float)(M_PI * 0.50f);

    float fReciprocalPrecisition = dAngleStep / M_2PI;
    int   iStackCount = 0;

    // Cone Bottom

    if (colorR || colorG || colorB)
        ::glColor3f(MIN(1.0F, colorR / 255.0F),
            MIN(1.0F, colorG / 255.0F),
            MIN(1.0F, colorB / 255.0F));
    ::glBegin(GL_TRIANGLES);
    // Plane: X/Y; Rotation axis: Z; 0° in positive X direction
    for (double dStackAngle1 = 0.0f; dStackAngle1 < M_PI; dStackAngle1 += dAngleStep)
    {
        double dStackAngle2 = dStackAngle1 + dAngleStep;
        double s1 = sin(dStackAngle1);
        double s2 = sin(dStackAngle2);
        float fStackHeightHalf1 = (float)(-fHeightHalf * cos(dStackAngle1) + zCord);
        float fStackHeightHalf2 = (float)(-fHeightHalf * cos(dStackAngle2) + zCord);
        float fStackWidthHalfTop = (float)(fWidthHalf * s1);
        float fStackWidthHalfBtm = (float)(fWidthHalf * s2);
        float fStackDepthHalfTop = (float)(fDepthHalf * s1);
        float fStackDepthHalfBtm = (float)(fDepthHalf * s2);
        int   iSectorCount = 0;

        // Plane: X/Z; Rotation axis: Y; 0° in positive X direction
        for (double dSectorAngle1 = 0.0f; dSectorAngle1 < M_2PI; dSectorAngle1 += dAngleStep)
        {
            double dSectorAngle2 = dSectorAngle1 + dAngleStep;

            // face corners
            float fLeftTop[3] = { (float)(fStackWidthHalfTop * cos(dSectorAngle1) + xCord),
                                  fStackHeightHalf1,
                                  (float)(fStackDepthHalfTop * sin(dSectorAngle1)) + yCord };
            float fRghtTop[3] = { (float)(fStackWidthHalfTop * cos(dSectorAngle2) + xCord),
                                  fStackHeightHalf1,
                                  (float)(fStackDepthHalfTop * sin(dSectorAngle2) + yCord) };
            float fLeftBtm[3] = { (float)(fStackWidthHalfBtm * cos(dSectorAngle1) + xCord),
                                  fStackHeightHalf2,
                                  (float)(fStackDepthHalfBtm * sin(dSectorAngle1) + yCord) };
            float fRghtBtm[3] = { (float)(fStackWidthHalfBtm * cos(dSectorAngle2) + xCord),
                                  fStackHeightHalf2,
                                  (float)(fStackDepthHalfBtm * sin(dSectorAngle2) + yCord) };

            // face normal
            float n[3] = { (fLeftTop[0] + fRghtBtm[0]) / 2,
                           (fStackHeightHalf1 + fStackHeightHalf2) / 2,
                           (fLeftTop[2] + fRghtBtm[2]) / 2 };

            // relative texture coordinates
            float fTextureOffsetS1 = iSectorCount * fReciprocalPrecisition;
            float fTextureOffsetT1 = 2 * iStackCount * fReciprocalPrecisition;
            float fTextureOffsetS2 = (iSectorCount + 1) * fReciprocalPrecisition;
            float fTextureOffsetT2 = 2 * (iStackCount + 1) * fReciprocalPrecisition;


            if (fLeftBtm[0] != fRghtBtm[0] || fLeftBtm[2] != fRghtBtm[2])
            {
                // face normal
                ::glNormal3f(n[0], n[1], n[2]);

                if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT1);
                ::glVertex3fv(fLeftTop);
                if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT2);
                ::glVertex3fv(fLeftBtm);
                if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT2);
                ::glVertex3fv(fRghtBtm);
            }
            if (fLeftTop[0] != fRghtTop[0] || fLeftTop[2] != fRghtTop[2])
            {
                // face normal
                ::glNormal3f(n[0], n[1], n[2]);

                if (bTexture) ::glTexCoord2f(fTextureOffsetS1, fTextureOffsetT1);
                ::glVertex3fv(fLeftTop);
                if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT2);
                ::glVertex3fv(fRghtBtm);
                if (bTexture) ::glTexCoord2f(fTextureOffsetS2, fTextureOffsetT1);
                ::glVertex3fv(fRghtTop);
            }

            iSectorCount++;
        }
        iStackCount++;
    }
    ::glEnd();
}