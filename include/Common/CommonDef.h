////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// @par ģ����
/// �����ṹ��������ģ��
/// @par ����ļ�
/// ���ô��ļ�ͷ�������ļ�
/// @par ������ϸ����
/// @par ���̰߳�ȫ��
/// [��˵��]
/// @par �쳣ʱ��ȫ��
/// [��˵��]
/// @note         -
/// @file         CommonDef.h
/// @brief        -
/// @author       Li.xl
/// @version      1.0
/// @date         2014/03/17
/// @todo         -
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COMM_LDEF_H__
#define __COMM_LDEF_H__

#include "Common/CommTypes.h"

/// 
/// @par ���� 
/// time_tת��ΪData
/// @param [in,out]	tTime	time_tʱ��
///	[in]		tTime			
/// @return 	DATE			DATEʱ��
/// @note -
/// @par ʾ����
/// @code
/// @deprecated -
/// 
static DATE e_TimeToDate(time_t tTime)
{
	DATE dDate = (tTime + 28800) / (24.0 * 60.0 * 60.0) + 25569;
	return dDate;
};

/// 
/// @par ���� 
/// <Dataת��Ϊtime_t>
/// @param 
///	[in,out]	<������>		<����˵��>
///	[in]		DATE			DATEʱ��
/// @return 	time_t			time_tʱ��
/// @note -
/// @par ʾ����
/// @code
/// @deprecated -
/// 
static time_t e_DateToTime(DATE dDate)
{
	time_t tTime = (time_t)((dDate - 25569) * (24 * 60 * 60) - 28800);
	return tTime;
};

/// 
/// @par ���� 
/// ͨ�������ջ�ȡ�����������еڼ���
/// @param 
///	[in,out]	<������>		<����˵��>
/// [in]		nYear			��
/// [in]		nMonth			��
/// [in]		nDay			��
/// @return 	int				�������ڼ�
/// @note 
/// <����˵��>
/// @par ʾ����
/// @code 
/// <���ñ�������ʾ������>
/// @endcode 
/// @see		<�μ�����> 
/// @deprecated	<��ʱ˵��> 
/// 
static int e_GetWeekDay(int nYear, int nMonth, int nDay)
{
	/*int ny = nYear;
	int nm = nMonth;
	int nd = nDay;
	int nc = 0;
	int nw = 0;
	int weekday = 0;
	char ch = 0;

	if(1 == nm || 2 == nm)
	{
		ny = ny - 1;
		nc = (int)( ny / 100 );
		if( nm == 1 )
		{ nm = 13; }
		else
		{ nm = 14; }
		ny = ny - nc * 100;
	}
	else
	{
		nc = (int) ( ny / 100 );
		ny = ny - nc * 100;
	}

	nw = (int)(nc / 4) - 2 * nc + ny + (int)(ny / 4) + (int)(26 * (nm + 1) / 10) + nd - 1;
	weekday = nw % 7;
	return weekday;*/

	if(nMonth == 1|| nMonth == 2) 
	{
		nMonth += 12;
		nYear--;
	}
	int nWeek = ( nDay + 2 * nMonth + 3 * (nMonth + 1) / 5 + nYear + nYear / 4 - nYear / 100 + nYear / 400) % 7;
	return nWeek;
}

/// 
/// @par ���� 
/// ͨ�������ջ�ȡ�����Ǹ����еڼ���
/// @param 
///	[in,out]	<������>		<����˵��>
/// [in]		nYear			��
/// [in]		nMonth			��
/// [in]		nDay			��
/// @return 	int				һ���еĵڼ���
/// @note 
/// <����˵��>
/// @par ʾ����
/// @code 
/// <���ñ�������ʾ������>
/// @endcode 
/// @see		<�μ�����> 
/// @deprecated	<��ʱ˵��> 
/// 
static int e_GetYearDay(int nYear, int nMonth, int nDay)
{
	int nSum = 0;
	int nLeap = 0;

	/// �ȼ���ĳ����ǰ�·ݵ�������
	switch(nMonth)
	{
	case 1: nSum = 0; break;
	case 2: nSum = 31; break;
	case 3: nSum = 59; break;
	case 4: nSum = 90; break;
	case 5: nSum = 120; break;
	case 6: nSum = 151; break;
	case 7: nSum = 181; break;
	case 8: nSum = 212; break;
	case 9: nSum = 243; break;
	case 10: nSum = 273; break;
	case 11: nSum = 304; break;
	case 12: nSum = 334; break;
	}
	/// �ټ���ĳ�������
	nSum = nSum + nDay;
	/// �ж��ǲ�������
	if(nYear % 400 == 0 
		|| ( nYear % 4 == 0 && nYear % 100 != 0 ))
	{
		nLeap = 1;
	}
	else
	{
		nLeap = 0;
	}
	/// ������������·ݴ���2,������Ӧ�ü�һ��
	if( 1 == nLeap && nMonth > 2)
	{
		nSum++;
	}

	return nSum;
}

