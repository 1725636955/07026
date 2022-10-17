// SMTPwithAttachDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMTPwithAttach.h"
#include "SMTPwithAttachDlg.h"
#include "smtp.h"

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
// CSMTPwithAttachDlg dialog

CSMTPwithAttachDlg::CSMTPwithAttachDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMTPwithAttachDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSMTPwithAttachDlg)
	m_Address = _T("");
	m_BCC = _T("");
	m_CC = _T("");
	m_Letter = _T("");
	m_Name = _T("");
	m_PWD = _T("");
	m_Receiver = _T("");
	m_Server = _T("");
	m_Title = _T("");
	m_UID = _T("");
	m_IP = _T("");
	m_Port = 0;
	m_Attachment = _T("");
	m_test = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_Authenticate = CSMTPConnection::NoLoginMethod;
	m_Authenticate_1=CSMTPConnection::NoLoginMethod;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMTPwithAttachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

    CBAddStringAndData(this, IDC_AUTHENTICATE, _T("None"), CSMTPConnection::NoLoginMethod);
    CBAddStringAndData(this, IDC_AUTHENTICATE, _T("AUTH LOGIN"), CSMTPConnection::AuthLoginMethod);
    CBAddStringAndData(this, IDC_AUTHENTICATE, _T("LOGIN PLAIN"), CSMTPConnection::LoginPlainMethod);
	DDX_CBData(pDX, IDC_AUTHENTICATE, m_Authenticate_1);



	//{{AFX_DATA_MAP(CSMTPwithAttachDlg)
	DDX_Control(pDX, IDC_AUTHENTICATE, m_ctrlAuthenticate);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Address);
	DDX_Text(pDX, IDC_EDIT_BCC, m_BCC);
	DDX_Text(pDX, IDC_EDIT_CC, m_CC);
	DDX_Text(pDX, IDC_EDIT_LETTER, m_Letter);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_PWD, m_PWD);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_Receiver);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_Server);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT_UID, m_UID);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_Attachment, m_Attachment);
	DDX_Text(pDX, IDC_EDIT3, m_test);
	//}}AFX_DATA_MAP
	//DDX_CBData(pDX, IDC_AUTHENTICATE, m_Authenticate);

}

BEGIN_MESSAGE_MAP(CSMTPwithAttachDlg, CDialog)
	//{{AFX_MSG_MAP(CSMTPwithAttachDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BrowerFile, OnBrowerFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMTPwithAttachDlg message handlers

BOOL CSMTPwithAttachDlg::OnInitDialog()
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
	//
	//���г�ʼ����һЩ���ݲ������������
	SetPara();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMTPwithAttachDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSMTPwithAttachDlg::OnPaint() 
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

HCURSOR CSMTPwithAttachDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//��ok��ť�ĳɷ��Ͱ�ť��Ȼ���;����ż�
void CSMTPwithAttachDlg::OnOK() 
{
	// TODO: Add extra validation here

	CWaitCursor wc;
	UpdateData(true);
	//�����ж�SMTP�������Ƿ�Ϊ�գ����Ϊ�գ����趨ΪĬ��ֵ
	if (m_Server.IsEmpty())
	{
		m_Server="smtp.163.com";
		UpdateData(false);
	}
	else
	{

		//����SMTP��Ϣ�壬ͨ������ʵ��
		CSMTPMessage* pMessage = CreateMessage();
		//���ӵ�������
		CSMTPConnection connection;
		//�ж��Ƿ����Զ���������
		//if (m_bAutoDial)
		//connection.ConnectToInternet();
		UpdateData(true);
		m_IP=_T("");
		BOOL bConnect = connection.Connect(m_Server, m_Authenticate, m_UID, m_PWD, m_Port, m_IP);
		//������Ӳ��ɹ�
		if (!bConnect) 
		{
			CString sMsg;
			sMsg.Format(_T("�������ӵ�������!, Error:%d"), GetLastError());
			  AfxMessageBox(sMsg, MB_ICONSTOP);
		}
		else 
		{
			//���;�����Ϣ
			if (!connection.SendMessage(*pMessage)) 
			{
				CString sMsg;
				sMsg.Format(_T("������Ϣʧ��!\nResponse:%s"), connection.GetLastCommandResponse());
				AfxMessageBox(sMsg, MB_ICONSTOP);
			}
		}

        //ɾ����Ϣ��
        delete pMessage;
	}
}


//Ϊ�˵��Է��㣬�������е�ʱ���Զ�����һЩ����
void CSMTPwithAttachDlg::SetPara ()
{
	UpdateData(true);
	//��ʼ���г�ʼ����Ϊ�˷��������ԣ��ڳ������к��Զ�����
	//
	m_Receiver="busywxp@163.com";
	m_CC="busywxp@sohu.com";
	m_Address="busywxp@163.com";
	m_Server="smtp.163.com";
	m_Port=25;
	m_Name="����";
	m_UID="busywxp";
	m_IP="ANY_IP_ADDRESS";
	m_bMime=false;
	m_bHTML=false;
	m_sEncodingFriendly="Chinese Simplified (GB2312)";
    m_sEncodingCharset="gb2312";

	//m_
	UpdateData(false);
	
}

