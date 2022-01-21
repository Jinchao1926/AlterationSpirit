// AlterationSpirit.h : main header file for the ALTERATIONSPIRIT application
//

#if !defined(AFX_ALTERATIONSPIRIT_H__A856C8C4_B06B_45B7_91BF_059DA5551828__INCLUDED_)
#define AFX_ALTERATIONSPIRIT_H__A856C8C4_B06B_45B7_91BF_059DA5551828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritApp:
// See AlterationSpirit.cpp for the implementation of this class
//

class CAlterationSpiritApp : public CWinApp
{
public:
	CAlterationSpiritApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlterationSpiritApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAlterationSpiritApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALTERATIONSPIRIT_H__A856C8C4_B06B_45B7_91BF_059DA5551828__INCLUDED_)
