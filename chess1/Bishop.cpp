#include "Bishop.h"
#include "primitive.h"

int bishoppos[4][2] = {
	0,2,
	0,5,
	7,5,
	7,2
};
Bishop::Bishop()
{
	rpos = 0;// row;
	cpos = 0;// col;
	colorR = 255;
	colorG = 255;
	colorB = 255;
	isTexture = 1;

}
void Bishop::SetIndex(int idx)
{
	index = idx;
}
void Bishop::SetColor(int ired, int igreen, int iblue)
{
	colorR = ired;
	colorG = igreen;
	colorB = iblue;
}
void Bishop::Draw()
{
	float r, c;
	r = (float)(1.0 * (bishoppos[index][0] - 3.5));
	c = (float)(1.0 * (bishoppos[index][1] - 3.5));

	glPushMatrix();
	glTranslatef(r, 0.0f, c);
	DrawCylinder(0.5f, 0.1f, 0.5f, 0.0f, 0.0f, 0.1f, 1, colorR, colorG, colorB, isTexture);
	DrawSphere(0.45f, 0.2f, 0.45f, 0.0f, 0.0f, 0.3f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.4f, 0.25f, 0.0f, 0.0f, 0.8f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.4f, 0.1f, 0.4f, 0.0f, 0.0f, 1.3f, 1, colorR, colorG, colorB, isTexture);
	DrawCone(0.3f, 0.2f, 0.3f, 0.0f, 0.0f, 1.6f, 1, colorR, colorG, colorB, isTexture);
	glPopMatrix();

}

