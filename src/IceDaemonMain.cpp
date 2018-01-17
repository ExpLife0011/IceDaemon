////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// �����������
/// @par ����ļ�
/// DeamonService.h
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         IceDaemonMain.cpp
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DaemonService.h"
#include "DaemonServiceDef.h"


using namespace ICEDAEMON;

#ifndef _DEBUG
void main(int argc, char* argv[])
{
	/// ���õ�ǰ����Ŀ¼
	e_SetCurDirectory();
	// ���ö�ȡ�������ļ�
	CRWIniFile rwIniFile;
	rwIniFile.e_InitRWFile(CONFIG_FILE_NAME);
	// �ַ�����������
	string strServiceName = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_NAME_KEY);
	// �ַ���������������
	string strServiceDis = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_DISPLAY);
	char szServiceName[128];
	memset(szServiceName, 0x00, sizeof(szServiceName));
	strncpy(szServiceName, strServiceName.c_str(), sizeof(szServiceName) - 1);

	// ע�����
	SERVICE_TABLE_ENTRY DispatchTable[] =
	{
		// ��������
		{ szServiceName, (LPSERVICE_MAIN_FUNCTION)CDaemonService::e_ServiceMain },
		// ������Ϣ
		{ NULL, NULL }
	};
	
	CDaemonService CThisService;
	CThisService.e_IniConfig(strServiceName.c_str(), strServiceDis.c_str(), &rwIniFile);
	if(false == CThisService.e_ParseStandardArgs(argc, argv))
	{
		/// ��������Ŀ��Ʒ��ɻ��߳�
		if(FALSE == StartServiceCtrlDispatcher(DispatchTable))
		{
			CDaemonService::e_LogEvent(EVENTLOG_ERROR_TYPE, "StartServiceCtrlDispatcher Fails...");
		}
	}
}

#else

int main(int argc, char* argv[])
{
	/// ���õ�ǰ����Ŀ¼
	e_SetCurDirectory();

	// ���ö�ȡ�������ļ�
	CRWIniFile rwIniFile;
	rwIniFile.e_InitRWFile(CONFIG_FILE_NAME);
	// �ַ�����������
	string strServiceName = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_NAME_KEY);
	// �ַ�����������
	string strServiceDis = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_DISPLAY);

	/// ���������ö���
	CProcessMonitor processMonitor;
	// ��ȡִ���ļ�������Ϣ
	string strExecName = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_NAME);
	string strExecPath = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_PATH);
	string strExecArgv = rwIniFile.e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_ARGV);
	/// ��ʼ����������
	if(true == processMonitor.e_StartMonitor(strExecName.c_str(), strExecPath.c_str(), strExecArgv.c_str()))
	{
		char szchar;
		memset(&szchar, 0x00, sizeof(szchar));
		while(szchar = getchar())
		{
			if('0' == szchar)
			{
				// ֹͣ����
				processMonitor.e_StopProcessRun();
				break;
			}
		}
	}
	return 0;
}
#endif
