// HookDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE HookDllDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("HOOKDLL.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(HookDllDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(HookDllDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("HOOKDLL.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(HookDllDLL);
	}

	return 1;   // ok
}

HHOOK  g_HookKeyBoard = NULL;
HANDLE g_HandleDest = NULL;
//HWND  g_HWndDest = NULL;

// 动态数组，保存改建规则
// 对应数字键7/8/4/5/1/2
BYTE* changeKeys = NULL;
UINT keysCount = 0;

BOOL bIsKeyDown = FALSE;
BOOL bIsHooked = TRUE;

//char path[_MAX_PATH] = {0};
char name[_MAX_FNAME] = {0};

BOOL IsChatting(HANDLE hHandle)
{
	if (hHandle == NULL)
	{
		return FALSE;
	}

	CString strMsg;

	// Get War3 Version
	DWORD dwVersion;
	ReadProcessMemory(hHandle, (LPVOID)0x0047AFD0, (LPVOID)&dwVersion, 4, NULL);	//0x6989787A

	LPVOID lpBase = NULL;
	if (dwVersion == 0x6989787A)
	{
		//1.24
		lpBase = (LPVOID)0x6FAE8450;
	}
	else
	{
		//1.20
		lpBase = (LPVOID)0x0045cb8C;
	}

	// Get Chatting Flag. 1-TRUE 0-FALSE
	BYTE data;
	BOOL bSucc = ReadProcessMemory(hHandle, lpBase, (LPVOID)&data, 4, NULL);

	return (data == 1);
}

//extern "C" _declspec(dllexport)
LRESULT CALLBACK HookKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	// 线程钩子回调函数 WH_KEYBOARD_LL
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN && !bIsKeyDown)
		{
// 			memset(path, 0, _MAX_PATH);
// 			GetModuleFileName(NULL, path, _MAX_PATH);
//			HMODULE hModule = (HMODULE)GetClassLong(GetForegroundWindow(), GCL_HMODULE);
// 			OutputDebugString(path);
			
			memset(name, 0, _MAX_FNAME);
			GetWindowText(GetForegroundWindow(), name, _MAX_FNAME);
			//OutputDebugString(name);

			// Only Hook war3.exe
			//if (strstr(path, "war3.exe") != NULL)
			if (strstr(name, "Warcraft III") != NULL && !IsChatting(g_HandleDest))
			{
				// Cheat Engine这个软件，通过不断调出和关闭聊天条来查找内存中的1或0
				// 智能识别改键是通过读取魔兽的内存0045cb8c处的偏移，1-聊天模式，0-操作模式
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
						
						/*
						//pStruct->scanCode
						//::PostMessage(g_HWndDest, WM_KEYDOWN, wParam, 0);	
						//终止消息循环
						return TRUE;
						*/
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

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

extern "C" _declspec(dllexport)
void SetChangeKeys(BYTE* data, UINT count)
{
	if (NULL == changeKeys)
	{
		changeKeys = new BYTE[count];
	}
	
	for (UINT i = 0; i < count; i++)
	{
		changeKeys[i] = data[i];
	}
	keysCount = count;
}

// 创建全局钩子
extern "C" _declspec(dllexport)
BOOL SetHook(HANDLE hHandle, BYTE* data, UINT count)
{
	g_HandleDest = hHandle;

	HINSTANCE hInst = GetModuleHandle("HookDll.dll");
	g_HookKeyBoard = ::SetWindowsHookEx(WH_KEYBOARD_LL, HookKeyboardProc, hInst, NULL);
	if (g_HookKeyBoard == NULL)
	{
		CString strMsg;
		strMsg.Format("LastError:%d", GetLastError());
		OutputDebugString(strMsg);
	}

	// save regular
	SetChangeKeys(data, count);
	
	return (g_HookKeyBoard != NULL);
}

//销毁钩子
extern "C" _declspec(dllexport)
void DestroyHook()
{
	if (NULL != g_HookKeyBoard) 
	{
		UnhookWindowsHookEx(g_HookKeyBoard);
		g_HookKeyBoard = NULL;
		g_HandleDest = NULL;

		delete[] changeKeys;
		keysCount = 0;
    }
}

