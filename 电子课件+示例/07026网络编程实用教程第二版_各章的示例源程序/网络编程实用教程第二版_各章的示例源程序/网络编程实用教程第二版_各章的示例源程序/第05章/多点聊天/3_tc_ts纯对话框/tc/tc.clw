; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tc.h"

ClassCount=3
Class1=CTcApp
Class2=CTcDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TC_DIALOG

[CLS:CTcApp]
Type=0
HeaderFile=tc.h
ImplementationFile=tc.cpp
Filter=N

[CLS:CTcDlg]
Type=0
HeaderFile=tcDlg.h
ImplementationFile=tcDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTcDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=tcDlg.h
ImplementationFile=tcDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TC_DIALOG]
Type=1
Class=CTcDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_CNAME,static,1342308865
Control3=IDC_EDIT_CNAME,edit,1350631552
Control4=IDC_STATIC_SNAME,static,1342308865
Control5=IDC_EDIT_SNAME,edit,1350631552
Control6=IDC_STATIC_PORT,static,1342308865
Control7=IDC_EDIT_PORT,edit,1350631552
Control8=IDC_BUTTON_CONN,button,1342242816
Control9=IDC_STATIC_MSG,static,1342308865
Control10=IDC_EDIT_MSG,edit,1350631552
Control11=IDC_BUTTON_CLOSE,button,1342242816
Control12=IDC_LIST_MSG,listbox,1352728833