/// 
/// @par ���� 
/// ����ʽΪ[�������� ���� ���� ʱʱ �ַ� ����]���ַ���ת��Ϊ���ڸ�ʽ, 
/// �пո���Ի���������ַ�
/// @param 
///	[in,out]	<������>		<����˵��>
/// [in]		pTime			����ʱ���ַ���
/// @return 	time_t			����time_tʱ��
/// @note 
/// <����˵��>
/// @par ʾ����
/// @code 
/// <���ñ�������ʾ������>
/// @endcode 
/// @see		<�μ�����> 
/// @deprecated	<��ʱ˵��> 
/// 
static time_t e_StringToTime(const char* pTime)
{
	tm InTimetm;
	time_t InTime = 0;
	char szInYear[10];
	char szInMon[10];
	char szInDay[10];
	char szInHour[10];
	char szInMunite[10];
	char szInSec[10];

	if(NULL == pTime)
	{
		return InTime;
	}

	memset(szInYear, 0x0, sizeof(szInYear));
	memset(szInMon, 0x0, sizeof(szInMon));
	memset(szInDay, 0x0, sizeof(szInDay));
	memset(szInHour, 0x0, sizeof(szInHour));
	memset(szInMunite, 0x0, sizeof(szInMunite));
	memset(szInSec, 0x0, sizeof(szInSec));
	string strAll = pTime;
	if (0 == strAll.length())
	{
		return InTime;
	}
	string strTmp = "";
	strTmp = strAll.substr(0, 4);
	snprintf(szInYear, sizeof(szInYear), "%s", strTmp.c_str());

	strTmp = strAll.substr(5, 2);
	snprintf(szInMon, sizeof(szInMon), "%s", strTmp.c_str());

	strTmp = strAll.substr(8, 2);
	snprintf(szInDay, sizeof(szInDay), "%s", strTmp.c_str());

	strTmp = strAll.substr(11, 2);
	snprintf(szInHour, sizeof(szInHour), "%s", strTmp.c_str());

	strTmp = strAll.substr(14, 2);
	snprintf(szInMunite, sizeof(szInMunite), "%s", strTmp.c_str());

	strTmp = strAll.substr(17, 2);
	snprintf(szInSec, sizeof(szInSec), "%s", strTmp.c_str());

	memset(&InTimetm, 0x0, sizeof(InTimetm));
	InTimetm.tm_year = atoi(szInYear) - 1900;
	InTimetm.tm_mon = atoi(szInMon) - 1;
	InTimetm.tm_mday = atoi(szInDay);
	InTimetm.tm_hour = atoi(szInHour);
	InTimetm.tm_min = atoi(szInMunite);
	InTimetm.tm_sec = atoi(szInSec);
	/// ����
	InTimetm.tm_wday = e_GetWeekDay(InTimetm.tm_year+1900,InTimetm.tm_mon+1,InTimetm.tm_mday);
	/// ����
	InTimetm.tm_yday = e_GetYearDay(InTimetm.tm_year+1900,InTimetm.tm_mon+1,InTimetm.tm_mday);
	InTimetm.tm_isdst = 0;
	InTime = mktime(&InTimetm);
	return InTime;
}

