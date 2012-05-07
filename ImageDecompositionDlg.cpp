// ImageDecompositionDlg.cpp : implementation file
//

#include "stdafx.h"
#include <wingdi.h>
#include "ImageDecomposition.h"
#include "ImageDecompositionDlg.h"
#include "SelectFileDlg.h"
#include "SaveFileDlg.h"
#include "DisplayerDlg.h"
#include "AlbedoDlg.h"
#include "ShadingDlg.h"
#include "ImageDecomp.h"
#include "Img.h"
#include "Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CImageDecomp imageDecmp;

// typedef struct  
// {
// 	char *name;
// 	int  width;
// 	int  height;
// 	BYTE *buffer;
// }strParam, *pParam;
// 
// //a user define global thread function
// DWORD WINAPI showResult(LPVOID lpParameter)
// {
// 	pParam imgPar = (pParam)lpParameter;
// 	char   *winname = imgPar->name;
// 	int		width = imgPar->width;
// 	int		height = imgPar->height;
// 	BYTE    *imgBuffer = imgPar->buffer;
// 
// 	OpenGLDisplayer albedoImg;
// 	albedoImg.DisplayFromRGB(winname, width, height, imgBuffer);
// 
// 	return TRUE;
// }

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDecompositionDlg dialog

CImageDecompositionDlg::CImageDecompositionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageDecompositionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageDecompositionDlg)
	m_width = 0;
	m_height = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_conRCheck = FALSE;
	m_conICheck = FALSE;
	m_fixICheck = FALSE;
}

void CImageDecompositionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDecompositionDlg)
	DDX_Control(pDX, IDC_HEIGHT, m_ctrHeight);
	DDX_Control(pDX, IDC_F444, m_f444);
	DDX_Control(pDX, IDC_WIDTH, m_ctrWidth);
	DDX_Control(pDX, IDC_COMBOBITD, m_comboBitDepth);
	DDX_Control(pDX, IDC_COMBOLINW, m_comboLineWidth);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageDecompositionDlg, CDialog)
	//{{AFX_MSG_MAP(CImageDecompositionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_CONREFLECT, OnConreflect)
	ON_BN_CLICKED(IDC_CONILLUM, OnConillum)
	ON_BN_CLICKED(IDC_FIXILLUM, OnFixillum)
	ON_BN_CLICKED(IDC_DECOMPOSITION, OnDecomposition)
	ON_BN_CLICKED(IDC_CLOSEPIC, OnClosepic)
	ON_CBN_SELCHANGE(IDC_COMBOLINW, OnSelchangeCombolinw)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SAVEDRAWS, OnSavedraws)
	ON_BN_CLICKED(IDC_OUTPUT, OnOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDecompositionDlg message handlers

BOOL CImageDecompositionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

 	// Add "About..." menu item to system menu.

 	// IDM_ABOUTBOX must be in the system command range.
 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
 	ASSERT(IDM_ABOUTBOX < 0xF000);
 
 	CMenu* pSysMenu = GetSystemMenu(FALSE);
 	if (pSysMenu != NULL)
 	{
 		CString strAboutMenu;
 		strAboutMenu.LoadString(IDS_ABOUTBOX);
 		if (!strAboutMenu.IsEmpty())
 		{
 			pSysMenu->AppendMenu(MF_SEPARATOR);
 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
 		}
 	}
 
 	// Set the icon for this dialog.  The framework does this automatically
 	//  when the application's main window is not a dialog
 	SetIcon(m_hIcon, TRUE);			// Set big icon
 	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINTUX)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINTUX)), FALSE);
 	
 	// TODO: Add extra initialization here
	CString lineWid;
	lineWid = "1";
	m_comboLineWidth.AddString(lineWid);
	lineWid = "2";
	m_comboLineWidth.AddString(lineWid);
	lineWid = "3";
	m_comboLineWidth.AddString(lineWid);
	lineWid = "4";
	m_comboLineWidth.AddString(lineWid);
	m_comboLineWidth.SetCurSel(0);

	CString bitDepth;
	bitDepth = " 8";
	m_comboBitDepth.AddString(bitDepth);
	bitDepth = "10";
	m_comboBitDepth.AddString(bitDepth);
	bitDepth = "12";
	m_comboBitDepth.AddString(bitDepth);
	m_comboBitDepth.SetCurSel(0);

	GetDlgItem(IDC_WIDTH)->SetFocus();
	m_ctrWidth.SetSel(0, -1);
	m_f444.SetCheck(BST_CHECKED);
	GetDlgItem(IDC_F444)->EnableWindow(FALSE);
	GetDlgItem(IDC_F420)->EnableWindow(FALSE);
	GetDlgItem(IDC_F400)->EnableWindow(FALSE);
	
	return FALSE;
 	
 	// return TRUE;  // return TRUE  unless you set the focus to a control
 }

void CImageDecompositionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageDecompositionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageDecompositionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImageDecompositionDlg::OnOpenfile() 
{
	// TODO: Add your control notification handler code here

	
	//if the previous displayer dialog is not closed, close it before opening a new displayer dialog
	if (m_dspDlg.m_imgOpen)
	{
		OnClosepic();
	}
	else
		if ((!m_dspDlg.m_imgOpen)&&((m_dspDlg.m_RPEN)||(m_dspDlg.m_GPEN)||(m_dspDlg.m_BPEN)))
		{
			m_dspDlg.m_RPEN = FALSE;
			m_dspDlg.m_GPEN = FALSE;
			m_dspDlg.m_BPEN = FALSE;
		}
	

 	UpdateData();
 	if ((m_width==0)||(m_height==0))
 	{
 		MessageBox("Wrong image size!");
 		return;
 	}	
	
	CSelectFileDlg fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	
	CString fext;
	int retVal;
	retVal = fDlg.DoModal();	
	fext = fDlg.GetFileExt();
	while((fext != "bmp")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = fDlg.DoModal();
		fext = fDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;

 	if (fext=="bmp")
 	{
 		m_comboBitDepth.SetCurSel(0);
 		GetDlgItem(IDC_COMBOBITD)->EnableWindow(FALSE);
	}

	//the following gets the input parameters
	CString fpathnam;
	fpathnam = fDlg.GetPathName();
	int itype = 0;  /////
	int bd = 0;
	CString str;
	m_comboBitDepth.GetLBText(m_comboBitDepth.GetCurSel(), str);
	if (str==" 8")
		bd = 8;
	if (str=="10")
		bd = 10;
	if (str=="12")
		bd = 12;

	//create dialog
	m_dspDlg.Create(IDD_DISPLAYDLG, this);
	//get the space size between the border and client area of the dialog
	CWnd *pWnd = m_dspDlg.GetDlgItem(IDC_PICTUREDSP);
	CRect rect;
	pWnd->GetWindowRect(&rect);
	m_dspDlg.ScreenToClient(&rect);
	//set position
	::SetWindowPos(m_dspDlg.m_hWnd,HWND_TOPMOST,0, 0, m_width+(2*rect.left),m_height+(2*rect.top),SWP_SHOWWINDOW);
	//show dialog
	m_dspDlg.ShowWindow(SW_SHOW);

	if(!m_dspDlg.ImageShow(fpathnam, m_width, m_height, bd, itype))
	{
	  m_width = 0;
	  m_height = 0;
	  UpdateData(FALSE);
	}
	return;	
}


void CImageDecompositionDlg::OnConreflect() 
{
	// TODO: Add your control notification handler code here
	if ((!m_dspDlg.m_imgOpen)&&(!m_conRCheck))
	{		
		((CButton *)GetDlgItem(IDC_CONREFLECT))->SetCheck(BST_UNCHECKED);
		MessageBox("No Image, please Load An Image!");
		return;
	}		

	if (BST_CHECKED==IsDlgButtonChecked(IDC_CONREFLECT))
	{
		CString str;
		m_dspDlg.m_RPEN = m_conRCheck = TRUE;
		m_comboLineWidth.GetLBText(m_comboLineWidth.GetCurSel(), str);
		m_dspDlg.m_lineWid = atoi(str);
	}		
	else
	{
		m_dspDlg.m_RPEN = m_conRCheck = FALSE;
		m_comboLineWidth.SetCurSel(0);
	}
	
	return;
}

void CImageDecompositionDlg::OnConillum() 
{
	// TODO: Add your control notification handler code here
	if ((!m_dspDlg.m_imgOpen)&&(!m_conICheck))
	{		
		((CButton *)GetDlgItem(IDC_CONILLUM))->SetCheck(BST_UNCHECKED);
		MessageBox("No Image, please Load An Image!");
		return;
	}		
	
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CONILLUM))
	{
		CString str;
		m_dspDlg.m_GPEN = m_conICheck = TRUE;
		m_comboLineWidth.GetLBText(m_comboLineWidth.GetCurSel(), str);
		m_dspDlg.m_lineWid = atoi(str);
	}
	else
	{
		m_dspDlg.m_GPEN = m_conICheck = FALSE;
		m_comboLineWidth.SetCurSel(0);
	}
		
	return;	
}

