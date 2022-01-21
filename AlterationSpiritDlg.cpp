// AlterationSpiritDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AlterationSpirit.h"
#include "AlterationSpiritDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_NOTIFYICON	WM_USER + 105
#define IDI_ICON		0x0005
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

// ON_REGISTERED_MESSAGE
// 注册任务栏创建消息。用于重启explorer.exe进程后重新将图标加入托盘
const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));

class CAboutDlg : public CBCGPDialog
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

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDlg dialog

CAlterationSpiritDlg::CAlterationSpiritDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CAlterationSpiritDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlterationSpiritDlg)
	m_strNum1 = _T("");
	m_strNum2 = _T("");
	m_strNum4 = _T("");
	m_strNum5 = _T("");
	m_strNum7 = _T("");
	m_strNum8 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIsHooked = FALSE;
}

void CAlterationSpiritDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlterationSpiritDlg)
	DDX_Control(pDX, IDC_EDIT_NUM8, m_editNum8);
	DDX_Control(pDX, IDC_EDIT_NUM7, m_editNum7);
	DDX_Control(pDX, IDC_EDIT_NUM5, m_editNum5);
	DDX_Control(pDX, IDC_EDIT_NUM4, m_editNum4);
	DDX_Control(pDX, IDC_EDIT_NUM2, m_editNum2);
	DDX_Control(pDX, IDC_EDIT_NUM1, m_editNum1);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_strNum1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_strNum2);
	DDX_Text(pDX, IDC_EDIT_NUM4, m_strNum4);
	DDX_Text(pDX, IDC_EDIT_NUM5, m_strNum5);
	DDX_Text(pDX, IDC_EDIT_NUM7, m_strNum7);
	DDX_Text(pDX, IDC_EDIT_NUM8, m_strNum8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlterationSpiritDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CAlterationSpiritDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CORRECT_REGULAR, OnCorrectRegular)
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, OnTaskBarCreated)
	ON_MESSAGE(WM_NOTIFYICON, OnNotifyIcon)
	ON_COMMAND(IDM_TRAY_OPEN, OnTrayOpen)
	ON_COMMAND(IDM_TRAY_EXIT, OnTrayExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDlg message handlers

BOOL CAlterationSpiritDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

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
	// 设置寻找标记
	::SetProp(m_hWnd, AfxGetApp()->m_pszExeName, (HANDLE)1);

	GetAlteration();

	CString strMsg;
	DWORD dwPID = CProcessOperation::GetPIDByProcessName("war3.exe");
//	HWND hWnd = CProcessOperation::GetWndByPID(dwPID);
// 	strMsg.Format("PID:%d", dwPID);
//	OutputDebugString(strMsg);
// 	strMsg.Format("hWnd:%p", hWnd);
// 	OutputDebugString(strMsg);

	// 提升权限，否则程序运行正常，但是直接双击exe OpenProcess失败，提升权限不足
	CProcessOperation::ImproveProcPriv();
	m_hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (m_hHandle == NULL)
	{
		strMsg.Format("NULL Handle, GetLastError():%d", GetLastError());
		OutputDebugString(strMsg);
	}

	m_editNum7.GetTextByte(m_changeKeys[0]);
	m_editNum8.GetTextByte(m_changeKeys[1]);
	m_editNum4.GetTextByte(m_changeKeys[2]);
	m_editNum5.GetTextByte(m_changeKeys[3]);
	m_editNum1.GetTextByte(m_changeKeys[4]);
	m_editNum2.GetTextByte(m_changeKeys[5]);
	m_hookGlobal.CreateDllHook(m_hHandle, m_changeKeys, 6);
	m_bIsHooked = TRUE;

	AddToTray();

	EnableVisualManagerStyle(TRUE, TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAlterationSpiritDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		//最小化时隐藏窗口
		if (nID == SC_MINIMIZE || nID == SC_CLOSE)
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			CBCGPDialog::OnSysCommand(nID, lParam);
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAlterationSpiritDlg::OnPaint() 
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
		CBCGPDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAlterationSpiritDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAlterationSpiritDlg::AddToTray()
{
	// 将图标放入系统托盘
	nd.cbSize = sizeof (NOTIFYICONDATA);
	nd.hWnd	= m_hWnd;
	nd.uID = IDI_ICON;
	nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage	= WM_NOTIFYICON;
	nd.hIcon = m_hIcon;
	strcpy(nd.szTip, "改建精灵");	
	Shell_NotifyIcon(NIM_ADD, &nd);	
}

void CAlterationSpiritDlg::OnSave() 
{
	SetAlteration();

	m_editNum7.GetTextByte(m_changeKeys[0]);
	m_editNum8.GetTextByte(m_changeKeys[1]);
	m_editNum4.GetTextByte(m_changeKeys[2]);
	m_editNum5.GetTextByte(m_changeKeys[3]);
	m_editNum1.GetTextByte(m_changeKeys[4]);
	m_editNum2.GetTextByte(m_changeKeys[5]);
	m_hookGlobal.SetKeysAlteration(m_changeKeys, 6);
}

void CAlterationSpiritDlg::GetAlteration()
{
	m_strNum1 = g_ConfigInfo.GetAlteration(1, 1);
	m_strNum2 = g_ConfigInfo.GetAlteration(1, 2);
	m_strNum4 = g_ConfigInfo.GetAlteration(1, 4);
	m_strNum5 = g_ConfigInfo.GetAlteration(1, 5);
	m_strNum7 = g_ConfigInfo.GetAlteration(1, 7);
	m_strNum8 = g_ConfigInfo.GetAlteration(1, 8);

	UpdateData(FALSE);

//	g_ConfigInfo.GetMapAlteration();
}
void CAlterationSpiritDlg::SetAlteration()
{
	UpdateData(TRUE);
	
	g_ConfigInfo.SetAlteration(1, 1, m_strNum1);
	g_ConfigInfo.SetAlteration(1, 2, m_strNum2);
	g_ConfigInfo.SetAlteration(1, 4, m_strNum4);
	g_ConfigInfo.SetAlteration(1, 5, m_strNum5);
	g_ConfigInfo.SetAlteration(1, 7, m_strNum7);
	g_ConfigInfo.SetAlteration(1, 8, m_strNum8);

//	g_ConfigInfo.GetMapAlteration();
}

void CAlterationSpiritDlg::OnDestroy() 
{
	// 删除寻找标记
	::RemoveProp(m_hWnd, AfxGetApp()->m_pszExeName);

	// 删除托盘图标
	Shell_NotifyIcon(NIM_DELETE, &nd);	

	CBCGPDialog::OnDestroy();
	
	m_hookGlobal.DestroyDllHook();
	m_bIsHooked = FALSE;

	CloseHandle(m_hHandle);
}

// 规则互斥
LRESULT CAlterationSpiritDlg::OnCorrectRegular(WPARAM wParam, LPARAM lParam)
{
	CEditEx* pEdit = (CEditEx*)lParam;

	CString strText;
	pEdit->GetWindowText(strText);
	if (!strText.IsEmpty())
	{
		UpdateData(TRUE);
		if (pEdit != &m_editNum1 && strText.Compare(m_strNum1) == 0)
		{
			m_strNum1.Empty();
		}
		if (pEdit != &m_editNum2 && strText.Compare(m_strNum2) == 0)
		{
			m_strNum2.Empty();
		}
		if (pEdit != &m_editNum4 && strText.Compare(m_strNum4) == 0)
		{
			m_strNum4.Empty();
		}
		if (pEdit != &m_editNum5 && strText.Compare(m_strNum5) == 0)
		{
			m_strNum5.Empty();
		}
		if (pEdit != &m_editNum7 && strText.Compare(m_strNum7) == 0)
		{
			m_strNum7.Empty();
		}
		if (pEdit != &m_editNum8 && strText.Compare(m_strNum8) == 0)
		{
			m_strNum8.Empty();
		}
		UpdateData(FALSE);
	}

	return 0;
}

BOOL CAlterationSpiritDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		/*
		if (pMsg->wParam >= VK_PAUSE)
		{
			if (!m_bIsHooked)
			{
				m_editNum7.GetTextByte(m_changeKeys[0]);
				m_editNum8.GetTextByte(m_changeKeys[1]);
				m_editNum4.GetTextByte(m_changeKeys[2]);
				m_editNum5.GetTextByte(m_changeKeys[3]);
				m_editNum1.GetTextByte(m_changeKeys[4]);
				m_editNum2.GetTextByte(m_changeKeys[5]);
				m_hookGlobal.CreateDllHook(m_changeKeys, 6);
				m_bIsHooked = TRUE;
			}
			else
			{
				m_hookGlobal.DestroyDllHook();
				m_bIsHooked = FALSE;
			}
		}
		*/
	}
	
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

LRESULT CAlterationSpiritDlg::OnTaskBarCreated(WPARAM wParam, LPARAM lParam)
{
	Shell_NotifyIcon(NIM_ADD, &nd);

	return 1;
}

void CAlterationSpiritDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	if (wParam == IDI_ICON)
	{
		if (lParam == WM_LBUTTONDOWN)
		{
			if (IsWindowVisible())
			{
				ShowWindow(SW_HIDE);			
			}
			else
			{
				ShowWindow(SW_SHOW);
				::BringWindowToTop(this->GetSafeHwnd());
			}
		}
		else if (lParam == WM_RBUTTONDOWN)
		{
			CPoint pt ;
			ClientToScreen(&pt);
			GetCursorPos(&pt);
			
			CMenu menu;
			menu.LoadMenu(IDR_POPUPMENU);
			CMenu* pMenu = menu.GetSubMenu(0);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		}
	}
}

