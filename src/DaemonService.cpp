////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ����ģ��ͷ�ļ�
/// @par ����ļ�
/// CDaemonService.h
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         CDaemonService.cpp
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DaemonService.h"
#include "DaemonServiceDef.h"

namespace ICEDAEMON
{
	CDaemonService* pThisService = NULL;
	CDaemonService::CDaemonService()
	{
		pThisService = this;
		m_hSvcStopEvent = NULL;
		m_pRWIniFile = NULL;
		m_strServiceName = "";
	}

	CDaemonService::~CDaemonService()
	{
		m_pRWIniFile = NULL;
		m_strServiceName = "";
	}

	void WINAPI CDaemonService::e_ServiceMain(DWORD dwArgc, LPSTR* lpszArgv)
	{
		/// ��֤���ݺϷ���
		if(NULL == pThisService)
		{
			CDaemonService::e_LogEvent(EVENTLOG_ERROR_TYPE, "e_ServiceMain pThisService Is Null");
			return;
		}

		/// Ϊ����ע��֪ͨ����
		pThisService->m_SvcStatusHandle = ::RegisterServiceCtrlHandler(pThisService->m_strServiceName.c_str(), e_SvcCtrlHandler);
		if(!pThisService->m_SvcStatusHandle)
		{
			CDaemonService::e_LogEvent(EVENTLOG_ERROR_TYPE, "RegisterServiceCtrlHandler");
			return;
		}

		/// ֻ��һ�������ķ���
		pThisService->m_SvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		pThisService->m_SvcStatus.dwServiceSpecificExitCode = 0;
		/// �ϱ���ʼ��״̬�����������
		pThisService->e_ReportSvcStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

		/// ��������ֹͣ�¼�
		pThisService->m_hSvcStopEvent = CreateEvent(
			NULL,    // default security attributes
			TRUE,    // manual reset event
			FALSE,   // not signaled
			NULL);   // no name

		/// �¼�����ʧ�ܷ��أ���֪ͨ Windows ֹͣ����
		if(NULL == pThisService->m_hSvcStopEvent)
		{
			pThisService->e_ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
			return;
		}
		/// ���з���
		pThisService->e_ServerProgram(dwArgc, lpszArgv);
		/// �ϱ�����ֹͣ״̬
		pThisService->e_ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
	}

