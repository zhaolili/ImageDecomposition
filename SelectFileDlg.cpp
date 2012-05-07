// SelectFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageDecomposition.h"
#include "SelectFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectFileDlg

IMPLEMENT_DYNAMIC(CSelectFileDlg, CFileDialog)

CSelectFileDlg::CSelectFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
			GetModuleFileName(NULL, initdir, 200);
			m_ofn.lpstrTitle = TEXT("Select an image") ;
			m_ofn.lpstrFilter="BMP Files (*.bmp)\0*.bmp\0JPEG Files (*.jpg)\0*.jpg\0RGB Files (*.rgb; *.raw)\0*.rgb;*.raw\0All File(*.*)\0*.*\0\0";
			m_ofn.lpstrInitialDir = (LPCTSTR)initdir; 
}


BEGIN_MESSAGE_MAP(CSelectFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CSelectFileDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

