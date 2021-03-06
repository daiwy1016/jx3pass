// jx3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "jx3.h"
#include "jx3Dlg.h"

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
// CJx3Dlg dialog

CJx3Dlg::CJx3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJx3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJx3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJx3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJx3Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJx3Dlg, CDialog)
	//{{AFX_MSG_MAP(CJx3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJx3Dlg message handlers

BOOL CJx3Dlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJx3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJx3Dlg::OnPaint() 
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
HCURSOR CJx3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJx3Dlg::OnOK() 
{
	// TODO: Add extra validation here
	MessageBox("1");
	
	CDialog::OnOK();
	
}

void CJx3Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	MessageBox("开始启动");
	STARTUPINFO si;
	memset(&si,0,sizeof(STARTUPINFO));//初始化si 在内存块的值
	si.cb=sizeof(STARTUPINFO);
	si.dwFlags=STARTF_USESHOWWINDOW;
	si.wShowWindow=SW_SHOW;
	PROCESS_INFORMATION pi;
	//必备参数设置结束
	//创建进程 注入dll
	::CreateProcess(NULL,"JX3CLIENT.exe DOTNOTSTARTGAMEBYJX3CLIENT.EXE",NULL,NULL,0,CREATE_SUSPENDED,NULL,NULL,&si,&pi);
	char s[]=".\\jx3dll.dll";
	int nSize = ::strlen(s)+1;
	void *pParam=::VirtualAllocEx(pi.hProcess,0,nSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	::WriteProcessMemory(pi.hProcess,pParam,s,nSize,0);
	//创建远程线程
	HANDLE hThread=::CreateRemoteThread(pi.hProcess,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibraryA,pParam,0,NULL);
	::WaitForSingleObject(hThread,INFINITE);
	::CloseHandle(hThread);//不适用句柄最好关掉
	::VirtualFreeEx(pi.hProcess,pParam,nSize,MEM_DECOMMIT);
	::ResumeThread(pi.hThread);//恢复线程，必须要，不然会卡住
	MessageBox("结束启动");
	return ;

}
