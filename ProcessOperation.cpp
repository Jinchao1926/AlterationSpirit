// ProcessOperation.cpp: implementation of the CProcessOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "alterationspirit.h"
#include "ProcessOperation.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessOperation::CProcessOperation()
{

}

CProcessOperation::~CProcessOperation()
{

}

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)  
{  
    EnumFuncArgc *pArgc = (LPEnumFunArgc)lParam;     
    DWORD dwProcessId;  
    GetWindowThreadProcessId(hwnd, &dwProcessId);   
    if(dwProcessId == pArgc->dwProcessId)    
    {     
		// 回调函数返回FALSE，将停止枚举
        pArgc->hWnd = hwnd;  
        return FALSE;      
    }  
    return TRUE;     
}

//提升权限
BOOL CProcessOperation::ImproveProcPriv()
{
	HANDLE token;
	
	//提升权限
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		OutputDebugString("打开进程令牌失败");
		return FALSE;
	}
	
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	
	if (!AdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		OutputDebugString("调整令牌权限失败");
		return FALSE;
	}
	CloseHandle(token);
	return TRUE;
}

// 进程名、进程ID、进程句柄相关
DWORD CProcessOperation::GetPIDByProcessName(LPCTSTR lpProcessName)
{
	/*
	/  如果获取完整路径，请使用
	/  MODULEENTRY32 结构体和 Module32First 函数
	*/

	DWORD dwPID = 0;
	PROCESSENTRY32 process;

	// 获取系统内所有进程的快照
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	process.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapshot, &process))
	{
		return 0;
	}

	while(1)
	{
		process.dwSize = sizeof(PROCESSENTRY32);
		// 指向下一条进程信息
		if(!Process32Next(hSnapshot, &process))
		{
			break;
		}

		if(strcmp(process.szExeFile, lpProcessName) == 0)
		{
			dwPID = process.th32ProcessID;
			break;
		}	
	}

	CloseHandle(hSnapshot);
	return dwPID;
}

HMODULE CProcessOperation::GetProcessBase(DWORD PID)  
{  
    //获取进程基址  
    HANDLE hSnapShot;  
    //通过CreateToolhelp32Snapshot和线程ID，获取进程快照  
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);  
    if (hSnapShot == INVALID_HANDLE_VALUE)  
    {  
        return NULL;  
    }  

    MODULEENTRY32 ModuleEntry32;  
    ModuleEntry32.dwSize = sizeof(ModuleEntry32);  
    if (Module32First(hSnapShot, &ModuleEntry32))  
    {  
        do   
        {  
            TCHAR szExt[5];  
            strcpy(szExt, ModuleEntry32.szExePath + strlen(ModuleEntry32.szExePath) - 4);  
            for (int i = 0; i < 4; i++)  
            {  
                if ((szExt[i] >= 'a') && (szExt[i] <= 'z'))  
                {  
                    szExt[i] = szExt[i] - 0x20;  
                }  
            }  
            if (!strcmp(szExt, ".EXE"))  
            {  
                CloseHandle(hSnapShot);  
                return ModuleEntry32.hModule;  
            }  
        } 
		while (Module32Next(hSnapShot, &ModuleEntry32));  
    } 

    CloseHandle(hSnapShot);  
    return NULL;  
}  

DWORD CProcessOperation::GetDLLBase(char* DllName, DWORD dwPid)
{
	HANDLE snapMod;  
	MODULEENTRY32 me32;
	
	if (dwPid == 0) 
	{
		return 0;
	}
	snapMod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);  
	me32.dwSize = sizeof(MODULEENTRY32);  
	if (Module32First(snapMod, &me32))
	{ 
		do
		{
			if (lstrcmp(DllName, me32.szModule) == 0)
			{ 
				CloseHandle(snapMod); 
				return (DWORD) me32.modBaseAddr; 
			}
		}while(Module32Next(snapMod,&me32));
	}
	CloseHandle(snapMod); 
	return 0;  
}

HWND CProcessOperation::GetWndByPID(DWORD dwPID)  
{  
	HWND hWnd = NULL;    
	EnumFuncArgc enumFuncArgc;    
    enumFuncArgc.dwProcessId = dwPID;    
    enumFuncArgc.hWnd = NULL;    
    EnumWindows(lpEnumFunc, (LPARAM)&enumFuncArgc); 
	if(enumFuncArgc.hWnd)
	{     
		hWnd = enumFuncArgc.hWnd;  
	}   
	
	return hWnd;  
}