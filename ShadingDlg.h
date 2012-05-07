#if !defined(AFX_SHADINGDLG_H__CA37D15B_348A_4025_B44C_D09D31979B74__INCLUDED_)
#define AFX_SHADINGDLG_H__CA37D15B_348A_4025_B44C_D09D31979B74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShadingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShadingDlg dialog

class CShadingDlg : public CDialog
{
// Construction
public:
	BOOL ShowShading();
	void GetImgSize(int w, int h);
	CShadingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShadingDlg)
	enum { IDD = IDD_SHADINGDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShadingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShadingDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_height;
	int m_width;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHADINGDLG_H__CA37D15B_348A_4025_B44C_D09D31979B74__INCLUDED_)
