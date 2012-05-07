// ImageDecomp.cpp: implementation of the CImageDecomp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageDecomposition.h"
#include "ImageDecomp.h"
#include "Img.h"
#include "Color.h"
#include "Matrix.h"
#include "DisplayerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double ** LMatrix;
Img result;
//double **M;

//for G-S iterations
const int nbIter = 10;

CImageDecomp::CImageDecomp()
{
	scribbletype = 0;
	albedoNum = 0;
	shadingNum = 0;
	fixShadingNum = 0;

	//
	scribbleShadingImg = NULL;
	scribbleAlbedoImg = NULL;
	scribbleFixShadingImg = NULL;
	imgIn = NULL;
}

CImageDecomp::~CImageDecomp()
{
	if (flagMatrix)
	{
		for (int j=0; j<imgHeight; j++)
		{
			if(flagMatrix[j])
			{
				delete[] flagMatrix[j];
				flagMatrix[j]=NULL;
			}
		}
		delete[] flagMatrix;
		flagMatrix = NULL;
	}

	if(imgBuf)
	{
		delete[] imgBuf;
		imgBuf = NULL;
	}
	if(rgbBuf)
	{
		delete[] rgbBuf;
		rgbBuf = NULL;
	}
	if (albedoImgBuf)
	{
		delete[] albedoImgBuf;
		albedoImgBuf = NULL;
	}
	if (shadingImgBuf)
	{
		delete[] shadingImgBuf;
		shadingImgBuf = NULL;
	}

	if (scribbleAlbedoImg)
	{
		delete scribbleAlbedoImg;
		scribbleAlbedoImg = NULL;
	}
		
	if (scribbleShadingImg)
	{
		delete scribbleShadingImg;
		scribbleShadingImg = NULL;
	}
		
	if (scribbleFixShadingImg)
	{
		delete scribbleFixShadingImg;
		scribbleFixShadingImg = NULL;
	}
	if (imgIn)
	{
		delete imgIn;
		imgIn = NULL;
	}
		
}

CImageDecomp::CImageDecomp(int x, int y)
{
	scribbletype = 0;
	albedoNum = 0;
	shadingNum = 0;
	fixShadingNum = 0;
// 	imgWidth = x;
// 	imgHeight = y;
// 	flagMatrix = new int*[y];
// 	for (int j=0; j<y; j++)
// 	{
// 		flagMatrix[j] = new int[x];
// 	}
// 	for (j=0; j<y; j++)
// 	{
// 		for (int i=0; i<x; i++)
// 		{
// 			flagMatrix[j][i] = 0;
// 		}
// 	}
}

void CImageDecomp::LoadSrcImage(CString pathnam, int height, int width, int bitdep, int type, int format)
{
	//image format which denotes 4:4:4 format is 0 by default
	imgHeight = height;
	imgWidth	= width;
	bitDepth	= bitdep;

	FlagMemAlloc(imgWidth, imgHeight);

	CFile infile;
	infile.Open(pathnam, CFile::modeRead);
	UINT flen = (UINT)infile.GetLength();
	infile.SeekToBegin();
	if (imgBuf)
		delete[] imgBuf;
	imgBuf = new BYTE[flen];
	infile.Read((void *)imgBuf, flen);
	infile.Close();

	switch(type)
	{
		case TYPE_BMP:
			LoadBmpImage();
			break;
		case TYPE_RGB:
			LoadRgbImage();
			break;
		case TYPE_YUV:
			LoadYuvImage(format);
	}
}

void CImageDecomp::LoadYuvImage(int format)
{

}

void CImageDecomp::LoadBmpImage()
{
	BITMAPFILEHEADER *bmpfile = (BITMAPFILEHEADER *)imgBuf;
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));

	if (bmpfile->bfType != 0x4d42)
	{
		AfxMessageBox("Image is not bmp file!");
		return;
	}

 	if ((bmpinfo->biWidth!=imgWidth)||(bmpinfo->biHeight!=imgHeight))
 	{
 		AfxMessageBox("Wrong input image definition!");
 		return;
 	}

