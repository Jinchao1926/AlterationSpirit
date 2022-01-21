// ProcessOperation.h: interface for the CProcessOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSOPERATION_H__7A79B82C_0098_4FB7_9B28_6B416AFFB6E5__INCLUDED_)
#define AFX_PROCESSOPERATION_H__7A79B82C_0098_4FB7_9B28_6B416AFFB6E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct EnumFuncArgc  
{     
    HWND  hWnd;  
    DWORD dwProcessId;     
}EnumFuncArgc, *LPEnumFunArgc;  

class CProcessOperation  
{
public:
	CProcessOperation();
	virtual ~CProcessOperation();

	// 提示权限
	static BOOL ImproveProcPriv();

	// 进程名、进程ID、进程句柄相关
	static DWORD GetPIDByProcessName(LPCTSTR lpProcessName);

	static HMODULE GetProcessBase(DWORD PID);
	static DWORD GetDLLBase(char* DllName, DWORD dwPid);
	static HWND GetWndByPID(DWORD dwPID);

	

};

#endif // !defined(AFX_PROCESSOPERATION_H__7A79B82C_0098_4FB7_9B28_6B416AFFB6E5__INCLUDED_)
