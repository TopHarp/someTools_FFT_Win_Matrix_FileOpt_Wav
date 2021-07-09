/*****************************************************/
/* tool_win.h
 * Copyright (H) 2021/05/07 by 
 *
 * tool_win 窗函数
 * 
*/
/*****************************************************/

#ifndef _TOOLWIN_
#define _TOOLWIN_

#include <math.h>

#define WIN_PI 			(3.141592653589793238462643383279)

class CWindow
{
	public:
		CWindow();
		~CWindow();

	public:

		// 汉宁窗
		template <typename Type> void hanning(Type amp, int size, Type win[]);
		// 海明窗
		template <typename Type> void hamming(Type amp, int size, Type win[]);
		// 模板需要定义和实现在一个文件
};


/********************************************************
 * amp增益 size最终生成的窗大小  win输出的窗
 * w(k)=0.5*(1-cos(2*pi*k/(N-1)))     0<=k<=N-1
 * 此公式与matlab帮助文档中写的不一样，文档中计算如下：
 * w = .5*(1 - cos(2*pi*(1:m)'/(n+1)));  i从1开始
 * 这个计算方法可以不带第一个和最后一个0
 * 此处按照matlab来
*********************************************************/
template <typename Type>
void CWindow::hanning(Type amp, int size, Type win[])
{
	// 在math.h有一个宏定义WIN_PI

	for (int i = 0; i < (size+1)/2; i++)
	{
		win[i] = amp * Type(0.50 - 0.50*cos((2.0*WIN_PI*(i+1)) / (size+1.0)));
		win[size - 1 - i] = win[i];
	}

	return;
}

/********************************************************
 * 汉明窗/海明窗
*********************************************************/
template <typename Type>
void CWindow::hamming(Type amp, int size, Type win[])
{ 
	for(int i = 0; i < (size+1)/2; i++)
	{
		win[i] = amp * Type(0.54 - 0.46*cos((2*WIN_PI*i) / (size - 1.0)));
		win[size - 1 - i] = win[i];
	}
 
	return;
}









#endif
