// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//消息类的定义
class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg);

public:
	CMsg();            //构造函数
	virtual ~CMsg();   //析构函数
	virtual void Serialize(CArchive& ar);  //序列化函数

//Attributes
public:
	CString m_strBuf;       //字符串成员
	BOOL m_bClose;          //是否关闭状态
};

#endif // !defined(AFX_MSG_H__INCLUDED_)
