; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPuzzleOcxCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PuzzleOcx.h"
CDK=Y

ClassCount=3
Class1=CPuzzleOcxCtrl
Class2=CPuzzleOcxPropPage

ResourceCount=3
Resource1=IDD_PROPPAGE_PUZZLEOCX
LastPage=0
Resource2=IDD_ABOUTBOX_PUZZLEOCX
Class3=CDlgGame
Resource3=IDD_DIALOG_GAME

[CLS:CPuzzleOcxCtrl]
Type=0
HeaderFile=PuzzleOcxCtl.h
ImplementationFile=PuzzleOcxCtl.cpp
Filter=W
LastObject=CPuzzleOcxCtrl
BaseClass=COleControl
VirtualFilter=wWC

[CLS:CPuzzleOcxPropPage]
Type=0
HeaderFile=PuzzleOcxPpg.h
ImplementationFile=PuzzleOcxPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_PUZZLEOCX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_PUZZLEOCX]
Type=1
Class=CPuzzleOcxPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_GAME]
Type=1
Class=CDlgGame
ControlCount=13
Control1=IDC_STATIC,button,1073741831
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342177296
Control10=IDC_STATIC,static,1342177296
Control11=IDC_STATIC_CLICK,static,1342308352
Control12=IDC_STATIC_TIME,static,1342308352
Control13=IDC_STATIC_PERCENT,static,1342308352

[CLS:CDlgGame]
Type=0
HeaderFile=DlgGame.h
ImplementationFile=DlgGame.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgGame
VirtualFilter=dWC

