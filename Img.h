// Img.h: interface for the Img class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMG_H__B325E91C_7BE7_448B_B1D3_65EA16BBF824__INCLUDED_)
#define AFX_IMG_H__B325E91C_7BE7_448B_B1D3_65EA16BBF824__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Color.h"

class Img
{
public:
	// initilaize an image
	Img(void);
public:
	~Img(void);
	// image width
	int imgwidth;
	// image height
	int imgheight;
	// a picture
	Color **imga;
public:
	Img(int width, int height, Color pelcolor);
public:
	// get pixel color at (y, x)
	Color pixel(int x, int y);
public:
	void setPixel(int x, int y, Color curcolor);
public:
	// get image width
	int width(void);
public:
	// get image height
	int height(void);
public:
	// get pixel R value at (y, x)
	double getR(int x, int y);
public:
	// get pixel G value at (y, x)
	double getG(int x, int y);
public:
	// get pixel B value at (y, x)
	double getB(int x, int y);
};


#endif // !defined(AFX_IMG_H__B325E91C_7BE7_448B_B1D3_65EA16BBF824__INCLUDED_)
