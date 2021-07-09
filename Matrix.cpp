#include "Matrix.h"

CMatrix::CMatrix()
{
	
}

CMatrix::~CMatrix()
{

}


// 向量各个元素求次方 pow(double , double)所以不用模板
void CMatrix::NumPow(double const *matrixA, const int &Size, const double &powValu, double *matrixB)
{
	for (int i = 0; i < Size; i++)
	{
		matrixB[i] = pow(matrixA[i], powValu);
	}
	
	return;
}

// 四舍五入操作 整数浮点+0.5 负数浮点-0.5
double CMatrix::Round(const double &data)
{
	if (data > 0)
	{
		return data + 0.5;
	}
	else if (data < 0)
	{
		return data - 0.5;
	}	
	else
	{		
		return data;
	}	
	return data;
}



/*
CMatrix::CMatrix()
{
	
}

CMatrix::~CMatrix()
{

}




// 矩阵拷贝 A拷贝到B
void CMatrix::Matrix_Copy(std::complex<double> *matrixA, const int & lineSiz, const int & rowSiz, std::complex<double> *matrixB)
{
	for (int line = 0; line < lineSiz; line++)	// 原矩阵行
	{
		for (int row = 0; row < rowSiz; row++)	// 原矩阵列
		{
			matrixB[line*rowSiz + row] = matrixA[line*rowSiz + row];
		}
	}	
	return;
}

// 矩阵求逆
void CMatrix::Matrix_Inverse(   const int &size, std::complex<double> *matrixA)
{
	int lineSize = size;
	int rowSize 	= size * 2;
	// 新建一个扩展阵 增广矩阵
	std::complex<double> *MatTemp = new std::complex<double> [lineSize * rowSize];		// new !!!
	for (int i = 0; i < (lineSize * rowSize); i++)
	{
		MatTemp[i] = 0;
	}

	// 扩展矩阵初始化 拷贝matrixA 构造单位阵	
	for (int line = 0; line < lineSize; line++)
	{
		for (int row = 0; row < rowSize; row++)
		{
			if (row < size)				// 先拷贝matrixA到扩展阵
			{
				MatTemp[line*rowSize + row] = matrixA[line*size + row];
			}			
			else if (line == (row - size))	// 扩展部分初始化为单位阵
			{
				MatTemp[line*rowSize + row] = 1;
			}
			else
			{}
		}
	}
	
	std::complex<double> Zero = 0;
	for (int line = 0; line < lineSize; line++)
	{
		if (MatTemp[line*rowSize + line] == Zero)						// MatTemp[i][i] == 0
		{
			for (int k = line; k < size; k++)
			{
				if (MatTemp[k*rowSize + k] != Zero)
				{
					for (int row = 0; row < rowSize; row++)
					{
						std::complex<double> temp = 0;
						temp = MatTemp[line*rowSize + row];
						MatTemp[line*rowSize + row] = MatTemp[k*rowSize + row];
						MatTemp[k*rowSize + row] = temp;
					}
					break;
				}
			}
			// if k == size 矩阵不可逆			
		}

		for (int j = (rowSize-1); j >= line; j--)
		{
			MatTemp[line*rowSize + j] /= MatTemp[line*rowSize + line];
		}

		for (int kline = 0; kline < lineSize; kline++)
		{
			if (kline != line)
			{
				std::complex<double> temp = MatTemp[kline*rowSize + line];
				for (int jrow = 0; jrow < rowSize; jrow++)
				{
					MatTemp[kline*rowSize + jrow] -= (temp * MatTemp[line*rowSize + jrow]); 
				}				
			}
		}
	}

	// 结果
	for (int line = 0; line < lineSize; line++)
	{
		for (int row = size; row < rowSize; row++)
		{
			matrixA[line*size + (row-size)] = MatTemp[line*rowSize + row];
		}
	}	

	delete [] MatTemp;	// delete !!!

	return; 
}

// 矩阵乘法 A lineSizA行 Size列  B Size行 rowSizB列  Resoult  lineSizA行 rowSizB列
void CMatrix::Matrix_Mul(std::complex<double> *matrixA, const int &lineSizA, const int &Size
								, std::complex<double> *matrixB, const int &rowSizB
								, std::complex<double> *matResult)
{
	for (int line = 0; line < lineSizA; line++)	// A行
	{
		for (int row = 0; row < rowSizB; row++)  		// B列
		{
			for (int n = 0; n < Size; n++)		// 乘法求和 结果大小 lineSizA行 rowSizB列
			{
				matResult[line*rowSizB + row] += matrixA[line*Size + n] * matrixB[n*rowSizB + row];
			}
		}
	}
	
	return;
}

// 矩阵转置 输入matrix 返回matrix
void CMatrix::Matrix_Tran(std::complex<double> *matrix, const int &Size)
{
	std::complex<double> temp = 0;
	for (int line = 0; line < Size; line++)	// 原矩阵行
	{
		for (int row = 0; row < line; row++)	// 原矩阵列
		{
			temp = matrix[line*Size + row];			// 下三角
			matrix[line*Size + row] = matrix[row*Size + line];
			matrix[row*Size + line] = temp;
		}
	}
	return;
}

// 矩阵共轭     输入matrix 返回matrix
void CMatrix::Matrix_Conj(std::complex<double> *matrix, const int &lineSiz, const int &rowSiz)
{
	for (int line = 0; line < lineSiz; line++)	// 原矩阵行
	{
		for (int row = 0; row < rowSiz; row++)	// 原矩阵列
		{
			matrix[line*rowSiz + row] = std::conj(matrix[line*rowSiz + row]);
		}
	}	
	return;
}

// 矩阵R每层加上单位阵di di = sigma*eye(size(micloc,1))   R(:,:,I) = R(:,:,I)+di;   R[CHANNEL_NUM][CHANNEL_NUM][FFT_BINS]
void CMatrix::Matrix_R_Plus_di( const double &sigma, const int &size, std::complex<double> *R)
{
	for (int line = 0; line < size; ++line)
	{
		for (int row = 0; row < size; ++row)
		{
			if (line == row)
			{
				R[line*size + row] += sigma;		// sigma * 1 + R[][]
			}
		}
	}

}

// 将size大小的矩阵初始化成单位阵 sigma乘进单位阵的系数
void CMatrix::Matrix_EyeInit(const double &sigma, const int &size, double *matrix)
{
	for (int line = 0; line < size; ++line)
	{
		for (int row = 0; row < size; ++row)
		{
			if (line == row)
			{
				matrix[line*size + row] = sigma;
			}
			else
			{
				matrix[line*size + row] = 0;
			}			
		}
	}
	return;
}

// 矩阵上下翻转
void CMatrix::Matrix_UpDown(std::complex <double> *matrix, const int &Siz)
{
	std::complex<double> temp = 0;
	for (int row = 0; row < Siz; row++)
	{
		for (int line = 0; line < (Siz/2); line++)
		{
			temp = matrix[(Siz-1-line)*Siz + row];
			matrix[(Siz-1-line)*Siz + row] = matrix[line*Siz + row];
			matrix[line*Siz + row] = temp;
		}
	}

	return;
}

// 矩阵数乘    退化成一维数组 size=line*row
void CMatrix::Matrix_NumMult(std::complex <double> *matrixA, std::complex <double> *matrixB, const int Size)
{
	for (int line = 0; line < Size; line++)
	{
		matrixA[line] = matrixA[line] * matrixB[line];
	}
	
	return;
}

*/





