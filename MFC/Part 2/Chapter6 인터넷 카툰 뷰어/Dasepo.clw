; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Dasepo.h"
LastPage=0

ClassCount=8
Class1=CDasepoApp
Class2=CDasepoDoc
Class3=CDasepoView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CTreeLeft
Class6=CAboutDlg
Class7=CDPConf
Resource2=IDR_MAINFRAME
Class8=CDlgStart
Resource3=IDD_DIALOG_START

[CLS:CDasepoApp]
Type=0
HeaderFile=Dasepo.h
ImplementationFile=Dasepo.cpp
Filter=N

[CLS:CDasepoDoc]
Type=0
HeaderFile=DasepoDoc.h
ImplementationFile=DasepoDoc.cpp
Filter=N

[CLS:CDasepoView]
Type=0
HeaderFile=DasepoView.h
ImplementationFile=DasepoView.cpp
Filter=C
LastObject=CDasepoView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDC_BUTTON_FIND



[CLS:CTreeLeft]
Type=0
HeaderFile=TreeLeft.h
ImplementationFile=TreeLeft.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=CTreeLeft

[CLS:CAboutDlg]
Type=0
HeaderFile=Dasepo.cpp
ImplementationFile=Dasepo.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_FIND,edit,1350631552
Control3=IDC_BUTTON_FIND,button,1342242816

[CLS:CDPConf]
Type=0
HeaderFile=DPConf.h
ImplementationFile=DPConf.cpp
BaseClass=CSocket
Filter=N

[DLG:IDD_DIALOG_START]
Type=1
Class=CDlgStart
ControlCount=2
Control1=IDC_STATIC,static,1342177298
Control2=IDC_STATIC_INFO,static,1342308353

[CLS:CDlgStart]
Type=0
HeaderFile=DlgStart.h
ImplementationFile=DlgStart.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgStart
VirtualFilter=dWC

