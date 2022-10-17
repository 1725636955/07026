// LSocket.h: interface for the CLSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSOCKET_H__INCLUDED_)
#define AFX_LSOCKET_H__INCLUDED_

class  CTsDlg;

//ר���ڼ����ͻ�����������������׽����ඨ��
class CLSocket : public CSocket  
{
	DECLARE_DYNAMIC(CLSocket);

//Construction
public:
	CLSocket(CTsDlg* pDlg);
	virtual ~CLSocket();

// Attributes
public:
	CTsDlg* m_pDlg;   //��Ա����

// Overridable Callbacks
//�����صĻص����������׽����յ���������ʱ���Զ����ô˺���
protected:
	virtual void OnAccept(int nErrorCode);
};

#endif // !defined(AFX_LSOCKET_H__INCLUDED_)
