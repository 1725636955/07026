// Pop31.cpp: implementation of the CPop3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Gniazdo.h"
#include "pop3Dlg.h"
#include "Pop31.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUFF 20000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPop3::CPop3()
{
	state=FIRST;
	error="Not connected to server\r\n";
	delAfterRead=FALSE;
}

CPop3::~CPop3()
{
	
}

void CPop3::OnReceive(int err)
{
	if(err==0) //if no error
	{
		char buff[MAX_BUFF];
		int rec=Receive(buff,MAX_BUFF); //receive data
		buff[rec]=NULL;
		lastMsg=buff;
		ParseMsg(); //parse data
	}
	else
	{
		error="Error while receiving!\r\n";
		((DLG)m_pWnd)->Dispatch(S_CLOSE);
		
	}
}

void CPop3::GetLastMsg(CString &s)
{
	s=lastMsg;
}

void CPop3::SetProp(CString u, CString p)
{
	user=u;
	pass=p;
}

void CPop3::ParseMsg()
{
	CString s;
	strstream str;
	string check;
	str<<(LPCSTR)lastMsg;
	str>>check;
	if(check=="-ERR") //����д���
	{
		error="Received -ERR from server :"+lastMsg;
		Close(); //�Ͽ�Ȼ��ر�
		return;
	}
	switch(state) //���û�д�������ݲ�ͬ����Ӧ������
	{
	case FIRST: //����Ѿ����ӳɹ������ʼ����ʱ��stateΪFIRST
		msgs.clear();
		((DLG)m_pWnd)->Dispatch(S_RECEIVE); //������Ϣ������
		s.Format("user %s%c%c",user,13,10);
		Send((LPCSTR)s,s.GetLength()); //�����û��ʺ�
		state=USER;
		break;
		
	case USER:
		((DLG)m_pWnd)->Dispatch(S_RECEIVE);
		s.Format("pass %s%c%c",pass,13,10); 
		Send((LPCSTR)s,s.GetLength()); //��������
		state=PASS;
		break;
		
	case PASS:
		((DLG)m_pWnd)->Dispatch(S_RECEIVE);
		s.Format("stat%c%c",13,10);
		Send((LPCSTR)s,s.GetLength()); //����stat����
		state=STAT; 
		break;
		
	case STAT:
		{
			string s1;
			str.seekg(0);
			str>>s1>>numMsg>>sizeMsg; //��������ʹ�Ц
			flush(str);
			((DLG)m_pWnd)->Dispatch(S_GETNUMMSGS);
			((DLG)m_pWnd)->Dispatch(S_GETSIZEMSGS);
			if(numMsg>0) //������ʼ�������RETR����ʼ���Ϣ
			{
				state=RETR;
				s.Format("retr 1%c%c",13,10);
				retrMsg=1;
				MESSAGEPROP prop;
				prop.msgSize=0;
				prop.retrSize=0;
				prop.text="";
				msgs.push_back(prop); 
				Send((LPCSTR)s,s.GetLength()); 
				
			}
			else //���û���ʼ�����Ͽ�
			{
				error="No new messages\r\n";
				Close();
			}
		}
		break;
		
	case RETR:
		{
((DLG)m_pWnd)->Dispatch(S_RECEIVE);	
			if(msgs[retrMsg-1].msgSize==0) //�����һ�ν��յ�����
			{
				string temp;
				str.seekg(0);
				str>>temp>>msgs[retrMsg-1].msgSize; //�õ���Ϣ��С
			}
			msgs[retrMsg-1].text+=lastMsg; //��������
			msgs[retrMsg-1].retrSize+=lastMsg.GetLength(); //�������ݴ�С
			if(msgs[retrMsg-1].retrSize>=msgs[retrMsg-1].msgSize) //�ж��Ƿ�����������
			{	//����Ƿ��������ʼ�
				if(retrMsg<numMsg) //������У����������retr����
				{
					MESSAGEPROP prop;
					prop.msgSize=0;
					prop.retrSize=0;
					prop.text="";
					msgs.push_back(prop);
					retrMsg++;
					s.Format("retr %d%c%c",retrMsg,13,10); //request another
					Send((LPCSTR)s,s.GetLength());
				}
				else
				{
					//���ȫ��������ϣ��ж��Ƿ�Ҫɾ��
					if(delAfterRead && numMsg>0) 
					{
						state=DELE;
						delMsg=1;
						s.Format("dele %d%c%c",delMsg,13,10);
						Send((LPCSTR)s,s.GetLength());
					}
					else //�����˳�
					{
						state=ENDRETR;
						((DLG)m_pWnd)->Dispatch(S_ENDRETR);
						error="Session ended\r\n";
						s.Format("quit%c%c",13,10);
						Send((LPCSTR)s,s.GetLength());
						Close();
					}
				}
			}
			
		}break;
	case DELE:
		{
			//ɾ��ʣ���ʼ�
			if(delMsg<numMsg)
			{
				delMsg++;
				s.Format("dele %d%c%c",delMsg,13,10);
				Send((LPCSTR)s,s.GetLength());
			}
			else //����Ѿ�ɾ�����
			{
				((DLG)m_pWnd)->Dispatch(S_ENDRETR);
				state=GOON;
				error="Deleted all messages\r\n";
				s.Format("quit%c%c",13,10);
				Send((LPCSTR)s,s.GetLength());
				Close();
			}
		}
		break;
	case GOON: //Ĭ��
	default:
		((DLG)m_pWnd)->Dispatch(S_RECEIVE);
		break;
	}
}


