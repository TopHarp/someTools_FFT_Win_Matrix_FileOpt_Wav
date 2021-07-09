#ifndef _MATRIX_
#define _MATRIX_


#include <math.h>
#include <complex>
#include "DebugPrint.h"



class CMatrix
{
	public:
		CMatrix();
		~CMatrix();

		// 向量各个元素求次方 不用模板
		void NumPow(double const *matrixA, const int &Size, const double &powValu, double *matrixB);
		// 四舍五入操作 整数浮点+0.5 负数浮点-0.5
		double Round(const double &data);


		/*******成员模板************/

		// 矩阵拷贝 A拷贝到B
		template <typename Type>
		void Copy(Type *matrixA, const int & lineSiz, const int & rowSiz, Type *matrixB);
		// 矩阵拷贝 将A以块形式按照m行 n列拷贝到B 注意B的总尺寸 防止溢出
		template <typename Type>
		void repmat(Type *matrixA, const int & lineSiz, const int & rowSiz
							,const int & mSiz, const int &nSiz, Type *matrixB);
		// 一位数组看做队列 先进后出
		template <typename Type>
		void queuePushOne(Type *ArrayA, const int & Siz, const Type &pushValu);

		// 矩阵求逆
		template <typename Type>
		void Inverse(const     int &size, Type *matrixA);
		
		// 矩阵乘法 A lineSizA行 Size列  B Size行 rowSizB列  Resoult  lineSizA行 rowSizB列
		template <typename Type>
		void Mul(Type *matrixA,    const int &lineSizA, const int &Size
								, Type *matrixB, const int &rowSizB
								, Type *matResult);
		// 矩阵数乘
		template <typename Type>
		void NumMult(Type *matrixA, const Type &Num, const int &Size);
		template <typename Type>
		void NumMult(Type *matrixA, const Type &Num, const int &Size, Type *resultMat);
		// 矩阵点乘    退化成一维数组 size=line*row
		template <typename Type>
		void PointMult(Type *matrixA, Type *matrixB, const int &Size);

		
		// 矩阵加法
		template <typename Type>
		void Plus(Type *matrixA, const int &lineSiz, const int &rowSiz, Type *matrixB);	
		// 矩阵加数字
		template <typename Type>
		void NumPlus(Type *matrixA, const int &Size, const double Num, Type *matrixB);
		// 矩阵R每层加上单位阵di di = sigma*eye(size(micloc,1))   R(:,:,I) = R(:,:,I)+di;
		template <typename Type>
		void R_Plus_di(const double &sigma, const int &size, Type *R);
		
		// 矩阵转置 输入matrix 返回matrix
		template <typename Type>
		void Tran(Type *matrix, const int &Size);
		// 矩阵共轭     输入matrix 返回matrix
		template <typename Type>
		void Conj(Type *matrix, const int &lineSiz, const int &rowSiz);
		
		// 将size大小的矩阵初始化成单位阵 sigma乘进单位阵的系数
		template <typename Type>
		void EyeInit(const double &sigma, const int &size, Type *matrix);
		// 矩阵上下翻转
		template <typename Type>
		void UpDown(Type *matrix, const int &lineSiz, const int &rowSiz);
		
		// 数除 矩阵没个元素对应相除 结果放入result
		template <typename Type>
		void PointDiv(Type *matrixA, Type *matrixB, const int &Size, Type *resultMat);
		// 矩阵 向量 除以数    退化成一维数组 size=line*row
		template <typename Type> 
		void NumDiv(Type *matrixA, const int &Size, Type &divValue);
		
		// 向量求各元素和
		template <typename Type> 
		void Sum(Type *matrixA, const int &Size, Type &result);
		// 向量求均值 矩阵退化为一维数组也可求 size=line*row
		template <typename Type> 
		void Mean(Type *matrixA, const int &Size, Type &result);	
		// 数组各元素取最大的 结果放在result数组中
		template <typename Type> 
		void Max(Type *matrixA, Type *matrixB, const int &Size, Type	*resultMat);
		template <typename Type> 
		void Max(Type *matrixA,    const Type &Num, const int &Size, Type *resultMat);
		// 数组各元素取最小的 结果放在result数组中
		template <typename Type>
		void Min(Type *matrixA, Type *matrixB, const int &Size, Type *resultMat);
		// 找到每行中的元素最小值 列向量 输出到resultmat中
		template <typename Type>
		void Min(Type *matrixA, const int &lineSiz, const int &rowSiz, Type *resultMat);

		// 向量卷积 ArrayA	ArrayB  注意大小resultArray[SizA+SizB-1]
		template <typename Type>
		void Conv(Type *ArrayA, const int &SizA, Type *ArrayB, const int &SizB, Type *resultArray);
		
		// 指数积分
		template <typename Type>
		Type expint(const Type &x);


		/*******成员模板END************/


		

		

};



/*
// 没有定义类模板 只定义了成员模板 此处默认构造函数在这里实现 会编译提示重复定义  所以注释掉
CMatrix::CMatrix()
{
	
}

CMatrix::~CMatrix()
{

}*/



