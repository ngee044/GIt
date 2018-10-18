; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInternetTamView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "InternetTam.h"
LastPage=0

ClassCount=5
Class1=CInternetTamApp
Class2=CInternetTamDoc
Class3=CInternetTamView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME

[CLS:CInternetTamApp]
Type=0
HeaderFile=InternetTam.h
ImplementationFile=InternetTam.cpp
Filter=N

[CLS:CInternetTamDoc]
Type=0
HeaderFile=InternetTamDoc.h
ImplementationFile=InternetTamDoc.cpp
Filter=N

[CLS:CInternetTamView]
Type=0
HeaderFile=InternetTamView.h
ImplementationFile=InternetTamView.cpp
Filter=C
BaseClass=CHtmlView
VirtualFilter=7VWC
LastObject=CInternetTamView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SOUCE




[CLS:CAboutDlg]
Type=0
HeaderFile=InternetTam.cpp
ImplementationFile=InternetTam.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SOUCE
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_BACK
Command2=ID_FORWARD
Command3=ID_STOP
Command4=ID_REFRESH
Command5=ID_HOME
Command6=ID_APP_ABOUT
CommandCount=6

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552

