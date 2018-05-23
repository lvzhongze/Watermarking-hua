#pragma once
#include<iostream>
/***************************************************************************************

作者:李华超
日期:2018-05-16
描述:
0）结构体 dataRect 描述了一个矩形数据块儿，用于array的数据切块。
1）mat2array 是一个mat转二维array的函数。
2）array2mat 是一个array转mat的函数。
3）arraySplit 是一个切分array的函数。

***************************************************************************************/

#include <opencv2/core/core.hpp>
using namespace cv;

//描述了一个矩形数据块儿，用于array的数据切块。
struct dataRect {
	int rowsBegin;			//行开始位置，包含		
	int rowsEnd;			//行结束位置，不包含
	int colsBegin;			//列开始位置，包含
	int colsEnd;			//列结束位置，不包含
	int cols;				//原数组的列数
};

void mat2array(int* imageArray,Mat mat);

/**************************************************************************************
描述:				mat转array          
输入:               imageArray数组的首地址，一般要强制(int*)转换而来，mat是一个二维的mat。
输出:				无返回值，但是通过直接使用指针，完成输出。
返回值:
调用清单:
其他:         
**************************************************************************************/

template<unsigned N>
void mat2oneDarray(int (&imageArray)[N], Mat mat)
{
	for (int i = 0; i < mat.rows; i++)
	{
		for (int j = 0; j < mat.cols; j++)
		{
			//cout << "mat.at<uchar>(i, j)" << (int)mat.at<uchar>(i, j) << endl;
			imageArray[i*mat.cols+j] = mat.at<uchar>(i, j);
		}
	}
}

template<unsigned N>
void oneDarray2mat(int(&imageArray)[N], Mat mat)
{
	for (int i = 0; i < mat.rows; i++)
	{
		for (int j = 0; j < mat.cols; j++)
		{
			mat.at<uchar>(i, j) = (uchar)imageArray[i*mat.cols + j];
		}
	}
}

void array2mat(int* imageArray, Mat mat);
/**************************************************************************************
描述:				array转mat
输入:               imageArray数组的首地址，一般要强制(int*)转换而来，mat是一个二维的mat。
输出:				无返回值，但是通过直接使用指针，完成输出。
返回值:
调用清单:
其他:
**************************************************************************************/

void arraySplit(int* imageArray, int* subImageArray, dataRect* rect);
/**************************************************************************************
描述:				根据rect描述切割出一个二维数组
输入:               imageArray数组的首地址，一般要强制(int*)转换而来。subImageArray是存放
					切割后返回数组的指针。rect是一个dataRect结构体。
输出:				无返回值，但是通过直接使用指针，完成输出。
返回值:
调用清单:
其他:
**************************************************************************************/

void arrayInsert(int* imageArray, int* subImageArray, dataRect* rect);
/**************************************************************************************
描述:				根据rect描述嵌入一个二维数组来替换原来的数组
输入:               imageArray数组的首地址，一般要强制(int*)转换而来。subImageArray是存放
					切割后返回数组的指针。rect是一个dataRect结构体。
输出:				无返回值，但是通过直接使用指针，完成输出。
返回值:
调用清单:
其他:
**************************************************************************************/