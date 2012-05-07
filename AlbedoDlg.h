#if !defined(AFX_ALBEDODLG_H__7CCDD3A4_5B9E_49D3_9D81_794052069333__INCLUDED_)
#define AFX_ALBEDODLG_H__7CCDD3A4_5B9E_49D3_9D81_794052069333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbedoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlbedoDlg dialog

class CAlbedoDlg : public CDialog
{
// Construction
public:
	void GetImgSize(int w, int h);
	CAlbedoDlg(int w, int h);
	BOOL ShowAlbedo();
	CAlbedoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlbedoDlg)
	enum { IDD = IDD_ALBEDODLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlbedoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlbedoDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_height; //image height
	int m_width;  //image width
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBEDODLG_H__7CCDD3A4_5B9E_49D3_9D81_794052069333__INCLUDED_)
