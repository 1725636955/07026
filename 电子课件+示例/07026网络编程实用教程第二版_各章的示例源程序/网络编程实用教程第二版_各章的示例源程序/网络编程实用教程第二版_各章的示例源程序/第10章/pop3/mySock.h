#if !defined(AFX_MYSOCK_H__0444E4E0_0C28_11DA_BB87_AF2B44E1925E__INCLUDED_)
#define AFX_MYSOCK_H__0444E4E0_0C28_11DA_BB87_AF2B44E1925E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mySock.h : header file
//
#include <vector>
#include <strstream>
#include <string>

using namespace std;

class  CPop3Dlg;

/////////////////////////////////////////////////////////////////////////////
// mySock command target

//��ʾ��ͬ��Ϣ�ı�־
#define S_CLOSE   1  //���ر�����ʱ����ʾ�ر���Ϣ
#define S_CONNECT 2  //�����ӳɹ�ʱ����ʾ������Ϣ
#define S_RECEIVE 3  //���յ���������������Ϣʱ����ʾ����Ϣ
#define S_GETNUM  4 //�������ż�������Ϻ���ʾ�����е��ż�����
#define S_GETSIZE 5 //�������ż�������Ϻ���ʾ�����е��ż��ܴ�С
#define S_ENDRETR 6 //�������ż�������Ϻ���ʾ�����Ϣ

//����pop3�Ự״̬��ö������
typedef enum {FIRST=0,USER,PASS,STAT,LIST,RETR,ENDRETR,DELE,GOON} STATE;

//��������һ���ż���Ϣ�Ľṹ
typedef struct 
{
	CString text;  //�洢�ż����ı�
	int msgSize;   //�ż��Ĵ�С
	int	retrSize;  //�ż�ʵ�����صĴ�С�������ع����ж�̬�仯
} MESSAGEPROP;

//�Լ����׽�����
class mySock : public CAsyncSocket
{
// Attributes
public:
	CString lastMsg;
	CString error;
	int numMsg, sizeMsg, retrMsg;
	vector<MESSAGEPROP> msgs; //ʢ���ż���Ϣ������

// Operations
public:
	//��û������ʼ���ͷ�ֶ�: From, To, Date, Subject, Body
	CString GetMsgStuff(int i); 
	CString GetMsgBody(int i);     //����ż���
	CString GetMsgSubject(int i);  //����ż�����
	CString GetMsg(int i);         //��������ŵ�����
	CString ReadLn(int index,CString src);

	void Close();            //�˳�������
	void SetParent(CPop3Dlg *  pDlg);
	mySock();
	virtual ~mySock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mySock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(mySock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	void AnalyzeMsg();
	CPop3Dlg* m_pDlg;
	STATE state;
	int delMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCK_H__0444E4E0_0C28_11DA_BB87_AF2B44E1925E__INCLUDED_)
