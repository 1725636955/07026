// mySock.cpp : implementation file
//

#include "stdafx.h"
#include "pop3.h"
#include "mySock.h"
#include  "pop3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BUFF 20000
/////////////////////////////////////////////////////////////////////////////
// mySock

//���캯������ĳЩ��Ա������ʼ��
mySock::mySock()
{
	m_pDlg = NULL;
	state=FIRST;
	error="Not connected to server\r\n";
}

mySock::~mySock()
{
	m_pDlg = NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(mySock, CAsyncSocket)
	//{{AFX_MSG_MAP(mySock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// mySock member functions
//�ӵ�����Ϣ������ʾ��һ�仰��������һЩ��ť���ӳɹ��󣬷�����������Ӧ�����
//�������յ���OnReceive��Ϣ�������ĻỰ�����У�һ��һ�������������յ�
//OnReceive��Ϣ��������������������������
void mySock::OnConnect(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CONNECT);
}

//�������˹ر����ӣ��Ż��յ�����Ϣ��
void mySock::OnClose(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CLOSE);
}

//�׽����յ�����������������ʱ��ִ�д˺���
void mySock::OnReceive(int nErrorCode) 
{
	if(nErrorCode==0) 
	{
		char buff[MAX_BUFF];            //���ջ�����
		int rec=Receive(buff,MAX_BUFF); //���շ���������������
		buff[rec]=NULL;                  //��β��ΪNULL��
		lastMsg=buff;
		AnalyzeMsg();                      //�����յ������ݣ�����ͬ�Ĵ���
	}  else  {
		error="�ڽ�������ʱ�����˴���!\r\n";
		m_pDlg->Disp(S_CLOSE);   //��ʾ��Ϣ
	}
}
//�����׽�����ĶԻ���ָ�����
void mySock::SetParent(CPop3Dlg *pDlg)
{
	m_pDlg = pDlg;
}

//��õ� i ���ż��ı�����Ϣ
CString mySock::GetMsgStuff(int i)
{
	CString ret;
CString s;
	int where=msgs[i].text.Find("From:");

s.Format("From:λ�ã�%d\r\n",where);
m_pDlg->m_Info+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);
		ret+="\r\n";
	}

	where=msgs[i].text.Find("To:");

s.Format("To:λ�ã�%d\r\n",where);
m_pDlg->m_Info+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);
		ret+="\r\n";
	}
	
	where=msgs[i].text.Find("Date:");

s.Format("Date:λ�ã�%d\r\n",where);
m_pDlg->m_Info+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);	
		ret+="\r\n";
	}
	ret+=GetMsgSubject(i);
	ret+="\r\n";
	return ret;

}

//��õ� i ���ż����ż���
CString mySock::GetMsgBody(int i)
{
	CString ret;
	int where=msgs[i].text.Find("\r\n\r\n");
	if(where!=-1) where+=4;
	else          where=0;
	ret=msgs[i].text.Right(msgs[i].text.GetLength()-where);
	ret=ret.Left(ret.GetLength()-3);
	return ret;
}

//��õ� i ���ż��ı���
CString mySock::GetMsgSubject(int i)
{
//	CString s;
//	s.Format("%s",msgs[i].text);
//	int where=s.Find("Subject:");
	
	CString ret;
	int where=msgs[i].text.Find("Subject:");
	if (where!=-1) 	ret=ReadLn(where,msgs[i].text);
	else ret.Format("�Ҳ���Subject:");
	return ret;
}

//��õ� i ���������ŵ�����
CString mySock::GetMsg(int i)
{
	return msgs[i].text;
}