// 	int imgsize = imgWidth*imgHeight;
// 	int bufsize = (bitDepth==8) ? imgsize*3 : imgsize*3*2;
	int bbc=24;  //3*8
	int bpl = ((bbc*imgWidth + 31)/32)*4;
	int bufsize = bpl*imgHeight;

	if(rgbBuf)
		delete[] rgbBuf;
	rgbBuf = new BYTE[bufsize];
	BYTE *rgbdata = imgBuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	memcpy(rgbBuf, rgbdata, bufsize);
	HeadStand((void*)rgbBuf, imgHeight, imgWidth, bitDepth);
	//
	ImgIn();
}

void CImageDecomp::LoadRgbImage()
{

}

//from bottom->top to top->bottom, for bmp file
void CImageDecomp::HeadStand(void *buffer, int height, int width, int bitdep)
{
	int imgsize = width*height;
	void *buftmp;

	int bbc = 24; //3*8
	int bpl = ((bbc*imgWidth + 31)/32)*4;
	int bufsize = bpl*imgHeight;
	buftmp = new BYTE[bufsize];

	for (int i=0; i<height/2; i++)
	{
		memcpy((BYTE*)buftmp, (BYTE*)buffer+i*bpl, bpl);
		memcpy((BYTE*)buffer+i*bpl, (BYTE*)buffer+(height-1)*bpl-i*bpl, bpl);
		memcpy((BYTE*)buffer+(height-1)*bpl-i*bpl, buftmp, bpl);
	}
	
	delete[] buftmp;
}


BOOL CImageDecomp::InitFlags(int w, int h)
{
	if (!flagMatrix)
	{
		AfxMessageBox("Flag memory failed.");
		return FALSE;
	}

	for (int j=0; j<h; j++)
	{
		memset(flagMatrix[j], 0, w);
	}
	scribbletype = 0;
	return TRUE;
}

void CImageDecomp::StoreFlags(int y, int x, BYTE type, int scribID)
{
	flagMatrix[y][x] = scribID;
	//type: 1-R, 2-G, 3-B
	scribbletype = type;   
}

BOOL CImageDecomp::FlagMemAlloc(int w, int h)
{
	if (flagMatrix)
	{
		AfxMessageBox("Flag memory not released.");
		return FALSE;
	}
	
	flagMatrix = new BYTE*[h];
	for (int k=0; k<h; k++)
	{
		flagMatrix[k] = new BYTE[w];
	}

	//initialize
	InitFlags(w, h);

	return TRUE;
}

BOOL CImageDecomp::FlagMemRelease(int w, int h)
{
	if (!flagMatrix)
	{
		AfxMessageBox("Flag memory already released");
		return FALSE;
	}

	if (flagMatrix)
	{
		for (int k=0; k<h; k++)
		{
			if(flagMatrix[k])
			{
				delete[] flagMatrix[k];
				flagMatrix[k] = NULL;
			}
		}
		delete[] flagMatrix;
		flagMatrix = NULL;
	}
	return TRUE;
}