//����һ���½�������
CSMTPMessage* CSMTPwithAttachDlg::CreateMessage()
{
	//������Ϣ��
	CSMTPMessage* pMessage = new CSMTPMessage;
	CSMTPBodyPart attachment;

  //�趨mine��־mime
  pMessage->SetMime(m_bMime);

  //�趨��Ϣ�͸����ı��뷽ʽ
  pMessage->SetCharset(m_sEncodingCharset);
  attachment.SetCharset(m_sEncodingCharset);

  //��ø��ֻ�����Ϣ
	pMessage->AddMultipleRecipients(m_Receiver, CSMTPMessage::TO);
	if (!m_CC.IsEmpty()) 
		pMessage->AddMultipleRecipients(m_CC, CSMTPMessage::CC);
	if (!m_BCC.IsEmpty()) 
		pMessage->AddMultipleRecipients(m_BCC, CSMTPMessage::BCC);
	if (!m_Title.IsEmpty()) 
		pMessage->m_sSubject = m_Title;
	if (!m_Letter.IsEmpty())
	{
	//��ʾ�Ƿ���HTML�ĸ�ʽ�����ʼ�
    if (m_bHTML)
		pMessage->AddHTMLBody(m_Letter, _T(""));
    else
		pMessage->AddTextBody(m_Letter);
	}

    //���Ӹ��������Ҫ���͸���
	if (!m_Attachment.IsEmpty()) 
		pMessage->AddMultipleAttachments(m_Attachment);		

	//�趨�����ߵ�ַ
	if (m_Name.IsEmpty()) 
	{
		pMessage->m_From = m_Address;
		pMessage->m_ReplyTo = m_Address;
	}
	else 
	{
		CSMTPAddress address(m_Name, m_Address);
		pMessage->m_From = address;
		pMessage->m_ReplyTo = address;
	}

	m_Authenticate=(CSMTPConnection::LoginMethod) m_Authenticate_1;

	//����һ���Զ���ͷ��������
	#ifdef _DEBUG
	pMessage->AddCustomHeader(_T("X-Program: CSTMPMessageTester"));
	#endif

	return pMessage;
}

//ѡ���������½��ʽ
void DDX_CBData(CDataExchange* pDX, int nIDC, DWORD& dwItemData)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		dwItemData = 0L;
		int nCurSel = (int) ::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
		if (nCurSel != CB_ERR)
			dwItemData = ::SendMessage(hWndCtrl, CB_GETITEMDATA, nCurSel, 0L);
	}
	else
	{
		for (int nIndex = (int) ::SendMessage(hWndCtrl, CB_GETCOUNT, 0, 0L) - 1; 
		nIndex >= 0; nIndex--)
		{
			DWORD dwData = ::SendMessage(hWndCtrl, CB_GETITEMDATA, nIndex, 0L);
			if (dwData == dwItemData)
			{
				::SendMessage(hWndCtrl, CB_SETCURSEL, nIndex, 0L);
				break;
			}
		}
		if (nIndex < 0) // item wasn't found
		SendMessage(hWndCtrl, WM_SETTEXT, 0, (LPARAM) (LPCSTR) "???");
	}
}

//��������������һЩѡ��
int CSMTPwithAttachDlg::CBAddStringAndData(CWnd* pDlg, int nIDC, LPCTSTR pszString, DWORD dwItemData)
{
  int nInserted = CB_ERR;
  CWnd* pComboBox = pDlg->GetDlgItem(nIDC);
  if (pComboBox)
  {
    nInserted = (int) pComboBox->SendMessage(CB_ADDSTRING, 0, (LPARAM) pszString);
    if (nInserted >= 0)
    {
      if (pComboBox->SendMessage(CB_SETITEMDATA, nInserted, dwItemData) == CB_ERR)
        nInserted = CB_ERR;
    }
  }
  return nInserted;
}

//��ѡ�񸽼��ĶԻ���
void CSMTPwithAttachDlg::OnBrowerFile() 
{
	CDataExchange DX(this, TRUE);
    DDX_Text(&DX, IDC_EDIT_Attachment, m_Attachment);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) 
	{
		CString sNewFile = dlg.GetPathName();
		if (m_Attachment.GetLength())
		{
			m_Attachment += _T(", ");
			m_Attachment += sNewFile;
		}
		else
			m_Attachment = sNewFile;
    //Update the UI  
    CDataExchange DX2(this, FALSE);
    DDX_Text(&DX2, IDC_EDIT_Attachment, m_Attachment);
  }

	
}


