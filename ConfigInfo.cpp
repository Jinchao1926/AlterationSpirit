// ConfigInfo.cpp: implementation of the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConfigInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfigInfo g_ConfigInfo;

CConfigInfo::CConfigInfo()
{

}

CConfigInfo::~CConfigInfo()
{

}

CString CConfigInfo::GetAlteration(int nPlan, int nNum)
{
	if (nPlan < 1)
	{
		nPlan = 1;
	}
	if (nPlan > 10)
	{
		nPlan = 10;
	}

	CString strKey;
	CString strSection;
	strSection.Format("Game%d", nPlan);
	strKey.Format("num%d", nNum);

	return ReadIniFileString(strSection, strKey, "");
}

void CConfigInfo::SetAlteration(int nPlan, int nNum, CString strVal)
{
	if (nPlan < 1)
	{
		nPlan = 1;
	}
	if (nPlan > 10)
	{
		nPlan = 10;
	}
	
	CString strKey;
	CString strSection;
	strSection.Format("Game%d", nPlan);
	strKey.Format("num%d", nNum);
	
	WriteIniFileString(strSection, strKey, strVal);
}

/*
//获取设置改建的数字键
CString CConfigInfo::GetNumAltered(DWORD VK)
{
	CString strKey;
	strKey.Format("%d", VK);

	CString strNumAltered;
	m_mapAlteration.Lookup(strKey, strNumAltered);

	return strNumAltered;
}

void CConfigInfo::GetMapAlteration()
{
	m_mapAlteration.RemoveAll();
	for (int i = 1; i <= 8 ; i++)
	{
		CString strKey = GetAlteration(1, i);
		if (!strKey.IsEmpty())
		{
			char cKey = strKey.GetAt(0);
			strKey.Format("%d", cKey);		//ASCII
			CString strVal;
			strVal.Format("%d", i);

			m_mapAlteration.SetAt(strKey, strVal);	//Q(ASCII) - 1
		}
	}

	for (POSITION pos = m_mapAlteration.GetStartPosition(); pos != NULL; )
	{
		CString strKey;
		CString strVal;
		m_mapAlteration.GetNextAssoc(pos, strKey, strVal);

		CString strMsg;
		strMsg.Format("%s - %s", strKey, strVal);
		OutputDebugString(strMsg);
	}
}
*/