BOOL CImageDecomp::SaveScribbles()
{
	int maxScribbleIds = 0;
	int tmp, i, j;

	switch (scribbletype)
	{
	case 1:
		//constant reflectance/albedo
		if (scribbleAlbedoImg!=NULL)
		{
			delete scribbleAlbedoImg;
			scribbleAlbedoImg = NULL;
		}
		scribbleAlbedoImg = new Img(imgWidth, imgHeight, Color(0, 0, 0));
		for (j=0; j<imgHeight; j++)
		{
			for (i=0; i<imgWidth; i++)
			{
				tmp = flagMatrix[j][i];
				//current pixel is scribbles
				if (tmp!=0)
				{
					scribbleAlbedoImg->setPixel(i, j, Color(tmp, tmp, tmp, tmp));
//					(scribbleAlbedoImg->pixel(i, j)).setScribbled();
					if (maxScribbleIds<tmp)
						maxScribbleIds = tmp;
				}
			}
		}
		albedoNum = maxScribbleIds;

		break;
	case 2:
		//constant illumination/shading
		if (scribbleShadingImg!=NULL)
		{
			delete scribbleShadingImg;
			scribbleShadingImg = NULL;
		}
		scribbleShadingImg = new Img(imgWidth, imgHeight, Color(0,0,0));
		for (j=0; j<imgHeight; j++)
		{
			for (i=0; i<imgWidth; i++)
			{
				tmp = flagMatrix[j][i];
				if (tmp!=0)
				{
					scribbleShadingImg->setPixel(i, j, Color(tmp, tmp, tmp, tmp));
//					(scribbleShadingImg->pixel(i, j)).setScribbled();
					if (maxScribbleIds<tmp)
						maxScribbleIds = tmp;
				}
			}
		}
		shadingNum = maxScribbleIds;
		break;
	case 3:
		//fix illumination
		if (scribbleFixShadingImg!=NULL)
		{
			delete scribbleFixShadingImg;
			scribbleFixShadingImg = NULL;
		}
		scribbleFixShadingImg = new Img(imgWidth, imgHeight, Color(0, 0, 0));

		int val = FIXEDSHADING;
		for (j=0; j<imgHeight; j++)
		{
			for (i=0; i<imgWidth; i++)
			{
				tmp = flagMatrix[j][i];
				if (tmp!=0)
				{
					//set "val" fix illumination pixels
					scribbleFixShadingImg->setPixel(i, j, Color(val, val, val, tmp));
//					(scribbleFixShadingImg->pixel(i, j)).setScribbled();
					if (maxScribbleIds<tmp)
						maxScribbleIds = tmp;
				}
			}
		}
		fixShadingNum = maxScribbleIds;
		break;
	}

	scribbletype = 0;
	return TRUE;
}


//this function convert rgb value of inputing image to an Img type object, 
BOOL CImageDecomp::ImgIn()
{
	int i, j, sp;
	double r, g, b;
	int mpv = MAX_PIX_VAL;
	if (imgIn)
	{
		delete imgIn;
		imgIn = NULL;
	}

	int bbc=24;  //3*8
	int bpl = ((bbc*imgWidth + 31)/32)*4;

	//initialized to be 0
	imgIn = new Img(imgWidth, imgHeight, Color(0, 0, 0));
	for (j=0; j<imgHeight; j++)
	{
		for (i=0; i<imgWidth; i++)
		{
			sp = j*bpl + i*3;    //3 for three bytes for rgb
			r = (double)rgbBuf[sp];
			g = (double)rgbBuf[sp+1];
			b = (double)rgbBuf[sp+2];
			//get the color value, here color value is the pixel value/max value
 			r = r/mpv;
 			g = g/mpv;
 			b = b/mpv;
			imgIn->setPixel(i, j, Color(r, g, b));   
		}
	}
	return TRUE;
}

