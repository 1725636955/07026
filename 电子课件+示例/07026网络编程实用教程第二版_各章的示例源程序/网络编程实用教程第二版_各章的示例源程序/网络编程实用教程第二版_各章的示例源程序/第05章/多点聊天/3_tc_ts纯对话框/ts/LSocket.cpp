// LSocket.cpp: implementation of the CLSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ts.h"
#include "LSocket.h"
#include "tsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLSocket::CLSocket(CTsDlg* pDlg)
{
	m_pDlg = pDlg;   //�Գ�Ա������ֵ
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;
}

//OnAccept�¼�������
void CLSocket::OnAccept(int nErrorCode) 
{
	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();  ////�������Ի������е���Ӧ����
}

IMPLEMENT_DYNAMIC(CLSocket,CSocket)