void CImageDecompositionDlg::OnFixillum() 
{
	// TODO: Add your control notification handler code here
	if ((!m_dspDlg.m_imgOpen)&&(!m_fixICheck))
	{		
		((CButton *)GetDlgItem(IDC_FIXILLUM))->SetCheck(BST_UNCHECKED);
		MessageBox("No Image, please Load An Image!");
		return;
	}		
	
	if (BST_CHECKED==IsDlgButtonChecked(IDC_FIXILLUM))
	{
		CString str;
		m_dspDlg.m_BPEN = m_fixICheck = TRUE;	
		m_comboLineWidth.GetLBText(m_comboLineWidth.GetCurSel(), str);
		m_dspDlg.m_lineWid = atoi(str);
	}			
	else
	{
		m_dspDlg.m_BPEN = m_fixICheck = FALSE;
		m_comboLineWidth.SetCurSel(0);
	}		
	
	return;		
}

void CImageDecompositionDlg::OnDecomposition() 
{
	// TODO: Add your control notification handler code here
	if (!m_dspDlg.m_hWnd)
	{
		MessageBox("No Image, please Load An Image!");
		return;
	}
	//image decomposition
	imageDecmp.decompImg();

	int cx = GetSystemMetrics(SM_CXSCREEN);  //get the width of the screen
	int cy = GetSystemMetrics(SM_CYSCREEN);  //screen height
	CRect rect;
	CWnd *pWnd;

	//create the albedo dialog for display
	albedoDlg.Create(IDD_ALBEDODLG, this);
	//get the space size between the border and client area of the dialog
	pWnd = albedoDlg.GetDlgItem(IDC_ALBEDOIMG);
	pWnd->GetWindowRect(&rect);
	albedoDlg.ScreenToClient(&rect);
	//set position
	::SetWindowPos(albedoDlg.m_hWnd,HWND_TOPMOST,cx/3, 0, m_width+(2*rect.left),m_height+(2*rect.top),SWP_SHOWWINDOW);
	albedoDlg.ShowWindow(SW_SHOW);

	//create the shading dialog for display
	shadingDlg.Create(IDD_SHADINGDLG, this);
	//
	pWnd = shadingDlg.GetDlgItem(IDC_SHADINGIMG);
	pWnd->GetWindowRect(&rect);
	shadingDlg.ScreenToClient(&rect);
	//set position
	::SetWindowPos(shadingDlg.m_hWnd,HWND_TOPMOST,(cx*2)/3, 0, m_width+(2*rect.left),m_height+(2*rect.top),SWP_SHOWWINDOW);
	shadingDlg.ShowWindow(SW_SHOW);

	//set size
	albedoDlg.GetImgSize(m_width, m_height);
	shadingDlg.GetImgSize(m_width, m_height);

	//show albedo and shading
	albedoDlg.ShowAlbedo();
	shadingDlg.ShowShading();
}

void CImageDecompositionDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CImageDecompositionDlg::OnClosepic() 
{
	// TODO: Add your control notification handler code here

	if (/*m_dspDlg.m_imgOpen*/m_dspDlg.m_hWnd)
	{
		m_dspDlg.m_imgOpen = FALSE;
		::DestroyWindow(m_dspDlg.m_hWnd);

		if (albedoDlg.m_hWnd)
			::DestroyWindow(albedoDlg.m_hWnd);
		if (shadingDlg.m_hWnd)
			::DestroyWindow(shadingDlg.m_hWnd);
		
		((CButton *)GetDlgItem(IDC_CONREFLECT))->SetCheck(BST_UNCHECKED);
		m_conRCheck = FALSE;
		m_dspDlg.m_RPEN = FALSE;


		((CButton *)GetDlgItem(IDC_CONILLUM))->SetCheck(BST_UNCHECKED);
		m_conICheck = FALSE;
		m_dspDlg.m_GPEN = FALSE;

		((CButton *)GetDlgItem(IDC_FIXILLUM))->SetCheck(BST_UNCHECKED);
		m_fixICheck = FALSE;
		m_dspDlg.m_BPEN = FALSE;

		imageDecmp.FlagMemRelease(m_width, m_height);
	}
	else
	{
		MessageBox("No Image to Close!");
	}
	
}