void CImageDecomp::buildLMatrix(Img imgIn)
{
	int i,j,ik,jk;
	int x,y;
	int xC,yC,xiC,yiC,xjC,yjC;
	
	double epsilon = 0.0000001;
	double sqrt_epsilon = 0.001;
	int w = imgIn.width();
	int h = imgIn.height();
	
	double **M = new double*[MSIZE];
	for (i=0; i<MSIZE; i++)
	{
		M[i] = new double[3];
	}
	//M matrix (see equation 8)
	M[MSIZE-3][0] = sqrt_epsilon; M[MSIZE-3][1] = 0; M[MSIZE-3][2] = 0;
	M[MSIZE-2][0] = 0; M[MSIZE-2][1] = sqrt_epsilon; M[MSIZE-2][2] = 0;
	M[MSIZE-1][0] = 0; M[MSIZE-1][1] = 0; M[MSIZE-1][2] = sqrt_epsilon;
	
	//Init the L matrix. L is a sparse matrix that only contains SIZE_N2 non-zero elements per row.
	//We store the L matrix in an array with one row per image pixel and one column per non-zero value. 
	//Each array cell accumulates values according to equation 11.
	LMatrix = new double* [w*h];
	for(i=0; i<w*h; i++){
		LMatrix[i] = new double[SIZE_N2];
		for(j=0; j<SIZE_N2; j++){
			LMatrix[i][j] = 0;
		}
	}
	
	//Compute the L matrix
	for( y = WSIZE_2; y < h-WSIZE_2; y++) {//for each pixel...
		for( x = WSIZE_2; x < w-WSIZE_2; x++) {
			//fill the M matrix with the image values in the current window
			for (int m=-WSIZE_2; m<=WSIZE_2; m++) {
				yC = y+m;
				for (int n=-WSIZE_2; n<=WSIZE_2; n++) {
					xC = x+n;
					M[(m+WSIZE_2)*WSIZE + n+WSIZE_2][0] = imgIn.getR(xC,yC);
					M[(m+WSIZE_2)*WSIZE + n+WSIZE_2][1] = imgIn.getG(xC,yC);
					M[(m+WSIZE_2)*WSIZE + n+WSIZE_2][2] = imgIn.getB(xC,yC);
				}
			}
			//Compute the N matrix (equation 9 and 10)
			/*Matrix<MSIZE,3,double> Mi(M);
			Matrix<3,MSIZE,double> Mit(Mi.transpose());
			Square_matrix<3,double> MitMi(Mit*Mi);
			MitMi_inv = inverse_matrix(MitMi);
			Square_matrix<MSIZE,double> Ni(Mi*MitMi_inv*Mit);
			Ni = Ni.identity() - Ni;
			Square_matrix<MSIZE,double> Nit(Ni.transpose());
			Square_matrix<MSIZE,double> NitNi(Nit*Ni);*/
			//in fact, Nitmp==Nit==Nit*Nitmp
			Matrix<double> Mi(M, 12, 3);
			Matrix<double> Mit(Mi.transpose());
			Matrix<double> MitMi(Mit*Mi);
			Matrix<double> MitMi_inv(MitMi.inverse());
			Matrix<double> Ni(Mi*MitMi_inv*Mit);
			Matrix<double> Nitmp(Ni.identity()-Ni);
			Matrix<double> Nit(Nitmp.transpose());
			Matrix<double> NitNi(Nit*Nitmp);  /////////

			//accumulate the values in the L matrix, for each couple of pixels (i,j) covered by the window
			//--- i
			for (int mi=-WSIZE_2; mi<=WSIZE_2; mi++) {//(mi,ni) = coordinate of pixel i in the local window
				yiC = y+mi; //(xiC,yiC) = coordinate of pixel i in the image
				for (int ni=-WSIZE_2; ni<=WSIZE_2; ni++) {
					xiC = x+ni;
					i = yiC*w+xiC; //row number in the matrix
					ik = (mi+WSIZE_2)*WSIZE + ni+WSIZE_2;
					//--- j
					for (int mj=-WSIZE_2; mj<=WSIZE_2; mj++) {
						yjC = y+mj;
						for (int nj=-WSIZE_2; nj<=WSIZE_2; nj++) {
							xjC = x+nj;
							jk = (mj+WSIZE_2)*WSIZE + nj+WSIZE_2;
							//accumulate values (equation 11)
							LMatrix[i][(yiC-yjC+2*WSIZE_2)*SIZE_N+(xiC-xjC+2*WSIZE_2)] += NitNi.matrix[ik][jk];
							//pixel j is at coordinate (xiC-xjC,yiC-yjC) in the SIZE_N*SIZE_N neighborhood affected by pixel i (centered at pixel i)
						}
					}
				}
			}
		}
	}
	for (i=0; i<MSIZE; i++)
	{
		delete[] M[i];
		M[i] = NULL;
	}
	delete[] M;
	M = NULL;
}

//----- Gauss-Seidel iterations -----//

/*
imgScribbleAbsolute: image that stores the fixed-illumination scribbles (pixels store illumination values, alpha = true if the pixel is scribbled)
imgScribbleSimAlbedo: image that stores the constant-reflectance scribbles (pixels store scribbles ids)
imgScribbleSimShading: image that stores the constant-illumination scribbles (pixels store scribbles ids)
maxAlbedoNum: number of constant-reflectance scribble ids
maxShadingNum: number of constant-illumination scribble ids
albedoNumColors: constant-reflectance scribble ids
shadingNumColors: constant-illumination scribble ids
*/

