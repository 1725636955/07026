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
	CCSocket(CTcDlg* pDlg);  //构造函数
	virtual ~CCSocket();     //析构函数

// Attributes
public:
	CTcDlg* m_pDlg;          //成员变量

//Implementation
protected:
	virtual void OnReceive(int nErrorCode);  //事件处理函数
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)