BOOL CImageDecompositionDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if ((pMsg->message == WM_KEYDOWN)&&(pMsg->wParam == VK_RETURN))
	{
 		switch(::GetDlgCtrlID(pMsg->hwnd))
 		{
		case IDC_WIDTH:
			GetDlgItem(IDC_HEIGHT)->SetFocus();
			m_ctrHeight.SetSel(0, -1);
			return TRUE;
		case IDC_HEIGHT:
			GetDlgItem(IDC_COMBOBITD)->SetFocus();
			return TRUE;
		case IDC_COMBOBITD:
			GetDlgItem(IDC_OPENFILE)->SetFocus();
			return TRUE;
		default:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CImageDecompositionDlg::OnSelchangeCombolinw() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_comboLineWidth.GetLBText(m_comboLineWidth.GetCurSel(), str);
	m_dspDlg.m_lineWid = atoi(str);
}

//clear user draws
void CImageDecompositionDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	if (!m_dspDlg.m_hWnd)
	{
		MessageBox("No image!");
		return;
	}
	HWND hWnd = m_dspDlg.GetSafeHwnd();
	m_dspDlg.m_counter = 0;  //reset scribbles ids
	::SendMessage(hWnd, WM_MSGFROMIDDLG, 0, 0);
	imageDecmp.InitFlags(m_width, m_height);
}

void CImageDecompositionDlg::OnSavedraws() 
{
	// TODO: Add your control notification handler code here
	if (!m_dspDlg.m_hWnd)
	{
		MessageBox("No image!");
		return;
	}
	if (m_dspDlg.scribbled==FALSE)
	{
		MessageBox("No scribbles, please scribble first.");
		return;
	}
// 	//send message to displayer dialog to clear the user drawings
// 	HWND hWnd = m_dspDlg.GetSafeHwnd();
// 	::SendMessage(hWnd, WM_MSGFROMIDDLG, 0, 0);

	//SAVE flags of current type: constant reflectance illumination..
	imageDecmp.SaveScribbles();

	/*Set unchecked*/
	((CButton *)GetDlgItem(IDC_CONREFLECT))->SetCheck(BST_UNCHECKED);
	m_conRCheck = FALSE;
	m_dspDlg.m_RPEN = FALSE;	
	
	((CButton *)GetDlgItem(IDC_CONILLUM))->SetCheck(BST_UNCHECKED);
	m_conICheck = FALSE;
	m_dspDlg.m_GPEN = FALSE;
	
	((CButton *)GetDlgItem(IDC_FIXILLUM))->SetCheck(BST_UNCHECKED);
	m_fixICheck = FALSE;
	m_dspDlg.m_BPEN = FALSE;
	/************************************************************************/

	//clear the flags
	m_dspDlg.scribbled = FALSE;
	m_dspDlg.m_counter = 0;  //reset scribbles ids
	imageDecmp.InitFlags(m_width, m_height);	
}


//save the decomposition result
void CImageDecompositionDlg::OnOutput() 
{
	// TODO: Add your control notification handler code here
	if (!m_dspDlg.m_hWnd)
	{
		MessageBox("NO intrinsic images!");
		return;
	}
	CSaveFileDlg	fDlg(FALSE, NULL, "albedo.bmp", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_OVERWRITEPROMPT , NULL, NULL);

	CString pathname;
	CString filename;
	if ( IDOK == fDlg.DoModal() )
	{
		pathname = fDlg.GetPathName();
		filename = fDlg.GetFileName();
    }
	CString albedopathnam = pathname;   //albedo file path name
	CString shadingname = "shading.bmp"; //default shading name
	int len1 = pathname.GetLength();
	int len2 = filename.GetLength();
	CString shadingpathnam =  pathname.Mid(0, (len1-len2)) + shadingname;  //shading file path name

	//output
	BYTE *albedoBuf = (BYTE *)imageDecmp.GetAlbedoBuf();
	BYTE *shadingBuf = (BYTE *)imageDecmp.GetShadingBuf();
	SnapShot(m_width, m_height, albedoBuf, albedopathnam);
	SnapShot(m_width, m_height, shadingBuf, shadingpathnam);

	return;
}

//create and save the albedo and shading bmp file
void CImageDecompositionDlg::SnapShot(int w, int h, BYTE *pData, CString fpathnam)
{
	int imagesize = w*h*3;

	//file header information
	BITMAPFILEHEADER bfh;
	bfh.bfType = 0x4d42;  //bm
	bfh.bfSize = imagesize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = bfh.bfSize - imagesize;

	//bitmap data information
	BITMAPINFOHEADER bih;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = w;
	bih.biHeight = h;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = imagesize;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	//
	FILE *fp = fopen(fpathnam, "wb");
	if (!fp)
	{
		MessageBox("intrinsic images saving failed.");
		return;
	}
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
	fwrite(pData, 1, imagesize, fp);
	fclose(fp);
}
