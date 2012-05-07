// Color.cpp: implementation of the Color class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageDecomposition.h"
#include "Color.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
 Color class
 zhao lili
*/

// #if (IMGTYPE==0)
// #define MAX_PIX_VAL 255
// #else
// #define MAX_PIX_VAL 65535
// #endif

Color::Color(void)
: cr(0)
, cg(0)
, cb(0)
{
	index = -1;
	//scribbled = false;
}

Color::~Color(void)
{
}

Color::Color(Color &C)
{
	cr = C.getR();
	cg = C.getG();
	cb = C.getB();
	index = C.index;
//	scribbled = false;
}
// the real pixel value divided by the maximum pixel value
Color::Color(double r, double g, double b)
{
	cr = r;
	cg = g;
	cb = b;
	index = -1;
//	scribbled = false;
}

Color::Color(double r, double g, double b, int indx)
{
	cr = r;
	cg = g;
	cb = b;
	index = indx;
//	scribbled = true;
}

// get R value
double Color::getR()
{
	return cr;
}

// get G value
double Color::getG()
{
	return cg;
}

//
double Color::getB()
{
	return cb;
}

// current pixel  is fixed-illumination or not
bool Color::getA(void)
{
	if (cb>0)
	{
		index = (int)cb;
		return true;
	}
	else
		return false;
//	return scribbled;
	//return (cb>0);
}

//get scribble index
int Color::indexOf(Color &C)
{
	return C.index;
}

//set scribbled
void Color::setScribbled(void)
{
	//scribbled = true;
}

//clear scribbles
void Color::clearScribble(void)
{
	//scribbled = false;
	index			= -1;
}

//overload operator ==
bool Color::operator== (Color &rpar)
{
	if((rpar.cb==cb)&&(rpar.cg=cg)&&(rpar.cr==cr))
		return true;
	else
		return false;
}
