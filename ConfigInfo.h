// ConfigInfo.h: interface for the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGINFO_H__91741992_B918_4D8F_A069_D993A9A0947F__INCLUDED_)
#define AFX_CONFIGINFO_H__91741992_B918_4D8F_A069_D993A9A0947F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseConfigInfo.h"

class CConfigInfo : public CBaseConfigInfo
{
public:
	CConfigInfo();
	virtual ~CConfigInfo();

	//改建
	CString GetAlteration(int nPlan, int nNum);
	void    SetAlteration(int nPlan, int nNum, CString strVal);

 	//获取设置改建的数字键 1.2.4.5.7.8
// 	CString GetNumAltered(DWORD VK);
 	//获取改建设置规则 Q(ASCII)-数字键1
// 	void GetMapAlteration();

protected:
//	CMapStringToString m_mapAlteration;
};

#endif // !defined(AFX_CONFIGINFO_H__91741992_B918_4D8F_A069_D993A9A0947F__INCLUDED_)
