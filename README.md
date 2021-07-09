# someTools_FFT_Win_Matrix_FileOpt_Wav
  I wrote some tool classes, including FFT, matrix calculation, window function, file operation, wav file format, printing tools
  
DebugPrint： encapsulates a debug print file, which can be output to log file and can time the program

Fileopt： encapsulates the file operation. Create a new fileopt, open a file, and the file descriptor is in the class member variable. When the file is not used,close it and then destruct the class

Matrix： wrote some recently used matrix operations, can be used, but not easy to use, there is no definition of symbolic operation

tool_fft： fast Fourier transform and inverse transform, when creating a new instance, input the FFT sample size, execute initialization, and then you can use it

tool_win： Two window functions are written in win, Hamming window and Hanning window. Just use the header file

Wavefile： is the data structure of wav file header, which is used for file operation

自己写的一些工具类，包括FFT、矩阵计算、窗函数、文件操作、Wav文件格式、打印工具

DebugPrint封装了一个调试打印的，可以输出到log文件，可以对程序计时

FileOpt封装了文件操作，新建一个FileOpt打开一个文件，文件描述符在类成员变量里，文件不用了关闭后析构类就行

Matrix写了一些最近使用的矩阵运算，能用，但不好用，没有定义符号操作

tool_fft快速傅里叶变换和逆变换，新建实例的时候传入fft输入采样点大小，执行初始化，然后可以使用了

tool_win里面写了两个窗函数，汉明窗hamming和汉宁窗hanning，直接用头文件就行了

WaveFile是wav文件头的数据结构，文件操作的时候用就行了
