// HookGlobal.cpp: implementation of the CHookGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "alterationspirit.h"
#include "HookGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHookGlobal::CHookGlobal()
{
	m_hDll = NULL;

	_lpFunc_SetHook = NULL;
	_lpFunc_DestroyHook = NULL;

	LoadHookLibrary();
}

CHookGlobal::~CHookGlobal()
{
	if (NULL != m_hDll)
	{
		FreeLibrary(m_hDll);
	}
}

void CHookGlobal::LoadHookLibrary()
{
	m_hDll = LoadLibrary("HookDll.dll");
	if (m_hDll != NULL)
	{
		_lpFunc_SetHook = (lpFunc_SetHook)GetProcAddress(m_hDll, "SetHook");
		_lpFunc_DestroyHook = (lpFunc_DestroyHook)GetProcAddress(m_hDll, "DestroyHook");
		_lpFunc_SetChangeKeys = (lpFunc_SetChangeKeys)GetProcAddress(m_hDll, "SetChangeKeys");
		if (_lpFunc_SetHook == NULL || _lpFunc_DestroyHook == NULL || _lpFunc_SetChangeKeys == NULL)
		{
			AfxMessageBox("¶¯Ì¬¿âº¯ÊýÑ°Ö·Ê§°Ü£¡");
		}
	}
	else
	{
		AfxMessageBox("¶¯Ì¬¿â HookDll.dll ¼ÓÔØÊ§°Ü£¡");
	}
}

void CHookGlobal::CreateDllHook(HANDLE hHandle, BYTE* data, UINT count)
{
	if (NULL != _lpFunc_SetHook)
	{
		_lpFunc_SetHook(hHandle, data, count);
	}
}

void CHookGlobal::DestroyDllHook()
{
	if (NULL != _lpFunc_DestroyHook)
	{
		_lpFunc_DestroyHook();
	}
}

void CHookGlobal::SetKeysAlteration(BYTE* data, UINT count)
{
	if (NULL != _lpFunc_SetChangeKeys)
	{
		_lpFunc_SetChangeKeys(data, count);
	}
}
