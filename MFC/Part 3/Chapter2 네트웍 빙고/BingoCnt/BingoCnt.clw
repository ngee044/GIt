; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBingoCntDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bingocnt.h"
LastPage=0

ClassCount=5
Class1=CBingoCntApp
Class2=CAboutDlg
Class3=CBingoCntDlg
Class4=CDlgConnect
Class5=CSocCom

ResourceCount=3
Resource1=IDD_DIALOG_CONNECT
Resource2=IDD_ABOUTBOX
Resource3=IDD_BINGOCNT_DIALOG

[CLS:CBingoCntApp]
Type=0
BaseClass=CWinApp
HeaderFile=BingoCnt.h
ImplementationFile=BingoCnt.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=BingoCntDlg.cpp
ImplementationFile=BingoCntDlg.cpp
LastObject=CAboutDlg

[CLS:CBingoCntDlg]
Type=0
BaseClass=CDialog
HeaderFile=BingoCntDlg.h
ImplementationFile=BingoCntDlg.cpp
LastObject=CBingoCntDlg

[CLS:CDlgConnect]
Type=0
BaseClass=CDialog
HeaderFile=DlgConnect.h
ImplementationFile=DlgConnect.cpp

[CLS:CSocCom]
Type=0
BaseClass=CSocket
HeaderFile=SocCom.h
ImplementationFile=SocCom.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BINGOCNT_DIALOG]
Type=1
Class=CBingoCntDlg
ControlCount=10
Control1=IDC_EDIT_SEND,edit,1350631552
Control2=IDC_BUTTON_SEND,button,1476460544
Control3=IDC_LIST1,listbox,1353777409
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC_STATUS,static,1342308352
Control8=IDC_STATIC_CONNECT,static,1342308352
Control9=IDC_STATIC_ME,static,1342308352
Control10=IDC_BUTTON_CONNECT,button,1342242816

[DLG:IDD_DIALOG_CONNECT]
Type=1
Class=CDlgConnect
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_IP,edit,1350631552

