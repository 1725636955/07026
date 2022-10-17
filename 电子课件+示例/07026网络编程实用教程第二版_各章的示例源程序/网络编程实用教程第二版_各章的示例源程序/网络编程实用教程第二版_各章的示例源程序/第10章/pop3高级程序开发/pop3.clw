; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CViewDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pop3.h"
LastPage=0

ClassCount=4
Class1=CChooseDlg
Class2=CPop3App
Class3=CPop3Dlg
Class4=CViewDlg

ResourceCount=3
Resource1=IDD_MSGCHOOSE
Resource2=IDD_MSGVIEW
Resource3=IDD_POP3_DIALOG

[CLS:CChooseDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChooseDlg.h
ImplementationFile=ChooseDlg.cpp

[CLS:CPop3App]
Type=0
BaseClass=CWinApp
HeaderFile=pop3.h
ImplementationFile=pop3.cpp
LastObject=CPop3App

[CLS:CPop3Dlg]
Type=0
BaseClass=CDialog
HeaderFile=pop3Dlg.h
ImplementationFile=pop3Dlg.cpp
LastObject=CPop3Dlg

[CLS:CViewDlg]
Type=0
BaseClass=CDialog
HeaderFile=ViewDlg.h
ImplementationFile=ViewDlg.cpp
LastObject=CViewDlg

[DLG:IDD_MSGCHOOSE]
Type=1
Class=CChooseDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MSGLIST,combobox,1344339971
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_POP3_DIALOG]
Type=1
Class=CPop3Dlg
ControlCount=12
Control1=IDOK,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SERVER,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_USER,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PASS,edit,1350631584
Control8=IDC_CONN,button,1342242817
Control9=IDC_INFO,RICHEDIT,1352738820
Control10=IDC_DISC,button,1476460544
Control11=IDC_VIEW,button,1476460544
Control12=IDC_DEL,button,1342242819

[DLG:IDD_MSGVIEW]
Type=1
Class=CViewDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_MSGTEXT,RICHEDIT,1352738820
Control3=IDC_SAVE,button,1342242816

