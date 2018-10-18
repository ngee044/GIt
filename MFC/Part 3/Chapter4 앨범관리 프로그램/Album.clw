; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "album.h"
LastPage=0

ClassCount=8
Class1=CAlbumApp
Class2=CAboutDlg
Class3=CAlbumDoc
Class4=CAlbumView
Class5=CMainFrame
Class6=CProcessDlg
Class7=CResultView
Class8=CSearchDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_PROCESS_DLG
Resource4=IDD_SEARCH_DLG

[CLS:CAlbumApp]
Type=0
BaseClass=CWinApp
HeaderFile=Album.h
ImplementationFile=Album.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Album.cpp
ImplementationFile=Album.cpp
LastObject=CAboutDlg

[CLS:CAlbumDoc]
Type=0
BaseClass=CDocument
HeaderFile=AlbumDoc.h
ImplementationFile=AlbumDoc.cpp

[CLS:CAlbumView]
Type=0
BaseClass=CTreeView
HeaderFile=AlbumView.h
ImplementationFile=AlbumView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CProcessDlg]
Type=0
BaseClass=CDialog
HeaderFile=ProcessDlg.h
ImplementationFile=ProcessDlg.cpp

[CLS:CResultView]
Type=0
BaseClass=CListView
HeaderFile=ResultView.h
ImplementationFile=ResultView.cpp

[CLS:CSearchDlg]
Type=0
BaseClass=CDialog
HeaderFile=SearchDlg.h
ImplementationFile=SearchDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342177296
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342177297
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_PROCESS_DLG]
Type=1
Class=CProcessDlg
ControlCount=13
Control1=IDC_SINGER_EDIT,edit,1350631552
Control2=IDC_TITLE_EDIT,edit,1350631552
Control3=IDC_GENRE_COMBO,combobox,1344340227
Control4=IDC_DATETIME,SysDateTimePick32,1342242848
Control5=IDC_FEELING_EDIT,edit,1350631552
Control6=IDOK,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342177296

[DLG:IDD_SEARCH_DLG]
Type=1
Class=CSearchDlg
ControlCount=7
Control1=IDC_ITEM_COMBO,combobox,1344340226
Control2=IDC_SEARCH_EDIT,edit,1350631552
Control3=IDC_SEARCH_BUTTON,button,1342242816
Control4=IDOK,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177296

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_ADD_DATA
Command2=ID_UPDATE_DATA
Command3=ID_DELETE_DATA
Command4=ID_SEARCH_DATA
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_ADD_DATA
Command2=ID_UPDATE_DATA
Command3=ID_DELETE_DATA
Command4=ID_SEARCH_DATA
Command5=ID_APP_EXIT
Command6=ID_APP_ABOUT
CommandCount=6

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