	/// ����������
	bool CDaemonService::e_ServerProgram(DWORD dwArgc, LPSTR* lpszArgv)
	{
		/// ���������ö���
		CProcessMonitor processMonitor;
		// ��ȡִ���ļ�������Ϣ
		string strExecName = m_pRWIniFile->e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_NAME);
		string strExecPath = m_pRWIniFile->e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_PATH);
		string strExecArgv = m_pRWIniFile->e_ReadConfigFromFile(SERVICE_MOUDLE_KEY, SERVICE_EXEC_ARGV);
		/// ��ʼ����������
		if(true == processMonitor.e_StartMonitor(strExecName.c_str(), strExecPath.c_str(), strExecArgv.c_str()))
		{
			/// ��������ʧ��
			e_ServiceRun();
			/// ����ֹͣʱ, ֹͣ��Ҫ�ػ��Ľ���
			processMonitor.e_StopProcessRun();
		}
		else
		{
			/// ��������ʧ��
			CDaemonService::e_LogEvent(EVENTLOG_ERROR_TYPE, "e_ServerProgram pThisService Start Fails.");
		}		
		return true;
	}

	void CDaemonService::e_ServiceRun()
	{
		while(1)
		{
			/// �ϱ���������״̬
			e_ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);
			/// ��֤����
			::WaitForSingleObject(m_hSvcStopEvent, INFINITE);
			return;
		}
	}

	void CDaemonService::e_ReportSvcStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
	{
		static DWORD dwCheckPoint = 1;
		/// ��ֵ����״̬��Ϣ
		m_SvcStatus.dwCurrentState = dwCurrentState;
		m_SvcStatus.dwWin32ExitCode = dwWin32ExitCode;
		m_SvcStatus.dwWaitHint = dwWaitHint;
		/// ��ֵ����״̬
		if(SERVICE_START_PENDING == dwCurrentState)
		{
			m_SvcStatus.dwControlsAccepted = 0;
		}
		else
		{
			m_SvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
		}

		/// �����ϱ�����
		if((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED))
		{
			m_SvcStatus.dwCheckPoint = 0;
		}
		else
		{
			m_SvcStatus.dwCheckPoint = dwCheckPoint++;
		}

		/// �ϱ�����״̬��Ϣ
		::SetServiceStatus(m_SvcStatusHandle, &m_SvcStatus);
	}

	void WINAPI CDaemonService::e_SvcCtrlHandler(DWORD dwCtrl)
	{
		/// ��������ź�
		switch(dwCtrl)
		{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			{
				/// ��ӡ��Ϣ
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "Rev Stop OR Shutdown Message.");
				/// �ϱ�����ֹͣ��
				pThisService->e_ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
				// ��ӡ�¼�
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "%s Service Stoping1 CtrlEvenType = %ld", pThisService->m_strServiceName.c_str(), dwCtrl);
				/// ����ֹͣ�����ź���
				::SetEvent(pThisService->m_hSvcStopEvent);
				return;
			}
		case SERVICE_CONTROL_PRESHUTDOWN:
		case SERVICE_CONTROL_PAUSE:
			{
				/// ��ӡ��Ϣ
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "Rev PAUSE Or PRESHUTDOWN Message.");
				/// �ϱ�����ֹͣ��
				pThisService->e_ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
				// ��ӡ�¼�
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "%s Service Stoping2 CtrlEvenType = %ld", pThisService->m_strServiceName.c_str(), dwCtrl);
				/// ����ֹͣ�����ź���
				::SetEvent(pThisService->m_hSvcStopEvent);
				return;
			}

		case SERVICE_CONTROL_CONTINUE:
			{
				/// ��ӡ��Ϣ
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "e_SvcCtrlHandler Rev Stop Message.");
				/// �ϱ�����ֹͣ��
				pThisService->e_ReportSvcStatus(SERVICE_CONTINUE_PENDING, NO_ERROR, 0);
				// ��ӡ�¼�
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "%s Service Continue3 CtrlEvenType = %ld", pThisService->m_strServiceName.c_str(), dwCtrl);
				/// ����ֹͣ�����ź���
				// ::SetEvent(pThisService->m_hSvcStopEvent);
				return;
			}
		case SERVICE_CONTROL_INTERROGATE: 
			{
				/// ��ӡ��Ϣ
				CDaemonService::e_LogEvent(EVENTLOG_INFORMATION_TYPE, "%s �ϱ���ǰ����״̬", pThisService->m_strServiceName.c_str());
				/// ���ʣ���Ҫ���浱ǰ����״̬
				pThisService->e_ReportSvcStatus(pThisService->m_SvcStatus.dwCurrentState, NO_ERROR, 0);
				break;
			}
		default:
			/// Ĭ��Ҳ�ϱ�һ�µ�ǰ����״̬
			pThisService->e_ReportSvcStatus(pThisService->m_SvcStatus.dwCurrentState, NO_ERROR, 0);
			break;
		}		
	}

	void CDaemonService::e_LogEvent(WORD wType, const char* pszFormat, ...)
	{
		HANDLE hEventSource;
		LPCTSTR lpszStrings[2];
		/// ���󻺳�
		const UINT LOG_EVENT_MSG_SIZE = 1024;
		char szBuffer[LOG_EVENT_MSG_SIZE] = {0};
		/// Format����
		va_list argptr;
		va_start(argptr, pszFormat);
		// ����Ҫ��va_start���ʼ������
		memset(szBuffer, 0x00, LOG_EVENT_MSG_SIZE);
		vsnprintf_s(szBuffer, LOG_EVENT_MSG_SIZE - 1, pszFormat, argptr);
		va_end(argptr);

		/// �����ϱ���Դ
		hEventSource = RegisterEventSource(NULL, pThisService->m_strServiceName.c_str());
		if(NULL != hEventSource)
		{
			lpszStrings[0] = pThisService->m_strServiceName.c_str();
			lpszStrings[1] = szBuffer;

			ReportEvent(hEventSource,// event log handle
				wType,				 // event type /// EVENTLOG_INFORMATION_TYPE | EVENTLOG_ERROR_TYPE
				0,                   // event category
				SVC_ERROR,           // event identifier Or 0
				NULL,                // no security identifier
				2,                   // size of lpszStrings array
				0,                   // no binary data
				lpszStrings,         // array of strings
				NULL);               // no binary data
			DeregisterEventSource(hEventSource);
		}
	}

	bool CDaemonService::e_IsInstalled()
	{
		bool bResult = false;
		/// �򿪷��������,��������ɹ�������ֵ��һ��ָ���ķ�����ƹ��������ݿ�ľ�����������ʧ�ܣ�����ֵΪNULL

		SC_HANDLE hSCM = ::OpenSCManager(NULL,	// local machine(��һ������Ϊ�ձ�ʾ���ӱ��ط��������)
			NULL,								// ServicesActive database(ָ����Ҫ�򿪵ķ�����ƹ������ݿ������,�����ָ��ΪNULL,���Ĭ�ϵ�SERVICES_ACTIVE_DATABASE)
			SC_MANAGER_ALL_ACCESS);				// full access(ָ��������ʿ��ƹ�������Ȩ�ޡ�)

		if(hSCM)
		{
			// Try to open the service
			SC_HANDLE hService = ::OpenService(hSCM,
				(LPCSTR)m_strServiceName.c_str(),
				SERVICE_QUERY_CONFIG);
			if(hService)
			{
				bResult = true;
				::CloseServiceHandle(hService);
			}
			::CloseServiceHandle(hSCM);
		}
		return bResult;
	}

	bool CDaemonService::e_Install()
	{
		/// �򿪷��������
		SC_HANDLE hSCM = ::OpenSCManager(NULL,	// local machine
			NULL,								// ServicesActive database
			SC_MANAGER_ALL_ACCESS);				// full access
		if(!hSCM)
		{
			return false;
		}

		/// ��ȡ��ǰ·��
		TCHAR szFilePath[_MAX_PATH];
		::GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));

		// ��������
		SC_HANDLE hService = ::CreateService(hSCM,
			(LPCSTR)m_strServiceName.c_str(),
			(LPCSTR)m_strServiceName.c_str(),
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,	//SERVICE_INTERACTIVE_PROCESS�����潻��
			SERVICE_AUTO_START,											//SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			(LPCSTR)szFilePath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

		if(!hService)
		{
			::CloseServiceHandle(hSCM);
			return false;
		}

		/// д��ע���
		char szKey[256];
		HKEY hKey = NULL;
		strcpy_s(szKey, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
		strcat_s(szKey, m_strServiceName.c_str());
		if (::RegCreateKey(HKEY_LOCAL_MACHINE, (LPCSTR)szKey, &hKey) != ERROR_SUCCESS) {
			::CloseServiceHandle(hService);
			::CloseServiceHandle(hSCM);
			return false;
		}
		/// ���ü�ֵ
		::RegSetValueEx(hKey,
			"EventMessageFile",
			0,
			REG_EXPAND_SZ, 
			(const BYTE *)&szFilePath,
			strlen(szFilePath)*2 + 1);

		// Set the supported types flags.
		DWORD dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;
		::RegSetValueEx(hKey,
			"TypesSupported",
			0,
			REG_DWORD,
			(CONST BYTE*)&dwData,
			sizeof(DWORD));
		::RegCloseKey(hKey);

		char szTempServiceDis[256];
		memset(szTempServiceDis, 0x00, sizeof(szTempServiceDis) - 1);
		strncpy(szTempServiceDis, m_strServiceDis.c_str(), sizeof(szTempServiceDis) - 1);
		/// ��ӷ�������
		SERVICE_DESCRIPTION sdBuf;
		sdBuf.lpDescription = szTempServiceDis;
		if(FALSE == ::ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		{
			e_LogEvent(EVENTLOG_ERROR_TYPE, "SERVICE_CONFIG_DESCRIPTION ERROR");
		}

		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return true;
	}

	bool CDaemonService::e_Uninstall()
	{
		/// �򿪷��������
		SC_HANDLE hSCM = ::OpenSCManager(
			NULL,					// local machine
			NULL,					// ServicesActive database
			SC_MANAGER_ALL_ACCESS); // full access

		if(!hSCM)
		{
			return false;
		}

		bool bResult = false;
		SC_HANDLE hService = ::OpenService(hSCM,
			(LPCSTR)m_strServiceName.c_str(),
			DELETE);
		if(hService)
		{
			if(::DeleteService(hService))
			{
				bResult = true;
			}
			else
			{
				CDaemonService::e_LogEvent(EVENTLOG_ERROR_TYPE, "Delete Service Fails");
			}
			::CloseServiceHandle(hService);
		}

		::CloseServiceHandle(hSCM);
		return bResult;
	}

	bool CDaemonService::e_ParseStandardArgs(int argc, char* argv[])
	{
		/// �����������С��1������Ϊϵͳ���÷���false
		if(1 >= argc)
		{
			return false;
		}

		/// �鿴�����Ƿ��Ѱ�װ
		if(0 == strcmp(argv[1], "-e"))
		{
			printf("The service is %s installed\n", e_IsInstalled() ? "currently" : "not");
			return true;
		} 
		else if(0 == strcmp(argv[1], "-i"))
		{
			/// ��֤�Ƿ��Ѿ���װ�˸÷���
			if(true == e_IsInstalled())
			{
				printf("%s is already installed\n", m_strServiceName.c_str());
			}
			else
			{
				/// ��װ����
				if(true == e_Install())
				{
					printf("%s installed\n", m_strServiceName.c_str());
				}
				else
				{
					/// ��װ����ʧ��
					printf("%s failed to install. Error %d\n", m_strServiceName.c_str(), GetLastError());
				}
			}
			return true;
		}
		else if(0 == strcmp(argv[1], "-u"))
		{
			/// ��֤�����Ƿ����
			if(false == e_IsInstalled())
			{
				printf("%s is not installed\n", m_strServiceName.c_str());
			}
			else
			{
				/// ж�ط���
				if (true == e_Uninstall())
				{
					TCHAR szFilePath[_MAX_PATH];
					::GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
					printf("%s removed. The File %s\r\n", m_strServiceName.c_str(), szFilePath);
				}
				else
				{
					/// ж�ط���ʧ��
					printf("Could not remove %s. Error %d\n", m_strServiceName.c_str(), GetLastError());
				}
			}
			return true;
		}
		/// δ֪�������
		return false;
	}

	void CDaemonService::e_IniConfig(const char* pszServiceName, const char* pszServiceDis, CRWIniFile* pRWIniFile)
	{
		if (NULL != pszServiceName)
		{
			m_strServiceName = pszServiceName;
		}

		if (NULL != pszServiceDis)
		{
			m_strServiceDis = pszServiceDis;
		}
		m_pRWIniFile = pRWIniFile;
	}
}