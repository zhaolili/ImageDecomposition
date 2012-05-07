// DisplayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageDecomposition.h"
#include "DisplayerDlg.h"
#include "ImageDecomp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageDecomp imageDecmp;
/////////////////////////////////////////////////////////////////////////////
// CDisplayerDlg dialog


CDisplayerDlg::CDisplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisplayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_imgOpen = FALSE;
	m_RPEN	= FALSE;
	m_GPEN	= FALSE;
	m_BPEN	= FALSE;
	m_isMaxed = FALSE;
	m_draw	= FALSE;
	inh = inw = 0;
	bitd = itype =0;
	m_lineWid = 0;
	m_counter = 0;
	wrongResolution = FALSE;
	scribbled = FALSE;
	mouse_moved = FALSE;
}


void CDisplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisplayerDlg, CDialog)
	//{{AFX_MSG_MAP(CDisplayerDlg)
	ON_WM_CLOSE()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	//ON_MESSAGE(WM_MSGFROMIDDLG, OnMsgFromIDDlg)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

//dispose message from image decomposition dialog
void CDisplayerDlg::OnMsgFromIDDlg(WPARAM wParam, LPARAM lParam)
{
	if (wParam==0)
	{
		CRect rect;
		GetClientRect(&rect);
		::InvalidateRect(this->m_hWnd, &rect, TRUE);

		//clear the scribbles
		scribbled = FALSE;
	}
}

void CDisplayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_imgOpen = FALSE;
	::DestroyWindow(this->m_hWnd);
	imageDecmp.FlagMemRelease(inw, inh);
	// CDialog::OnClose();
}



BOOL CDisplayerDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

	ShowWindow(SW_SHOW);

	CRect rdlg, rpic, rclient;
	GetWindowRect(&rdlg);
	pWnd = GetDlgItem(IDC_PICTUREDSP);	
	pWnd->GetWindowRect(&rpic);
	GetClientRect(&rclient);
	ClientToScreen(&rclient);
	CPoint cursor;
	GetCursorPos(&cursor);

	if ((rpic.left<=cursor.x)&&(cursor.x<=rclient.right)&&(rclient.top<=cursor.y)&&(cursor.y<=rclient.bottom))
	{
		if ((rpic.left<=cursor.x)&&(cursor.x<=rpic.right)&&(rpic.top<=cursor.y)&&(cursor.y<=rpic.bottom))
		{
			if (m_RPEN)
			{
				if (SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSORCONR))))
					return TRUE;
				else
				{
					m_RPEN = FALSE;
					return m_RPEN;
				}
			}
			if (m_GPEN)
			{
				if (SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSORCONI))))
					return TRUE;
				else
				{
					m_GPEN = FALSE;
					return m_GPEN;
				}
			}
			if (m_BPEN)
			{
				if (SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSORFIXI))))
					return TRUE;
				else
				{
					m_BPEN = FALSE;
					return m_BPEN;
				}
			}

			return CDialog::OnSetCursor(pWnd, nHitTest, message);
		}
		else
		{
			if (!m_isMaxed)
				SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_ZOOMPLUS)));
			else
				SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_ZOOMMINUS)));			
		}
		
	}
	else
	{
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
	}
	
	return true;
}

void CDisplayerDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	//Invalidate(true);
	DisplayImage();
 	// Do not call CDialog::OnPaint() for painting messages
}


void CDisplayerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType==SIZE_MAXIMIZED)
	{
		// SetParent(GetDesktopWindow());
		// MessageBox("!!!!!!");
	}
	
}

