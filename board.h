#pragma once
#include "Pawn.h"
#include "king.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rock.h"
#include "vkgllib.h"
#include <iostream>
#include "../gl/glut.h"

class Board {
public:
	Board();
	virtual ~Board();

	void Draw();
	void InitializePieces();
	int setMoveEnable();

private:
	//Square board[8][8];
	void drawterrain();
	void drawBoardSquares();
	bool LoadLandTextures();
	void drawChessBoard();

	void skydraw();
	GLuint LoadSky(char* filename);

	
private:
	GLuint texture[6];

	Pawn whitePawn[8], blackPawn[8];

	King whiteKing[1], blackKing[1];

	Queen whiteQueen[1], blackQueen[1];

	Bishop whiteBishop[2], blackBishop[2];

	Rock whiteRock[2], blackRock[2];
	
	Knight whiteKnight[2], blackKnight[2];

	//int imove;
	bool imove;
	bool wb_PawnMove;
	int wMoveIndex;
	int bMoveIndex;
	float step;


	BITMAPINFOHEADER	bitmapInfoHeader;	// temp bitmap info header
	BITMAPINFOHEADER	landInfo;			// land texture info header
	BITMAPINFOHEADER	waterInfo;			// water texture info header

	//AUX_RGBImageRec
	unsigned char* imageData;		   // the map image data
	unsigned char* landTexture;	   // land texture data
	unsigned int		   land;			      // the land texture object

	////// Terrain Data
	float terrain[MAP_X][MAP_Z][3];		// heightfield terrain data (0-255); 256x256

};
