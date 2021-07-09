/*****************************************************/
/* WaveFile
 * Copyright (H) 2021/04/25 by 
 *
 * wave 文件操作
 * 
*/
/*****************************************************/


#ifndef _WAVEFILEOPT_
#define _WAVEFILEOPT_


//#define MAKE_FOURCC(a,b,c,d) \
//( ((uint32_t)d) | ( ((uint32_t)c) << 8 ) | ( ((uint32_t)b) << 16 ) | ( ((uint32_t)a) << 24 ) )

// four character codes
//#define FOURCC unsigned int 	// 此处重复定义了 注释掉
template <char ch0, char ch1, char ch2, char ch3> struct MakeFOURCC{	enum{ value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) };};
//unsigned int fourcc_fmt = MakeFOURCC<'f', 'm', 't', ' '>::value;

// RIFF file basic unit RIFF文件基本单元
/*
struct chunk
{
	unsigned int id;   		// 块标志
	unsigned int size; 		// 块大小
	unsigned char data[size]; 	// 块数据
};
*/

// The basic chunk of RIFF file format    RIFF chunk=id+size+data(other chunk)
struct Base_chunk
{ 
	unsigned int fcc;    			// FourCC id  uint32
	unsigned int cb_size; 	// 数据域的大小

	/*
	Base_chunk(unsigned int fourcc)	: fcc(fourcc)
	{
		cb_size = 0;
	}*/
}__attribute__((packed));


// Format chunk data field;     Format chunk. FORCC='f''m''t''' 
struct Wave_format
{
 
	unsigned short format_tag;	  		// WAVE的数据格式，PCM数据该值为1非压缩格式 不需要fact块
	unsigned short channels;		  	// 声道数 单声道1 立体声和双声道2 多声道交替存放
	unsigned int sample_per_sec;  	// 采样率 每个声道单位时间采样次数
	unsigned int bytes_per_sec;   	// 码率（传输速率），channels * sample_per_sec * bits_per_sample / 8
	unsigned short block_align;	  	// 音频数据块，数据块对齐单位，每次采样处理的数据大小，channels * bits_per_sample / 8 播放软件需要一次处理多个该值大小的字节数据，用该数值调整缓冲区
	unsigned short bits_per_sample; 	// 量化位数，采样位数，8、16、32等 小端模式 低位在低地址
	unsigned short ex_size;		  	// 增加后结构体对不齐 后用编译器指令忽略对齐 扩展块的大小，附加块的大小 有两种方法来设置不使用扩展块，一种是设置fmt中的size字段为16（无ex_size字段）；或者，有ex_size,设置其值为0.在本文中，使用第二种方法，设置ex_size的值为0，不使用扩展块。

	/*
	Wave_format()
	{
		format_tag		= 1; // PCM format data
		ex_size 		= 0; // don't use extesion field
 
		channels		= 0;
		sample_per_sec	= 0;
		bytes_per_sec	= 0;
		block_align 	= 0;
		bits_per_sample = 0;
	}
 
	Wave_format(unsigned short nb_channel, unsigned int sample_rate, unsigned short sample_bits)
		:channels(nb_channel), sample_per_sec(sample_rate), bits_per_sample(sample_bits)
	{
		format_tag	  = 0x01;											 // PCM format data
		bytes_per_sec = channels * sample_per_sec * bits_per_sample / 8; // 码率
		block_align   = channels * bits_per_sample / 8;
		ex_size 	  = 0;												 // don't use extension field
	}*/
}__attribute__((packed));


// Fact chunk 可选
/*
id FOURCC 'f''a''c''t'

size 数据与长度 4字节 最小值4

采样总数4字节
*/

// Data chunk
/*
id FOURCC 'd''a''t''a'

size 数据与长度 4字节 最小值4

data 具体音频数据
数据每个单位大小有量化位数决定 小端模式 多通道交叉存储可放多维数组
*/



/*
    数据格式为PCM的WAV文件头
    --------------------------------
    | Base_chunk | RIFF |
    ---------------------
    | WAVE              |
    ---------------------
    | Base_chunk | fmt  |   Header
    ---------------------
    | Wave_format|      |
    ---------------------
    | Base_chunk | data |
    --------------------------------
*/
struct strWaveHeader
{
	Base_chunk 	riff;
	unsigned int	waveFcc;
	Base_chunk 	fmt;		// fmt.c size 格式块的大小
	Wave_format fmtData;
	Base_chunk 	dataHead;
	//char 	data[0];	// char[0]sizeof不占字节
}__attribute__((packed));

// 使用boost库
/*
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

struct Wave_header{
 
    shared_ptr<Base_chunk> riff;
    FOURCC wave_fcc;
    shared_ptr<Base_chunk> fmt;
    shared_ptr<Wave_format>  fmt_data;
    shared_ptr<Base_chunk> data;
 
    Wave_header(unsigned short nb_channel, unsigned int sample_rate, unsigned short sample_bits)
    {
        riff      = make_shared<Base_chunk>(MakeFOURCC<'R', 'I', 'F', 'F'>::value);
        fmt       = make_shared<Base_chunk>(MakeFOURCC<'f', 'm', 't', ' '>::value);
        fmt->cb_size = 18;
 
        fmt_data  = make_shared<Wave_format>(nb_channel, sample_rate, sample_bits);
        data      = make_shared<Base_chunk>(MakeFOURCC<'d', 'a', 't', 'a'>::value);
 
        wave_fcc = MakeFOURCC<'W', 'A', 'V', 'E'>::value;
    }
 
    Wave_header()
    {
        riff         = nullptr;
        fmt          = nullptr;
 
        fmt_data     = nullptr;
        data         = nullptr;
 
        wave_fcc     = 0;
    }
};
*/




#endif


