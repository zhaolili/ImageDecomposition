#if !defined(AFX_SELECTFILEDLG_H__5317F080_8C1F_44E7_BD7C_9476F28EA8DC__INCLUDED_)
#define AFX_SELECTFILEDLG_H__5317F080_8C1F_44E7_BD7C_9476F28EA8DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectFileDlg dialog

class CSelectFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CSelectFileDlg)

public:
	CSelectFileDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CSelectFileDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char initdir[200];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFILEDLG_H__5317F080_8C1F_44E7_BD7C_9476F28EA8DC__INCLUDED_)
