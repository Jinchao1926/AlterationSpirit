// AlterationSpiritDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AlterationSpiritDemo.h"
#include "AlterationSpiritDemoDlg.h"

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
// CAlterationSpiritDemoDlg dialog

CAlterationSpiritDemoDlg::CAlterationSpiritDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlterationSpiritDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlterationSpiritDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlterationSpiritDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlterationSpiritDemoDlg)
	DDX_Control(pDX, IDC_LIST_LOG, m_lsbLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlterationSpiritDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CAlterationSpiritDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDemoDlg message handlers

BOOL CAlterationSpiritDemoDlg::OnInitDialog()
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
	CString strMsg;
	strMsg.Format("GetSafeHwnd():%p", GetSafeHwnd());
//	OutputDebugString(strMsg);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAlterationSpiritDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlterationSpiritDemoDlg::OnPaint() 
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
HCURSOR CAlterationSpiritDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAlterationSpiritDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		CString strMsg;
		CString strButton;
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:		strMsg = "Button[Esc] is pressed!"; break;
		case VK_CAPITAL:	strMsg = "Button[Caps Lock] is pressed!"; break;
		case VK_SHIFT:		strMsg = "Button[Shift] is pressed!"; break;
		case VK_CONTROL:	strMsg = "Button[Ctrl] is pressed!"; break;
		case VK_PAUSE:		strMsg = "Button[Pause] is pressed!"; break;
		case VK_DELETE:		strMsg = "Button[Delete] is pressed!"; break;
		case VK_INSERT:		strMsg = "Button[Insert] is pressed!"; break;
		case VK_TAB:		strMsg = "Button[Tab] is pressed!"; break;
		case VK_BACK:		strMsg = "Button[Backspace] is pressed!"; break;
		case VK_SPACE:		strMsg = "Button[Space] is pressed!"; break;
		case VK_HOME:		strMsg = "Button[Home] is pressed!"; break;
		case VK_END:		strMsg = "Button[End] is pressed!"; break;
		case VK_PRIOR:		strMsg = "Button[PgUp] is pressed!"; break;
		case VK_NEXT:		strMsg = "Button[PgDn] is pressed!"; break;
		case VK_LEFT:		strMsg = "Button[Left] is pressed!"; break;
		case VK_RIGHT:		strMsg = "Button[Right] is pressed!"; break;
		case VK_UP:			strMsg = "Button[Up] is pressed!"; break;
		case VK_DOWN:		strMsg = "Button[Down] is pressed!"; break;
		case 0xc0:			strMsg = "Button[~] is pressed!"; break;
		// F1 - F12
		case VK_F1:			strMsg = "Button[F1] is pressed!"; break;
		case VK_F2:			strMsg = "Button[F2] is pressed!"; break;
		case VK_F3:			strMsg = "Button[F3] is pressed!"; break;
		case VK_F4:			strMsg = "Button[F4] is pressed!"; break;
		case VK_F5:			strMsg = "Button[F5] is pressed!"; break;
		case VK_F6:			strMsg = "Button[F6] is pressed!"; break;
		case VK_F7:			strMsg = "Button[F7] is pressed!"; break;
		case VK_F8:			strMsg = "Button[F8] is pressed!"; break;
		case VK_F9:			strMsg = "Button[F9] is pressed!"; break;
		case VK_F10:		strMsg = "Button[F10] is pressed!"; break;
		case VK_F11:		strMsg = "Button[F11] is pressed!"; break;
		case VK_F12:		strMsg = "Button[F12] is pressed!"; break;
		// numpad0 - numpad9
		case VK_NUMPAD0:	strMsg = "Button[num0] is pressed!"; break;
		case VK_NUMPAD1:	strMsg = "Button[num1] is pressed!"; break;
		case VK_NUMPAD2:	strMsg = "Button[num2] is pressed!"; break;
		case VK_NUMPAD3:	strMsg = "Button[num3] is pressed!"; break;
		case VK_NUMPAD4:	strMsg = "Button[num4] is pressed!"; break;
		case VK_NUMPAD5:	strMsg = "Button[num5] is pressed!"; break;
		case VK_NUMPAD6:	strMsg = "Button[num6] is pressed!"; break;
		case VK_NUMPAD7:	strMsg = "Button[num7] is pressed!"; break;
		case VK_NUMPAD8:	strMsg = "Button[num8] is pressed!"; break;
		case VK_NUMPAD9:	strMsg = "Button[num9] is pressed!"; break;

		case 0xdb:			strMsg = "Button[¡¾] is pressed!"; break;
		case 0xdd:			strMsg = "Button[¡¿] is pressed!"; break;
		
		default:
			char ch;
			sprintf(&ch, "%c", pMsg->wParam);

			CString strTmp;
			strTmp.Format("0x%x", pMsg->wParam);
			OutputDebugString(strTmp);

			strMsg.Format("Button[%c] is pressed!", ch);	
		}
		m_lsbLog.AddString(strMsg);
		
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CAlterationSpiritDemoDlg::OnBtnClear() 
{
	m_lsbLog.ResetContent();
}
