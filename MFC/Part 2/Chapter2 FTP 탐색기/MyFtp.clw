; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myftp.h"
LastPage=0

ClassCount=12
Class1=CClientView
Class2=CDlgAddFtp
Class3=CDlgConnect
Class4=CDlgFile
Class5=CListCtrlEx
Class6=CMainFrame
Class7=CMyFtpApp
Class8=CAboutDlg
Class9=CMyFtpDoc
Class10=CMyFtpView
Class11=CStatusView
Class12=CTest

ResourceCount=6
Resource1=IDD_DIALOG_ADDFTP
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_DIALOG_CONNECT
Resource5=IDD_DIALOG1
Resource6=IDD_DIALOG_FILE

[CLS:CClientView]
Type=0
BaseClass=CView
HeaderFile=ClientView.h
ImplementationFile=ClientView.cpp

[CLS:CDlgAddFtp]
Type=0
BaseClass=CDialog
HeaderFile=dlgAddFtp.h
ImplementationFile=dlgAddFtp.cpp

[CLS:CDlgConnect]
Type=0
BaseClass=CDialog
HeaderFile=DlgConnect.h
ImplementationFile=DlgConnect.cpp

[CLS:CDlgFile]
Type=0
BaseClass=CDialog
HeaderFile=DlgFile.h
ImplementationFile=DlgFile.cpp

[CLS:CListCtrlEx]
Type=0
BaseClass=CListCtrl
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMyFtpApp]
Type=0
BaseClass=CWinApp
HeaderFile=MyFtp.h
ImplementationFile=MyFtp.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MyFtp.cpp
ImplementationFile=MyFtp.cpp

[CLS:CMyFtpDoc]
Type=0
BaseClass=CDocument
HeaderFile=MyFtpDoc.h
ImplementationFile=MyFtpDoc.cpp

[CLS:CMyFtpView]
Type=0
BaseClass=CView
HeaderFile=MyFtpView.h
ImplementationFile=MyFtpView.cpp

[CLS:CStatusView]
Type=0
BaseClass=CListView
HeaderFile=StatusView.h
ImplementationFile=StatusView.cpp

[CLS:CTest]
Type=0
BaseClass=CDialog
HeaderFile=Test.h
ImplementationFile=Test.cpp

[DLG:IDD_DIALOG_ADDFTP]
Type=1
Class=CDlgAddFtp
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342177283

[DLG:IDD_DIALOG_CONNECT]
Type=1
Class=CDlgConnect
ControlCount=17
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_TREE1,SysTreeView32,1350631471
Control4=IDC_STATIC,button,1342177287
Control5=IDC_BUTTON_DEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_ADD,edit,1484849280
Control11=IDC_EDIT_ID,edit,1484849280
Control12=IDC_EDIT_PASS,edit,1484849312
Control13=IDC_BUTTON_ANO,button,1476460544
Control14=IDC_BUTTON_CONNECT,button,1476460544
Control15=IDC_BUTTON_ADDSERVER,button,1342242816
Control16=IDC_BUTTON_SAVE,button,1476460544
Control17=IDC_STATIC_NAME,static,1342308352

[DLG:IDD_DIALOG_FILE]
Type=1
Class=CDlgFile
ControlCount=9
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC_FILENAME,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC_SERVER,static,1342308352
Control5=IDC_STSTIC_ADD,static,1342308352
Control6=IDC_ANIMATE,SysAnimate32,1342242818
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_PROGRESS1,msctls_progress32,1350565888

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=CTest
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_CLIENT,SysListView32,1350631424
Control4=IDC_LIST_FTP,SysListView32,1350631424

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CONNECT
Command2=ID_DISCONNECT
Command3=ID_UPLOAD
Command4=ID_DOWNLOAD
Command5=ID_EXIT
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CONNECT
Command2=ID_DISCONNECT
Command3=ID_EXIT
Command4=ID_UPLOAD
Command5=ID_DOWNLOAD
Command6=ID_APP_ABOUT
CommandCount=6