static string e_FormatTimeString(const char* pTimeStr)
{
	char szInYear[10];
	char szInMon[10];
	char szInDay[10];
	char szInHour[10];
	char szInMunite[10];
	char szInSec[10];

	memset(szInYear, 0x0, sizeof(szInYear));
	memset(szInMon, 0x0, sizeof(szInMon));
	memset(szInDay, 0x0, sizeof(szInDay));
	memset(szInHour, 0x0, sizeof(szInHour));
	memset(szInMunite, 0x0, sizeof(szInMunite));
	memset(szInSec, 0x0, sizeof(szInSec));

	string strAll = pTimeStr;
	string strTmp = "";
	strTmp = strAll.substr(0, 4);
	snprintf(szInYear, sizeof(szInYear), "%s-", strTmp.c_str());

	strTmp = strAll.substr(4, 2);
	snprintf(szInMon, sizeof(szInMon), "%s-", strTmp.c_str());

	strTmp = strAll.substr(6, 2);
	snprintf(szInDay, sizeof(szInDay), "%s ", strTmp.c_str());

	strTmp = strAll.substr(8, 2);
	snprintf(szInHour, sizeof(szInHour), "%s:", strTmp.c_str());

	strTmp = strAll.substr(10, 2);
	snprintf(szInMunite, sizeof(szInMunite), "%s:", strTmp.c_str());

	strTmp = strAll.substr(12, 2);
	snprintf(szInSec, sizeof(szInSec), "%s", strTmp.c_str());

	strAll.clear();
	strAll.append(szInYear);
	strAll.append(szInMon);
	strAll.append(szInDay);
	strAll.append(szInHour);
	strAll.append(szInMunite);
	strAll.append(szInSec);

	return strAll;
}

/// 
/// @par ���� 
/// ��ȡtm ʱ��ṹ��
/// @param 
///	[in,out]	<������>		<����˵��>
/// 
/// @return 		-
/// @note -
/// @par ʾ����
/// @code
/// @deprecated -
/// 
static void e_GetTmStruct(tm* m_tm, time_t& t_time)
{
#ifdef WIN32
	localtime_s(m_tm, &t_time);
#else
	tm* ttm = NULL;

	ttm = localtime(&t_time);

	if(NULL != ttm)
	{
		memcpy(m_tm, ttm, sizeof(tm));
	}
#endif
};
/// 
/// @par ���� 
/// ʱ������ת��Ϊstring���ĸ�����
/// @param 
///	[in,out]	<������>		<����˵��>
/// [in]		t_time			time_tʱ��
/// [in,out]	pTime			ת������ַ���
/// [in]		nszSize			ת������ַ�����С
/// [in]		flag			Ҫת���ɵ��ַ�������
/// @return 		-
/// @note -
/// @par ʾ����
/// @code
/// @deprecated - 
/// 
static void e_TimeToString(time_t t_time, char* pTime, int nszSize, int flag = 4)
{
	int nYear = 0, mon = 0, nDay = 0, hour = 0, min = 0, sec = 0;
	struct tm m_tm;
	e_GetTmStruct(&m_tm, t_time);

	nYear = (int)m_tm.tm_year + 1900;
	mon = (int)m_tm.tm_mon + 1;
	nDay = (int)m_tm.tm_mday;
	hour = (int)m_tm.tm_hour;
	min = (int)m_tm.tm_min;
	sec = (int)m_tm.tm_sec;
	switch(flag)
	{
	case 1:
		{ 
			snprintf(pTime, nszSize, "%04d%02d%02d%02d%02d%02d", nYear, mon, nDay, hour, min, sec); 
			break; 
		}
	case 2:
		{ 
			snprintf(pTime, nszSize, "%04d%02d%02d", nYear, mon, nDay); 
			break; 
		}
	case 3:
		{ 
			snprintf(pTime, nszSize, "%02d%02d%02d", hour, min, sec); 
			break; 
		}
	case 4:
		{ 
			snprintf(pTime, nszSize, "%04d-%02d-%02d %02d:%02d:%02d", nYear, mon, nDay, hour, min, sec); 
			break; 
		}
	case 5:
		{ 
			snprintf(pTime, nszSize, "%04d-%02d-%02d", nYear, mon, nDay); 
			break; 
		}
	case 6:
		{ 
			snprintf(pTime, nszSize, "%nd:%nd:%nd", hour, min, sec); 
			break; 
		}
	case 7:
		{
			hour = (int)t_time / (60 * 60);
			t_time = (int)t_time % ( 60 * 60 );
			min = (int)t_time / 60;
			t_time = (int)t_time % 60;
			sec = (int)t_time;
			snprintf(pTime, nszSize, "%nd:%nd:%nd", hour, min, sec);
			break;
		}
	case 8:
		{
			/// ����Ϊ��
			hour = (int)t_time / (60 * 60);
			snprintf(pTime, nszSize, "%nd", hour*( 60* 60 )+(min*60)+sec);
			break;
		}
	case 9:
		{
			nYear = nYear % 100;
			/// ������ں�ʱ��
			snprintf(pTime, nszSize, "%02d%02d%02d000", nYear, mon, nDay);
			break;
		}
	case 10:
		{
			// ת����ָ����ʽ��ʱ��
			snprintf(pTime, nszSize, "%04d/%02d/%02d %02d.%02d.%02d", nYear, mon, nDay, hour, min, sec);
			break; 
		}
	default:
		{
			snprintf(pTime, nszSize, "%04d%02d%02d%02d%02d%02d", nYear, mon, nDay, hour, min, sec);
			break;
		}
	}
};

