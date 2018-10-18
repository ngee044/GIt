; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendMsgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SendMsg.h"

ClassCount=3
Class1=CSendMsgApp
Class2=CSendMsgDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SENDMSG_DIALOG

[CLS:CSendMsgApp]
Type=0
HeaderFile=SendMsg.h
ImplementationFile=SendMsg.cpp
Filter=N

[CLS:CSendMsgDlg]
Type=0
HeaderFile=SendMsgDlg.h
ImplementationFile=SendMsgDlg.cpp
Filter=D
LastObject=CSendMsgDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SendMsgDlg.h
ImplementationFile=SendMsgDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDMSG_DIALOG]
Type=1
Class=CSendMsgDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342181390
Control3=IDC_EDIT_SEND,edit,1350631552
Control4=IDC_BUTTON_SEND,button,1342242816
Control5=IDC_STATIC,static,1342308352

