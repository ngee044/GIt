; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CQueryView
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "datamanager.h"
LastPage=0

ClassCount=13
Class1=CDataManagerApp
Class2=CAboutDlg
Class3=CDataManagerDoc
Class4=CDataManagerView
Class5=CFieldInfoView
Class6=CLeftContainerView
Class7=CMainFrame
Class8=CQueryView
Class9=CResultView
Class10=CRightContainerView

ResourceCount=4
Resource1=IDR_MAINFRAME (Korean)
Class11=CSplitterWndEx
Class12=CCaption
Resource2=IDD_ABOUTBOX (Korean)
Resource3=IDR_MAINFRAME
Class13=CListCtrlEx
Resource4=IDD_ABOUTBOX

[CLS:CDataManagerApp]
Type=0
BaseClass=CWinApp
HeaderFile=DataManager.h
ImplementationFile=DataManager.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DataManager.cpp
ImplementationFile=DataManager.cpp
LastObject=CAboutDlg

[CLS:CDataManagerDoc]
Type=0
BaseClass=CDocument
HeaderFile=DataManagerDoc.h
ImplementationFile=DataManagerDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CDataManagerDoc

[CLS:CDataManagerView]
Type=0
BaseClass=CView
HeaderFile=DataManagerView.h
ImplementationFile=DataManagerView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CDataManagerView

[CLS:CFieldInfoView]
Type=0
BaseClass=CView
HeaderFile=FieldInfoView.h
ImplementationFile=FieldInfoView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CFieldInfoView

[CLS:CLeftContainerView]
Type=0
BaseClass=CView
HeaderFile=LeftContainerView.h
ImplementationFile=LeftContainerView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CQueryView]
Type=0
BaseClass=CView
HeaderFile=QueryView.h
ImplementationFile=QueryView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_EXECUTESQL

[CLS:CResultView]
Type=0
BaseClass=CView
HeaderFile=ResultView.h
ImplementationFile=ResultView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CResultView

[CLS:CRightContainerView]
Type=0
BaseClass=CView
HeaderFile=RightContainerView.h
ImplementationFile=RightContainerView.cpp
LastObject=CRightContainerView

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342177296

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EXECUTESQL
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

[CLS:CSplitterWndEx]
Type=0
HeaderFile=SplitterWndEx.h
ImplementationFile=SplitterWndEx.cpp
BaseClass=CSplitterWnd
Filter=W
LastObject=CSplitterWndEx
VirtualFilter=pWC

[CLS:CCaption]
Type=0
HeaderFile=Caption.h
ImplementationFile=Caption.cpp
BaseClass=generic CWnd
Filter=W

[TB:IDR_MAINFRAME (Korean)]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_MAINFRAME (Korean)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME (Korean)]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (Korean)]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CListCtrlEx]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CListCtrlEx

