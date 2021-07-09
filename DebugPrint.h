#ifndef _DEBUGPRINT_
#define _DEBUGPRINT_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "FileOpt.h"

#define PRINT_SWITCH_DEBUG (0)
#define PRINT_SWITCH_ERROR (1)

#define DEBUG_LOG_PATH "E://OwenTestPro/log.txt"
#define PRINT_LOG_DATA_SIZE (256)


/*
#define Debug_Print(usrChr...) gdebug_print( __FILE__, __FUNCTION__, __LINE__, __TIME__, usrChr)
#define Debug_Perror(usrChr...) gdebug_print( __FILE__, __FUNCTION__, __LINE__, __TIME__, usrChr)

void gdebug_print(const char *file, const char *fun, int line, const char *time,const char *usrChr, ...);
void gdebug_perror(const char *file, const char *fun, int line, const char *time,const char *usrChr, ...);
*/


#define Debug_Error(usrChr...) gdebug_print(__FUNCTION__, __LINE__, __TIME__, usrChr)
#define Debug_Debug(usrChr...) gdebug_debug(__FUNCTION__, __LINE__, __TIME__, usrChr)

//#define Debug_Perror(usrChr...) gdebug_print(__FUNCTION__, __LINE__, __TIME__, usrChr)


void gdebug_print(const char *fun, int line, const char *time,const char *usrChr, ...);
void gdebug_debug(const char *fun, int line, const char *time,const char *usrChr, ...);
void gdebug_perror(const char *fun, int line, const char *time,const char *usrChr, ...);

class CFileOpt;

static CFileOpt *g_pFileOpt;

// 打开日志文件
int gdebug_OpenLogFile();
// 将日志写入文件
int gdebug_LogWrite(char *data, const int Count);
// 程序结束关闭日志文件
int gdebug_CloseLogFile();








#define TIME_CHECK_SWITCH (1)
class cTimeCheck
{
	public:
		cTimeCheck();
		~cTimeCheck();

		void Start();
		void End();	
		void End(const char *data);
		
		void GetAvage();
		
	private:
		bool m_switch;
		struct timeval m_startT;
		int m_runConut;
		long m_totalUsec;

};




#endif




