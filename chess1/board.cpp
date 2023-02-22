#include "../gl/glut.h"
#include "board.h"



GLfloat     chessBoard[24][3] = {
    {-4.5, -0.01 , -4.5},
    {-4.5, -0.01 ,  4.5},
    { 4.5, -0.01 ,  4.5},
    { 4.5, -0.01 , -4.5},

    {-4.5, -0.5 , -4.5},
    {-4.5, -0.5 ,  4.5},
    { 4.5, -0.5 ,  4.5},
    { 4.5, -0.5 , -4.5},

    {-4.5, -0.01 , -4.5},
    {-4.5, -0.01 ,  4.5},
    {-4.5, -0.5 ,  4.5},
    {-4.5, -0.5 , -4.5},

    {-4.5, -0.01,  4.5},
    { 4.5, -0.01,  4.5},
    { 4.5, -0.5 ,  4.5},
    {-4.5, -0.5 ,  4.5},

    { 4.5, -0.01 ,  4.5},
    { 4.5, -0.01 , -4.5},
    { 4.5, -0.5 , -4.5},
    { 4.5, -0.5 ,  4.5},

    { 4.5, -0.01 , -4.5},
    {-4.5, -0.01 , -4.5},
    {-4.5, -0.5 , -4.5},
    { 4.5, -0.5 , -4.5}

};

// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		   No support for 8-bit bitmaps.
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;							      // the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char* bitmapImage;			// bitmap image data
	int					imageIdx = 0;		   // image index counter
	unsigned char		tempRGB;				   // swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	//fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	unsigned char* temp1 = (unsigned char*)malloc(14);
    unsigned char* temp2 = (unsigned char*)malloc(40);
	fread(temp1, 14, 1, filePtr);
	bitmapFileHeader.bfType = temp1[1] << 8 | temp1[0];
	bitmapFileHeader.bfSize = temp1[5] << 24 | temp1[4] << 24 | temp1[3] << 8 | temp1[2];
	bitmapFileHeader.bfReserved1 = temp1[7] << 8 | temp1[6];
	bitmapFileHeader.bfReserved2 = temp1[9] << 8 | temp1[8];
	bitmapFileHeader.bfOffBits = temp1[13] << 24 | temp1[12] << 24 | temp1[11] << 8 | temp1[10];


	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(temp2, sizeof(BITMAPINFOHEADER), 1, filePtr);
	bitmapInfoHeader->biSize = temp2[3] << 24 | temp2[2] << 24 | temp2[1] << 8 | temp2[0];
	bitmapInfoHeader->biWidth = temp2[7] << 24 | temp2[6] << 24 | temp2[5] << 8 | temp2[4];
	bitmapInfoHeader->biHeight = temp2[11] << 24 | temp2[10] << 24 | temp2[9] << 8 | temp2[8];
	bitmapInfoHeader->biPlanes = temp2[13] << 8 | temp2[12];
	bitmapInfoHeader->biBitCount = temp2[15] << 8 | temp2[14];
	bitmapInfoHeader->biCompression = temp2[19] << 24 | temp2[18] << 24 | temp2[17] << 8 | temp2[16];
	bitmapInfoHeader->biSizeImage = temp2[23] << 24 | temp2[22] << 24 | temp2[21] << 8 | temp2[20];
	bitmapInfoHeader->biXPelsPerMeter = temp2[27] << 24 | temp2[26] << 24 | temp2[25] << 8 | temp2[24];
	bitmapInfoHeader->biYPelsPerMeter = temp2[31] << 24 | temp2[30] << 24 | temp2[29] << 8 | temp2[28];
	bitmapInfoHeader->biClrUsed = temp2[35] << 24 | temp2[34] << 24 | temp2[33] << 8 | temp2[32];
	bitmapInfoHeader->biClrImportant = temp2[39] << 24 | temp2[38] << 24 | temp2[37] << 8 | temp2[36];

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}


GLuint Board::LoadSky(char* filename)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;

    landTexture = LoadBitmapFile(filename, &landInfo);
    if (!landTexture)
    {
        return 0x1;//NULL;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, landInfo.biHeight, landInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture);
    free(landTexture);
    return texture;

}

void Board::skydraw()
{
    float x = 0;
    float y = 0;
    float z = 0;
    float width = 100;
    float height = 100;
    float length = 100;
    // Bind the BACK texture of the sky map to the BACK side of the cube
    //glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // Center the skybox
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();

}

/**
    Drawing a chess board using points from array "chessBoard"
*/
void Board::drawChessBoard()
{
    glPushMatrix();
    /**Drawing bottom of the chess board*/
    //glNormal3fv(normal_valid_move);
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.3, 0.3);

    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 4; i++)
            glVertex3fv(chessBoard[j*4+i]);
    }
    glEnd();

    glPopMatrix();
}

bool Board::LoadLandTextures()
{
	// load the land texture data
	landTexture = LoadBitmapFile((char*)"green1.bmp", &landInfo);
    if (!landTexture)
    {
        return false;
    }
    
	// generate the land texture as a mipmap
	glGenTextures(1, &land);
    glBindTexture(GL_TEXTURE_2D, land);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo.biHeight, landInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture);

	return true;
}

