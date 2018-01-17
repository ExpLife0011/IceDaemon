////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ���̼�������Ϣ
/// @par ����ļ�
/// CProcessMonitor.cpp
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         CProcessMonitor.h
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ICE_DAEMON_PROCESS_MONITOR__H_H__
#define __ICE_DAEMON_PROCESS_MONITOR__H_H__

#include "Common/CommTypes.h"

namespace ICEDAEMON
{
	class CProcessMonitor
	{
	public:
		CProcessMonitor();
		~CProcessMonitor();

		/// ==============================================
		/// @par ���� 
		/// �������̼����ػ�
		/// @param	
		/// [in,out]	<������>			<����˵��>
		///	[in]		pszProcessName		��������
		/// [in]		pszProcessPath		����·��
		/// [in]		pszProcessArgv		���̲���
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool e_StartMonitor(const char* pszProcessName, const char* pszProcessPath, const char* pszProcessArgv);

		/// ==============================================
		/// @par ���� 
		/// ֹͣ��������
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool e_StopProcessRun();

	private:

		/// ==============================================
		/// @par ���� 
		/// ͨ������ID��ȡ���̾��
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		ulProcessID		����ID
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool i_CheckProcessHasExitByID(ULONG ulProcessID);

		/// ==============================================
		/// @par ���� 
		/// ��ȡ���̾��ByID
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/17 
		/// ==============================================
		HANDLE i_GetProcessHandleByID(ULONG ulProcessID);

		/// ==============================================
		/// @par ���� 
		/// ��������
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool i_StartProcessRun();

		/// ==============================================
		/// @par ���� 
		/// ���������߳�
		/// @param 
		/// [in,out]	<������>		<����˵��>		
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool i_StartMonitorProcessThread();

		/// ==============================================
		/// @par ���� 
		/// 
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	[in]		lpParama		�̲߳���
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		UINT static WINAPI i_MonitorProcessThread(LPVOID lpParama);

		/// ==============================================
		/// @par ���� 
		/// 
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool i_LoopCheckProcessExsit();

		/// ==============================================
		/// @par ���� 
		/// 
		/// @param 
		/// [in,out]	<������>		<����˵��>
		///	
		/// @return 	-
		/// @note 		Creat By li.xl 2018/01/15 
		/// ==============================================
		bool i_RunProcess();

	private:
		// ��������
		string				m_strProcessName;
		// ����·��
		string				m_strProcessPath;
		// ��������
		string				m_strProcessArgv;
		// ��ѯ�߳̾��
		HANDLE				m_hThreadHandle;
		// ��ѯ�߳�״̬
		HANDLE				m_hThreadStatus;
		// ����ID
		ULONG				m_ulProcessID;

	};
}
#endif	/// __ICE_DAEMON_PROCESS_MONITOR__H_H__