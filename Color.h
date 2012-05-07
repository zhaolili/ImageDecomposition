// Color.h: interface for the Color class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOR_H__AD2BF0FB_ABDD_4709_8709_7ECA3A0EED90__INCLUDED_)
#define AFX_COLOR_H__AD2BF0FB_ABDD_4709_8709_7ECA3A0EED90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Color
{
public:
	Color(void);
	Color(Color &);
	// the real pixel value divided by the maximum pixel value
	Color(double r, double g, double b);
	Color(double r, double g, double b, int indx);
	virtual ~Color(void);
	
public:
	// get RGB value
	double getR();
	double getG();
	double getB();
	// current pixel  is fixed-illumination or not
	bool getA(void);
	//get index
	int		indexOf(Color &);
	void  setScribbled(void);
	void  clearScribble(void);
	
public:
	//R value
	double cr;
	//G value
	double cg;
	//B value
	double cb;
	//whether scribbled
	//bool scribbled;  //default false
	//index for scribbles default -1
	int    index;

public:
	//overload operator ==
	bool operator== (Color &rpar);
};

#define  FIXEDSHADING 1    //define fixed shading value
#define  IMGTYPE 0

#if (IMGTYPE==0)
#define MAX_PIX_VAL 255
#else
#define MAX_PIX_VAL 65535
#endif

#endif // !defined(AFX_COLOR_H__AD2BF0FB_ABDD_4709_8709_7ECA3A0EED90__INCLUDED_)
