#pragma once
class Rock
{
public:
	Rock();

	void Draw();
	void SetIndex(int idx);
	void SetColor(int ired, int igreen, int iblue);

private:
	int iteam;
	int index;
	int rpos, cpos;
	int colorR, colorG, colorB;
	int isTexture;
};

