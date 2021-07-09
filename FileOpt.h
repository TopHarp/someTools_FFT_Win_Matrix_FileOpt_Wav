#ifndef _FILEOPT_
#define _FILEOPT_

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include <stddef.h>

#include "DebugPrint.h"


// 一个文件操作类 只存一个fd类在内部
class CFileOpt
{
    public:
        CFileOpt();
        ~CFileOpt();
		
		/* flag
			r 以只读方式打开文件，该文件必须存在。

		　　r+ 以可读写方式打开文件，该文件必须存在。

		　　rb+ 读写打开一个二进制文件，只允许读写数据。

		　　rt+ 读写打开一个文本文件，允许读和写。

		　　w 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。

		　　w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。

		　　a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）

		　　a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）

		　　wb 只写打开或新建一个二进制文件；只允许写数据。

		　　wb+ 读写打开或建立一个二进制文件，允许读和写。

		　　wt+ 读写打开或着建立一个文本文件；允许读写。

		　　at+ 读写打开一个文本文件，允许读或在文本末追加数据。

		　　ab+ 读写打开一个二进制文件，允许读或在文件末追加数据。 
		*/
        int OpenFileOrCreate(const char *pathname, const char *flag);
		/*
		 * origin 从哪个位置开始偏移offset个字节
		 * SEEK_SET 文件头
		 * SEEK_CUR 当前文件指针
		 * SEEK_END 文件末尾
		*/
        int SeekFile(long offset, int origin);
		// 获取文件大小
		size_t GetFileSize();
        size_t ReadFile(char *readData, const int &size, const int &readCount);
        size_t WriteFile(char *data, const int &size, const int &writeCount);
        int CloseFile();
        int MakeDir(const char *pathName);


    private:
        //int m_Openfd;
		FILE *m_Openfp;


};

#endif







