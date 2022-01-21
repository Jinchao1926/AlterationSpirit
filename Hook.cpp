// Hook.cpp: implementation of the Hook class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Hook.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK HookKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	/*
	// 线程钩子回调函数 WH_KEYBOARD_LL
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN && !bIsKeyDown)
		{
			memset(path, 0, _MAX_PATH);
			GetModuleFileName(NULL, path, _MAX_PATH);
			
			OutputDebugString(path);
		
			// Only Hook war3.exe
			if (strstr(path, "war3.exe") != NULL)
			{
				PKBDLLHOOKSTRUCT pStruct = (PKBDLLHOOKSTRUCT)lParam; 
				
				// Pause键开启/停用钩子
				if (pStruct->vkCode == VK_PAUSE)
				{
					bIsHooked = !bIsHooked;
				}
				if (bIsHooked)
				{
					if (pStruct->vkCode == changeKeys[0])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD7, 0, 0, 0);  
						keybd_event(VK_NUMPAD7, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
					else if (pStruct->vkCode == changeKeys[1])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD8, 0, 0, 0);  
						keybd_event(VK_NUMPAD8, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
					else if (pStruct->vkCode == changeKeys[2])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD4, 0, 0, 0);  
						keybd_event(VK_NUMPAD4, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
					else if (pStruct->vkCode == changeKeys[3])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD5, 0, 0, 0);  
						keybd_event(VK_NUMPAD5, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
					else if (pStruct->vkCode == changeKeys[4])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD1, 0, 0, 0);  
						keybd_event(VK_NUMPAD1, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
					else if (pStruct->vkCode == changeKeys[5])
					{
						bIsKeyDown = TRUE;  
						keybd_event(VK_NUMPAD2, 0, 0, 0);  
						keybd_event(VK_NUMPAD2, 0, KEYEVENTF_KEYUP, 0);  
						bIsKeyDown = FALSE; 
						
						return TRUE;
					}
				}//end Hooked
			}//war3.exe
		}
	}
	*/

	/*
	// 线程钩子回调函数 WH_KEYBOARD
	if (nCode == HC_ACTION)
	{
		if (wParam >= 0x08 && wParam <= 0x87 && wParam != VK_RETURN)
		{
			CString strTmp;
			strTmp.Format("wParam: 0x%x %d", wParam, wParam);
			OutputDebugString(strTmp);
			
			//pStruct->scanCode
			CString strNumAltered;// = g_ConfigInfo.GetNumAltered(wParam);
			if (!strNumAltered.IsEmpty())
			{
				OutputDebugString("strNumAltered:" + strNumAltered);
				
				wParam = VK_NUMPAD0 + atoi(strNumAltered);

				CString strMsg;
				DWORD dwPID = CProcessOperation::GetPIDByProcessName("AlterationSpiritDemo.exe");
				HWND hWnd = CProcessOperation::GetWndByPID(dwPID);
				strMsg.Format("PID:%d", dwPID);
				OutputDebugString(strMsg);
				strMsg.Format("hWnd:%p", hWnd);
				OutputDebugString(strMsg);

				::PostMessage(hWnd, WM_KEYDOWN, wParam, 0);
				
				//终止消息循环
				return TRUE;
			}
		}
	}
	*/

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

CHook::CHook()
{
	m_hookKeyboard = NULL;
	m_hDll = NULL;
	_lpFunc_HookKeyboardProc = NULL;
	_lpFunc_SetChangeKeys = NULL;

	LoadHookLibrary();
}

CHook::~CHook()
{
	if (NULL != m_hDll)
	{
		FreeLibrary(m_hDll);
	}
}

BOOL CHook::CreateHook(BYTE* data, UINT count)
{
	//全局键盘钩子
    //m_hookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookKeyboardHook, AfxGetInstanceHandle(), NULL);

	//线程键盘钩子
	//DWORD dwPID = CProcessOperation::GetPIDByProcessName(/*"war3.exe"*/"AlterationSpiritDemo.exe");
	//HMODULE hModule = GetProcessBase(dwPID);

	SetKeysAlteration(data, count);
	//m_hookKeyboard = ::SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)_lpFunc_HookKeyboardProc, m_hDll, NULL);
    if (m_hookKeyboard == NULL)
	{
		/*
		LPVOID lpv;    
		DWORD dwRv; 
		dwRv = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |    
			FORMAT_MESSAGE_FROM_SYSTEM,    
			NULL,    
			GetLastError(),    
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),    
			(LPSTR)&lpv,    
			0,    
        NULL);   

		CString strError;
		strError.Format("%s", (LPCSTR)lpv);
		OutputDebugString(strError); 
		
		if(dwRv)  
		{
			LocalFree(lpv);    
		}
		SetLastError(0); 
		*/

		DWORD dwError = GetLastError();
		CString strError;
		strError.Format("GetLastError():%d", dwError);
		OutputDebugString(strError);

		return FALSE;
	}
	
	return TRUE;
}

BOOL CHook::DestroyHook()
{		
	BOOL bKeyBoard = TRUE;
    if (m_hookKeyboard != NULL) 
	{
        bKeyBoard = UnhookWindowsHookEx(m_hookKeyboard);
        m_hookKeyboard = NULL;
    }
	
	return bKeyBoard;
}

void CHook::LoadHookLibrary()
{
	m_hDll = LoadLibrary("HookDll.dll");
	if (m_hDll != NULL)
	{
		_lpFunc_HookKeyboardProc = (lpFunc_HookKeyboardProc)GetProcAddress(m_hDll, "_HookKeyboardProc@12");
		_lpFunc_SetChangeKeys = (lpFunc_SetChangeKeys)GetProcAddress(m_hDll, "SetChangeKeys");
		if (_lpFunc_HookKeyboardProc == NULL || _lpFunc_SetChangeKeys == NULL)
		{
			AfxMessageBox("动态库函数寻址失败！");
		}
	}
	else
	{
		AfxMessageBox("动态库 HookDll.dll 加载失败！");
	}
}

void CHook::SetKeysAlteration(BYTE* data, UINT count)
{
	if (NULL != _lpFunc_SetChangeKeys)
	{
		_lpFunc_SetChangeKeys(data, count);
	}
}