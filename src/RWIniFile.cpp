///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ��дIni �����ļ�
/// @par ����ļ�
/// RWIniFile.cpp
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         RWIniFile.h
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RWIniFile.h"
#include "Common/CommonDef.h"


CRWIniFile::CRWIniFile()
{
	m_strFilePath = "";
}


CRWIniFile::~CRWIniFile()
{
}

CRWIniFile::CRWIniFile(const char* pszFilePath)
{
	m_strFilePath = "";
	e_InitRWFile(pszFilePath);
}


bool CRWIniFile::e_InitRWFile(const char* pszFilePath)
{
	if (NULL == pszFilePath || '\0' == pszFilePath)
	{
		return false;
	}

	if (e_CheckFileExist(pszFilePath))
	{
		m_strFilePath = pszFilePath;
		return true;
	}
	return false;
}

bool CRWIniFile::e_WriteConfigIntoFile(const char* pszConfigKey, const char* pszConfigName, const char* pszConfigValue)
{
	if (NULL == pszConfigKey)
	{
		return false;
	}

	if (NULL == pszConfigName || '\0' == pszConfigName)
	{
		return false;
	}

	if (NULL == pszConfigValue)
	{
		return false;
	}
	return (TRUE == WritePrivateProfileString(pszConfigKey, pszConfigName, pszConfigValue, m_strFilePath.c_str()));
}

string CRWIniFile::e_ReadConfigFromFile(const char* pszConfigKey, const char* pszConfigName)
{
	if (NULL == pszConfigKey)
	{
		return "";
	}

	if (NULL == pszConfigName || '\0' == pszConfigName)
	{
		return "";
	}
	// �����ȡ�ķ���ֵ
	char szConfigValue[256];
	memset(szConfigValue, 0x00, sizeof(szConfigValue));
	// ��ȡ�����ļ���
	GetPrivateProfileString(pszConfigKey, pszConfigName, "", szConfigValue, sizeof(szConfigValue) - 1, m_strFilePath.c_str());
	// ���ػ�ȡ��������Ϣ
	return szConfigValue;
}