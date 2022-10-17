; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTalkcDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "talkc.h"

ClassCount=4
Class1=CTalkcApp
Class2=CTalkcDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMySocket
Resource3=IDD_TALKC_DIALOG

[CLS:CTalkcApp]
Type=0
HeaderFile=talkc.h
ImplementationFile=talkc.cpp
Filter=N

[CLS:CTalkcDlg]
Type=0
HeaderFile=talkcDlg.h
ImplementationFile=talkcDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_CONNECT

[CLS:CAboutDlg]
Type=0
HeaderFile=talkcDlg.h
ImplementationFile=talkcDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TALKC_DIALOG]
Type=1
Class=CTalkcDlg
ControlCount=13
Control1=IDOK,button,1476460545
Control2=IDC_STATIC_SERVNAME,static,1342308865
Control3=IDC_STATIC_SERVPORT,static,1342308865
Control4=IDC_STATIC_MSG,static,1476526593
Control5=IDC_EDIT_SERVNAME,edit,1350631552
Control6=IDC_EDIT_SERVPORT,edit,1350631552
Control7=IDC_EDIT_MSG,edit,1484849280
Control8=IDC_BUTTON_CONNECT,button,1342242816
Control9=IDC_BUTTON_CLOSE,button,1342242816
Control10=IDC_STATIC_SENT,static,1476526081
Control11=IDC_STATIC_RECEIVED,static,1476526081
Control12=IDC_LIST_SENT,listbox,1352679681
Control13=IDC_LIST_RECEIVED,listbox,1352679681

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CMySocket