static void e_GetSysTime(string& strCurrentTime, bool bIsCheckDir = false)
{
	char szTime[64];
	memset(szTime, 0x00, sizeof(szTime));
#ifdef WIN32
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);

	if(true == bIsCheckDir)
	{
		snprintf(szTime, sizeof(szTime) - 1, "%d-%02d-%02d %02d.%02d.%02d.%03d", 
			SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour,
			SystemTime.wMinute, SystemTime.wSecond, SystemTime.wMilliseconds);
	}
	else
	{
		snprintf(szTime, sizeof(szTime) - 1, "%d-%02d-%02d %02d:%02d:%02d.%03d", 
			SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour,
			SystemTime.wMinute, SystemTime.wSecond, SystemTime.wMilliseconds);
	}
	
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long ltime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif

	strCurrentTime = szTime;
}

/// 
/// @par ���� 
/// ����ϵͳʱ��(�������紫�䴦�����ʱ�䶼������1����)
/// @param 
///	[in,out]	<������>		<����˵��>
/// [in]		tmStruct		Ҫ���õ�tm�ṹ��	
/// @return 	bool			����ϵͳʱ��ɹ�����ʧ��
/// @note -
/// @par ʾ����
/// @code
/// @deprecated - 
/// 
static bool e_SetSystemTime(tm& tmStruct)
{
	time_t tTime = mktime(&tmStruct);

#ifdef WIN32

	SYSTEMTIME SystemTime;

	SystemTime.wYear = tmStruct.tm_year + 1900;
	SystemTime.wMonth = tmStruct.tm_mon + 1;
	SystemTime.wDay = tmStruct.tm_mday;
	SystemTime.wHour = tmStruct.tm_hour;
	SystemTime.wMinute = tmStruct.tm_min;
	SystemTime.wSecond = tmStruct.tm_sec + 1;
	SystemTime.wDayOfWeek = tmStruct.tm_wday;
	SystemTime.wMilliseconds = 0;

	BOOL bRet = SetLocalTime(&SystemTime);
	return (bRet == TRUE);

#else

	struct timeval tv;
	tv.tv_sec = tTime + 1;
	tv.tv_usec = 0;
	settimeofday(&tv, 0);
	return true;

#endif
};

/// ==============================================
/// @par ���� 
/// ����ת��Ϊʼ����ʾ
/// @param 
/// [in,out]	<������>		<����˵��>
///	[in]		ulSecondsTime	����
/// [out]		strSecondsTime	ת������ַ����������� ��ʽ:[HH:mm:ss]
/// @return 	-
/// @note 		Creat By li.xl 2014/06/05 
/// ==============================================
static void e_TransSecondsToStr(ULONG ulSecondsTime, string& strSecondsTime)
{
	int nHour = 0, nMins = 0, nSecond = 0;

	nHour = ulSecondsTime / 3600;

	ulSecondsTime = ulSecondsTime % 3600;

	nMins = ulSecondsTime / 60;

	nSecond = ulSecondsTime % 60;

	char szTempTime[16];
	memset(szTempTime, 0x00, sizeof(szTempTime));
	snprintf(szTempTime, sizeof(szTempTime) - 1, 
	  "%02d:%02d:%02d", nHour, nMins, nSecond);
	strSecondsTime = szTempTime;
}

/// �����ڴ滻�㵥λ
#define MEMDIV 1024

/// 
/// @par ���� 
/// ��ȡ�����ڴ�
/// @param 
/// [in,out]	<������>		<����˵��>
/// @return 	Int				�����ڴ��С����λM
/// @note 		-
/// @par ʾ����
/// @code 		-
/// @endcode 
/// @see		-
/// @deprecated	- 
/// 
inline int e_GetSystemMemoryStat()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	//cout<<"statex.dwLingth :"<<statex.dwLength<<endl;
	GlobalMemoryStatusEx (&statex);

	int nMemoryAvail = (int)(statex.ullAvailPhys / (MEMDIV * MEMDIV));

	//cout<<"�����ڴ����������"<< nMemoryAvail <<"M"<<endl;
	//cout<<"�����ڴ���������"<<statex.ullTotalPhys/MEMDIV/MEMDIV<<"M"<<endl;
	//cout<<"�����ڴ���������"<<statex.ullTotalVirtual/MEMDIV/MEMDIV<<"M"<<endl;
	//cout<<"�����ڴ����������"<<statex.ullAvailVirtual/MEMDIV/MEMDIV<<"M"<<endl;
	return nMemoryAvail;
}

/// 
/// @par ���� 
/// �Ա�ʱ��Ƭ
/// @param 
/// [in,out]	<������>		<����˵��>
///	[in]		time1			��һ��ϵͳʱ��Ƭ
///	[in]		time2			�ڶ���ϵͳʱ��Ƭ
/// @return 	-
/// @note 		-
/// @par ʾ����
/// @code 		-
/// @endcode 
/// @see		-
/// @deprecated	- 
/// 
inline INT64 e_CompareFileTime(FILETIME time1, FILETIME time2)
{
	/// ���Ծ����ֵǿ��ת��Ϊ�޷���
	INT64 a = (UINT64)time1.dwHighDateTime << 32 | time1.dwLowDateTime;
	INT64 b = (UINT64)time2.dwHighDateTime << 32 | time2.dwLowDateTime;
	return (b - a);
};

/// 
/// @par ���� 
/// ��ȡCPUʹ����
/// @param 
/// [in,out]	<������>		<����˵��>
/// @return 	int				ʹ���ʰٷֱ�
/// @note 		-
/// @par ʾ����
/// @code 		-
/// @endcode 
/// @see		-
/// @deprecated	- 
/// 
inline int e_GetSystemCupStat()
{ 
	/// �����¼��ź�
	HANDLE hEvent;
	BOOL res;

	FILETIME preidleTime;
	FILETIME prekernelTime;
	FILETIME preuserTime;

	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;

	/// ��ȡϵͳʱ��Ƭ
	res = GetSystemTimes(&preidleTime, &prekernelTime, &preuserTime);

	/// ��ʼֵΪ nonsignaled ������ÿ�δ������Զ�����Ϊnonsignaled
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	/// ���û�л�ȡ���źţ��ȴ�1500���뷵��
	WaitForSingleObject(hEvent, 1500);

	/// �ٴλ�ȡϵͳʱ��Ƭ
	res = GetSystemTimes(&idleTime, &kernelTime, &userTime);

	INT64 idle	 = e_CompareFileTime(preidleTime, idleTime);
	INT64 kernel = e_CompareFileTime(prekernelTime, kernelTime);
	INT64 user	 = e_CompareFileTime(preuserTime, userTime);

	/// CPU������:
	int nUseCpu = (int)((kernel + user - idle) * 100 / (kernel + user));
	///// CPU������:
	//int nCpuIdle = (int)((idle) * 100 / (kernel + user));
	///// ��ӡ
	//printf("CPU������: %d%%, ������ %d%%\r\n", nUseCpu, nCpuIdle);
	return nUseCpu;
};

/// 
/// @par ���� 
/// �滻�ַ����е��ַ�
/// @param 
/// [in,out]	<������>		<����˵��>
///	[in]		str				Ŀ���ַ���
///	[in]		pattern			Ҫ�滻���ַ�/�ַ���
///	[in]		dstPattern		�滻����ַ�/�ַ���
/// @return 	-
/// @note 		-
/// @par ʾ����
/// @code 		-
/// @endcode 
/// @see		-
/// @deprecated	- 
/// 
static string e_ReplaceAll(string str, string pattern, string dstPattern)
{
	std::string retStr="";
	string::size_type pos;

	int szStr = str.length();
	int szPattern = pattern.size();
	int i=0;
	int l_count=0;
	// replace all
	int count = szStr;

	for(i=0; i<szStr; i++)
	{
		pos=str.find(pattern,i);

		if(pos == std::string::npos)
		{
			break;
		}
		if(szStr > (int)pos)
		{
			std::string s=str.substr(i,pos-i);
			retStr += s;
			retStr += dstPattern;
			i=pos+pattern.length()-1;
			if(++l_count >= count)
			{
				i++;
				break;
			}
		}
	}
	retStr += str.substr(i);
	return retStr;
}

/// ==============================================
/// @par ���� 
/// �����ַ����еڼ��γ���Ŀ���ַ�����λ��
/// @param 
/// [in,out]	<������>		<����˵��>
///	
/// @return 	-
/// @note 		by li.xl 2013/04/27 
/// ==============================================
inline int e_Instr(char* pszSrc, char* pszDes, USHORT usIndex)
{
	int nFindeIndex = 0;
	/// ��֤����
	if(NULL == pszSrc || NULL == pszDes)
	{
		return nFindeIndex;
	}

	bool bIsFind = false;
	/// ��ֵ����Դ
	char* pszCharTemp = pszSrc;
	while(NULL != (pszCharTemp = strstr(pszCharTemp, pszDes)))
	{
		nFindeIndex++;
		if(nFindeIndex == usIndex)
		{
			bIsFind = true;
			break;
		}
		// �ƶ����ҵ���λ�ã������´β�����Ȼ�Ǵ�λ��
		pszCharTemp = pszCharTemp + strlen(pszDes);
	}
	/// ����Ҷ�Ӧλ�õ��ַ����ִ�
	if(true == bIsFind)
	{
		nFindeIndex = pszCharTemp - pszSrc;
	}
	return nFindeIndex;
}

/// ==============================================
/// @par ���� 
/// ���õ�ǰ����Ŀ¼
/// @return 	-
/// @note 		by li.xl 2013/04/12 
/// ==============================================
inline void e_SetCurDirectory()
{
	/// ���õ�ǰ����Ŀ¼
	char szBuf[512];
	char szDirectPath[512];
	memset(szDirectPath, 0x00, sizeof(szDirectPath));
	/// �õ���ǰģ��·��
	::GetModuleFileName(NULL, szDirectPath, sizeof(szDirectPath) - 1);
	char* pszLastPoint = strrchr(szDirectPath, '\\');
	if(NULL != pszLastPoint)
	{
		UINT nSize = pszLastPoint - szDirectPath;
		if(0 < nSize)
		{
			strncpy_s(szBuf, szDirectPath, nSize);
			szBuf[nSize] = 0;
		}
	}
	::SetCurrentDirectory(szBuf);
}

