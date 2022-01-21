// Hook.h: interface for the Hook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOK_H__21B670E2_8A2B_4320_A0BA_A381557A1349__INCLUDED_)
#define AFX_HOOK_H__21B670E2_8A2B_4320_A0BA_A381557A1349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//钩子回调函数
typedef void (*funCallBack) (INT nCode, WPARAM wParam, LPARAM lParam);

class CHook  
{
public:
	CHook();
	virtual ~CHook();

	BOOL CreateHook(BYTE* data, UINT count);
	BOOL DestroyHook();	
	void SetKeysAlteration(BYTE* data, UINT count);

protected:
	void LoadHookLibrary();
	
	typedef void (*lpFunc_SetChangeKeys)(BYTE* data, UINT count);
	typedef LRESULT (*lpFunc_HookKeyboardProc)(int nCode, WPARAM wParam, LPARAM lParam);
	lpFunc_SetChangeKeys _lpFunc_SetChangeKeys;
	lpFunc_HookKeyboardProc _lpFunc_HookKeyboardProc;
	
protected:
	HINSTANCE m_hDll;

private:	
	HHOOK m_hookKeyboard;
};

#endif // !defined(AFX_HOOK_H__21B670E2_8A2B_4320_A0BA_A381557A1349__INCLUDED_)
