// CSocket.cpp: implementation of the CCSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ts.h"
#include "CSocket.h"
#include "tsDlg.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//���캯��
CCSocket::CCSocket(CTsDlg* pDlg)
{
	m_pDlg = pDlg;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

//��������
CCSocket::~CCSocket()
{
	m_pDlg = NULL;
	if (m_pArchiveOut != NULL) delete m_pArchiveOut;
	if (m_pArchiveIn != NULL) delete m_pArchiveIn;
	if (m_pFile != NULL) delete m_pFile;
}

//��ʼ��
void CCSocket::Initialize()
{
	//��������׽�����Ӧ��CSocketFile����
	m_pFile=new CSocketFile(this,TRUE);
	//��������׽�����Ӧ��CArchive����
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
}

//������Ϣ
void CCSocket::SendMessage(CMsg* pMsg)
{
	if (m_pArchiveOut != NULL)
	{
		//������Ϣ������л�������������Ϣ
		pMsg->Serialize(*m_pArchiveOut);
		//��CArchive�����е�����ǿ����д��CSocketFile�ļ���
		m_pArchiveOut->Flush();	
	}
}

//������Ϣ
void CCSocket::ReceiveMessage(CMsg* pMsg)
{
	//������Ϣ������л�������������Ϣ
	pMsg->Serialize(*m_pArchiveIn);
}

//OnReceive�¼������������׽����յ�����ʱ���������¼�
void CCSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);
	//�������Ի������е���Ӧ����������
	m_pDlg->OnReceive(this);
}

IMPLEMENT_DYNAMIC(CCSocket,CSocket)
