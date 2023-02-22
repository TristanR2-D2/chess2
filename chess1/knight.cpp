#include "Knight.h"
#include "primitive.h"

int knightpos[4][2] = {
	0,1,
	0,6,
	7,6,
	7,1
};
Knight::Knight()
{
	rpos = 0;// row;
	cpos = 0;// col;
	colorR = 255;
	colorG = 255;
	colorB = 255;
	isTexture = 1;

}
void Knight::SetIndex(int idx)
{
	index = idx;
}
void Knight::SetColor(int ired, int igreen, int iblue)
{
	colorR = ired;
	colorG = igreen;
	colorB = iblue;
}
void Knight::Draw()
{
	float r, c;
	r = (float)(1.0 * (knightpos[index][0] - 3.5));
	c = (float)(1.0 * (knightpos[index][1] - 3.5));

	glPushMatrix();
	glTranslatef(r, 0.0f, c);
	DrawCylinder(0.5f, 0.1f, 0.5f, 0.0f, 0.0f, 0.1f, 1, colorR, colorG, colorB, isTexture);
	DrawCone(0.4f, 0.5f, 0.4f, 0.0f, 0.0f, 0.7f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.4f, 0.25f, 0.0f, 0.0f, 0.8f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.4f, 0.1f, 0.4f, 0.0f, 0.0f, 1.3f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.2f, 0.25f, 0.0f, 0.0f, 1.6f, 1, colorR, colorG, colorB, isTexture);
	glPopMatrix();

}