// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//��Ϣ��Ķ���
class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg);

public:
	CMsg();            //���캯��
	virtual ~CMsg();   //��������
	virtual void Serialize(CArchive& ar);  //���л�����

//Attributes
public:
	CString m_strBuf;       //�ַ�����Ա
	BOOL m_bClose;          //�Ƿ�ر�״̬
};

#endif // !defined(AFX_MSG_H__INCLUDED_)
