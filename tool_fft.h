/*****************************************************/
/* tool_fft.h
 * Copyright (H) 2021/05/07 by 
 *
 * fft 快速傅里叶变换
 * 
*/
/*****************************************************/

#ifndef _FFT_
#define _FFT_

#include <math.h>
#include <stdio.h>
#include <complex.h>
#include "DebugPrint.h"

//#define cp std::complex <double>
#define PI_FFT (3.141592653589793238462643383279)
	//(3.141592653589793)

class CFFT
{
	public:
		CFFT(int size);
		~CFFT();
		
		// 基2傅里叶变换只能变长度为2的n次方的数据
		bool CheckSize();
		// 初始化单位根
		void Init();
		// 点值转系数 不需要跳跃处理step写0
		int fft(std::complex <double> *data, int step);
		// 系数转点值
		int ifft(std::complex <double> *data, int step);

	private:		
		std::complex <double> x(int k, int n, int inv);
		void fft(std::complex <double> *data, int step, std::complex <double> *pOmg);
		int Size;	// 处理数据大小
		
		std::complex <double> *m_pOmg;  // 单位根
		std::complex <double> *m_pInv;

};


#endif


