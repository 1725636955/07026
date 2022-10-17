// smtpDlg.cpp : implementation file
//

//#include "rpcdce.h"
#include "stdafx.h"
#include "smtp.h"
#include "smtpDlg.h"
#include "mySock.h"
#include "Base64.h"

#define SMTP_MAXLINE  76

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmtpDlg dialog

CSmtpDlg::CSmtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmtpDlg)
	m_Addr = _T("");
	m_Attach = _T("");
	m_BCC = _T("");
	m_CC = _T("");
	m_Letter = _T("");
	m_Name = _T("");
	m_Pass = _T("");
	m_Port = 0;
	m_Receiver = _T("");
	m_Server = _T("");
	m_Title = _T("");
	m_User = _T("");
	m_Info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmtpDlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Addr);
	DDX_Text(pDX, IDC_EDIT_ATTACH, m_Attach);
	DDX_Text(pDX, IDC_EDIT_BCC, m_BCC);
	DDX_Text(pDX, IDC_EDIT_CC, m_CC);
	DDX_Text(pDX, IDC_EDIT_LETTER, m_Letter);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_PASS, m_Pass);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_Receiver);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_Server);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT_USER, m_User);
	DDX_Text(pDX, IDC_RICH_LIST, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSmtpDlg, CDialog)
	//{{AFX_MSG_MAP(CSmtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmtpDlg message handlers

BOOL CSmtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Name = _T("wang");               //������
	m_Addr = _T("mu_l@163.com");     //���ŵ�ַ
	m_Server = _T("smtp.163.com");   //smtp������
	m_Port = 25;                     //smtp�ı����˿�
	m_User = _T("mu_l");             //�û���
	m_Pass = _T("491015");           //����

	m_Receiver = _T("mu_lm@sina.com"); //�����˵�ַ
	m_Title = _T("");            //����
	m_CC = _T("");                   //����
	m_BCC = _T("");                  //����
	m_Letter = _T("");               //�ż�����
	m_Attach = _T("");               //����
	UpdateData(FALSE);               //�����û�����

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//���û���������͡���ťʱ��ִ�д˺���
void CSmtpDlg::OnOK() 
{
	//�趨smtp��ı�����ʹָ֮�򱾶Ի����Ա㴫����Ϣ
	smtpSocket.SetParent(this); 
	UpdateData(TRUE);           //ȡ���û��ڶԻ��������������
	smtpSocket.Create();        //�����׽��ֶ���ĵײ��׽���
	smtpSocket.Connect((LPCSTR)m_Server,m_Port); //����pop3������
	//�б�����
	//while (m_listInfo.GetCount()!=0)
     //          m_listInfo.DeleteString(0);
	UpdateData(FALSE);          //�����û�����
}

//���û�������������ť��Ѱ�Ҹ���ʱ��ִ�д˺���
void CSmtpDlg::OnBtnView() 
{
	UpdateData(TRUE); 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) 
	{
		CString sNewFile = dlg.GetPathName();
		if (m_Attach.GetLength())
		{
			m_Attach += _T(", ");
			m_Attach += sNewFile;
		}
		else
			m_Attach = sNewFile;
		UpdateData(FALSE);
	}
	LPSTR pszBody = NULL;
	int nBodySize = 0;
	if (!GetBody(pszBody, nBodySize))
	{
		TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
	}
	CString s;
	s = pszBody;
	m_Info += s;
	UpdateData(FALSE);

//	CString s;
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	coder.Encode(m_User);
//	s.Format(_T("%s\r\n"), coder.EncodedMessage());
//	m_listInfo.AddString(m_User);	
//	m_listInfo.AddString(s);
//	AfxMessageBox(s);

//	coder.Encode(m_Pass);
//	s.Format(_T("%s\r\n"), coder.EncodedMessage());
//	m_listInfo.AddString(m_Pass);	
//	m_listInfo.AddString(s);
//	AfxMessageBox(s);
}

//���ݲ�ͬ����������û���ʾ��ͬ����Ϣ
void CSmtpDlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //�����ӵ�����������ʾ��Ϣ
		s = "�Ѿ����ӵ�"+m_Server+"������\r\n";
		m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //�յ�����������������,��ʾ������
		m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break; 
	case S_CLOSE: //��ʾ�ر����ӵ���Ϣ
		m_Info += smtpSocket.error;
//		m_listInfo.AddString(smtpSocket.error);
		s = "�����Ѿ��ر�\r\n";
		m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //�����û�����
}

