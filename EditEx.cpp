// EditEx.cpp : implementation file
//

#include "stdafx.h"
#include "alterationspirit.h"
#include "EditEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditEx

CEditEx::CEditEx()
{
}

CEditEx::~CEditEx()
{
}


BEGIN_MESSAGE_MAP(CEditEx, CBCGPEdit)
	//{{AFX_MSG_MAP(CEditEx)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers

void CEditEx::SetText(CString strText)
{
	SetWindowText(strText);
	SetSel(strText.GetLength(), strText.GetLength());
}

void CEditEx::GetTextByte(BYTE& data)
{
	CString strText;
	GetWindowText(strText);
	if (strText.Compare("»»") == 0)
	{
		data = VK_TAB;
	}
	else if (strText.Compare("Ëø") == 0)
	{
		data = VK_CAPITAL;
	}
	else if (strText.Compare("¿Õ") == 0)
	{
		data = VK_SPACE;
	}
	else
	{
		data = *((BYTE*)strText.GetBuffer(0));
	}
}

BOOL CEditEx::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_TAB:	  SetText("»»"); return TRUE;
		case VK_CAPITAL:  SetText("Ëø"); return TRUE;
		case VK_SPACE:	  SetText("¿Õ"); return TRUE;
		case VK_F1:		  SetText("F1"); return TRUE;
		case VK_F2:		  SetText("F2"); return TRUE;
		case VK_F3:		  SetText("F3"); return TRUE;
		case VK_F4:		  SetText("F4"); return TRUE;
		case VK_F5:		  SetText("F5"); return TRUE;
		case VK_F6:		  SetText("F6"); return TRUE;
		case VK_F7:		  SetText("F7"); return TRUE;
		case VK_F8:		  SetText("F8"); return TRUE;
		case VK_F9:		  SetText("F9"); return TRUE;
		case VK_F10:	  SetText("F10"); return TRUE;
		default:
			/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
			/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */
			if (pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39 ||
				pMsg->wParam >= 0x41 && pMsg->wParam <= 0x5A)
			{
				SetWindowText("");
			}
			break;
		}
	}

	return CBCGPEdit::PreTranslateMessage(pMsg);
}


void CEditEx::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CORRECT_REGULAR, 0, LPARAM(this));
}
