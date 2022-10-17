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
	m_pDlg = pDlg;   //对成员变量赋值
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;
}

//OnAccept事件处理函数
void CLSocket::OnAccept(int nErrorCode) 
{
	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();  ////调用主对话框类中的相应函数
}

IMPLEMENT_DYNAMIC(CLSocket,CSocket)
