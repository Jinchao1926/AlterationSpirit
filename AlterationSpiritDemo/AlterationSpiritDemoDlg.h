// AlterationSpiritDemoDlg.h : header file
//

#if !defined(AFX_ALTERATIONSPIRITDEMODLG_H__DE311535_654C_4F4C_A514_ABC91CBDC23C__INCLUDED_)
#define AFX_ALTERATIONSPIRITDEMODLG_H__DE311535_654C_4F4C_A514_ABC91CBDC23C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAlterationSpiritDemoDlg dialog

class CAlterationSpiritDemoDlg : public CDialog
{
// Construction
public:
	CAlterationSpiritDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlterationSpiritDemoDlg)
	enum { IDD = IDD_ALTERATIONSPIRITDEMO_DIALOG };
	CListBox	m_lsbLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlterationSpiritDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlterationSpiritDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALTERATIONSPIRITDEMODLG_H__DE311535_654C_4F4C_A514_ABC91CBDC23C__INCLUDED_)
