// ConfigInfo.h: interface for the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGINFO_H__F8D53B5B_4976_4C02_A531_E1B91ACD38AB__INCLUDED_)
#define AFX_CONFIGINFO_H__F8D53B5B_4976_4C02_A531_E1B91ACD38AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _MAX_STRING (256)

class CBaseConfigInfo  
{
public:
	CBaseConfigInfo();
	virtual ~CBaseConfigInfo();

	int  ReadIniFileInt(LPCSTR lpSectionName, LPCSTR lpKeyName, int nDefault);
	void WriteIniFileInt(LPCSTR lpSectionName, LPCSTR lpKeyName, int nDefault);

	BOOL ReadIniFileBool(LPCSTR lpSectionName, LPCSTR lpKeyName, BOOL bDefault);
	void WriteIniFileBool(LPCSTR lpSectionName, LPCSTR lpKeyName, BOOL bDefault);

	LPCSTR ReadIniFileString(LPCSTR lpSectionName, LPCSTR lpKeyName, LPCSTR lpDefault);
	void   WriteIniFileString(LPCSTR lpSectionName, LPCSTR lpKeyName, LPCSTR lpDefault);

protected:
	char m_szFileName[_MAX_PATH];
	char m_szPrifileString[_MAX_STRING];
//	CString m_strFileName;
};

#endif // !defined(AFX_CONFIGINFO_H__F8D53B5B_4976_4C02_A531_E1B91ACD38AB__INCLUDED_)
