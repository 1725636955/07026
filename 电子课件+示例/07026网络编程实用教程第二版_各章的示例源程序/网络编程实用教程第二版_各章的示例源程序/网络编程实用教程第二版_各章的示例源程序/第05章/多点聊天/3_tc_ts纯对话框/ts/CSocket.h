// CSocket.h: interface for the CCSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSOCKET_H__INCLUDED_)
#define AFX_CSOCKET_H__INCLUDED_

class  CTsDlg;
class  CMsg;

//���ڽ������Ӻʹ��ͽ�����Ϣ�Ŀͻ��׽����ඨ��
class CCSocket : public CSocket  
{
	DECLARE_DYNAMIC(CCSocket);

//Construction
public:
	CCSocket(CTsDlg* pDlg);   //���캯��
	virtual ~CCSocket();      //��������

//Attributes
public:
	CTsDlg* m_pDlg;         //���Ի�����ָ�����
	CSocketFile* m_pFile;   //CSocketFile�����ָ�����
	CArchive* m_pArchiveIn; //���������CArchive�����ָ�����
	CArchive* m_pArchiveOut;//���������CArchive�����ָ�����

//Operations
public:
	void Initialize();               //��ʼ��
	void SendMessage(CMsg* pMsg);    //������Ϣ
	void ReceiveMessage(CMsg* pMsg); //������Ϣ

//Overridable callbacks
//�����صĻص����������׽����յ�����ʱ���Զ����ô˺���
protected:
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)