/// ==============================================
/// @par ���� 
/// �����༶Ŀ¼
/// @param 
/// [in,out]	<������>		<����˵��>
/// @return 	-
/// @note 		by li.xl 2013/04/19 
/// ==============================================
inline bool e_CreatUserDir(char* pszDir)
{
	int i = 0;
	int iRet;
	int iLen = strlen(pszDir);

	// ��ĩβ�� ��/��
	if(pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	// ����Ŀ¼
	for(i = 0; i <= iLen; i++)
	{
		if(pszDir[i] == '\\' || pszDir[i] == '/')
		{ 
			pszDir[i] = '\0';
			// ���������,����
			if(0 != (iRet = _access(pszDir, 0)))
			{
				if(0 != (iRet = _mkdir(pszDir)))
				{
					return false;
				}
			}
			// ֧��linux,������\����/
			pszDir[i] = '/';
		} 
	}
	return true;
};


/// 
/// @par ���� 
/// ��ȡ��ǰ�ļ�����Ŀ¼
/// @param 
///	[in,out]	<������>		<����˵��>
/// @return 	string			�����ļ�·��
/// @note 
/// <����˵��>
/// @par ʾ����
/// @code 
/// <���ñ�������ʾ������>
/// @endcode 
/// @see		<�μ�����> 
/// @deprecated	<��ʱ˵��> 
/// 
static string e_GetFilePath()
{
	/// �����ȡ�ַ��ַ���
	char szExePath[512];
	memset(szExePath, 0x00, sizeof(szExePath));
	/// ��ȡ����ĵ�ַ����
	int nPathLen = sizeof(szExePath);
	/// �����ȡ���صı���
	DWORD ldwReturn = 0;
	/// �����ַ�ָ��
	char* pPos = NULL;
	/// ����·�����Ŀ¼�ַ�
	char cInchar = '\\';

	/// ��ȡ·��
#ifndef WIN32
	ldwReturn = readlink( "/proc/self/exe", szExePath, nPathLen);
	cInchar = '/';
#else
	ldwReturn = GetModuleFileNameA(NULL, szExePath, nPathLen);
	cInchar = '\\';
#endif

	if(0 < (int)ldwReturn && nPathLen > (int)ldwReturn)
	{
		pPos = strrchr(szExePath, cInchar);
		if(NULL != pPos)
		{
			*++pPos = '\0';
		}
	}
	/// �����ػ�ȡ����·���ַ���
	string strExePath = szExePath;
	return strExePath;
}

/// ==============================================
/// @par ���� 
/// ��ȡһ��INI��ĳһbitλ��ֵ
/// @param 
/// [in,out]	<������>		<����˵��>
///	
/// @return 	-
/// @note 		Creat By li.xl 2013/12/23 
/// ==============================================
static int e_GetBit(int nTest, int index) 
{
	return ((nTest & (1 << index)) > 0) ? 1: 0;
}

/// ==============================================
/// @par ���� 
/// ��ȡϵͳʱ��
/// @param 
/// [in,out]	<������>		<����˵��>
///	
/// @return 	��(ʱ*3600+��*60+��)
/// @note 		Creat By li.xl 2014/01/10 
/// ==============================================
static UINT e_GetSysTime()
{
	UINT unTimeRet = 0;
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	unTimeRet = SystemTime.wHour * 3600;
	unTimeRet += SystemTime.wMinute * 60;
	unTimeRet += SystemTime.wSecond;

	return unTimeRet;
}

static bool e_CheckFileExist(const char* pszFilePath)
{
	// ���巵��ֵ
	bool bRet = false;
	// ��֤���ݺϷ���
	if(NULL == pszFilePath)
	{
		return bRet;
	}
	// �������ļ��Ƿ���ڷ���ֵ
	int nRet = 0;
	/// ����ļ��Ƿ����
#ifdef WIN32
	struct _stat	tFileStatus;
	nRet = _stat(pszFilePath, &tFileStatus);
#else
	struct stat		tFileStatus;
	nRet = stat(pszFilePath, &tFileStatus);
#endif
	bRet = (0 == nRet);
	return bRet;
}

static bool e_MakeStrSub(const char* pszStrSrc, string& strStrDes)
{
	bool bRet = false;
	int nStrLen = 0;
	strStrDes = "";
	char cTemp;
	if(NULL != pszStrSrc && 0 < (nStrLen = strlen(pszStrSrc)))
	{
		for(int i = 0; i < nStrLen; i++)
		{
			cTemp = pszStrSrc[i];
			strStrDes += cTemp;
			strStrDes += " ";
		}
		bRet = true;
	}	
	return bRet;
}

/// ==============================================
/// @par ���� 
/// ��ȡȫ·���е��ļ���
/// @param 
/// [in,out]	<������>		<����˵��>
///	
/// @return 	-
/// @note 		Creat By li.xl 2015/05/10 
/// ==============================================
inline string e_GetNameFromPath(const char* pszFullName)
{
	string strFileName = pszFullName;
	const char*  pszFistPoint = pszFullName;
	const char*  pszLastPoint  = pszFullName + strlen(pszFullName);
	if ( strrchr( pszFullName, '\\' ) != NULL )
		pszFistPoint = strrchr( pszFullName, '\\' ) + 1;
	else if ( strrchr( pszFullName, '/' ) != NULL )
		pszFistPoint = strrchr( pszFullName, '/' ) + 1;
	//if ( strrchr( pszFullName, '.' ) != NULL )
	//	pszLastPoint = strrchr( pszFullName, '.' );
	if ( pszLastPoint < pszFistPoint )
		pszLastPoint = pszFullName + strlen( pszFullName );

	strFileName.assign(pszFistPoint, pszLastPoint);

	return strFileName;
}

/// ==============================================
/// @par ���� 
/// ��ȡ��ǰ�߳�ID
/// @param 
/// [in,out]	<������>		<����˵��>
///	-
/// @return 	��ǰ�̵߳�ID 
/// @note 		Creat By li.xl 2016/08/12 
/// ==============================================
inline UINT e_GetCurrentThreadID()
{
#ifdef WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif
}

#endif	/// __COMM_LDEF_H__