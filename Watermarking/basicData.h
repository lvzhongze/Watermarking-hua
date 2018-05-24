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


template<unsigned N>
void mat2array4x4(Mat image, int (&imageArray)[N])
/**************************************************************************************
描述:				将输入的mat格式的image转换成一维数组，转换的策略是以每个4x4小块为单位
输入:               mat格式的image
				    imageArray是一个一维数组，其大小是image.rows*image.cols
输出:				
返回值:
调用清单:
其他:
**************************************************************************************/
{
	//使用k来记录一维数组的下标
	int k = 0;
	for (int i = 0; i < image.rows; i = i+4) {
		for (int j = 0; j < image.cols; j = j+4) {
			
				imageArray[k] = (int)image.at<uchar>(i, j);  //block[0]
				imageArray[k + 1] = (int)image.at<uchar>(i, j + 1);  //block[1]
				imageArray[k + 2] = (int)image.at<uchar>(i, j + 2);  //block[2]
				imageArray[k + 3] = (int)image.at<uchar>(i, j + 3);  //block[3]

				imageArray[k + 4] = (int)image.at<uchar>(i + 1, j);  //block[4]
				imageArray[k + 5] = (int)image.at<uchar>(i + 1, j + 1);  //block[5]
				imageArray[k + 6] = (int)image.at<uchar>(i + 1, j + 2);  //block[6]
				imageArray[k + 7] = (int)image.at<uchar>(i + 1, j + 3);  //block[7]

				imageArray[k + 8] = (int)image.at<uchar>(i + 2, j);  //block[8]
				imageArray[k + 9] = (int)image.at<uchar>(i + 2, j + 1);  //block[9]
				imageArray[k + 10] = (int)image.at<uchar>(i + 2, j + 2);  //block[10]
				imageArray[k + 11] = (int)image.at<uchar>(i + 2, j + 3);  //block[11]

				imageArray[k + 12] = (int)image.at<uchar>(i + 3, j);  //block[12]
				imageArray[k + 13] = (int)image.at<uchar>(i + 3, j + 1);  //block[13]
				imageArray[k + 14] = (int)image.at<uchar>(i + 3, j + 2);  //block[14]
				imageArray[k+15] = (int)image.at<uchar>(i + 3, j + 3);  //block[15]
				
				k = k + 16;		//每复制16个（也就是一个4x4小块）k要加16
		}
	}
}

template<unsigned N>
void array2mat4x4(Mat image, int(&imageArray)[N])
/**************************************************************************************
描述:				将输入的一维数组转换成mat，转换的策略是以每个4x4小块为单位
输入:               mat格式的image
					
					imageArray是一个一维数组，其大小是image.rows*image.cols
输出:
返回值:
调用清单:
其他:
**************************************************************************************/
{
	int k = 0;		//使用k来记录一维数组的下标
	for (int i = 0; i < image.rows; i += 4) {
		for (int j = 0; j < image.cols; j += 4) {
			
				image.at<uchar>(i, j) = (uchar)imageArray[k];				//block[0]
				image.at<uchar>(i, j + 1) = (uchar)imageArray[k + 1];		//block[1]
				image.at<uchar>(i, j + 2) = (uchar)imageArray[k + 2];		//block[2]
				image.at<uchar>(i, j + 3) = (uchar)imageArray[k + 3];		//block[3]
				image.at<uchar>(i + 1, j) = (uchar)imageArray[k + 4];		//block[4]
				image.at<uchar>(i + 1, j + 1) = (uchar)imageArray[k + 5];	//block[5]
				image.at<uchar>(i + 1, j + 2) = (uchar)imageArray[k + 6];	//block[6]
				image.at<uchar>(i + 1, j + 3) = (uchar)imageArray[k + 7];	//block[7]

				image.at<uchar>(i + 2, j) = (uchar)imageArray[k + 8];		//block[8]
				image.at<uchar>(i + 2, j + 1) = (uchar)imageArray[k + 9];	//block[9]
				image.at<uchar>(i + 2, j + 2) = (uchar)imageArray[k + 10];	//block[10]
				image.at<uchar>(i + 2, j + 3) = (uchar)imageArray[k + 11];	//block[11]

				image.at<uchar>(i + 3, j) = (uchar)imageArray[k + 12];		//block[12]
				image.at<uchar>(i + 3, j + 1) = (uchar)imageArray[k + 13];	//block[13]
				image.at<uchar>(i + 3, j + 2) = (uchar)imageArray[k + 14];	//block[14]
				image.at<uchar>(i + 3, j + 3) = (uchar)imageArray[k + 15];	//block[15]

				k = k + 16;		//每复制16个（也就是一个4x4小块）k要加16
		}
	}
}