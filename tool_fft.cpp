#include "tool_fft.h"

CFFT::CFFT(int size):Size(size)
{
	if (!CheckSize())
	{
		Debug_Error("Warning. Date Size not base 2. Size:%d", Size);
	}

	// 初始化单位根
	Init();
}

CFFT::~CFFT()
{
	if (NULL != m_pOmg)
	{
		delete [] m_pOmg;
	}
	m_pOmg = NULL;

	if (NULL != m_pInv)
	{
		delete [] m_pInv;
	}
	m_pInv = NULL;

}

// 基2傅里叶变换只能变长度为2的n次方的数据
bool CFFT::CheckSize()
{
	int len = Size;
	while(true)
	{
		len = len / 2;
		if (2 == len)
		{
			return true;
		}
		else if (len < 1)
		{
			Debug_Error("Warning. Date Size not base 2. Size:%d", Size);
			return false;
		}
		else
		{}
	}
	
	return true;
}

std::complex <double> CFFT::x(int k, int n, int inv)
{
	return std::complex <double>(cos(2 * PI_FFT * k/n), inv * sin(2 * PI_FFT * k/n));
}

// 初始化单位根
void CFFT::Init()
{
	m_pOmg = NULL;
	m_pOmg = new std::complex <double> [Size];
	if (NULL == m_pOmg)
	{
		Debug_Error("FFT Init Failed. new omg[] ERROR.\n");
		return;
	}

	m_pInv = NULL;
	m_pInv = new std::complex <double> [Size];
	if (NULL == m_pInv)
	{
		Debug_Error("FFT Init Failed. new inv[] ERROR.\n");
		return;
	}

	for (int i = 0; i < Size; i++)
	{
		m_pOmg[i] = x(i, Size, -1);
		m_pInv[i] = conj(m_pOmg[i]);
	}
}

int CFFT::fft(std::complex <double> *data, int step)
{
	if ((NULL == data) || (step < 0))
	{
		return -1;
	}
	
	fft(data, step, m_pOmg);
	return 0;
}

int CFFT::ifft(std::complex <double> *data, int step)
{
	if ((NULL == data) || (step < 0))
	{
		return -1;
	}
	
	fft(data, step, m_pInv);

	std::complex <double> N = {(double)Size, 0};

	for (int i = 0; i < Size; i++)
	{
		data[i * step] = data[i * step] / N;
	}

	return 0;
}

// 快速傅里叶变换 增加step就可以处理列
void CFFT::fft(std::complex <double> *data, int step, std::complex <double> *pOmg)
{
	int lim = 0;
	while ((1 << lim) < Size)
	{
		lim++;
	}

	for (int num = 0; num < Size; num++)
	{
		int numSwap = 0;
		for (int bitCnt = 0; bitCnt < lim; bitCnt++)
		{
			if ((num >> bitCnt) & 1)
			{
				numSwap |= (1 << (lim - bitCnt - 1));
			}
		}
		if (num < numSwap)
		{
			swap(data[num * step], data[numSwap * step]);
		}
	}

	for (int lay = 2; lay <= Size; lay *= 2)
	{
		int halfLay = lay / 2;
		for (int group = 0; group < Size; group += lay)
		{
			for (int i = 0; i < halfLay; i++)
			{
				std::complex <double> tmp = pOmg[Size / lay * i] * data[(group + i + halfLay) * step];
				data[(group + i + halfLay) * step] = data[(group + i) * step] - tmp;
				data[(group + i) * step] = data[(group + i) * step] + tmp;
			}
		}		
	}
	return;
}

