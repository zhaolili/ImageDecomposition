; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImageDecompositionDlg
LastTemplate=CFileDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "imagedecomposition.h"
LastPage=0

ClassCount=8
Class1=CAlbedoDlg
Class2=CDisplayerDlg
Class3=CImageDecompositionApp
Class4=CAboutDlg
Class5=CImageDecompositionDlg
Class6=CSelectFileDlg

ResourceCount=7
Resource1=IDD_ALBEDODLG
Resource2=IDD_SHADINGDLG
Resource3=IDD_SELECTFILEDLG
Resource4=IDD_DISPLAYDLG
Resource5=IDD_IMAGEDECOMPOSITION_DIALOG
Resource6=IDD_ABOUTBOX
Class7=CShadingDlg
Class8=CSaveFileDlg
Resource7=IDD_SAVEFILEDLG

[CLS:CAlbedoDlg]
Type=0
BaseClass=CDialog
HeaderFile=AlbedoDlg.h
ImplementationFile=AlbedoDlg.cpp
LastObject=CAlbedoDlg
Filter=D
VirtualFilter=dWC

[CLS:CDisplayerDlg]
Type=0
BaseClass=CDialog
HeaderFile=DisplayerDlg.h
ImplementationFile=DisplayerDlg.cpp

[CLS:CImageDecompositionApp]
Type=0
BaseClass=CWinApp
HeaderFile=ImageDecomposition.h
ImplementationFile=ImageDecomposition.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ImageDecompositionDlg.cpp
ImplementationFile=ImageDecompositionDlg.cpp
LastObject=CAboutDlg

[CLS:CImageDecompositionDlg]
Type=0
BaseClass=CDialog
HeaderFile=ImageDecompositionDlg.h
ImplementationFile=ImageDecompositionDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CImageDecompositionDlg

[CLS:CSelectFileDlg]
Type=0
BaseClass=CFileDialog
HeaderFile=SelectFileDlg.h
ImplementationFile=SelectFileDlg.cpp

[DLG:IDD_ALBEDODLG]
Type=1
Class=CAlbedoDlg
ControlCount=1
Control1=IDC_ALBEDOIMG,static,1342177287

[DLG:IDD_DISPLAYDLG]
Type=1
Class=CDisplayerDlg
ControlCount=1
Control1=IDC_PICTUREDSP,static,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177287

[DLG:IDD_IMAGEDECOMPOSITION_DIALOG]
Type=1
Class=CImageDecompositionDlg
ControlCount=22
Control1=IDCANCEL,button,1342242816
Control2=IDC_OPENFILE,button,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_STATIC,button,1342178055
Control5=IDC_DECOMPOSITION,button,1342242816
Control6=IDC_COMBOBITD,combobox,1344340227
Control7=IDC_STATIC,static,1342308865
Control8=IDC_CONREFLECT,button,1342373891
Control9=IDC_CONILLUM,button,1342242819
Control10=IDC_FIXILLUM,button,1342242819
Control11=IDC_COMBOLINW,combobox,1344340227
Control12=IDC_STATIC,static,1342308865
Control13=IDC_CLOSEPIC,button,1342242816
Control14=IDC_WIDTH,edit,1350631553
Control15=IDC_STATIC,static,1342308865
Control16=IDC_HEIGHT,edit,1350631553
Control17=IDC_F444,button,1342308361
Control18=IDC_F420,button,1342177289
Control19=IDC_F400,button,1342177289
Control20=IDC_CLEAR,button,1342242816
Control21=IDC_SAVEDRAWS,button,1342242816
Control22=IDC_OUTPUT,button,1342242816

[DLG:IDD_SELECTFILEDLG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_SAVEFILEDLG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_SHADINGDLG]
Type=1
Class=CShadingDlg
ControlCount=1
Control1=IDC_SHADINGIMG,static,1342177287

[CLS:CShadingDlg]
Type=0
HeaderFile=ShadingDlg.h
ImplementationFile=ShadingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CShadingDlg
VirtualFilter=dWC

[CLS:CSaveFileDlg]
Type=0
HeaderFile=SaveFileDlg.h
ImplementationFile=SaveFileDlg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=CSaveFileDlg
VirtualFilter=dWC