Img CImageDecomp::solve(Img imgIn, Img &imgScribbleAbsolute, Img imgScribbleSimAlbedo, Img imgScribbleSimShading, int maxAlbedoNum, int maxShadingNum, Color *albedoNumColors, Color *shadingNumColors)
{
	int w = imgIn.width();
	int h = imgIn.height();
	result = Img(w,h,Color(0.5,0.5,0.5));  //initial value(noted by zhll)
	//result = Img(w,h,Color(1,1,1));
	double rRes, gRes, bRes;//temporary result values
	double denom;
	double lambdaCstr = 0.5;//weight of the user constraints

	int i, xjC, yjC, nbP;

	//variables used to compute user constraints
	double rSumI, gSumI, bSumI;//sum of images values
	double rSumS, gSumS, bSumS;//sum of illumination values
	double rAvrg, gAvrg, bAvrg;//average illumination
	Color imgVal, resVal, scribVal;
	Color* albedoAvgColors = new Color[maxAlbedoNum];//average reflectance for each constant-reflectance scribble
	Color* shadingAvgColors = new Color[maxShadingNum];//average illumination for each constant-illumination scribble

	Img scribbleSimAlbedo = imgScribbleSimAlbedo;
	Img scribbleSimShading = imgScribbleSimShading;
	Img scribbleAbsolute = imgScribbleAbsolute;

	//Gauss-Seidel iterations.
	//for simplicity, we apply here a fixed number of iterations
	for (int k=0; k<nbIter; k++){
		//-------------------------------//
		//--- User constraints values ---//
		//-------------------------------//

		//In order to apply the user constraints, we first need to compute the average value of constant reflectance or illumination pixels
		//-- Constant-reflectance
		for (int c=0; c<maxAlbedoNum; c++){//for each constant-reflectance scribble id
			//illumination estimation for pixel p = I(p)*sum(S)/sum(I), where S stands for illumination values of constant pixels and I for input value of constant pixels
			rSumI = gSumI = bSumI = 0;
			rSumS = gSumS = bSumS = 0;
			nbP = 0;
			for (int y = 0; y < h; y++) {//for each pixel of the scribbles image
				for (int x = 0; x < w; x++) {
					if(scribbleSimAlbedo.pixel(x,y)==albedoNumColors[c]){//pixel scribbled with the current constraint
						//get the image values for this pixel
// 						imgVal = imgIn.pixel(x,y);
// 						resVal = result.pixel(x,y);
						imgVal = imgIn.imga[y][x];
						resVal = result.imga[y][x];
						rSumI += imgVal.getR();
						rSumS += resVal.getR();
						gSumI += imgVal.getG();
						gSumS += resVal.getG();
						bSumI += imgVal.getB();
						bSumS += resVal.getB();
						nbP++;
					}
				}//for
			}//for
			if(nbP>0){//if there was some scribbled pixels
				albedoAvgColors[c] = Color(rSumS/rSumI,gSumS/gSumI,bSumS/bSumI);
			}//if(nbP>0){
		}
		//-- Constant-illumination
		for (int c=0; c<maxShadingNum; c++){//for each constant-illumination scribble id
			//illumination estimation = average illumination
			rAvrg = gAvrg = bAvrg = 0;
			nbP = 0;
			for (int y = 0; y < h; y++) {//for each pixel of the scribbles image
				for (int x = 0; x < w; x++) {
					if(scribbleSimShading.pixel(x,y)==shadingNumColors[c]){//pixel scribbled with the current constraint
						//resVal = result.pixel(x,y);
						resVal = result.imga[y][x];
						rAvrg += resVal.getR();
						gAvrg += resVal.getG();
						bAvrg += resVal.getB();
						nbP++;
					}
				}
			}
			if(nbP>0){//if there was some scribbled pixels
				rAvrg/=nbP;
				gAvrg/=nbP;
				bAvrg/=nbP;
				shadingAvgColors[c] = Color(rAvrg,gAvrg,bAvrg);
			}
		}

		//------------------------------------------------//
		//--- Gauss-Seidel iteration with the L matrix ---//
		//------------------------------------------------//

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				i = y*w+x; //row number for the current pixel
				//is that a fixed-illumination pixel?
				//imgVal = scribbleAbsolute.pixel(x,y);
				imgVal = scribbleAbsolute.imga[y][x];
				if(imgVal.getA()){//fixed-illumination pixel: impose the constraint
					rRes = imgVal.getR();
					gRes = imgVal.getG();
					bRes = imgVal.getB();
				}//if
				else{//non scribbled pixel
					//-- Gauss-Seidel update
					rRes = gRes = bRes = 0;
					for (int k=0; k < SIZE_N2; k++){//for each value on the matrix row corresponding to the current pixel
						if(LMatrix[i][k]!=0){
							//coordinate of the corresponding pixel in the image
							yjC = -k/SIZE_N+2*WSIZE_2+y;
							xjC = -k+(y-yjC+2*WSIZE_2)*SIZE_N+2*WSIZE_2+x;

							if(x==xjC && y==yjC){//diagonal
								denom = LMatrix[i][k];
							}
							else{
								//resVal = result.pixel(xjC,yjC);
								resVal = result.imga[yjC][xjC];
								//relaxation
								rRes -= LMatrix[i][k]*resVal.getR();
								gRes -= LMatrix[i][k]*resVal.getG();
								bRes -= LMatrix[i][k]*resVal.getB();
							}
						}//if(LMatrix[i][k]!=0)
					}//for
					rRes /= denom;
					gRes /= denom;
					bRes /= denom;
					//-- User constraints updates
					//check for constant-reflectance
					scribVal = scribbleSimAlbedo.pixel(x,y);
					if(scribVal.getA()){//constant-reflectance pixel
						//get the scribble id
						//int id = albedoNumColors.indexOf(QColor(scribVal));
						int id = scribVal.index-1;   //here is modified by zhaoll
						//get the image value for this pixel
						//imgVal = imgIn.pixel(x,y);
						imgVal = imgIn.imga[y][x];
						//illumination = I(p) * sum(S)/sum(I)
						//if one channel is too small, take another one
						//red
						if(imgVal.getR()>EPSILON_PIXEL_VAL && albedoAvgColors[id].getR()>EPSILON_PIXEL_VAL)
							rRes = lambdaCstr*rRes + (1.0-lambdaCstr)*imgVal.getR()*albedoAvgColors[id].getR();
						else{
							if(imgVal.getG()>EPSILON_PIXEL_VAL && albedoAvgColors[id].getG()>EPSILON_PIXEL_VAL)
								rRes = lambdaCstr*gRes + (1.0-lambdaCstr)*imgVal.getG()*albedoAvgColors[id].getG();
							else
								rRes = lambdaCstr*bRes + (1.0-lambdaCstr)*imgVal.getB()*albedoAvgColors[id].getB();
						}
						//green
						if(imgVal.getG()>EPSILON_PIXEL_VAL && albedoAvgColors[id].getG()>EPSILON_PIXEL_VAL)
							gRes = lambdaCstr*gRes + (1.0-lambdaCstr)*imgVal.getG()*albedoAvgColors[id].getG();
						else
							gRes = rRes;
						//blue 
						if(imgVal.getB()>EPSILON_PIXEL_VAL && albedoAvgColors[id].getB()>EPSILON_PIXEL_VAL)
							bRes = lambdaCstr*bRes + (1.0-lambdaCstr)*imgVal.getB()*albedoAvgColors[id].getB();
						else
							bRes = rRes;
					}//if(scribVal.getA()){
					else{
						//check for constant-illumination
						//scribVal = scribbleSimShading[deepness-1].pixel(x,y);
						scribVal = scribbleSimShading.pixel(x,y); ////////////////////////////////////
						if(/*qAlpha(scribVal)>1*/scribVal.getA()){//constant-illumination pixel
							//get the scribble id
							//int id = shadingNumColors.indexOf(QColor(scribVal));
							int id = scribVal.index-1;  //by zhaoll
							rRes = lambdaCstr*rRes + (1.0-lambdaCstr)*shadingAvgColors[id].getR();
							double test = shadingAvgColors[id].getR();
							double test2 = shadingAvgColors[id].cr;
							gRes = lambdaCstr*gRes + (1.0-lambdaCstr)*shadingAvgColors[id].getG();
							bRes = lambdaCstr*bRes + (1.0-lambdaCstr)*shadingAvgColors[id].getB();
						}
					}//else
				}//else
				if(rRes<EPSILON_PIXEL_VAL)
					rRes = EPSILON_PIXEL_VAL;
				if(gRes<EPSILON_PIXEL_VAL)
					gRes = EPSILON_PIXEL_VAL;
				if(bRes<EPSILON_PIXEL_VAL)
					bRes = EPSILON_PIXEL_VAL;

				//normalized, so is 1,
				if(rRes>1.0)
					rRes = 1.0;
				if(gRes>1.0)
					gRes = 1.0;
				if(bRes>1.0)
					bRes = 1.0;
				result.setPixel(x,y,Color(rRes,gRes,bRes));
			}//for (int x = 0; x < w; x++) {
		}//for (int y = 0; y < h; y++) {
	}//for (int k=0; k<nbIter; k++){

	delete[] albedoAvgColors;
	albedoAvgColors = NULL;

	delete[] shadingAvgColors;
	shadingAvgColors = NULL;

	return result;
}

