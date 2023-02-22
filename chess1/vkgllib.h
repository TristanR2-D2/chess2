
#ifndef _vkgllib_h
#define _vkgllib_h

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

#pragma warning(disable:4996)

using namespace std;


// definition of PI
#define PI						3.14159265

////// Defines
#define BITMAP_ID 0x4D42		      // the universal bitmap ID
#define MAP_X	32				         // size of map along x-axis
#define MAP_Z	32				         // size of map along z-axis
#define MAP_SCALE	50/32//20.0f		         // the scale of the terrain map

////// Texture Information

typedef unsigned long DWORD;
typedef long LONG;
typedef unsigned short WORD;

typedef struct tagBITMAPINFOHEADER {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;



#endif