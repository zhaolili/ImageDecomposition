// AlbedoDlg.cpp : implementation file
//

#include "stdafx.h"
#include <wingdi.h>
#include "ImageDecomposition.h"
#include "AlbedoDlg.h"
#include "DisplayerDlg.h"
#include "ImageDecomp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageDecomp imageDecmp;

/////////////////////////////////////////////////////////////////////////////
// CAlbedoDlg dialog


CAlbedoDlg::CAlbedoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlbedoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlbedoDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_width = 0;
	m_height = 0;
	//}}AFX_DATA_INIT
}

//constructor overload
CAlbedoDlg::CAlbedoDlg(int w, int h)
{
	m_width = w;
	m_height = h;
}

//get image size
void CAlbedoDlg::GetImgSize(int w, int h)
{
	m_width = w;
	m_height = h;
}



void CAlbedoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlbedoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlbedoDlg, CDialog)
	//{{AFX_MSG_MAP(CAlbedoDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlbedoDlg message handlers

BOOL CAlbedoDlg::ShowAlbedo()
{
	//image width and height
	int imgw = m_width;
	int imgh = m_height;

	//BITMAPINFO
	LPBITMAPINFO lpbmi = new BITMAPINFO;
	ZeroMemory(lpbmi, sizeof(BITMAPINFO));
	lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //The number of bytes required by the structure
	lpbmi->bmiHeader.biWidth = imgw; //The width of the bitmap, in pixels
	lpbmi->bmiHeader.biHeight = imgh;
	lpbmi->bmiHeader.biPlanes = 1; //The number of planes for the target device. This value must be set to 1
	lpbmi->bmiHeader.biBitCount = 24; //The number of bits-per-pixel
	lpbmi->bmiHeader.biCompression = BI_RGB;  //An uncompressed format
	lpbmi->bmiHeader.biSizeImage = 0; //The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps	
	lpbmi->bmiHeader.biXPelsPerMeter = 0; //The horizontal resolution, in pixels-per-meter, of the target device for the bitmap
	lpbmi->bmiHeader.biYPelsPerMeter = 0;	
	lpbmi->bmiHeader.biClrUsed = 0; //The number of color indexes in the color table that are actually used by the bitmap. 
	// 									//If this value is zero, the bitmap uses the maximum number of colors 
	// 									//corresponding to the value of the biBitCount member for the compression mode specified by biCompression.
	lpbmi->bmiHeader.biClrImportant = 0;  //The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.
 
	//create an albedo DIB bitmap	
	BYTE *pData = (BYTE *)imageDecmp.GetAlbedoBuf();

	//
	CRect rect;
	CWnd  *pWnd = GetDlgItem(IDC_ALBEDOIMG);
	if (pWnd==NULL)
	{
		MessageBox("error!");
		return FALSE;
	}
	
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pWnd->MoveWindow(rect.left, rect.top, imgw, imgh, true);
	
	CPaintDC dc(pWnd);

	::SetStretchBltMode(dc, COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(),  0,  0, m_width,  m_height,  0,  0,  m_width,  m_height,  pData,  lpbmi,  DIB_RGB_COLORS,  SRCCOPY);  

 	return TRUE;
}

void CAlbedoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	ShowAlbedo();
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}




