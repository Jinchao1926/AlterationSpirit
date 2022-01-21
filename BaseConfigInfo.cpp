// ConfigInfo.cpp: implementation of the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlterationSpirit.h"
#include "ConfigInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseConfigInfo::CBaseConfigInfo()
{
	char path_buffer[_MAX_PATH] = {0};
	char drive[_MAX_DRIVE] = {0};
	char dir[_MAX_DIR] = {0};
	char fname[_MAX_FNAME] = {0};
	char ext[_MAX_EXT] = {0};
	
	GetModuleFileName(NULL, path_buffer, _MAX_PATH);
	
	//void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
	_splitpath(path_buffer, drive, dir, fname, ext);
	
//	m_strFileName.Format("%s\\%s%s.ini", drive, dir, fname);
	memset(m_szFileName, 0, _MAX_PATH);
	sprintf(m_szFileName, "%s%s%s.ini", drive, dir, fname);
}

CBaseConfigInfo::~CBaseConfigInfo()
{
	
}

int CBaseConfigInfo::ReadIniFileInt(LPCSTR lpSectionName, LPCSTR lpKeyName, int nDefault)
{
	return GetPrivateProfileInt(lpSectionName, lpKeyName, nDefault, m_szFileName);
}
	
void CBaseConfigInfo::WriteIniFileInt(LPCSTR lpSectionName, LPCSTR lpKeyName, int nDefault)
{
	CString strDefault;
	strDefault.Format("%d", nDefault);

	WritePrivateProfileString(lpSectionName, lpKeyName, strDefault, m_szFileName);
}

BOOL CBaseConfigInfo::ReadIniFileBool(LPCSTR lpSectionName, LPCSTR lpKeyName, BOOL bDefault)
{
	return ReadIniFileInt(lpSectionName, lpKeyName, bDefault);
}
void CBaseConfigInfo::WriteIniFileBool(LPCSTR lpSectionName, LPCSTR lpKeyName, BOOL bDefault)
{
	WriteIniFileInt(lpSectionName, lpKeyName, bDefault);
}

LPCSTR CBaseConfigInfo::ReadIniFileString(LPCSTR lpSectionName, LPCSTR lpKeyName, LPCSTR lpDefault)
{
	memset(m_szPrifileString, NULL, _MAX_STRING);
	GetPrivateProfileString(lpSectionName, lpKeyName, lpDefault, m_szPrifileString, _MAX_STRING, m_szFileName);

	return m_szPrifileString;
}
void CBaseConfigInfo::WriteIniFileString(LPCSTR lpSectionName, LPCSTR lpKeyName, LPCSTR lpDefault)
{
	WritePrivateProfileString(lpSectionName, lpKeyName, lpDefault, m_szFileName);
}