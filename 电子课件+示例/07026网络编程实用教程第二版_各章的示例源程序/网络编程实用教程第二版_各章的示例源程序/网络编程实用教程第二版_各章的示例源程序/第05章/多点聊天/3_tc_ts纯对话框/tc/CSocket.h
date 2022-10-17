// CSocket.h: interface for the CCSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSOCKET_H__INCLUDED_)
#define AFX_CSOCKET_H__INCLUDED_

class CTcDlg;

class CCSocket : public CSocket  
{
	DECLARE_DYNAMIC(CCSocket);


//Construction
public:
	CCSocket(CTcDlg* pDlg);  //���캯��
	virtual ~CCSocket();     //��������

// Attributes
public:
	CTcDlg* m_pDlg;          //��Ա����

//Implementation
protected:
	virtual void OnReceive(int nErrorCode);  //�¼�������
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)