void CPop3::Close()
{
	CString str;
	str.Format("quit%c%c",13,10);
	Send((LPCSTR)str,str.GetLength());
	((DLG)m_pWnd)->Dispatch(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="Not connected to server\r\n";
}

CString CPop3::GetError()
{
	return error;
}

int CPop3::GetNumMsg()
{
	return numMsg;
}

int CPop3::GetSizeMsg()
{
	return sizeMsg;
}

int CPop3::GetRetrMsgNum()
{
	return msgs.size();
}

CString CPop3::GetMsg(int i)
{
	return msgs[i].text;
}

CString CPop3::GetMsgSubject(int i)
{
	int where=msgs[i].text.Find("Subject:");
	CString ret;
	if (where!=-1)
	ReadLn(where,msgs[i].text,ret);
	return ret;
}

void CPop3::DelAfterRead(BOOL del)
{
	delAfterRead=del;
}

CString CPop3::GetMsgBody(int i)
{
	CString ret;
	int where=msgs[i].text.Find("\r\n\r\n");
	if(where!=-1)
		where+=4;
	else where=0;
	ret=msgs[i].text.Right(msgs[i].text.GetLength()-where);
	ret=ret.Left(ret.GetLength()-3);
	return ret;

}

CString CPop3::GetMsgStuff(int i)
{
	CString ret;
	int where=msgs[i].text.Find("From:");
	ReadLn(where,msgs[i].text,ret);
	ret+="\r\n";
	
	where=msgs[i].text.Find("To:");
	if (where!=-1)
	{
		ReadLn(where,msgs[i].text,ret);
		ret+="\r\n";
	}
	where=msgs[i].text.Find("Date:");
	if (where!=-1)
	{
		ReadLn(where,msgs[i].text,ret);	
		ret+="\r\n";
	}
	ret+=GetMsgSubject(i);
	ret+="\r\n";
	return ret;
}

void CPop3::ReadLn(int index,CString src, CString &dst)
{
	CString comp;
	comp=src[index];
	while(comp!="\r")
	{
		dst+=comp;
		comp=src[++index];
	}
}

void CPop3::WriteMsg(int i, CString name)
{
CStdioFile file(name,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
file.Write((LPCSTR)msgs[i].text,msgs[i].text.GetLength());
file.Close();
}
