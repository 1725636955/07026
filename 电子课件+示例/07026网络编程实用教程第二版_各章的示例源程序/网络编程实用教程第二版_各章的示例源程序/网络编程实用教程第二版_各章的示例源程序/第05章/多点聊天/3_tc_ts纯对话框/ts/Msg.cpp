// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ts.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_strText = _T("");   //≥ı ºªØ
	m_bClose=FALSE;
}

CMsg::~CMsg()
{
}

void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<(WORD)m_bClose;
		ar << m_strText;
	} else {
		WORD wd;
		ar>>wd;
		m_bClose=(BOOL)wd;
		ar >> m_strText;
	}
}

IMPLEMENT_DYNAMIC(CMsg,CObject)

