; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFtpDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Ftp.h"

ClassCount=3
Class1=CFtpApp
Class2=CFtpDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FTP_DIALOG

[CLS:CFtpApp]
Type=0
HeaderFile=Ftp.h
ImplementationFile=Ftp.cpp
Filter=N

[CLS:CFtpDlg]
Type=0
HeaderFile=FtpDlg.h
ImplementationFile=FtpDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFtpDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=FtpDlg.h
ImplementationFile=FtpDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FTP_DIALOG]
Type=1
Class=CFtpDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_FTP,static,1342308864
Control4=IDC_STATIC_NAME,static,1342308864
Control5=IDC_EDIT_FTP,edit,1350631552
Control6=IDC_EDIT_NAME,edit,1350631552
Control7=IDC_STATIC_PWD,static,1342308864
Control8=IDC_EDIT_PWD,edit,1350631552
Control9=IDC_STATIC_FILE,static,1342308864
Control10=IDC_LIST_FILE,listbox,1352728833
Control11=IDC_DOWNLOAD,button,1342242816
Control12=IDC_UPLOAD,button,1342242816

