// ImageDecomposition.h : main header file for the IMAGEDECOMPOSITION application
//

#if !defined(AFX_IMAGEDECOMPOSITION_H__52923502_B3FD_45FE_A9B4_04838391CE62__INCLUDED_)
#define AFX_IMAGEDECOMPOSITION_H__52923502_B3FD_45FE_A9B4_04838391CE62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ImageDecomp.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CImageDecompositionApp:
// See ImageDecomposition.cpp for the implementation of this class
//



class CImageDecompositionApp : public CWinApp
{
public:
	CImageDecompositionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDecompositionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImageDecompositionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDECOMPOSITION_H__52923502_B3FD_45FE_A9B4_04838391CE62__INCLUDED_)
