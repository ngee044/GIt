; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHWPConvertDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HWPConvert.h"

ClassCount=4
Class1=CHWPConvertApp
Class2=CHWPConvertDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_HWPCONVERT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CDlgOpt
Resource4=IDD_DIALOG_OPTION

[CLS:CHWPConvertApp]
Type=0
HeaderFile=HWPConvert.h
ImplementationFile=HWPConvert.cpp
Filter=N

[CLS:CHWPConvertDlg]
Type=0
HeaderFile=HWPConvertDlg.h
ImplementationFile=HWPConvertDlg.cpp
Filter=D
LastObject=CHWPConvertDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=HWPConvertDlg.h
ImplementationFile=HWPConvertDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HWPCONVERT_DIALOG]
Type=1
Class=CHWPConvertDlg
ControlCount=3
Control1=IDC_BUTTON_OPTION,button,1342242816
Control2=IDC_BUTTON_AUTO,button,1342242816
Control3=IDC_LIST,SysListView32,1350631433

[DLG:IDD_DIALOG_OPTION]
Type=1
Class=CDlgOpt
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CHECK_HWP,button,1342242819
Control5=IDC_CHECK_DOC,button,1342242819
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC_WATCHDIR,static,1342312448
Control8=IDC_BUTTON_WATCH,button,1342242816
Control9=IDC_STATIC_HWPDIR,static,1342312448
Control10=IDC_BUTTON_HWP,button,1342242816
Control11=IDC_STATIC_DOCDIR,static,1342312448
Control12=IDC_BUTTON_DOC,button,1342242816

[CLS:CDlgOpt]
Type=0
HeaderFile=DlgOpt.h
ImplementationFile=DlgOpt.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_DOC
VirtualFilter=dWC

