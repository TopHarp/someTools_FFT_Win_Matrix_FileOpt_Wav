#include "tool_win.h"
CWindow::CWindow()
{

}

CWindow::~CWindow()
{

}


/*
CWindow::CWindow()
{

}

CWindow::~CWindow()
{

}


void CWindow::hanning(const double &amp, const rm_int32_t size, double *win)
{
	for (rm_int32_t i = 0; i < (size+1)/2; i++)
	{
		win[i] = amp * (0.54 - 0.46*cos((2*M_PI*i) / (size-1.0)));
		win[size - 1 - i] = win[i]; 	
	}

	return;
}*/


// amp增益 size最终生成的窗大小  win输出的窗
// w(k)=0.5*(1-cos(2*pi*k/(N-1)))     0<=k<=N-1
/*
template <typename Type>
void CWindow::hanning(Type amp, rm_int32_t size, double win[])
{
	// 在math.h有一个宏定义M_PI

	for (rm_int32_t i = 0; i < (size+1)/2; i++)
	{
		win[i] = amp * Type(0.54 - 0.46*cos((2*M_PI*i) / (size-1.0)));
		win[size - 1 - i] = win[i];		
	}

	return;
}*/








