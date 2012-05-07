// Img.cpp: implementation of the Img class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageDecomposition.h"
#include "Img.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// initilaize an image
Img::Img(void)
: imgwidth(0)
, imgheight(0)
, imga(NULL)
{
}

Img::~Img(void)
{
// 	if(imga)
// 	{
// 		for (int k=0; k<imgheight; k++)
// 		{
// 			delete[] imga[k];
// 			imga[k] = NULL;
// 		}
// 		delete[] imga;
// 		imga = NULL;
// 	}
}

Img::Img(int width, int height, Color pelcolor)
{
	imgwidth = width;
	imgheight = height;
	
	//image memory allocation
	imga = new Color*[height];
	for (int k=0; k<height; k++)
	{
		imga[k] = new Color[width];
	}
	
	//image initialization
	for (int j=0; j<height; j++)
	{
		for (int i=0; i<width; i++)
		{
			imga[j][i].cr = pelcolor.cr;
			imga[j][i].cg = pelcolor.cg;
			imga[j][i].cb = pelcolor.cb;
		}
	}
}

// get pixel color at (y, x)
Color Img::pixel(int x, int y)
{
	Color curcolor = imga[y][x];
	return curcolor;
}

//set pixel color value at (y,x)
void Img::setPixel(int x, int y, Color curcolor)
{
	imga[y][x].cr = curcolor.cr;
	imga[y][x].cg = curcolor.cg;
	imga[y][x].cb = curcolor.cb;
}

// get image width
int Img::width(void)
{
	return imgwidth;
}

// get image height
int Img::height(void)
{
	return imgheight;
}

// get pixel R value at (y, x)
double Img::getR(int x, int y)
{
	return imga[y][x].cr;
}

// get pixel G value at (y, x)
double Img::getG(int x, int y)
{
	return imga[y][x].cg;
}

// get pixe lB value at (y, x)
double Img::getB(int x, int y)
{
	return imga[y][x].cb;
}


