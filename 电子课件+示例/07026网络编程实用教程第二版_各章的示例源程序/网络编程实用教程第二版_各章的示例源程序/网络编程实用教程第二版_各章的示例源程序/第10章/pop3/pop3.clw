; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPop3Dlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pop3.h"

ClassCount=4
Class1=CPop3App
Class2=CPop3Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=mySock
Resource3=IDD_POP3_DIALOG

[CLS:CPop3App]
Type=0
HeaderFile=pop3.h
ImplementationFile=pop3.cpp
Filter=N

[CLS:CPop3Dlg]
Type=0
HeaderFile=pop3Dlg.h
ImplementationFile=pop3Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BTN_VIEW

[CLS:CAboutDlg]
Type=0
HeaderFile=pop3Dlg.h
ImplementationFile=pop3Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_POP3_DIALOG]
Type=1
Class=CPop3Dlg
ControlCount=14
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EDIT_SERVER,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EDIT_USER,edit,1350631552
Control6=IDC_STATIC,static,1342308864
Control7=IDC_EDIT_PASS,edit,1350631552
Control8=IDC_BTN_DISC,button,1342242816
Control9=IDC_BTN_CONN,button,1342242816
Control10=IDC_BTN_VIEW,button,1342242816
Control11=IDC_CHECK_DEL,button,1342242819
Control12=IDC_RICH_INFO,RICHEDIT,1352736772
Control13=IDC_COMB_LIST,combobox,1344340227
Control14=IDC_BTN_SAVE,button,1342242816

[CLS:mySock]
Type=0
HeaderFile=mySock.h
ImplementationFile=mySock.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=mySock
VirtualFilter=q

