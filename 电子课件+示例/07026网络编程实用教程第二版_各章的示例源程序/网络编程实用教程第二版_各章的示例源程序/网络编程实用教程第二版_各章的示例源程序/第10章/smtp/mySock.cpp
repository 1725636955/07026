// mySock.cpp : implementation file
//

#include "stdafx.h"
#include "smtp.h"
#include "mySock.h"
#include  "smtpDlg.h"    //�Լ���ӵİ������
#include  "Base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BUFF 20000
/////////////////////////////////////////////////////////////////////////////
// mySock

mySock::mySock()
{
	m_pDlg = NULL;
	state=FIRST;
	error="���Ӳ��Ϸ�����\r\n";
}

mySock::~mySock()
{
	m_pDlg = NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(mySock, CAsyncSocket)
	//{{AFX_MSG_MAP(mySock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// mySock member functions

//���׽����յ�FD_CONNECT��Ϣʱ��ִ�д˺��������������ѽ���
void mySock::OnConnect(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CONNECT);
}

//���׽����յ�����������������ʱ��ִ�д˺���
void mySock::OnReceive(int nErrorCode) 
{
	if(nErrorCode==0) 
	{
		char buff[MAX_BUFF];             //���ջ�����
		int rec=Receive(buff,MAX_BUFF);  //���շ���������������
		buff[rec]=NULL;                  //��β��ΪNULL��
		lastMsg=buff;
		AnalyzeMsg();             //�����յ������ݣ�����ͬ�Ĵ���
	}  else  {
		error="�����ڼ䷢���˴���!\r\n";
		m_pDlg->Disp(S_CLOSE);   //��ʾ��Ϣ
	}
}

//���ر�����ʱ��ִ�д˺���
void mySock::OnClose(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CLOSE);
}
//ʹ�׽�����ĶԻ���ָ�����ָ�����Ի���
void mySock::SetParent(CSmtpDlg *pDlg)
{
	m_pDlg = pDlg;
}

//�˳�������
void mySock::Close()
{
	CString str;
	str.Format("quit%c%c",13,10);
	Send((LPCSTR)str,str.GetLength());
	m_pDlg->Disp(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="��������������Ѿ��Ͽ�\r\n";
}

//�������������������ݣ�������Ӧ�Ĵ���
void mySock::AnalyzeMsg()
{
	CString s;
	strstream str;
	string check;
	str<<(LPCSTR)lastMsg;
	str>>check;

	//����smtp�Ự������״̬������ͬ�Ĵ���	
	switch(state)
	{
	case FIRST: //����Ѿ����ӳɹ������ʼ����ʱ��stateΪFIRST
		m_pDlg->Disp(S_RECEIVE); //������Ϣ������
		if(!(check=="220")) {}
		s.Format("EHLO %s%c%c",m_pDlg->m_Name,13,10);
		Send((LPCSTR)s,s.GetLength()); //����EHLO����
		state=EHLO;
		break;

	case EHLO:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("AUTH LOGIN%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //����AUTH LOGIN����
		state=AUTH;
		break;

	case AUTH:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="334")) {}
		coder.Encode(m_pDlg->m_User);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
//	AfxMessageBox(s);

//		s.Format("bXVfbA==%c%c",13,10);  ///mu_l
//		s.Format("bXVfbGxs%c%c",13,10);  //mu_lll
		Send((LPCSTR)s,s.GetLength()); //�����û���
		state=USER; 
		break;

	case USER:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="334")) {}
		
		coder.Encode(m_pDlg->m_Pass);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
//	AfxMessageBox(s);
//		s.Format("NDkxMDE1%c%c",13,10); //491015
		Send((LPCSTR)s,s.GetLength()); //���Ϳ���
		state=PASS;
		break;

	case PASS:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="235")) {}
		s.Format("MAIL FROM:<%s>%c%c",m_pDlg->m_Addr,13,10); 
//		s.Format("MAIL FROM:<mu_lm@sina.com>%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //����MAIL FROM����
		state=MAIL;
		break;
	case MAIL:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
//		s.Format("RCPT TO: <mu_lm@sina.com>%c%c",13,10); 
		s.Format("RCPT TO: <%s>%c%c",m_pDlg->m_Receiver,13,10); 
		Send((LPCSTR)s,s.GetLength()); //����RECP����
		state=RCPT;
		break;
	case RCPT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("DATA%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //����DATA����
		state=DATA;
		break;
	case DATA: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="354")) {}
//		s.Format("From: %s%c%c",m_pDlg->m_Addr,13,10); 
//		Send((LPCSTR)s,s.GetLength()); //�����ż�����
	
//	s.Format("To: %s%c%c",m_pDlg->m_Receiver,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Date: Tue,04 Dec 2005 16:18:08 +800%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Subject: %s%c%c",m_pDlg->m_Title,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%s%c%c",m_pDlg->m_Letter,13,10); 
//	Send((LPCSTR)s,s.GetLength());

//		s.Format("%c%c.%c%c",13,10,13,10); 
//		Send((LPCSTR)s,s.GetLength());

		m_pDlg->GetHeader();
		state=QUIT;
		break;
	case QUIT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("QUIT%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //����QUIT����
		state=DATA;
		break;
	default:
		m_pDlg->Disp(S_RECEIVE);
		break;
	}
}