// 矩阵拷贝 A拷贝到B
template <typename Type>
void CMatrix::Copy(Type *matrixA, const int & lineSiz, const int & rowSiz, Type *matrixB)
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

// 矩阵拷贝 将A以块形式按照m行 n列拷贝到B 注意B的总尺寸 防止溢出
template <typename Type>
void CMatrix::repmat(Type *matrixA, const int & lineSiz, const int & rowSiz
						,const int & mSiz, const int &nSiz, Type *matrixB)
{
	for (int m = 0; m < mSiz; m++)						// m行
	{
		for (int line = 0; line < lineSiz; line++) 		// 原矩阵行
		{
			for (int n = 0; n < nSiz; n++)				// n列
			{
				for (int row = 0; row < rowSiz; row++)	// 原矩阵列
				{
					matrixB[((m*lineSiz + line)*nSiz*rowSiz) + (n*rowSiz + row)] = matrixA[line*rowSiz + row];
				}
			}
		}		
	}

	return;
}

// 一位数组看做队列 先进后出
template <typename Type>
void CMatrix::queuePushOne(Type *ArrayA, const int & Siz, const Type &pushValu)
{
	for (int i = 0; i < (Siz-1); i++)
	{
		ArrayA[i] = ArrayA[i+1];
	}
	ArrayA[Siz-1] = pushValu; 
	return;
}

