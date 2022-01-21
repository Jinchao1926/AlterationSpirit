// HookGlobal.h: interface for the CHookGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOKGLOBAL_H__83F3418A_3D6A_4201_BAD2_380C54CD6130__INCLUDED_)
#define AFX_HOOKGLOBAL_H__83F3418A_3D6A_4201_BAD2_380C54CD6130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHookGlobal  
{
public:
	CHookGlobal();
	virtual ~CHookGlobal();

	void CreateDllHook(HANDLE hHandle, BYTE* data, UINT count);
	void DestroyDllHook();

	void SetKeysAlteration(BYTE* data, UINT count);

protected:
	void LoadHookLibrary();

	typedef BOOL (*lpFunc_SetHook)(HANDLE hHandle, BYTE* data, UINT count);
	typedef void (*lpFunc_DestroyHook)();
	typedef void (*lpFunc_SetChangeKeys)(BYTE* data, UINT count);
	lpFunc_SetHook _lpFunc_SetHook;
	lpFunc_DestroyHook _lpFunc_DestroyHook;
	lpFunc_SetChangeKeys _lpFunc_SetChangeKeys;

protected:
	HINSTANCE m_hDll;
};

#endif // !defined(AFX_HOOKGLOBAL_H__83F3418A_3D6A_4201_BAD2_380C54CD6130__INCLUDED_)
