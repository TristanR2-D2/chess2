#include "Rock.h"
#include "primitive.h"

int rockpos[4][2] = {
	0,0,
	0,7,
	7,7,
	7,0
};
Rock::Rock()
{
	rpos = 0;// row;
	cpos = 0;// col;
	colorR = 255;
	colorG = 255;
	colorB = 255;
	isTexture = 1;

}
void Rock::SetIndex(int idx)
{
	index = idx;
}
void Rock::SetColor(int ired, int igreen, int iblue)
{
	colorR = ired;
	colorG = igreen;
	colorB = iblue;
}
void Rock::Draw()
{
	float r, c;
	r = (float)(1.0 * (rockpos[index][0] - 3.5));
	c = (float)(1.0 * (rockpos[index][1] - 3.5));

	glPushMatrix();
	glTranslatef(r, 0.0f, c);
	DrawCylinder(0.5f, 0.1f, 0.5f, 0.0f, 0.0f, 0.1f, 1, colorR, colorG, colorB, isTexture);
	DrawCone(0.4f, 0.5f, 0.4f, 0.0f, 0.0f, 0.7f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.4f, 0.25f, 0.0f, 0.0f, 0.8f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.4f, 0.1f, 0.4f, 0.0f, 0.0f, 1.3f, 1, colorR, colorG, colorB, isTexture);
	DrawCylinder(0.25f, 0.2f, 0.25f, 0.0f, 0.0f, 1.6f, 1, colorR, colorG, colorB, isTexture);
	glPopMatrix();

}
