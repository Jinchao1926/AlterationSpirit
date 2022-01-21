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
		// �ص���������FALSE����ֹͣö��
        pArgc->hWnd = hwnd;  
        return FALSE;      
    }  
    return TRUE;     
}

//����Ȩ��
BOOL CProcessOperation::ImproveProcPriv()
{
	HANDLE token;
	
	//����Ȩ��
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		OutputDebugString("�򿪽�������ʧ��");
		return FALSE;
	}
	
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	
	if (!AdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		OutputDebugString("��������Ȩ��ʧ��");
		return FALSE;
	}
	CloseHandle(token);
	return TRUE;
}

// ������������ID�����̾�����
DWORD CProcessOperation::GetPIDByProcessName(LPCTSTR lpProcessName)
{
	/*
	/  �����ȡ����·������ʹ��
	/  MODULEENTRY32 �ṹ��� Module32First ����
	*/

	DWORD dwPID = 0;
	PROCESSENTRY32 process;

	// ��ȡϵͳ�����н��̵Ŀ���
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	process.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapshot, &process))
	{
		return 0;
	}

	while(1)
	{
		process.dwSize = sizeof(PROCESSENTRY32);
		// ָ����һ��������Ϣ
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
    //��ȡ���̻�ַ  
    HANDLE hSnapShot;  
    //ͨ��CreateToolhelp32Snapshot���߳�ID����ȡ���̿���  
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