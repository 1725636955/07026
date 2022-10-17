// Pop31.h: interface for the CPop3 class.
//mailto: zmoraa@box43.pl
// feel free to e-mail me!
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_POP31_H__1957A2DC_027A_43AF_82B6_789B397147F3__INCLUDED_)
#define AFX_POP31_H__1957A2DC_027A_43AF_82B6_789B397147F3__INCLUDED_

#include "Gniazdo.h"
#include <vector>
#include <strstream>
#include <string>

using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//enum type describing actual pop3 state
typedef enum {FIRST=0,USER,PASS,STAT,LIST,RETR,ENDRETR,DELE,GOON} STATE;

#define S_GETNUMMSGS 5 //send when user can obtain number of messages
#define S_GETSIZEMSGS 6 //as above, but size of messages
#define S_ENDRETR 7 //send when done retrieving

//simple struct that keeps message data, size, and retrieving size
typedef struct 
{
	CString text;
	int msgSize, retrSize;
} MESSAGEPROP;

class CPop3  : public CBase4Pop3
{

public:
	void WriteMsg(int i,CString name); //�����ʼ����ļ�
	//��û������ʼ���Ϣ�ֶ�: From, To, Date, Subject, Body
	CString GetMsgStuff(int i); 
	//����ż���
	CString GetMsgBody(int i);
	//�Ƿ������ź�ӷ�����ɾ���ʼ�
	void DelAfterRead(BOOL del=FALSE);
	//����ż�����
	CString GetMsgSubject(int i);
	//��������ŵ�����
	CString GetMsg(int i);
	//����ʼ�������
	int GetRetrMsgNum();
	//��������ʼ��Ĵ�С
	int GetSizeMsg();
	//��÷��������ʼ�������
	int GetNumMsg();
	//��ô���
	CString GetError();
	//�˳�������
	void Close();
	//�趨�û���������
	void SetProp(CString u, CString p);
	//��ôӷ��������������һ����Ϣ
	void GetLastMsg(CString &);
	//����ʱ��
	void OnReceive(int err);
	CPop3();
	virtual ~CPop3();

private:
	//����һ������
	void ReadLn(int index,CString src, CString &dst);
	// �ֿ�ÿ����Ϣ
	void ParseMsg();
	CString lastMsg, error;
	STATE state;
	CString user, pass;
	int numMsg, sizeMsg, retrMsg;
	vector<MESSAGEPROP> msgs; //vector for message stuff
	BOOL delAfterRead;
	int delMsg;
};

#endif // !defined(AFX_POP31_H__1957A2DC_027A_43AF_82B6_789B397147F3__INCLUDED_)
