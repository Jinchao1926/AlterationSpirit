// AlterationSpirit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AlterationSpirit.h"
#include "AlterationSpiritDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritApp

BEGIN_MESSAGE_MAP(CAlterationSpiritApp, CWinApp)
	//{{AFX_MSG_MAP(CAlterationSpiritApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	//屏蔽F1启动帮助
	//ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritApp construction

CAlterationSpiritApp::CAlterationSpiritApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAlterationSpiritApp object

CAlterationSpiritApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritApp initialization

BOOL CAlterationSpiritApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// 进程单例
	// 用应用程序名创建信号量，信号量已存在说明已有一个实例运行   
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, AfxGetApp()->m_pszExeName);      
	if (GetLastError() == ERROR_ALREADY_EXISTS)  
	{   
		// 关闭信号量句柄  
		CloseHandle(hSem);
		
		// 寻找先前实例的主窗口   
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);  
		while (::IsWindow(hWndPrevious))  
		{   
			// 检查窗口是否有预设的标记
			// CMainFrame OnCreate里面调用::SetProp
			if (::GetProp(hWndPrevious, m_pszExeName))  
			{   
				// 主窗口已最小化，则恢复其大小  
				//if (::IsIconic(hWndPrevious))  //无法判断是否加入托盘
				if (!::IsWindowVisible(hWndPrevious))
				{
					::ShowWindow(hWndPrevious, SW_RESTORE);  
				}
				
				// 将主窗激活  
				::SetForegroundWindow(hWndPrevious);  
				//::BringWindowToTop(hWndPrevious);
				//::SetActiveWindow(hWndPrevious);
				// 将主窗的对话框激活  
				::SetForegroundWindow(::GetLastActivePopup(hWndPrevious)); 
				
				// 退出本实例  
				return FALSE;  
			}   
			// 继续寻找下一个窗口   
			hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);  
		}   
		// 前一实例已存在，但找不到其主窗，退出本实例  
		return FALSE;  
	}  

	CAlterationSpiritDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAlterationSpiritApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}
