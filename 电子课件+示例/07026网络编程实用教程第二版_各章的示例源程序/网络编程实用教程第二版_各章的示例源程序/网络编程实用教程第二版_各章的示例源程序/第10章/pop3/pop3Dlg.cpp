// pop3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "pop3.h"
#include "pop3Dlg.h"
#include "mySock.h"      //�ֹ���ӵİ������

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
// CPop3Dlg dialog

CPop3Dlg::CPop3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPop3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPop3Dlg)
	m_strPass = _T("");
	m_strServer = _T("");
	m_strUser = _T("");
	m_bolDel = FALSE;
	m_Info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPop3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPop3Dlg)
	DDX_Control(pDX, IDC_RICH_INFO, m_ctrInfo);
	DDX_Control(pDX, IDC_COMB_LIST, m_ctrList);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Check(pDX, IDC_CHECK_DEL, m_bolDel);
	DDX_Text(pDX, IDC_RICH_INFO, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPop3Dlg, CDialog)
	//{{AFX_MSG_MAP(CPop3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONN, OnBtnConn)
	ON_BN_CLICKED(IDC_BTN_DISC, OnBtnDisc)
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPop3Dlg message handlers

BOOL CPop3Dlg::OnInitDialog()
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
	//�û���������ӿؼ���Ա�����ĳ�ʼ������
	m_strServer = _T("pop.sina.com.cn");   //POP3��������ַ
	m_strUser = _T("mu_lm");               //������û���
	m_strPass = _T("491015");              //����
	m_bolDel = FALSE;                      //�����ʼ���ɾ��
	m_Info = _T("");                       //���ı������
	m_ctrList.Clear();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPop3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPop3Dlg::OnPaint() 
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
HCURSOR CPop3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//�������¼���������������Ա�����Ĵ���
//���û����"����"��ťʱ��ִ�д˺���
void CPop3Dlg::OnBtnConn() 
{
	//�趨pop3��ĶԻ���ָ�������ʹָ֮�򱾶Ի����Ա㴫����Ϣ
	pop3Socket.SetParent(this); 
	UpdateData(TRUE);           //ȡ���û��ڶԻ��������������
	pop3Socket.Create();        //�����׽��ֶ���ĵײ��׽���
	pop3Socket.Connect((LPCSTR)m_strServer,110); //����pop3������
	m_Info = "";                //���ı��б�����
	UpdateData(FALSE);          //�����û�����

}
//���û����"�Ͽ�"��ťʱ��ִ�д˺���
void CPop3Dlg::OnBtnDisc() 
{
	pop3Socket.Close();
}
//���û����"�鿴�ʼ�"��ťʱ��ִ�д˺���
void CPop3Dlg::OnBtnView() 
{
	int i;
	i = m_ctrList.GetCurSel();  //����û�����Ͽ��е�ѡ��
	//��ò���ʾָ���ż��Ļ������Լ��ż�����
	m_Info += pop3Socket.GetMsgStuff(i);
	m_Info += pop3Socket.GetMsgBody(i);
//	CString s;
//	for(int i=0;i<pop3Socket.retrMsg;i++)
//	{
//		s.Format("%c%c�� %d ���� %c%c",13,10,i,13,10);
//		m_Info +=s;
//		m_Info += pop3Socket.msgs[i].text;
//	}
	UpdateData(FALSE);
}
//�ڲ�ͬ������£����û���ʾ��ͬ����Ϣ
void CPop3Dlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //�����ӵ�����������ʾ��Ϣ
		s = "�����ӵ�"+m_strServer+"...\r\n";
		m_Info+=s;
		//�������Ӱ�ť
		GetDlgItem(IDC_BTN_CONN)->EnableWindow(FALSE);
		//���öϿ���ť
		GetDlgItem(IDC_BTN_DISC)->EnableWindow(TRUE); 
		//���ò鿴�ʼ���ť
		GetDlgItem(IDC_BTN_VIEW)->EnableWindow(FALSE);
		break;
	case S_RECEIVE: //�յ���������������Ӧ����ʾ��������
		m_Info+=pop3Socket.lastMsg;
		break; 
	case S_CLOSE: //��ʾ�ر����ӵ���Ϣ
		m_Info+=pop3Socket.error;
		s = "�����Ѿ��ر�\r\n";
		m_Info+=s;
		//�������Ӱ�ť
		GetDlgItem(IDC_BTN_CONN)->EnableWindow(TRUE);
		//���öϿ���ť
		GetDlgItem(IDC_BTN_DISC)->EnableWindow(FALSE);
		break;
	case S_GETNUM: //�Ѿ�֪�����������ż�������
		s.Format("�����й��� %d ����\r\n",pop3Socket.numMsg);
		m_Info+=s;
		break;
	case S_GETSIZE: //��ʾ�ż��Ĵ�С
		s.Format("�������ż���СΪ��%d�ֽ�\r\n",pop3Socket.sizeMsg);
		m_Info+=s;
		break;
	case S_ENDRETR: //�����ż���������ϣ���ʾ��Ϣ
		s.Format("�������� %d ���ż�\r\n",pop3Socket.msgs.size());
		m_Info+=s;
		//������ż����أ����ò鿴�ʼ���ť
		if((pop3Socket.msgs.size())>0)
			GetDlgItem(IDC_BTN_VIEW)->EnableWindow(TRUE);
		break;
	}
	UpdateData(FALSE);   //�����û�����
}

void CPop3Dlg::OnBtnSave() 
{
	int i;
	CString s;
	i = m_ctrList.GetCurSel();
	//���ָ���ż��Ļ������Լ��ż�����
	s = pop3Socket.GetMsgStuff(i);
	s += pop3Socket.GetMsgBody(i);
	
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		file.Write((LPCSTR)s,s.GetLength());
		file.Close();
	}
}
