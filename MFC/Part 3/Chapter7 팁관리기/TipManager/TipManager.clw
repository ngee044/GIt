; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tipmanager.h"
LastPage=0

ClassCount=11
Class1=CContainerView
Class2=CMainFrame
Class3=CSearchView
Class4=CTipManagerApp
Class5=CAboutDlg
Class6=CTipManagerDoc
Class7=CTipManagerView
Class8=CTipView

ResourceCount=4
Resource1=IDR_MAINFRAME
Class9=CCaption
Resource2=IDD_ABOUTBOX
Class10=CSearchDlg
Resource3=IDD_SEARCH_DIALOG
Class11=CProcessDlg
Resource4=IDD_PROCESS_DIALOG

[CLS:CContainerView]
Type=0
BaseClass=CView
HeaderFile=ContainerView.h
ImplementationFile=ContainerView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSearchView]
Type=0
BaseClass=CView
HeaderFile=SearchView.h
ImplementationFile=SearchView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CSearchView

[CLS:CTipManagerApp]
Type=0
BaseClass=CWinApp
HeaderFile=TipManager.h
ImplementationFile=TipManager.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=TipManager.cpp
ImplementationFile=TipManager.cpp
LastObject=CAboutDlg

[CLS:CTipManagerDoc]
Type=0
BaseClass=CDocument
HeaderFile=TipManagerDoc.h
ImplementationFile=TipManagerDoc.cpp

[CLS:CTipManagerView]
Type=0
BaseClass=CView
HeaderFile=TipManagerView.h
ImplementationFile=TipManagerView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CTipManagerView

[CLS:CTipView]
Type=0
BaseClass=CView
HeaderFile=TipView.h
ImplementationFile=TipView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CTipView

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
Command1=ID_ADD_DATA
Command2=ID_UPDATE_DATA
Command3=ID_SAVE_DATA
Command4=ID_DELETE_DATA
Command5=ID_SEARCH_DATA
Command6=ID_SEARCH_PANE
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_ADD_DATA
Command2=ID_UPDATE_DATA
Command3=ID_DELETE_DATA
Command4=ID_APP_EXIT
Command5=ID_SEARCH_DATA
Command6=ID_SEARCH_PANE
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

[CLS:CCaption]
Type=0
HeaderFile=Caption.h
ImplementationFile=Caption.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CCaption

[DLG:IDD_SEARCH_DIALOG]
Type=1
Class=CSearchDlg
ControlCount=9
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO_TITLE,button,1342308361
Control6=IDC_RADIO_GROUP,button,1342177289
Control7=IDC_RADIO_NOTE,button,1342177289
Control8=IDC_EDIT_SEARCH,edit,1350631552
Control9=IDC_STATIC,static,1342177296

[CLS:CSearchDlg]
Type=0
HeaderFile=SearchDlg.h
ImplementationFile=SearchDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSearchDlg

[DLG:IDD_PROCESS_DIALOG]
Type=1
Class=CProcessDlg
ControlCount=7
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_GROUP,combobox,1344339970
Control6=IDC_EDIT_TITLE,edit,1350631552
Control7=IDC_STATIC,static,1342177296

[CLS:CProcessDlg]
Type=0
HeaderFile=ProcessDlg.h
ImplementationFile=ProcessDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProcessDlg

