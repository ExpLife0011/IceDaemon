////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// ��ض���ģ��
/// @par ����ļ�
/// 
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         DaemonServiceDef.h
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2018/01/15
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ICE_DAEMON_DEAMON_SERVICE_DEF_H_H__
#define __ICE_DAEMON_DEAMON_SERVICE_DEF_H_H__

namespace ICEDAEMON
{	
	// �����ļ�����
	#define CONFIG_FILE_NAME	"./daemon.ini"

	// ����ģ��ؼ���
	#define SERVICE_MOUDLE_KEY	"ServiceDaemon"

	// ����ע������
	#define SERVICE_NAME_KEY	"ServiceName"
	// ����ע������
	#define SERVICE_DISPLAY		"ServiceDis"

	// �����ػ��Ŀ�ִ���ļ���
	#define SERVICE_EXEC_NAME	"ServiceExecName"
	// �����ػ��Ŀ�ִ���ļ�·��
	#define SERVICE_EXEC_PATH	"ServiceExecPath"
	// ��ִ���ļ�ִ�еĲ���
	#define SERVICE_EXEC_ARGV	"ServiceExecArgv"
}

#endif // __ICE_DAEMON_DEAMON_SERVICE_DEF_H_H__