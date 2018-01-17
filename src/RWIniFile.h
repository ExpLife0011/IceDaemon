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

#ifndef __ICE_DAEMON_RWFINIILE_H_H__
#define __ICE_DAEMON_RWFINIILE_H_H__

#include "Common/CommTypes.h"

class CRWIniFile
{
public:
	// Ĭ�Ϲ��캯��
	CRWIniFile();

	// Ĭ����������
	virtual ~CRWIniFile();

	/// ==============================================
	/// @par ���� 
	/// ��д���캯��
	/// @param 
	/// [in,out]	<������>		<����˵��>
	///	[in]		pszFilePath		�����ļ�·��	
	/// @return 	-
	/// @note 		Creat By li.xl 2018/01/15 
	/// ==============================================
	CRWIniFile(const char* pszFilePath);

	/// ==============================================
	/// @par ���� 
	/// ��ʼ���ļ�Ҫ��ȡ�����ļ�·��
	/// @param 
	/// [in,out]	<������>		<����˵��>
	///	[in]		pszFilePath		�����ļ�·��
	/// @return 	-
	/// @note 		Creat By li.xl 2018/01/15 
	/// ==============================================
	bool e_InitRWFile(const char* pszFilePath);

	/// ==============================================
	/// @par ���� 
	/// д�������ļ�
	/// @param 
	/// [in,out]	<������>		<����˵��>
	///	[in]		pszConfigKey	���ùؼ���
	/// [in]		pszConfigName	��������
	/// [in]		pszConfigValue	����ֵ
	/// @return 	-
	/// @note 		Creat By li.xl 2018/01/15 
	/// ==============================================
	bool e_WriteConfigIntoFile(const char* pszConfigKey, const char* pszConfigName, const char* pszConfigValue);

	/// ==============================================
	/// @par ���� 
	/// ��ȡ�����ļ��ؼ���
	/// @param 
	/// [in,out]	<������>		<����˵��>
	///	[in]		pszConfigKey	���ùؼ���
	/// [in]		pszConfigName	��������
	/// @return 	-
	/// @note 		Creat By li.xl 2018/01/15 
	/// ==============================================
	string e_ReadConfigFromFile(const char* pszConfigKey, const char* pszConfigName);

private:
	// �����ļ�·��
	string		m_strFilePath;

};

#endif // __ICE_DAEMON_RWFINIILE_H_H__