BOOL CDisplayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_DISPLAYER)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_DISPLAYER)), FALSE);
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDisplayerDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	HCURSOR hCursor = GetCursor();
	if (hCursor==LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_ZOOMPLUS)))
	{
		ShowWindow(SW_SHOWMAXIMIZED);
		m_isMaxed = true;
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_PICTUREDSP);
		CRect rclient;
		pWnd->GetWindowRect(&rclient);
		SetCursorPos(rclient.right+1, rclient.top-1);
	}
	else
	{		
		if (hCursor==LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_ZOOMMINUS)))
		{
			ShowWindow(SW_SHOWNORMAL);
			m_isMaxed = FALSE;
		}

		CRect rclient;
		GetClientRect(&rclient);
		ClientToScreen(&rclient);
		SetCursorPos(rclient.right-1, rclient.top+1);
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDisplayerDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint cursor;
	GetCursorPos(&cursor);
	CRect rpic;
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_PICTUREDSP);	
	pWnd->GetWindowRect(&rpic);
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	int hor = rpic.left-rect.left;
	int ver = rpic.top-rect.top;

	// char text[100];
	CString titleStr;
	char tmp1[5], tmp2[5];
	
	titleStr = textStr + "    pixel:";
	if ((rpic.left<=cursor.x)&&(cursor.x<=rpic.right)&&(rpic.top<=cursor.y)&&(cursor.y<=rpic.bottom))
	{
		titleStr = titleStr + "(" + itoa((cursor.x-rpic.left), tmp1, 10) + "," + itoa((cursor.y-rpic.top), tmp2, 10)+")";	
		
		if(m_RPEN||m_GPEN||m_BPEN)
		{
			//CClientDC dc((CWnd*)GetDlgItem(IDC_PICTUREDSP));
			CClientDC dc(this);
			CPen penR(PS_SOLID, m_lineWid, RGB(255,0,0));
			CPen penG(PS_SOLID, m_lineWid, RGB(0,255,0));
			CPen penB(PS_SOLID, m_lineWid, RGB(0,0,255));
			CPen *pPen;
			int type;
			if (m_RPEN)
			{
				pPen = dc.SelectObject(&penR);
				type = 1;
			}				
			if (m_GPEN)
			{
				pPen = dc.SelectObject(&penG);
				type = 2;
			}				
			if (m_BPEN)
			{
				pPen = dc.SelectObject(&penB);
				type = 3;
			}				
			if (m_draw)
			{
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(point);
				m_ptOrigin = point;
				dc.SelectObject(pPen);
				FlagLine((point.y-ver), (point.x-hor), type, m_lineWid);
				mouse_moved = TRUE;
			}
		}	
		//titleStr = titleStr + itoa((point.x-hor), tmp1,10); //right
	}
	SetWindowText(titleStr);
	
	CDialog::OnMouseMove(nFlags, point);
}

//display an image to screen
BOOL CDisplayerDlg::DisplayImage()
{
	if (m_bmp.m_hObject != NULL)
		m_bmp.DeleteObject();
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), fpathnam, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if(hBmp==NULL)
		return FALSE;
	m_bmp.Attach(hBmp);
	DIBSECTION ds;
	BITMAPINFOHEADER &bmpInfo = ds.dsBmih;
	m_bmp.GetObject(sizeof(DIBSECTION), &ds);
	
	int cx = bmpInfo.biWidth; //image width
	int cy = bmpInfo.biHeight; //image height;

 	if ((cx!=inw)||(cy!=inh))
 	{
 		wrongResolution = TRUE;
 		return FALSE;
 	}

	char tmp1[5], tmp2[5];
	textStr = fpathnam+"          Resolution:"+"("+itoa(cx, tmp1, 10)+"x"+itoa(cy, tmp2, 10)+")";
	SetWindowText(textStr);

	CRect rect;
	CWnd  *pWnd;
	pWnd = GetDlgItem(IDC_PICTUREDSP);
	if (pWnd==NULL)
	{
		MessageBox("error!");
		return false;
	}
		
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pWnd->MoveWindow(rect.left, rect.top, cx, cy, true);

	CPaintDC dc(pWnd);

	CRect rcclient;
	pWnd->GetClientRect(&rcclient);
 	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
 	CBitmap bitmap;
 	// bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
	bitmap.CreateCompatibleBitmap(&dc, cx, cy);
	memdc.SelectObject(&bitmap);
 
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC, 0);
 
	::SetStretchBltMode(dc, COLORONCOLOR);
	CBrush brush;
 	brush.CreatePatternBrush(&m_bmp);
 	dc.FillRect(rcclient, &brush);
 	// dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &memdc, rcclient.left, rcclient.top, SRCPAINT);
//	dc.StretchBlt(rcclient.left, rcclient.top, cx, cy, &memdc, rcclient.left, rcclient.top, cx, cy, SRCPAINT);
 	brush.DeleteObject();

	return true;
}

