// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tc.h"
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
CMsg::CMsg()
{
	m_strBuf=_T("");         //��ʼ��
	m_bClose=FALSE;
}

//��������
CMsg::~CMsg()
{
}

//���л�����
void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<(WORD)m_bClose;
		ar<<m_strBuf;
	} else {
		WORD wd;
		ar>>wd;
		m_bClose=(BOOL)wd;
		ar>>m_strBuf;
	}
	//m_msgList.Serialize(ar);
}

IMPLEMENT_DYNAMIC(CMsg,CObject)