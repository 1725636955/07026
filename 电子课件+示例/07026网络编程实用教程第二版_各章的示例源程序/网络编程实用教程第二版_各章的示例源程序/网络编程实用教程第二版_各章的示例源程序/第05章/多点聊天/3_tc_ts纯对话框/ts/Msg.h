// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//��Ϣ�ඨ��
class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg);

//Construction
public:
	CMsg();
	virtual ~CMsg();

//Attributes
public:
	CString m_strText;      //�ַ�����Ա
	BOOL m_bClose;          //�Ƿ�ر�״̬

//Implementation
public:
	virtual void Serialize(CArchive& ar);   //���л�����
};

#endif // !defined(AFX_MSG_H__INCLUDED_)
