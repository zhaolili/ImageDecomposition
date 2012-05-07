// ImageDecompositionDlg.h : header file
//

#if !defined(AFX_IMAGEDECOMPOSITIONDLG_H__9C272550_E7ED_4790_94CC_89653745D0D9__INCLUDED_)
#define AFX_IMAGEDECOMPOSITIONDLG_H__9C272550_E7ED_4790_94CC_89653745D0D9__INCLUDED_

#include "DisplayerDlg.h"	// Added by ClassView
#include "AlbedoDlg.h"	// Added by ClassView
#include "ShadingDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageDecompositionDlg dialog

class CImageDecompositionDlg : public CDialog
{
public:
	void SnapShot(int w, int h, BYTE *pData, CString fpathnam);
	CShadingDlg shadingDlg;
	CAlbedoDlg albedoDlg;
	CDisplayerDlg m_dspDlg;
	CImageDecompositionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageDecompositionDlg)
	enum { IDD = IDD_IMAGEDECOMPOSITION_DIALOG };
	CEdit	m_ctrHeight;
	CButton	m_f444;
	CEdit	m_ctrWidth;
	CComboBox	m_comboBitDepth;
	CComboBox	m_comboLineWidth;
	UINT	m_width;
	UINT	m_height;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDecompositionDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageDecompositionDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenfile();
	afx_msg void OnConreflect();
	afx_msg void OnConillum();
	afx_msg void OnFixillum();
	afx_msg void OnDecomposition();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClosepic();
	afx_msg void OnSelchangeCombolinw();
	afx_msg void OnClear();
	afx_msg void OnSavedraws();
	afx_msg void OnOutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_shadingbmp;
	CBitmap m_albedobmp;
	BOOL m_fixICheck;
	BOOL m_conICheck;
	BOOL m_conRCheck;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDECOMPOSITIONDLG_H__9C272550_E7ED_4790_94CC_89653745D0D9__INCLUDED_)
