// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9A68C624_0C02_4CE1_8BD9_1B69CF17252F__INCLUDED_)
#define AFX_STDAFX_H__9A68C624_0C02_4CE1_8BD9_1B69CF17252F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <BCGCBProInc.h>			// BCGPro Control Bar

//解决WM_MOUSE_LL未定义问题
//该宏和BCG头文件冲突
//#define _WIN32_WINNT  0x0500

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "ProcessOperation.h"
#include "ConfigInfo.h"
extern CConfigInfo g_ConfigInfo;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9A68C624_0C02_4CE1_8BD9_1B69CF17252F__INCLUDED_)