void CAlterationSpiritDlg::OnTrayOpen() 
{
	ShowWindow(SW_SHOW);
	::BringWindowToTop(this->GetSafeHwnd());
}

void CAlterationSpiritDlg::OnTrayExit() 
{
	CBCGPDialog::OnCancel();
}

/*
#define PATCH(i,w,l) WriteProcessMemory(hopen,reinterpret_cast<LPVOID>(gameBase+i),w,l,&dSize)
#define PATCH1(i,w)   WriteProcessMemory(hopen,(LPVOID)(gameBase + i), w, sizeof(w)-1, 0)
void CAlterationSpiritDlg::MapFog()
{
	CProcessOperation::ImproveProcPriv();
	DWORD dwPID = CProcessOperation::GetPIDByProcessName("war3.exe");
	if (dwPID == 0)
	{
		::MessageBox(m_hWnd, "貌似您 没有开war3吧？", 0, MB_ICONERROR);
		return ;
	}
    HANDLE hopen = OpenProcess( PROCESS_ALL_ACCESS|PROCESS_TERMINATE|PROCESS_VM_OPERATION|PROCESS_VM_READ|
		PROCESS_VM_WRITE,FALSE, dwPID);
	if (hopen == NULL)
	{
		::MessageBox(m_hWnd, "不能打开war3进程！", 0, MB_ICONERROR);
		return ;
	}
	BOOL bret = FALSE;
	DWORD gameBase = CProcessOperation::GetDLLBase(_T("Game.dll"), dwPID);
	DWORD dSize = 0;
	
	CString strMsg;
	strMsg.Format("gameBase:%p", gameBase);
	OutputDebugString(strMsg);
	
	////////////////////////////////////////////////////////////////////////大地图去除迷雾   
//	PATCH1(0x74D1B9,"\xB2\x00\x90\x90\x90\x90");   
	////////////////////////////大地图显示单位   
// 	PATCH(0x39EBBC,"\x75", 1);   
// 	PATCH(0x3A2030,"\x90\x90", 2);   
// 	PATCH(0x3A20DB,"\x90\x90", 2);   
	///////////////////////////////显示隐形单位
	/*
	PATCH(0x362391,"\x3B");   
	PATCH(0x362394,"\x85");   
	PATCH(0x39A51B,"\x90\x90\x90\x90\x90\x90");   
	PATCH(0x39A52E,"\x90\x90\x90\x90\x90\x90\x90\x90\x33\xC0\x40");   
	///////////////////////////////////////////////////分辨幻影 
	PATCH(0x28357C,"\x40\xC3");   
	/////////////////////////////////////////////////////显示物品   
	PATCH(0x3A201B,"\xEB");   
	PATCH(0x40A864,"\x90\x90");   
	////////////////////////////////////////////小地图 去除迷雾   
	PATCH(0x357065,"\x90\x90");   
	////////////////////////////////////////////小地图显示单位
	PATCH(0x361F7C,"\x00");   
	/*
	/////////////////////////////////////////////小地图显示隐形   
	/////////////////////////////////////////////敌方信号   
	PATCH(0x43F9A6,"\x3B");   
	PATCH(0x43F9A9,"\x85");   
	PATCH(0x43F9B9,"\x3B");   
	PATCH(0x43F9BC,"\x85");   
	/////////////////////////////////////////////他人提示   
	PATCH(0x3345E9,"\x39\xC0\x0F\x85");   
	////////////////////////////////////////////////敌方头像
	PATCH(0x371700,"\xE8\x3B\x28\x03\x00\x85\xC0\x0F\x85\x8F\x02\x00\x00\xEB\xC9\x90\x90\x90\x90");   
	/////////////////////////////////////盟友头像   
	PATCH(0x371700,"\xE8\x3B\x28\x03\x00\x85\xC0\x0F\x84\x8F\x02\x00\x00\xEB\xC9\x90\x90\x90\x90");   
	////////////////////////////////////////////////////////////数显攻速   
	PATCH(0x87EA63,"\x25\x30\x2E\x32\x66\x7C\x52\x00");   
	PATCH(0x87EA70,"\x8D\x4C\x24\x18\xD9\x44\x24\x60\x83\xEC\x08\xDD\x1C\x24\x68");   
	DWORD tmp=0x87EA63+GameAddr;   
	memcpy(LPVOID(GameAddr+0x87EA7F),&tmp,4);   
	PATCH(0x87EA83,"\x57\x51\xE8\xBC\xD2\xE6\xFF\x83\xC4\x14\x58\x57\x8D\x4C\x24\x18\xFF\xE0");   
	PATCH(0x339DF4,"\xE8\x77\x4C\x54\x00");   
	//////////////////////////////////////////////////////////数显移速   
	PATCH(0x87EA63,"\x25\x30\x2E\x32\x66\x7C\x52\x00");   
	PATCH(0x87EA70,"\x8D\x4C\x24\x18\xD9\x44\x24\x60\x83\xEC\x08\xDD\x1C\x24\x68");   
	DWORD tmp=0x87EA63+GameAddr;   
	memcpy(LPVOID(GameAddr+0x87EA7F),&tmp,4);   
	PATCH(0x87EA83,"\x57\x51\xE8\xBC\xD2\xE6\xFF\x83\xC4\x14\x58\x57\x8D\x4C\x24\x18\xFF\xE0");   
	PATCH(0x339C54,"\xE8\x17\x4E\x54\x00");   
	//////////////////////////////////////////////////////资源面板   
	PATCH(0x36058A,"\x90");   
	PATCH(0x36058B,"\x90");   
	///////////////////////////////////////////   允许交易
	PATCH(0x34E8E2,"\xB8\xC8\x00\x00");      
	PATCH(0x34E8E7,"\x90");   
	PATCH(0x34E8EA,"\xB8\x64\x00\x00");      
	PATCH(0x34E8EF,"\x90");   
	////////////////////////////////////////////////显示技能    
	PATCH(0x2031EC,"\x90\x90\x90\x90\x90\x90");   
	PATCH(0x34FDE8,"\x90\x90");   
	/////////////////////////////////////////////////技能CD
	PATCH(0x28ECFE,"\xEB");   
	PATCH(0x34FE26,"\x90\x90\x90\x90");   
	//////////////////////////////////////////////资源条   
	//////////////////////////////////////////////野外显血   
	///////////////////////////////////////////////视野外点击
	PATCH(0x285CBC,"\x90\x90");   
	PATCH(0x285CD2,"\xEB");   
	//////////////////////////////////////////////////无限取消   
	PATCH(0x57BA7C,"\xEB");   
	PATCH(0x5B2D77,"\x03");   
	PATCH(0x5B2D8B,"\x03");   
	/////////////////////////////////////////////////////过-MH   
	PATCH(0x3C84C7,"\xEB\x11");   
	PATCH(0x3C84E7,"\xEB\x11");   
	////////////////////////////////////////////////////反-AH   
	PATCH(0x3C6EDC,"\xB8\xFF\x00\x00\x00\xEB");   
	PATCH(0x3CC3B2,"\xEB");   
///////////////////////////////////////////////////////////

#ifdef 0
	PATCH(0x406B4F,"\x09\x90",2); //Patch 6F3A04AB to nop nop :-)
	PATCH(0x406B54,"\x09\x90",2);
	PATCH(0x147C12,"\x40\x33\xC0",3);  
	PATCH(0x147C17,"\x41\x33\xC9",3);  
	PATCH(0x1486F4,"\x41\x33\xC9",3);
	PATCH(0x1486FB,"\x41\x33\xC9",3);
	PATCH(0x2A0923,"\x40\x33\xC0\x42\x33\xD2",6);
	PATCH(0x1ACFFC,"\x40\xC3",2);
	PATCH(0x7D4E8,"\x90\x90\x90\x90\xB8\x01\x00",7);
	PATCH(0x1491A8,"\x00",1);
	PATCH(0x1494E0,"\x39",1);
	PATCH(0x1494E3,"\x85",1);
#endif
	CloseHandle(hopen);
}
*/