; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatserver.h"
LastPage=0

ClassCount=5
Class1=CChatServerApp
Class2=CAboutDlg
Class3=CChatServerDlg
Class4=CSocServer

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CSocCom
Resource2=IDD_CHATSERVER_DIALOG

[CLS:CChatServerApp]
Type=0
BaseClass=CWinApp
HeaderFile=ChatServer.h
ImplementationFile=ChatServer.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatServerDlg.cpp
ImplementationFile=ChatServerDlg.cpp

[CLS:CChatServerDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatServerDlg.h
ImplementationFile=ChatServerDlg.cpp
LastObject=CChatServerDlg
Filter=D
VirtualFilter=dWC

[CLS:CSocServer]
Type=0
BaseClass=CSocket
HeaderFile=SocServer.h
ImplementationFile=SocServer.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATSERVER_DIALOG]
Type=1
Class=CChatServerDlg
ControlCount=6
Control1=IDC_STATIC_STATUS,static,1342308352
Control2=IDC_LIST1,listbox,1353777409
Control3=IDC_EDIT_SEND,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON_SEND,button,1342242816
Control6=IDC_BUTTON2,button,1342242816

[CLS:CSocCom]
Type=0
HeaderFile=SocCom.h
ImplementationFile=SocCom.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CSocCom

