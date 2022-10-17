; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSmtpDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "smtp.h"

ClassCount=4
Class1=CSmtpApp
Class2=CSmtpDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=mySock
Resource3=IDD_SMTP_DIALOG

[CLS:CSmtpApp]
Type=0
HeaderFile=smtp.h
ImplementationFile=smtp.cpp
Filter=N

[CLS:CSmtpDlg]
Type=0
HeaderFile=smtpDlg.h
ImplementationFile=smtpDlg.cpp
Filter=D
LastObject=IDC_EDIT_TITLE
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=smtpDlg.h
ImplementationFile=smtpDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SMTP_DIALOG]
Type=1
Class=CSmtpDlg
ControlCount=29
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_EDIT_NAME,edit,1350631552
Control10=IDC_EDIT_ADDR,edit,1350631552
Control11=IDC_EDIT_SERVER,edit,1350631552
Control12=IDC_EDIT_PORT,edit,1350631552
Control13=IDC_EDIT_USER,edit,1350631552
Control14=IDC_EDIT_PASS,edit,1350631552
Control15=IDC_EDIT_LETTER,edit,1350631552
Control16=IDC_STATIC,static,1342308864
Control17=IDC_EDIT_RECEIVER,edit,1350631552
Control18=IDC_STATIC,static,1342308864
Control19=IDC_EDIT_CC,edit,1350631552
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EDIT_BCC,edit,1350631552
Control22=IDC_STATIC,static,1342308864
Control23=IDC_EDIT_TITLE,edit,1350631552
Control24=IDC_STATIC,static,1342308864
Control25=IDC_EDIT_ATTACH,edit,1350631552
Control26=IDC_BTN_VIEW,button,1342242816
Control27=IDC_STATIC,static,1342308864
Control28=IDC_RICH_LIST,RICHEDIT,1352736772
Control29=IDC_STATIC,static,1342308352

[CLS:mySock]
Type=0
HeaderFile=mySock.h
ImplementationFile=mySock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=mySock

