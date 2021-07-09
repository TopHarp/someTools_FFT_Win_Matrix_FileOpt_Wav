#include "DebugPrint.h"


/*
void gdebug_print(const char *file, const char *fun, int line, const char *time,const char *usrChr, ...)
{
    printf("[%s:%s:%d][T%s] ",file, fun, line, time);
    va_list args;       //定义一个va_list类型的变量，用来储存单个参数
    va_start(args,usrChr); //使args指向可变参数的第一个参数
    vprintf(usrChr,args);  //必须用vprintf等带V的
    va_end(args);       //结束可变参数的获取
}


void gdebug_perror(const char *file, const char *fun, int line, const char *time,const char *usrChr, ...)
{
	printf("[%s:%s:%d][T%s] ",file, fun, line, time);
	perror("perror:");
	printf(". ");
	va_list args;		//定义一个va_list类型的变量，用来储存单个参数
	va_start(args,usrChr); //使args指向可变参数的第一个参数
	vprintf(usrChr,args);	//必须用vprintf等带V的
	va_end(args);		//结束可变参数的获取
}*/


void gdebug_print(const char *fun, int line, const char *time,const char *usrChr, ...)
{
#if PRINT_SWITCH_ERROR
    printf("[%s:%d][T%s] ",fun, line, time);
    va_list args;       //定义一个va_list类型的变量，用来储存单个参数
    va_start(args,usrChr); //使args指向可变参数的第一个参数
    vprintf(usrChr,args);  //必须用vprintf等带V的
    va_end(args);       //结束可变参数的获取
#endif
}

void gdebug_debug(const char *fun, int line, const char *time,const char *usrChr, ...)
{
#if PRINT_SWITCH_DEBUG
	char buffer[PRINT_LOG_DATA_SIZE] = {0};
	printf("[%s:%d][T%s] ",fun, line, time);
	snprintf(buffer, PRINT_LOG_DATA_SIZE, "[%s:%d][T%s] ", fun, line, time);
	
	va_list args;		//定义一个va_list类型的变量，用来储存单个参数
	va_start(args,usrChr); //使args指向可变参数的第一个参数	
	vprintf(usrChr,args);  //必须用vprintf等带V的
	vsnprintf(buffer+strlen(buffer), PRINT_LOG_DATA_SIZE, usrChr, args);
	va_end(args);		//结束可变参数的获取

	gdebug_LogWrite(buffer, strlen(buffer)); // 此处用strlen，因为实际看win端strlen包含了换行符，不在加1获得结束符，否则会有个0x00在换行第一个
#endif
}


void gdebug_perror(const char *fun, int line, const char *time,const char *usrChr, ...)
{
	printf("[%s:%d][T%s] ",fun, line, time);
	perror("perror:");
	printf(". ");
	va_list args;		    //定义一个va_list类型的变量，用来储存单个参数
	va_start(args,usrChr);  //使args指向可变参数的第一个参数
	vprintf(usrChr,args);	//必须用vprintf等带V的
	va_end(args);		    //结束可变参数的获取
}

// 打开日志文件
int gdebug_OpenLogFile()
{
	g_pFileOpt = NULL;
	g_pFileOpt = new CFileOpt;
	if (NULL == g_pFileOpt)
	{
    	printf("[%s:%d][T%s] new Log Opt failed.",__FUNCTION__, __LINE__, __TIME__);
		return -1;
	}

	if (g_pFileOpt->OpenFileOrCreate(DEBUG_LOG_PATH, "w") < 0)
	{
		printf("write file open failed. error.\n");
		return -1;
	}

	return 0;
}


// 将日志写入文件
int gdebug_LogWrite(char *data, const int Count)
{
	if (NULL == g_pFileOpt)
	{
		return -1;
	}
	
	g_pFileOpt->WriteFile(data, sizeof(char), Count);

	return 0;
}


// 程序结束关闭日志文件
int gdebug_CloseLogFile()
{
	if (NULL == g_pFileOpt)
	{
		return 0;
	}

	delete g_pFileOpt;

}


