; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyPaintView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mypaint.h"
LastPage=0

ClassCount=5
Class1=CMainFrame
Class2=CMyPaintApp
Class3=CAboutDlg
Class4=CMyPaintDoc
Class5=CMyPaintView

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMyPaintApp]
Type=0
BaseClass=CWinApp
HeaderFile=MyPaint.h
ImplementationFile=MyPaint.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MyPaint.cpp
ImplementationFile=MyPaint.cpp
LastObject=IDOK

[CLS:CMyPaintDoc]
Type=0
BaseClass=CDocument
HeaderFile=MyPaintDoc.h
ImplementationFile=MyPaintDoc.cpp

[CLS:CMyPaintView]
Type=0
BaseClass=CView
HeaderFile=MyPaintView.h
ImplementationFile=MyPaintView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_FILLCOLOR

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FREELINE
Command2=ID_LINE
Command3=ID_RECTANGLE
Command4=ID_ELLIPSE
Command5=ID_LINECOLOR
Command6=ID_FILLCOLOR
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_FREELINE
Command3=ID_LINE
Command4=ID_RECTANGLE
Command5=ID_ELLIPSE
Command6=ID_LINECOLOR
Command7=ID_FILLCOLOR
CommandCount=7

