#include "Queen.h"
#include "primitive.h"

int queenpos[2][2] = {
	0,4,
	7,3,
};
Queen::Queen()
{
	rpos = 0;// row;
	cpos = 0;// col;
	colorR = 255;
	colorG = 255;
	colorB = 255;
	isTexture = 1;

}
void Queen::SetIndex(int idx)
{
	index = idx;
}
void Queen::SetColor(int ired, int igreen, int iblue)
{
	colorR = ired;
	colorG = igreen;
	colorB = iblue;
}
void Queen::Draw()
{
	float r, c;
	r = (float)(1.0 * (queenpos[index][0] - 3.5));
	c = (float)(1.0 * (queenpos[index][1] - 3.5));

	glPushMatrix();
	glTranslatef(r, 0.0f, c);
	DrawCylinder(0.5f, 0.1f, 0.5f, 0.0f, 0.0f, 0.1f, 1, colorR, colorG, colorB, isTexture);
	DrawCone(0.45f, 0.4f, 0.45f, 0.0f, 0.0f, 0.6f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.6f, 0.25f, 0.0f, 0.0f, 1.0f, 1, colorR, colorG, colorB, isTexture);
	DrawSphere(0.45f, 0.2f, 0.45f, 0.0f, 0.0f, 1.7f, 1, colorR, colorG, colorB, isTexture);
	DrawSphere(0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 2.1f, 1, colorR, colorG, colorB, isTexture);
	glPopMatrix();

}