void CSmtpDlg::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//���� "Date:" ����������
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate +="+0800 (CST)";

	CString sBuf(sReply);
	if (m_Attach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//��� From �� to �ֶ�
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // �����ˣ������˱���
	//To: Li@163.com 

	coder.Encode(m_Addr);
	sReply.Format(_T("From: %s\r\n"), m_Addr);
//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;
	
	sReply.Format(_T("To: %s\r\n"),m_Receiver);
	sBuf += sReply;

	//��� Date�ֶ�
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // ���ŵ�����ʱ��
	sReply.Format(_T("Date: %s\r\n"),sDate);
	sBuf += sReply;

	//��� subject�ֶ�
	//Subject: =?GB2312?B?XXXXXX=?= // ���⣬�����˱���
	coder.Encode(m_Title);
	sReply.Format(_T("Subject: %s\r\n"),m_Title);
//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//����У���� Cc �ֶ�
	if (m_CC.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_CC);
		sBuf += sReply;
	}

	//����У����Bcc �ֶ�
	if (m_BCC.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_BCC);
		sBuf += sReply;
	}

	//�����Ҫ����� Mime �ֶ�
	//MIME-Version: 1.0               // MIME�汾
	//Content-type: multipart/mixed;  // ���������Ƕಿ��/�����
	//boundary = "NextPart_000_00A"  // ָ��һ���߽������ַ���
	
	sepa= _T("Boundary-=_HfNFaIwtPvzJDUQrvChaEKIMklNx");
	if (m_Attach.GetLength())
	{
//		sReply.Format(_T("MIME-Version: 1.0\r\n"));
//		sBuf += sReply;
		sReply.Format("Content-Type:Multipart/mixed;boundary=%s\r\n",sepa);
		sBuf += sReply;
		sBuf += _T("\r\n");
	} else {
		sBuf += _T("\r\n");
		sReply.Format(_T(" %s\r\n"), m_Letter);
		sBuf += sReply;
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
	}
	smtpSocket.Send((LPCSTR)sBuf,sBuf.GetLength());
	m_Info+=sBuf;

	if (m_Attach.GetLength())
	{
		sReply.Format(_T("--%s\r\n"),sepa);
		sBuf = sReply;	
		
		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		coder.Encode(m_Letter);
		sReply.Format(_T("%s\r\n"),coder.EncodedMessage());
		sBuf += sReply;
		
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		//add Letter	
		LPSTR pszBody = NULL;
		int nBodySize = 0;
		if (!GetBody(pszBody, nBodySize))
		{
			TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
		}
		sReply = pszBody;
		sBuf += sReply;
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;
		
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
		smtpSocket.Send((LPCSTR)sBuf,sBuf.GetLength());
		m_Info+=sBuf;
	}
	UpdateData(FALSE);
}

BOOL CSmtpDlg::GetBody(LPSTR& pszBody, int& nBodySize)
{
	BOOL bSuccess = FALSE;

	//�򿪸����ļ�
	CFile infile;
	if (infile.Open(m_Attach, CFile::modeRead | CFile::shareDenyWrite))
	{
		DWORD dwSize = infile.GetLength();
		if (dwSize)
		{
			//��������
			BYTE* pszIn = new BYTE[dwSize];
			try
			{
				infile.Read(pszIn, dwSize);
				bSuccess = TRUE;
			}
			catch(CFileException* pEx)
			{
				bSuccess = FALSE;
				pEx->Delete();
			}

			if (bSuccess)
			{
				coder.Encode(pszIn, dwSize); //����
				delete [] pszIn;               //ɾ�������뻺����
				infile.Close();                //�ر������ļ�

				//�γɱ����ķ�������
				LPSTR pszEncoded = coder.EncodedMessage();
				int nEncodedSize = coder.EncodedMessageSize();
				nBodySize = nEncodedSize + (((nEncodedSize/76)+1)*2) + 1;
				pszBody = new char[nBodySize];
				--nBodySize; 

				int nInPos = 0;
				int nOutPos = 0;
				while (nInPos < nEncodedSize)
				{
					int nThisLineSize = min(nEncodedSize - nInPos, SMTP_MAXLINE);
					CopyMemory(&pszBody[nOutPos], &pszEncoded[nInPos], nThisLineSize);
					nOutPos += nThisLineSize;
					CopyMemory(&pszBody[nOutPos], "\r\n", 2);
					nOutPos += 2;
					nInPos += nThisLineSize;
				}
				pszBody[nOutPos] = '\0'; //�Կ��ַ�������
			}
		}  else  {
			bSuccess = TRUE;
			pszBody = NULL;
			nBodySize = 0;
		}
	}  else
		TRACE(_T("No bodypart body text or filename specified!\n"));

	return bSuccess;
}

 
