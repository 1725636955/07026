// FtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
#include "Afxinet.h"

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
// CFtpDlg dialog

CFtpDlg::CFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFtpDlg)
	m_strFtp = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFtpDlg)
	DDX_Control(pDX, IDC_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, IDOK, m_btnQuery);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Control(pDX, IDC_STATIC_PWD, m_staPwd);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staName);
	DDX_Control(pDX, IDC_STATIC_FTP, m_staFtp);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFtpDlg, CDialog)
	//{{AFX_MSG_MAP(CFtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnQuery)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, OnSelchangeListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg message handlers

BOOL CFtpDlg::OnInitDialog()
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
	m_strFtp=_T("");    // ��ʼ������������
	m_strName=_T("");     // ��ʼ����¼�û���
	m_strPwd=_T("");      //  ��ʼ����¼����
	UpdateData(FALSE);    //���½���

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpDlg::OnPaint() 
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
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//���û����'��ѯ'��ť��ִ�д˺�����
void CFtpDlg::OnQuery() 
{
	CInternetSession* pSession;     //����Ự����ָ�����
	CFtpConnection* pConnection;   //�������Ӷ���ָ�����
	CFtpFileFind* pFileFind;          //�����ļ���ѯ����ָ�����
	CString strFileName;
	BOOL bContinue;

	pConnection=NULL;      //��ʼ��
	pFileFind=NULL;

	UpdateData(TRUE);      // ����û��ĵ�ǰ���루�����������û����Ϳ��
	while(m_listFile.GetCount()!=0) m_listFile.DeleteString(0);  // ����б�������

	pSession=new CInternetSession(          // ����Internet�Ự�����
			AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try 
	{  // ��ͼ������ָ��FTP������������
		pConnection=
			pSession->GetFtpConnection(m_strFtp,m_strName,m_strPwd);
	}  catch (CInternetException* e)  {   
		e->Delete();                          // �޷��������ӣ����д�����
		pConnection=NULL;
	}

	if (pConnection!=NULL)
	{
		// ����CFtpFileFind�������캯������CFtpConnection�����ָ��
		pFileFind=new CFtpFileFind(pConnection);
		bContinue=pFileFind->FindFile("*");  // ���ҷ������ϵ�ǰĿ¼�������ļ�
		if (!bContinue)   // ���һ���ļ����Ҳ�������������
		{
			pFileFind->Close();
			pFileFind=NULL;
		}

		while (bContinue)  // �ҵ��˵�һ���ļ����������������ļ�
		{
			strFileName=pFileFind->GetFileName();  // ����ҵ����ļ����ļ���
			// ����ҵ����Ƿ�Ŀ¼����Ŀ¼������������
			if (pFileFind->IsDirectory())  strFileName="["+strFileName+"]";
			// ���ҵ����ļ���Ŀ¼����ʾ���б���С�
			m_listFile.AddString(strFileName);
			bContinue=pFileFind->FindNextFile();    // ������һ���ļ�
		}

		if (pFileFind!=NULL)
		{
			pFileFind->Close();   // ������ѯ
			pFileFind=NULL;
		}
	}
	delete pFileFind;              // ɾ���ļ���ѯ����
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;      // ɾ��FTP���Ӷ���
	}
	delete pSession;             // ɾ��Internet �Ự���� 
	
}

//��ѯ�Ժ󣬵��û����б����ѡ����һ���ļ�ʱ��ִ�д˺�����
void CFtpDlg::OnSelchangeListFile() 
{
	// ��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);          //���������������ı���
	m_editName.EnableWindow(FALSE);        //��¼�û��������ı��� 
	m_editPwd.EnableWindow(FALSE);          //���������ı���
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//���ò�ѯ���ϴ���ť
	m_btnUpload.EnableWindow(FALSE);      //�ϴ���ť
	m_btnQuery.EnableWindow(FALSE);        //��ѯ��ť

	//�������ذ�ť
	m_btnDownload.EnableWindow(TRUE);
}

//���û����"����"��ťʱ��ִ�д˺���
void CFtpDlg::OnDownload() 
{
	//��õ�ǰ����
	UpdateData(TRUE);
	int nSel=m_listFile.GetCurSel();
	CString strSourceName;

	//����û����б���е�ѡ��
	nSel=m_listFile.GetCurSel();
	m_listFile.GetText(nSel,strSourceName);

	if (strSourceName.GetAt(0)!='[' )
	{
		//ѡ������ļ�
		CString strDestName;
		CFileDialog dlg(FALSE,"","*.*");   //������һ���ļ��Ի���������
		if (dlg.DoModal()==IDOK)        //�����ļ��Ի���
		{
			//��������ļ��ڱ��ػ��ϴ洢��·��������
			strDestName=dlg.GetPathName();

			//���ú��������ļ�
			if (Download (strSourceName,strDestName))
				AfxMessageBox("���سɹ���",MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox("����ʧ�ܣ�",MB_OK|MB_ICONSTOP);
		}  else  {
			AfxMessageBox("��д���ļ�����",MB_OK|MB_ICONSTOP);
		}
	}  else  {
		//ѡ�����Ŀ¼
		AfxMessageBox("��������Ŀ¼!\n����ѡ!",MB_OK|MB_ICONSTOP);
	}

	//�������ذ�ť
	m_btnDownload.EnableWindow(FALSE);

	//�����ѯ���ϴ���ť
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı��ͱ༭��ؼ�
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

// Download������OnDownload�������ã�ִ��ʵ�ʵ���������
BOOL CFtpDlg::Download(CString strSName, CString strDName)
{
	CInternetSession* pSession;      //����Ự�������ָ��
	CFtpConnection* pConnection;    //�������Ӷ������ָ��

	pConnection=NULL;

	//����Internet�Ự����
	pSession=new CInternetSession( AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection=pSession->GetFtpConnection(m_strFtp,
				m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//�����ļ�
		if (!pConnection->GetFile(strSName,strDName))
		{
			//�����ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
		delete pSession;

	return TRUE;
}

//���û����"�ϴ�"��ťʱ��ִ�д˺���
void CFtpDlg::OnUpload() 
{
	//��õ�ǰ����
	UpdateData(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);            //���������������ı���
	m_editName.EnableWindow(FALSE);          //��¼�ͻ��������ı���
	m_editPwd.EnableWindow(FALSE);            //���������ı���
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//���ò�ѯ��ť
	m_btnQuery.EnableWindow(FALSE);

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,"","*.*");       //�����ı��Ի���������
	if (dlg.DoModal()==IDOK)
	{
		//��ô��ϴ��ı��ػ��ļ�·�����ļ���
		strSourceName=dlg.GetPathName();
		strDestName=dlg.GetFileName();

		//����Upload�����ϴ��ļ�
		if (Upload (strSourceName,strDestName))
			AfxMessageBox("�ϴ��ɹ���",MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox("�ϴ�ʧ�ܣ�",MB_OK|MB_ICONSTOP);
	}  else  {
		//�ļ�ѡ���д���
		AfxMessageBox("��ѡ���ļ���",MB_OK|MB_ICONSTOP);
	}

	//�����ѯ��ť
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

// Upload�������¼�������OnUpload���ã�ִ��ʵ�ʵ��ϴ�����
BOOL CFtpDlg::Upload(CString strSName, CString strDName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection=NULL;

	//����Internet�Ự
	pSession=new CInternetSession(	AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection=pSession->GetFtpConnection(	m_strFtp,
		m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//�ϴ��ļ�
		if (!pConnection->PutFile(strSName,strDName))
		{
			//�ϴ��ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}

	delete pSession;

	return TRUE;
}
