// CSocket.cpp: implementation of the CCSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tc.h"
#include "CSocket.h"
#include "tcDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CCSocket,CSocket)

//���캯��
CCSocket::CCSocket(CTcDlg* pDlg)
{
	m_pDlg = pDlg;       //��Ա������ֵ
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
}

//�¼������������׽����յ�FD_READ��Ϣʱ��ִ�д˺���
void CCSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);
	//����CTcDlg�����Ӧ��������
	if (nErrorCode == 0) m_pDlg->OnReceive();
}