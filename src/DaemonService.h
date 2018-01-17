////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ����ģ��ͷ�ļ�
/// @par ����ļ�
/// CDaemonService.cpp
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         CDaemonService.h
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ICE_DAEMON_DEAMON_SERVICE_H_H__
#define __ICE_DAEMON_DEAMON_SERVICE_H_H__

#define SVC_ERROR		((DWORD)0xC0020001L)

#include "Common/CommonDef.h"
#include "RWIniFile.h"
#include "ProcessMonitor.h"

namespace ICEDAEMON
{
	class CDaemonService
	{
	public:
		CDaemonService();
		~CDaemonService();

		/// 
		/// @par ���� 
		/// ������ں���
		/// @param
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		static void WINAPI e_ServiceMain(DWORD dwArgc, LPSTR* lpszArgv);

		/// 
		/// @par ���� 
		/// ��֤�����Ƿ��Ѿ���װ
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		bool e_IsInstalled();

		/// 
		/// @par ���� 
		/// ��װ�������
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		bool e_Install();

		/// 
		/// @par ���� 
		/// ж�ط���
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		bool e_Uninstall();

		/// 
		/// @par ���� 
		/// ��������װ��ж������
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		argc			��������
		/// [in]		argv			��������
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		bool e_ParseStandardArgs(int argc, char* argv[]);

		/// 
		/// @par ���� 
		/// �յ������������Ϣ
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		dwCtrl			��Ϣ��Ϣ
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		static void WINAPI e_SvcCtrlHandler(DWORD dwCtrl);

		/// 
		/// @par ���� 
		/// дWindows ��־
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		wType			��־����
		/// [in]		pszFormat		��־����
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		static void e_LogEvent(WORD wType, const char* pszFormat, ...);

		/// 
		/// @par ���� 
		/// �ϱ�����״̬,����״̬��SCM����
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		dwCurrentState	��ǰ״̬
		/// [in]		dwWin32ExitCode
		/// [in]		dwWaitHint		�ȴ�ʱ��
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		///
		void e_ReportSvcStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);

		/// 
		/// @par ���� 
		/// ����������
		/// @param 
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		bool e_ServerProgram(DWORD dwArgc, LPSTR* lpszArgv);

		/// 
		/// @par ���� 
		/// ��ʼ���з���
		/// @return 	-
		/// @note 		-
		/// @par ʾ����
		/// @code 		-
		/// @endcode 
		/// @see		-
		/// @deprecated	- 
		/// 
		void e_ServiceRun();

		/// ==============================================
		/// @par ���� 
		/// ���������ļ�����
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		void e_IniConfig(const char* pszServiceName, const char* pszServiceDis, CRWIniFile* pRWIniFile);

	public:
		/// ����״̬
		SERVICE_STATUS          m_SvcStatus;
		/// ����״̬���
		SERVICE_STATUS_HANDLE   m_SvcStatusHandle;
		/// ����ֹͣ���
		HANDLE                  m_hSvcStopEvent;
		// �����ļ�����ָ��
		CRWIniFile*				m_pRWIniFile;
		// ��������
		string					m_strServiceName;
		// ��������
		string					m_strServiceDis;
	};
}

#endif	/// __ICE_DAEMON_DEAMON_SERVICE_H_H__