Board::Board() {
    //whitePawn = new Pawn(0, 0);
    imove = false;
    wb_PawnMove = false;
    wMoveIndex = 0;
    bMoveIndex = 0;
    step = 0.0;
}

Board::~Board() {
}

void Board::Draw() {

 /*
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(80.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 80.0f, 0.0f);
    glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 80.0f);
    glEnd();
*/
    glBindTexture(GL_TEXTURE_2D, land);
    drawterrain();

    for (int i = 0; i < 8; i++) {
        if (imove == true){
            if ((wMoveIndex == i) && !wb_PawnMove) {
                if (step < 1.0)
                {
                    step += 0.2;
                    whitePawn[wMoveIndex].SetNewPos(step);
                    whitePawn[wMoveIndex].Move();
                    whitePawn[wMoveIndex].GetCurPos();
                }
                else
                {
                    step = 0.0;
                    if (wb_PawnMove) wb_PawnMove = false;
                    else wb_PawnMove = true;
                    wMoveIndex++;
                    if (wMoveIndex == 8) wMoveIndex = 0;
                }
            }
            whitePawn[i].Draw();
        }   
        else {
            wMoveIndex = 0;
            wb_PawnMove = false;
            whitePawn[i].Reset();
            whitePawn[i].Draw();
        }
    }

    for (int i = 0; i < 8; i++) {
        if (imove == true){
            if ((bMoveIndex == i) && wb_PawnMove) {
                if (step < 1.0)
                {
                    step += 0.2;
                    blackPawn[bMoveIndex].SetNewPos(-step);
                    blackPawn[bMoveIndex].Move();
                    blackPawn[bMoveIndex].GetCurPos();
                }
                else
                {
                    step = 0.0;
                    if (wb_PawnMove) wb_PawnMove = false;
                    else wb_PawnMove = true;
                    bMoveIndex++;
                    if (bMoveIndex == 8)
                    {
                        bMoveIndex = 0;
                        for (int j = 0; j < 8; j++)
                        {
                            whitePawn[j].Reset();
                            blackPawn[j].Reset();
                        }
                    }

                }
            }
            blackPawn[i].Draw();
        }
        else
        {
            bMoveIndex = 0;
            blackPawn[i].Reset();
            blackPawn[i].Draw();
        }
    }

    whiteKing[0].Draw();
    blackKing[0].Draw();

    whiteQueen[0].Draw();
    blackQueen[0].Draw();

    for (int i = 0; i < 2; i++) {
        whiteRock[i].Draw();
    }
    for (int i = 0; i < 2; i++) {
        blackRock[i].Draw();
    }

    for (int i = 0; i < 2; i++) {
        whiteBishop[i].Draw();
    }
    for (int i = 0; i < 2; i++) {
        blackBishop[i].Draw();
    }

    for (int i = 0; i < 2; i++) {
        whiteKnight[i].Draw();
    }
    for (int i = 0; i < 2; i++) {
        blackKnight[i].Draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    drawBoardSquares();

    drawChessBoard();
    skydraw();
}

int Board::setMoveEnable()
{
    if (imove)imove = false;
    else imove = true;
    return imove;
}

void Board::drawterrain()
{


    // we are going to loop through all of our terrain's data points,
    // but we only want to draw one triangle strip for each set along the x-axis.
    for (int z = 0; z < MAP_Z - 1/*-mousecnt*/; z++)
        //for (int z = 0; z < 2 - 1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < MAP_X - 1; x++)
            //for (int x = 0; x < 2 - 1; x++)
        {
            // for each vertex, we calculate the grayscale shade color,             

            // draw vertex 0
            glColor3f(terrain[x][z][1] / 255.0f * 255.0f / 32.0f, terrain[x][z][1] / 255.0f * 255.0f / 32.0f, terrain[x][z][1] / 255.0f * 255.0f / 32.0f);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(terrain[x][z][0], terrain[x][z][1] - MAP_X, terrain[x][z][2]);

            // draw vertex 1
            glTexCoord2f(0.0f, 0.0f);
            glColor3f(terrain[x + 1][z][1] / 255.0f * 255.0f / 32.0f, terrain[x + 1][z][1] / 255.0f * 255.0f / 32.0f, terrain[x + 1][z][1] / 255.0f * 255.0f / 32.0f);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(terrain[x + 1][z][0], terrain[x + 1][z][1] - MAP_X, terrain[x + 1][z][2]);

            // draw vertex 2
            glTexCoord2f(0.0f, 0.0f);
            glColor3f(terrain[x][z + 1][1] / 255.0f * 255.0f / 32.0f, terrain[x][z + 1][1] / 255.0f * 255.0f / 32.0f, terrain[x][z + 1][1] / 255.0f * 255.0f / 32.0f);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(terrain[x][z + 1][0], terrain[x][z + 1][1] - MAP_X, terrain[x][z + 1][2]);

            // draw vertex 3
            glColor3f(terrain[x + 1][z + 1][1] / 255.0f * 255.0f / 32.0f, terrain[x + 1][z + 1][1] / 255.0f * 255.0f / 32.0f, terrain[x + 1][z + 1][1] / 255.0f * 255.0f / 32.0f);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1] - MAP_X, terrain[x + 1][z + 1][2]);

            if (0) {
                printf("%.02f,%.02f,%.02f\n", terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);
                printf("%.02f,%.02f,%.02f\n", terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);
                printf("%.02f,%.02f,%.02f\n", terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);
                printf("%.02f,%.02f,%.02f\n", terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1], terrain[x + 1][z + 1][2]);
                printf("\n");
            }


        }
        glEnd();
    }
}
void Board::InitializePieces() {

    // loop through all of the heightfield points, calculating
    // the coordinates for each point

    imageData = LoadBitmapFile((char*)"terrain3.bmp", &bitmapInfoHeader);

    for (int z = 0; z < MAP_Z; z++)
    {
        for (int x = 0; x < MAP_X; x++)
        {
            terrain[x][z][0] = float(x) * MAP_SCALE - 25.0f;
            terrain[x][z][1] = (float)imageData[(z * MAP_Z + x) * 3] * MAP_X / 255;
            terrain[x][z][2] = -float(z) * MAP_SCALE + 25.0f;
        }
    }


    // initialize the terrain data and load the textures

    LoadLandTextures();
    for (int i = 0; i < 8; i++)
    {
        whitePawn[i].SetIndex(i);
        whitePawn[i].SetColor(255, 255, 255);
    }
    for (int i = 0; i < 8; i++)
    {
        blackPawn[i].SetIndex(i+8);
        blackPawn[i].SetColor(255, 150, 150);
    }


    whiteKing[0].SetIndex(0);
    whiteKing[0].SetColor(255, 255, 255);

    blackKing[0].SetIndex(1);
    blackKing[0].SetColor(255, 150, 150);

    whiteQueen[0].SetIndex(0);
    whiteQueen[0].SetColor(255, 255, 255);

    blackQueen[0].SetIndex(1);
    blackQueen[0].SetColor(255, 150, 150);


    for (int i = 0; i < 2; i++)
    {
        whiteRock[i].SetIndex(i);
        whiteRock[i].SetColor(255, 255, 255);
    }

    for (int i = 0; i < 2; i++)
    {
        blackRock[i].SetIndex(i + 2);
        blackRock[i].SetColor(255, 150, 150);
    }

    for (int i = 0; i < 2; i++)
    {
        whiteBishop[i].SetIndex(i);
        whiteBishop[i].SetColor(255, 255, 255);
    }

    for (int i = 0; i < 2; i++)
    {
        blackBishop[i].SetIndex(i + 2);
        blackBishop[i].SetColor(255, 150, 150);
    }


    for (int i = 0; i < 2; i++)
    {
        whiteKnight[i].SetIndex(i);
        whiteKnight[i].SetColor(255, 255, 255);
    }

    for (int i = 0; i < 2; i++)
    {
        blackKnight[i].SetIndex(i + 2);
        blackKnight[i].SetColor(255, 150, 150);
    }

    texture[0] = LoadSky((char*)"skybox/Back.bmp"); //load the texture
    texture[1] = LoadSky((char*)"skybox/Front.bmp"); //load the texture
    texture[2] = LoadSky((char*)"skybox/Left.bmp"); //load the texture
    texture[3] = LoadSky((char*)"skybox/Right.bmp"); //load the texture
    texture[4] = LoadSky((char*)"skybox/Bottom.bmp"); //load the texture
    texture[5] = LoadSky((char*)"skybox/Top.bmp"); //load the texture

}

