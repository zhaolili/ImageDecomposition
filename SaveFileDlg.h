#if !defined(AFX_SAVEFILEDLG_H__BDF7FA01_9474_4D61_8E22_7E1B5F32974C__INCLUDED_)
#define AFX_SAVEFILEDLG_H__BDF7FA01_9474_4D61_8E22_7E1B5F32974C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDlg dialog

class CSaveFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CSaveFileDlg)

public:
	CSaveFileDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CSaveFileDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char savedir[200];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEFILEDLG_H__BDF7FA01_9474_4D61_8E22_7E1B5F32974C__INCLUDED_)