//image decomposition
void CImageDecomp::decompImg()
{
	//in case no srcibbles
	if (albedoNum==0)
	{
		AfxMessageBox("No saved constant reflectance!");
		return;
	}
	if (shadingNum==0)
	{
		AfxMessageBox("No saved constant illumination!");
		return;
	}
	//in case no scribbles
	if (scribbleFixShadingImg==NULL)
	{
		scribbleFixShadingImg = new Img(imgWidth, imgHeight, Color(0,0,0,0));
	}
	if (scribbleAlbedoImg==NULL)
	{
		scribbleAlbedoImg = new Img(imgWidth, imgHeight, Color(0,0,0,0));
	}
	if (scribbleShadingImg==NULL)
	{
		scribbleShadingImg = new Img(imgWidth, imgHeight, Color(0,0,0,0));
	}

	Img img = *imgIn;
	Img imgScribbleAbsolute = *scribbleFixShadingImg;
	Img imgScribbleSimAlbedo = *scribbleAlbedoImg;
	Img imgScribbleSimShading = *scribbleShadingImg;
	int maxAlbedoNum = albedoNum;
	int maxShadingNum = shadingNum;
	//albedoNumColors are the color value of all scribbles, which is used here as scribble line ids
	Color *albedoNumColors = new Color[albedoNum];
	Color *shadingNumColors = new Color[shadingNum];
	int k;
	for (k=0; k<albedoNum; k++)
	{
		albedoNumColors[k] = Color(k+1, k+1, k+1);
	}
	for (k=0; k<shadingNum; k++)
	{
		shadingNumColors[k] = Color(k+1, k+1, k+1);
	}

	//build L matrix
	buildLMatrix(img);

  //gauss-jordan for minimization solution, the follwing returns the illumination of the input image
	shadingImg = solve(img, imgScribbleAbsolute, imgScribbleSimAlbedo, imgScribbleSimShading, maxAlbedoNum, maxShadingNum, albedoNumColors, shadingNumColors);
	
	/************************************************************************/
	//compute the reflectance
	double rI, gI, bI;  //rgb component of imgIn
	double rS, gS, bS;  //rgb component of Shading image
	double rA, gA, bA;  //rgb component of albedo image, which is to be computed below
	Img tmp(imgWidth, imgHeight, Color(0,0,0));
	for (int j=0; j<imgHeight; j++)
	{
		for (int i=0; i<imgWidth; i++)
		{
			//img input
			rI = img.getR(i, j);
			gI = img.getG(i, j);
			bI = img.getB(i, j);
			//shading img
			rS = shadingImg.getR(i, j);
			gS = shadingImg.getG(i, j);
			bS = shadingImg.getB(i, j);
			//compute albedo img  I = S*A
			rA = rI/rS;
			gA = gI/gS;
			bA = bI/bS;
			tmp.setPixel(i, j, Color(rA, gA, bA));
		}
	}
	albedoImg = tmp;
	//
	/************************************************************************/

	//put images to buffers
	Img2buf(shadingImg, albedoImg);

// 	// output albedo and shading images //just for test here
// 		int     framesize = imgHeight*imgWidth*3;
// 		char filename1[128];
// 		char filename2[128];
// 	
// 		sprintf(filename1, "d:\\albedo.rgb");
// 		sprintf(filename2, "d:\\shading.rgb");
// 	
// 		FILE* fp = fopen(filename1, "wb");
// 		fwrite(albedoImgBuf, 1, framesize, fp);
// 		fclose(fp);
// 	
// 		fp = fopen(filename2, "wb");
// 		fwrite(shadingImgBuf, 1, framesize, fp);
// 		fclose(fp);

	//delete temporary mem
	delete[] albedoNumColors;
	delete[] shadingNumColors;
}

