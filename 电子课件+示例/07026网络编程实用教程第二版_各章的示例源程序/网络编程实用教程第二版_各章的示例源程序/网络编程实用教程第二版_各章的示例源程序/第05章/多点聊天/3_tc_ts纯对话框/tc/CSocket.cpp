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

//构造函数
CCSocket::CCSocket(CTcDlg* pDlg)
{
	m_pDlg = pDlg;       //成员变量赋值
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
}

//事件处理函数，当套接字收到FD_READ消息时，执行此函数
void CCSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);
	//调用CTcDlg类的相应函数处理
	if (nErrorCode == 0) m_pDlg->OnReceive();
}