// 矩阵求逆
template <typename Type>
void CMatrix::Inverse(   const int &size, Type *matrixA)
{
	int lineSize = size;
	int rowSize 	= size * 2;
	// 新建一个扩展阵 增广矩阵
	Type *MatTemp = new Type [lineSize * rowSize];		// new !!!
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
	
	Type Zero = 0;
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
						Type temp = 0;
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
				Type temp = MatTemp[kline*rowSize + line];
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
template <typename Type>
void CMatrix::Mul(Type *matrixA, const int &lineSizA, const int &Size
								, Type *matrixB, const int &rowSizB
								, Type *matResult)
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

// 矩阵点乘    退化成一维数组 size=line*row
template <typename Type>
void CMatrix::PointMult(Type *matrixA, Type *matrixB, const int &Size)
{
	for (int line = 0; line < Size; line++)
	{
		matrixA[line] = matrixA[line] * matrixB[line];
	}
	
	return;
}

// 矩阵数乘
template <typename Type>
void CMatrix::NumMult(Type *matrixA, const Type &Num, const int &Size)
{
	for (int line = 0; line < Size; line++)
	{
		matrixA[line] = matrixA[line] * Num;
	}
	
	return;
}
template <typename Type>
void CMatrix::NumMult(Type *matrixA, const Type &Num, const int &Size, Type *resultMat)
{
	for (int line = 0; line < Size; line++)
	{
		resultMat[line] = matrixA[line] * Num;
	}
	
	return;
}




// 矩阵转置 输入matrix 返回matrix
template <typename Type>
void CMatrix::Tran(Type *matrix, const int &Size)
{
	Type temp = 0;
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
template <typename Type>
void CMatrix::Conj(Type *matrix, const int &lineSiz, const int &rowSiz)
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

// 矩阵加法
template <typename Type>
void CMatrix::Plus(Type *matrixA, const int &lineSiz, const int &rowSiz, Type *matrixB)
{
	for (int line = 0; line < lineSiz; ++line)
	{
		for (int row = 0; row < rowSiz; ++row)
		{
			matrixB[line*rowSiz + row] += matrixA[line*rowSiz + row];
		}
	}
}

// 矩阵加数字
template <typename Type>
void CMatrix::NumPlus(Type *matrixA, const int &Size, const double Num, Type *matrixB)
{
	for (int i = 0; i < Size; ++i)
	{		
		matrixB[i] = matrixA[i] + Num;
	}
	return;
}

// 矩阵R每层加上单位阵di di = sigma*eye(size(micloc,1))   R(:,:,I) = R(:,:,I)+di;   R[CHANNEL_NUM][CHANNEL_NUM][FFT_BINS]
template <typename Type>
void CMatrix::R_Plus_di( const double &sigma, const int &size, Type *R)
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
template <typename Type>
void CMatrix::EyeInit(const double &sigma, const int &size, Type *matrix)
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
template <typename Type>
void CMatrix::UpDown(Type *matrix, const int &lineSiz, const int &rowSiz)
{
	Type temp = 0;
	for (int row = 0; row < rowSiz; row++)
	{
		for (int line = 0; line < (lineSiz/2); line++)
		{
			temp = matrix[(lineSiz-1-line)*rowSiz + row];
			matrix[(lineSiz-1-line)*rowSiz + row] = matrix[line*rowSiz + row];
			matrix[line*rowSiz + row] = temp;
		}
	}

	return;
}

// 数除 矩阵没个元素对应相除 结果放入result
template <typename Type>
void CMatrix::PointDiv(Type *matrixA, Type *matrixB, const int &Size, Type *resultMat)
{
	for (int line = 0; line < Size; line++)
	{
		if (0 == matrixB[line])
		{
			//Debug_Error("Warning:Divisor cannot be zero. matrixB[%d]:0x%x\n", line, matrixB[line]);
			continue;
		}
		
		resultMat[line] = matrixA[line] / matrixB[line];
	}
	
	return;
}


// 矩阵 向量 除以数    退化成一维数组 size=line*row
template <typename Type>
void CMatrix::NumDiv(Type *matrixA, const int &Size, Type &divValue)
{
	if (0 == divValue)
	{
		//Debug_Error("ERROR. Divisor cannot be zero. divValue is :%d\n", divValue);
		return;
	}

	for (int line = 0; line < Size; line++)
	{
		matrixA[line] /= divValue;
	}
	
	return;
}

// 向量求各元素和
template <typename Type>
void CMatrix::Sum(Type *matrixA, const int &Size, Type &result)
{
	Type out = 0;
	for (int i =  0; i < Size; i++)
	{
		out += matrixA[i]; 
	}
	result = out;
	
	return;
}

// 向量求均值 矩阵退化为一维数组也可求 size=line*row
template <typename Type>
void CMatrix::Mean(Type *matrixA, const int &Size, Type &result)
{
	if (Size <= 0)
	{
		Debug_Error("ERROR. Divisor cannot be zero. Size is :%d\n", Size);
		return;
	}
	Type out = 0;
	Sum(matrixA, Size, out);
	out /= (double)Size;
	result = out;
	
	return;
}



// 数组各元素取最大的 结果放在result数组中
template <typename Type>
void CMatrix::Max(Type *matrixA, Type *matrixB, const int &Size, Type *resultMat)
{
	for (int line = 0; line < Size; line++)
	{
		resultMat[line] = matrixA[line] > matrixB[line] ? matrixA[line] : matrixB[line];
	}
	
	return;
}

template <typename Type>
void CMatrix::Max(Type *matrixA, const Type &Num, const int &Size, Type *resultMat)
{
	for (int line = 0; line < Size; line++)
	{
		resultMat[line] = matrixA[line] > Num ? matrixA[line] : Num;
	}
	
	return;
}

// 数组各元素取最小的 结果放在result数组中
template <typename Type>
void CMatrix::Min(Type *matrixA, Type *matrixB, const int &Size, Type *resultMat)
{
	for (int line = 0; line < Size; line++)
	{
		resultMat[line] = (matrixA[line] < matrixB[line]) ? matrixA[line] : matrixB[line];
	}
	
	return;
}

// 找到每行中的元素最小值 列向量 输出到resultmat中
template <typename Type>
void CMatrix::Min(Type *matrixA, const int &lineSiz, const int &rowSiz, Type *resultMat)
{
	for (int line = 0; line < lineSiz; line++)
	{
		Type temp = matrixA[line*rowSiz];
		for (int row = 0; row < rowSiz; row++)
		{
			temp = (matrixA[line*rowSiz + row] < temp)  ?  matrixA[line*rowSiz + row] : temp;			
		}
		resultMat[line] = temp;
	}
	
	return;
}




// 向量卷积 ArrayA  ArrayB resultArray 结果向量大小 SizA+SizB-1
template <typename Type>
void CMatrix::Conv(Type *ArrayA, const int &SizA, Type *ArrayB, const int &SizB, Type *resultArray)
{
	int Allsize = SizA + SizB - 1;

	for (int i = 0; i < Allsize; i++)
	{
		for (int j = ((i+1-SizB) > 0 ? (i+1-SizB):0); j <= (i < (SizA-1) ? i : (SizA-1)); j++)
		{
			resultArray[i] += ArrayA[j] * ArrayB[i - j];
		}
	}

	return;
}


// 指数积分
template <typename Type>
Type CMatrix::expint(const Type &x)
{

	double a0, a1, a2, a3, a4, a5, x2, x3, x4, x5;
	double expint, b1, b2, b3, b4;

	if (x <= 1.0)
	{
		a0 = -0.57721566;
		a1 = 0.99999193;
		a2 = -0.24991055;
		a3 = 0.05519968;
		a4 = -0.00976004;
		a5 = 0.00107857;

		x2 = x * x;
		x3 = x * x2;
		x4 = x * x3;
		x5 = x * x4;

		expint = -log(x) + a0 + a1 * x + a2 * x2 +
			a3 * x3 + a4 * x4 + a5 * x5;


	}
	else
	{

		a1 = 8.5733287401;
		a2 = 18.0590169730;
		a3 = 8.6347608925;
		a4 = .2677737343;

		b1 = 9.5733223454;
		b2 = 25.6329561486;
		b3 = 21.0996530827;
		b4 = 3.9584969228;

		x2 = x * x;
		x3 = x * x2;
		x4 = x * x3;
		expint = (x4 + a1 * x3 + a2 * x2 + a3 * x + a4)
			/ (x4 + b1 * x3 + b2 * x2 + b3 * x + b4) / (x * exp(x));
	}
	return expint;




}













#endif