//��src���У���index��ָ��λ�ÿ�ʼ��ȡ���ִ���ֱ����ĩ��"\r"Ϊֹ��
//dst��һ�����ĵ�ַ��ȡ������׷���ڸô���ԭ����֮��
CString mySock::ReadLn(int index,CString src)
{
//	CString comp;
//	CString dst;
//	comp=src[index];
//	while(comp!="\r")
//	{
//		dst+=comp;
//		comp=src[++index];
//	}
//	return dst;

	CString ret;
	CString s;
	
	ret=src.Right(src.GetLength()-index);
	int where=ret.Find("\r");
//	s.Format("�����ڵ�λ�ã�%d",where);
//	m_pDlg->m_Info+=s;
//	m_pDlg->UpdateData(FALSE);
	if(where!=-1) where+=1;
	else          where=0;
//	s.Format("�����ڵ�λ�ã�%d, Length=%d ",where,ret.GetLength());
//	m_pDlg->m_Info+=s;
//	m_pDlg->UpdateData(FALSE);
	
	ret=ret.Left(where);
	return ret;

}

 
 //�˳�������
void mySock::Close()
{
	CString str;
	str.Format("quit%c%c",13,10);
	Send((LPCSTR)str,str.GetLength());
	m_pDlg->Disp(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="ִ��mySock::Close()���Not connected to server\r\n";
}

void mySock::AnalyzeMsg()
{
	int  ix;
	CString temp1;
	CString temp2;

	CString s;
	strstream str;
	string check;
	str<<(LPCSTR)lastMsg; //���յ�����Ϣ�������ַ���������  
	str>>check;           //��ȡ���յ���Ϣ�ĵ�һ�δ���
	if(check=="-ERR")     //����д���
	{
		error="Received -ERR from server :"+lastMsg;
		Close(); //�Ͽ����ӣ�Ȼ��ر�
		return;
	}
	
	//���û�д�������ݲ�ͬ�ĻỰ�׶���Ӧ������
	switch(state) 
	{
	case FIRST: //����Ѿ����ӳɹ������ʼ����ʱ��stateΪFIRST
		msgs.clear();
		//��ʾ���ӳɹ�����������ص���Ϣ
		m_pDlg->Disp(S_RECEIVE); 
		//���� user �û��� ����
		s.Format("user %s%c%c",m_pDlg->m_strUser,13,10);
		Send((LPCSTR)s,s.GetLength()); //�����û��ʺ�
		state=USER;
		break;

	case USER:
		//��ʾ����������user�������Ӧ
		m_pDlg->Disp(S_RECEIVE);
		//���� pass ���� �����������
		s.Format("pass %s%c%c",m_pDlg->m_strPass,13,10); 
		Send((LPCSTR)s,s.GetLength()); 
		state=PASS;
		break;

	case PASS:
		//��ʾ�������� pass �������Ӧ
		m_pDlg->Disp(S_RECEIVE);
		//���� stat ����������������������
		//�ʼ�����������ռ�ռ�Ĵ�С
		s.Format("stat%c%c",13,10);
		Send((LPCSTR)s,s.GetLength());
		state=STAT; 
		break;

	case STAT:
	{
		string s1;
		str.seekg(0);  //���ַ����ĵ�ǰָ����Ϊ0
		str>>s1>>numMsg>>sizeMsg; //��������ʹ�С
		flush(str);
		m_pDlg->Disp(S_GETNUM);
		m_pDlg->Disp(S_GETSIZE);
		if(numMsg>0) //������ʼ�������RETR����ʼ���Ϣ
		{
			retrMsg=1;        //Ҫȡ��һ����
			MESSAGEPROP prop; //׼������ż��ĵط�
			prop.msgSize=0;   //��Ա�ó�ֵ
			prop.retrSize=0;
			prop.text="";
			msgs.push_back(prop); //ѹ��������
			s.Format("retr 1%c%c",13,10);
			Send((LPCSTR)s,s.GetLength()); 
			state=RETR;
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
		//��ʾȡ�������ż��ı�

s.Format("numMsg= %d  retrMsg =%d",numMsg,retrMsg);	
m_pDlg->m_Info+=s;
s.Format("�ż���%d: ,�ż���С%d, �ż����ݣ� %s   �ż�����%c%c",
		 retrMsg-1,lastMsg.GetLength(),lastMsg,13,10);
m_pDlg->m_Info+=s;
m_pDlg->UpdateData(FALSE);		
				
		
				




		m_pDlg->Disp(S_RECEIVE);
		//һ���ŵ����ݿ��ܶ�β��ܽ��ܻ��������Ƕ���һ���ţ���һ��
		//���յ����ݵ�ʱ�򣬶�Ӧ�����ṹ��msgSize��Ա����Ϊ0
		//if(msgs[retrMsg-1].msgSize==0) 
		//{
//			string temp;
//			str.seekg(0);
			//�����ż��Ĵ�С��ŵ���Ա������
//			str>>temp>>msgs[retrMsg-1].msgSize; 
//		}
		//ix=lastMsg.Find("\r\n.\r\n");
		//if (ix == -1)
		//{
		//	msgs[retrMsg-1].text+=lastMsg;
		//	msgs[retrMsg-1].retrSize+=lastMsg.GetLength();
		//} else  {
		//	temp1=lastMsg.Left(ix+5);
		//	temp2=lastMsg.Right(lastMsg.GetLength()-ix-5);
		//	msgs[retrMsg-1].text+=temp1;
		//	msgs[retrMsg-1].retrSize +=temp1.GetLength();
		//}


		//������׷�ӱ��浽text��Ա������
		msgs[retrMsg-1].text+=lastMsg; 
		//�����ݴ�С�ۼӵ�retrSize��Ա�����У������Ѿ�ȡ����������
		msgs[retrMsg-1].retrSize+=lastMsg.GetLength();
		//�ж��Ƿ���������ŵ���������
		//if(msgs[retrMsg-1].retrSize>=msgs[retrMsg-1].msgSize)
		//{  //����Ƿ��������ʼ�
	
		ix=lastMsg.Find("\r\n.\r\n");
		if (ix != -1)	//�ҵ�������ŵĽ�β
		{	
			//����Ƿ��������ʼ�
			if(retrMsg<numMsg) //������У����������retr����
			{
				MESSAGEPROP prop;
				prop.msgSize=0;
				prop.retrSize=0;
				prop.text="";
				msgs.push_back(prop);
				retrMsg++;
				//��retr����ȡ��һ����
				s.Format("retr %d%c%c",retrMsg,13,10);
				Send((LPCSTR)s,s.GetLength());
			}  else	{
				//���ȫ���ż�������ϣ��ж��Ƿ�Ҫɾ��
				
				if(m_pDlg->m_bolDel && numMsg>0) 
				{
					state=DELE;
					delMsg=1;
					s.Format("dele %d%c%c",delMsg,13,10);
					Send((LPCSTR)s,s.GetLength());
				}  else {                      //�����˳�
					state=ENDRETR;
					m_pDlg->Disp(S_ENDRETR);
					error="�ż�������,��ɾ�ʼ����Ự����\r\n";
					s.Format("quit%c%c",13,10);
					Send((LPCSTR)s,s.GetLength());
					Close();

					for(int i=0;i<retrMsg;i++)
					{
						s.Format("%d:  %s",i,GetMsgSubject(i));
			//m_pDlg->m_Info+=s;

						m_pDlg->m_ctrList.AddString(s);
				//		m_pDlg->m_ctrList.AddString((LPCSTR)GetMsgSubject(i));
					}
			//m_pDlg->UpdateData(FALSE);
					m_pDlg->m_ctrList.SetCurSel(0);
				}
			}
		}  //DEBUG 
		//}
	}
	break;

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
			m_pDlg->Disp(S_ENDRETR);
			state=GOON;
			error="Deleted all messages\r\n";
			s.Format("quit%c%c",13,10);
			Send((LPCSTR)s,s.GetLength());
			Close();
		}
	}
	break;
	
	case GOON:
	
	default:
		m_pDlg->Disp(S_RECEIVE);
		break;
	}
}