#if !defined(AFX_EDITEX_H__F8A29C87_75C2_4A4B_9045_CCC412B87468__INCLUDED_)
#define AFX_EDITEX_H__F8A29C87_75C2_4A4B_9045_CCC412B87468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditEx window

#define WM_CORRECT_REGULAR	(WM_USER + 200)

class CEditEx : public CBCGPEdit
{
// Construction
public:
	CEditEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditEx)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void SetText(CString strText);
	void GetTextByte(BYTE& data);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEX_H__F8A29C87_75C2_4A4B_9045_CCC412B87468__INCLUDED_)