void Board::drawBoardSquares()
{
    float r, c;
    for (int row = 1; row <= 8; row++)
    {
        for (int col = 1; col <= 8; col++)
        {
            r = 1.0 * (row - 5);
            c = 1.0 * (col - 5);
            /*
            if (row == selectedRow && col == selectedCol)
            {
                if (selected) glColor3f(0.33f, 0.420f, 0.184f);
                else if (chess->isSquareOccupied(selectedRow, selectedCol))
                    if (chess->getPieceColor(selectedRow, selectedCol) == chess->getTurnColor())
                        glColor3f(0.0f, 0.5f, 0.0f);
                    else glColor3f(1.0f, 0.0f, 0.0f);
                else glColor3f(0.3f, 0.7f, 0.5f);
            }
            else if ((row + col) & 1) glColor3f(1.0, 1.0, 1.0);
            else glColor3f(0.0, 0.0, 0.0);
            */
            if ((row + col) & 1) glColor3f(1.0, 1.0, 1.0);
            else glColor3f(0.0, 0.0, 0.0);

            glPushMatrix();
            glTranslatef(r, 0.0f, c);
            glBegin(GL_TRIANGLES);
            //..glNormal3fv(normal_board);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glEnd();
            glPopMatrix();
        }
    }
    glColor3f(0, 0, 0);
}