// AlterationSpiritDemo.h : main header file for the ALTERATIONSPIRITDEMO application
//

#if !defined(AFX_ALTERATIONSPIRITDEMO_H__6F3CBA76_595A_4B90_B4FB_C5C859189B3E__INCLUDED_)
#define AFX_ALTERATIONSPIRITDEMO_H__6F3CBA76_595A_4B90_B4FB_C5C859189B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDemoApp:
// See AlterationSpiritDemo.cpp for the implementation of this class
//

class CAlterationSpiritDemoApp : public CWinApp
{
public:
	CAlterationSpiritDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlterationSpiritDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAlterationSpiritDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALTERATIONSPIRITDEMO_H__6F3CBA76_595A_4B90_B4FB_C5C859189B3E__INCLUDED_)
