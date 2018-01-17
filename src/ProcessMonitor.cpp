////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ���̼�������Ϣ
/// @par ����ļ�
/// CProcessMonitor.h
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         CProcessMonitor.cpp
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Common/CommTypes.h"
#include "psapi.h"
#include "tlhelp32.h" 
#include "stdio.h"
#include "ProcessMonitor.h"

namespace ICEDAEMON
{
	CProcessMonitor::CProcessMonitor()
	{
		// ������
		m_strProcessName = "";
		m_strProcessPath = "";
		// �������̲���
		m_strProcessArgv = "";
		// �߳�״̬�ź�
		m_hThreadStatus = CreateEvent(NULL, FALSE, FALSE, NULL);
		// ��ʼ���߳̾��
		m_hThreadHandle = NULL;
		// ����ID
		m_ulProcessID = 0;
	}

	CProcessMonitor::~CProcessMonitor()
	{
	}

	bool CProcessMonitor::e_StartMonitor(const char* pszProcessName, const char* pszProcessPath, const char* pszProcessArgv)
	{
		if (NULL == pszProcessName || NULL == pszProcessPath || NULL == pszProcessArgv)
		{
			return false;
		}
		// ����·��
		m_strProcessName = pszProcessName;
		// �������ȫ·��
		m_strProcessPath = pszProcessPath;
		if (0 < m_strProcessPath.length())
		{
			if ('/' != m_strProcessPath.at(m_strProcessPath.length() - 1) && 
				'\\' != m_strProcessPath.at(m_strProcessPath.length() - 1))
			{
				m_strProcessPath.append("/");
			}
			m_strProcessPath.append(pszProcessName);
		}		
		m_strProcessArgv = pszProcessArgv;
		// ��ʼ��������
		i_StartMonitorProcessThread();
		return true;
	}

	bool CProcessMonitor::i_StartMonitorProcessThread()
	{
		bool bRet = false;
		// ����̲߳�����
		if(NULL == m_hThreadHandle)
		{
			// �����߳�
			m_hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, 
				i_MonitorProcessThread, this, 0, NULL);
		}

		if(NULL != m_hThreadHandle)
		{
			bRet = true;
		}
		return bRet;
	}

	UINT CProcessMonitor::i_MonitorProcessThread(LPVOID lpParama)
	{
		CProcessMonitor* pThis = (CProcessMonitor*) lpParama;
		if (NULL != pThis)
		{
			pThis->i_LoopCheckProcessExsit();
		}
		return 0;
	}


	bool CProcessMonitor::i_LoopCheckProcessExsit()
	{
		bool bIsFindProcess = false;
		// ��ʼ�߳�ѭ��
		while(true)
		{
			bIsFindProcess = false;
			// ������ڽ���ID
			if (0 < m_ulProcessID)
			{
				bIsFindProcess = i_CheckProcessHasExitByID(m_ulProcessID);
			}			
			// ���û���ҵ����̣�ͨ�����ƻ�ȡ
			if (false == bIsFindProcess)
			{
				HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(pe32);
				BOOL IsCanGetMore = FALSE;
				do 
				{
					IsCanGetMore = ::Process32Next(hProcessSnap, &pe32);
					// �ҵ�����Ӧ�Ľ��������˳����ң��ȴ�һ�´β���
					if(TRUE == IsCanGetMore && 0 == strcmp(m_strProcessName.c_str(), pe32.szExeFile))
					{
						// ��ֵ�ҵ���ָ���Ľ�����
						bIsFindProcess =  true;
						break;
					}
				} while (TRUE == IsCanGetMore);

				// ���û���ҵ�ָ���Ľ���
				if (false == bIsFindProcess)
				{
					// ��������
					i_StartProcessRun();
				}
			}

			// ��������źţ��˳������߳� 30�� ����һ�β�ѯ
			if(WAIT_OBJECT_0 == WaitForSingleObject(m_hThreadStatus, 10000))
			{
				break;
			}
		}

		return false;
	}

	/// ͨ������ID��ȡ���̾��
	bool CProcessMonitor::i_CheckProcessHasExitByID(ULONG ulProcessID)
	{
		bool bIsExsit = false;
		
		HANDLE processHandle = i_GetProcessHandleByID(ulProcessID);
		if (NULL != processHandle)
		{
			// �ͷž�����ü���
			CloseHandle(processHandle);
			// ��ֵ���ڷ���ֵ
			bIsExsit = true;
		}
		return bIsExsit;
	}

	HANDLE CProcessMonitor::i_GetProcessHandleByID(ULONG ulProcessID)
	{
		if (0 < ulProcessID)
		{
			return OpenProcess(PROCESS_ALL_ACCESS, FALSE, ulProcessID);
		}
		return NULL;
	}

	bool CProcessMonitor::i_StartProcessRun()
	{
		//������Ϣ
		PROCESS_INFORMATION pro_info;
		//������Ϣ
		STARTUPINFO sti; 
		// ��ʼ�������ṹ��  
		ZeroMemory(&pro_info, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&sti, sizeof(STARTUPINFO));
		// ���������������
		char szCmdLine[256];
		memset(szCmdLine, 0x00, sizeof(szCmdLine) - 1);
		snprintf(szCmdLine, sizeof(szCmdLine) - 1, "\"%s\" %s", m_strProcessPath.c_str(), m_strProcessArgv.c_str());
		// ��ֵ����ID
		// CreateProcessAsUser(����һ��GUI����)
		// ����һ����Ĭ��ϵͳ����
		if(TRUE == ::CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &pro_info))
		{
			m_ulProcessID = pro_info.dwProcessId;
			// �ͷ��̺߳;�������ü���
			CloseHandle(pro_info.hProcess);
			CloseHandle(pro_info.hThread);
			return true;
		}
		return false;
	}

	bool CProcessMonitor::e_StopProcessRun()
	{
		HANDLE hProcessHandle = i_GetProcessHandleByID(m_ulProcessID);
		if (NULL != hProcessHandle)
		{
			/// �˳���
			DWORD exitCode;
			/// ��ȡ�˳���  
			GetExitCodeProcess(hProcessHandle, &exitCode);
			TerminateProcess(hProcessHandle, exitCode);  
			// �ͷž�����ü���
			CloseHandle(hProcessHandle);
			return true;
		}
		return false;
	}
}