//buffer albedo and shading images
BOOL CImageDecomp::Img2buf(Img &shadingImg, Img &albedoImg)
{
	//allocate memory for img buffer
	if (albedoImgBuf)
		delete[] albedoImgBuf;
	int bbc = 24;
	int bpl = ((bbc*imgWidth + 31)/32)*4;
	int imagesize = bpl*imgHeight;

	albedoImgBuf = new BYTE[imagesize];
	if (shadingImgBuf)
		delete[] shadingImgBuf;
	shadingImgBuf = new BYTE[imagesize];
	
	//
	double r, g, b;
	int i, j, mpv=MAX_PIX_VAL;
	Color tmp;
	BYTE pelR, pelG, pelB;
	int sp;
	//albedo img
	for (j=0; j<imgHeight; j++)
	{
		for (i=0; i<imgWidth; i++)
		{
			sp = (j*imgWidth + i)*3;
			//tmp = albedoImg.pixel(i, j);
			tmp = albedoImg.imga[j][i];
 			r = tmp.cr*mpv;
 			g = tmp.cg*mpv;
			b = tmp.cb*mpv;
// 			r = tmp.cr;
// 			g = tmp.cg;
// 			b = tmp.cb;
			pelR = (r<0) ? 0 : ((r>mpv)?mpv:r);
			pelG = (g<0) ? 0 : ((g>mpv)?mpv:g);
			pelB = (b<0) ? 0 : ((b>mpv)?mpv:b);
			albedoImgBuf[sp] = pelR;
			albedoImgBuf[sp+1] = pelG;
			albedoImgBuf[sp+2] = pelB;
		}
	}
	HeadStand((void *)albedoImgBuf, imgHeight, imgWidth, bitDepth);  //temporarily canceled
	//shading img
	for (j=0; j<imgHeight; j++)
	{
		for (i=0; i<imgWidth; i++)
		{
			sp = (j*imgWidth + i)*3;
	// 		tmp = shadingImg.pixel(i, j);
			tmp = shadingImg.imga[j][i];
 			r = tmp.cr*mpv;
 			g = tmp.cg*mpv;
 			b = tmp.cb*mpv;
// 			r = tmp.cr;
// 			g = tmp.cg;
// 			b = tmp.cb;
			pelR = (r<0) ? 0 : ((r>mpv)?mpv:r);
			pelG = (g<0) ? 0 : ((g>mpv)?mpv:g);
			pelB = (b<0) ? 0 : ((b>mpv)?mpv:b);
			shadingImgBuf[sp] = pelR;
			shadingImgBuf[sp+1] = pelG;
			shadingImgBuf[sp+2] = pelB;
		}
	}
	HeadStand((void *)shadingImgBuf, imgHeight, imgWidth, bitDepth);  //temporarily canceled

	return true;
}

//get the albedo image buffer
void * CImageDecomp::GetAlbedoBuf()
{
	return (void *)albedoImgBuf;
}

//get the shading image buffer
void * CImageDecomp::GetShadingBuf()
{
	return (void *)shadingImgBuf;
}