BOOL CDisplayerDlg::ImageShow(CString fpn, int inputwid, int inputhig, int bd, int imgtp)
{
	inh = inputhig;
	inw = inputwid;
	bitd = bd;
	itype = imgtp;
	fpathnam = fpn;
	if(!DisplayImage())
	{
		if(wrongResolution)
		{
			MessageBox("Wrong image resolution!");
			::DestroyWindow(this->m_hWnd);
		}
		return FALSE;
	}
	imageDecmp.LoadSrcImage(fpathnam, inh, inw, bitd, itype);
	m_imgOpen = TRUE;
	return TRUE;
}

void CDisplayerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_draw = TRUE;
	m_ptOrigin = point;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDisplayerDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_draw = FALSE;
	if (scribbled && mouse_moved)
		m_counter++;
	mouse_moved = FALSE;
	CDialog::OnLButtonUp(nFlags, point);
}


BOOL CDisplayerDlg::FlagLine(int y, int x, int type, int lineWid, int yb, int xb)
{
	int scribID = m_counter+1;
	imageDecmp.StoreFlags(y, x, type, scribID);
	scribbled = TRUE;
	switch(type)
	{
		case 1:
			break;
		case 2:
			if (((y+1)<inh)&&((x+1)<inw))
			{
				imageDecmp.StoreFlags(y+1, x, type, scribID);
				imageDecmp.StoreFlags(y, x+1, type, scribID);
			}
			else
			{
				if ((y+1)<inh)
				{
					imageDecmp.StoreFlags(y+1, x, type, scribID);
				}
				if ((x+1)<inw)
				{
					imageDecmp.StoreFlags(y, x+1, type, scribID);
				}
			}
			break;
		case 3:
			if (((y+2)<inh)&&((x+2)<inw))
			{
				imageDecmp.StoreFlags(y+1, x, type, scribID);
				imageDecmp.StoreFlags(y, x+1, type, scribID);
				imageDecmp.StoreFlags(y+2, x, type, scribID);
				imageDecmp.StoreFlags(y, x+2, type, scribID);
			}
			else
			{
				if ((y+2)<inh)
				{
					imageDecmp.StoreFlags(y+1, x, type, scribID);
					imageDecmp.StoreFlags(y+2, x, type, scribID);
					if ((x+1)<inw)
					{
						imageDecmp.StoreFlags(y, x+1, type, scribID);
					}
					break;
				}
				if ((x+2)<inw)
				{
					imageDecmp.StoreFlags(y, x+1, type, scribID);
					imageDecmp.StoreFlags(y, x+2, type, scribID);
					if ((y+1)<inh)
					{
						imageDecmp.StoreFlags(y+1, x, type, scribID);
					}
					break;
				}
			}
			break;
		case 4:
			if (((y+3)<inh)&&((x+3)<inw))
			{
				imageDecmp.StoreFlags(y+1, x, type, scribID);
				imageDecmp.StoreFlags(y+2, x, type, scribID);
				imageDecmp.StoreFlags(y+3, x, type, scribID);
				imageDecmp.StoreFlags(y, x+1, type, scribID);
				imageDecmp.StoreFlags(y, x+2, type, scribID);
				imageDecmp.StoreFlags(y, x+3, type, scribID);
			}
			else
			{
				if ((y+3)<inh)
				{
					imageDecmp.StoreFlags(y+1, x, type, scribID);
					imageDecmp.StoreFlags(y+2, x, type, scribID);
					imageDecmp.StoreFlags(y+3, x, type, scribID);
					if ((x+2)<inw)
					{
						imageDecmp.StoreFlags(y, x+1, type, scribID);
						imageDecmp.StoreFlags(y, x+2, type, scribID);
					}
					break;
				}
				if ((x+3)<inw)
				{
					imageDecmp.StoreFlags(y, x+1, type, scribID);
					imageDecmp.StoreFlags(y, x+2, type, scribID);
					imageDecmp.StoreFlags(y, x+3, type, scribID);
					if ((y+2)<inh)
					{
						imageDecmp.StoreFlags(y+1, x, type, scribID);
						imageDecmp.StoreFlags(y+2, x, type, scribID);
					}
					break;
				}
			}
			break;
	}

	return TRUE;
}
