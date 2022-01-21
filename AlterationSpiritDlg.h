// AlterationSpiritDlg.h : header file
//

#if !defined(AFX_ALTERATIONSPIRITDLG_H__7AC7392C_DC18_40C9_94E0_90F217E54C93__INCLUDED_)
#define AFX_ALTERATIONSPIRITDLG_H__7AC7392C_DC18_40C9_94E0_90F217E54C93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HookGlobal.h"
#include "EditEx.h"
/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDlg dialog

class CAlterationSpiritDlg : public CBCGPDialog
{
// Construction
public:
	CAlterationSpiritDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlterationSpiritDlg)
	enum { IDD = IDD_ALTERATIONSPIRIT_DIALOG };
	CEditEx	m_editNum8;
	CEditEx	m_editNum7;
	CEditEx	m_editNum5;
	CEditEx	m_editNum4;
	CEditEx	m_editNum2;
	CEditEx	m_editNum1;
	CString	m_strNum1;
	CString	m_strNum2;
	CString	m_strNum4;
	CString	m_strNum5;
	CString	m_strNum7;
	CString	m_strNum8;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlterationSpiritDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlterationSpiritDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSave();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnCorrectRegular(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTaskBarCreated(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM lParam); 
	afx_msg void OnTrayOpen();
	afx_msg void OnTrayExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void GetAlteration();
	void SetAlteration();

	void AddToTray();
	
//	void MapFog();

protected:
	CHookGlobal m_hookGlobal;

	BYTE m_changeKeys[6];
	BOOL m_bIsHooked;

	HANDLE m_hHandle;

private:
	// мпел
	NOTIFYICONDATA nd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALTERATIONSPIRITDLG_H__7AC7392C_DC18_40C9_94E0_90F217E54C93__INCLUDED_)
