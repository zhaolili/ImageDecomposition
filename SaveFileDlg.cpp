// SaveFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagedecomposition.h"
#include "SaveFileDlg.h"
#include <dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDlg

IMPLEMENT_DYNAMIC(CSaveFileDlg, CFileDialog)

CSaveFileDlg::CSaveFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
			GetModuleFileName(NULL, savedir, 200);
			m_ofn.lpstrTitle = TEXT("Save intrinsic images") ;
			m_ofn.lpstrFilter="BMP Files (*.bmp)\0*.bmp\0\0";
			m_ofn.lpstrInitialDir = (LPCTSTR)savedir;	//default path
}


BEGIN_MESSAGE_MAP(CSaveFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CSaveFileDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




BOOL CSaveFileDlg::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	// TODO: Add extra initialization here
	HideControl(edt1);   //hide save file name edit
	HideControl(stc3);   //hide file name label
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

