#if !defined(AFX_DISPLAYERDLG_H__911ECA0F_9703_458E_9450_3F2DC7317898__INCLUDED_)
#define AFX_DISPLAYERDLG_H__911ECA0F_9703_458E_9450_3F2DC7317898__INCLUDED_

#include "ImageDecomp.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayerDlg.h : header file
//
//caonimacao

#define WM_MSGFROMIDDLG (WM_USER+0x001)  //messsage from image decomposition dialog 

/////////////////////////////////////////////////////////////////////////////
// CDisplayerDlg dialog

class CDisplayerDlg : public CDialog
{
// Construction
public:
	int m_counter;
	BOOL scribbled;
	BOOL FlagLine(int y, int x, int type, int lineWid, int yb=0, int xb=0);
	int m_lineWid;
	BOOL ImageShow(CString fpn, int inputwid, int inputhig, int bd, int imgtp);
	BOOL m_BPEN;
	BOOL m_GPEN;
	BOOL m_RPEN;
	BOOL m_imgOpen;
	CDisplayerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisplayerDlg)
	enum { IDD = IDD_DISPLAYDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayerDlg)
	afx_msg void OnClose();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnMsgFromIDDlg(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL mouse_moved;
	CPoint m_ptOrigin;
	BOOL m_draw;
	int itype;
	int bitd;
	BOOL wrongResolution;
	BOOL DisplayImage();
	int inh;
	int inw;
	CString textStr;
	BOOL m_isMaxed;
	CString fpathnam;
	CBitmap m_bmp;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYERDLG_H__911ECA0F_9703_458E_9450_3F2DC7317898__INCLUDED_)
