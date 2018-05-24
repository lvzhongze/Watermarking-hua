#pragma once
#include<iostream>
/***************************************************************************************

����:���
����:2018-05-16
����:
0���ṹ�� dataRect ������һ���������ݿ��������array�������п顣
1��mat2array ��һ��matת��άarray�ĺ�����
2��array2mat ��һ��arrayתmat�ĺ�����
3��arraySplit ��һ���з�array�ĺ�����

***************************************************************************************/

#include <opencv2/core/core.hpp>
using namespace cv;

//������һ���������ݿ��������array�������п顣
struct dataRect {
	int rowsBegin;			//�п�ʼλ�ã�����		
	int rowsEnd;			//�н���λ�ã�������
	int colsBegin;			//�п�ʼλ�ã�����
	int colsEnd;			//�н���λ�ã�������
	int cols;				//ԭ���������
};

void mat2array(int* imageArray,Mat mat);

/**************************************************************************************
����:				matתarray          
����:               imageArray������׵�ַ��һ��Ҫǿ��(int*)ת��������mat��һ����ά��mat��
���:				�޷���ֵ������ͨ��ֱ��ʹ��ָ�룬��������
����ֵ:
�����嵥:
����:         
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
����:				arrayתmat
����:               imageArray������׵�ַ��һ��Ҫǿ��(int*)ת��������mat��һ����ά��mat��
���:				�޷���ֵ������ͨ��ֱ��ʹ��ָ�룬��������
����ֵ:
�����嵥:
����:
**************************************************************************************/

void arraySplit(int* imageArray, int* subImageArray, dataRect* rect);
/**************************************************************************************
����:				����rect�����и��һ����ά����
����:               imageArray������׵�ַ��һ��Ҫǿ��(int*)ת��������subImageArray�Ǵ��
					�и�󷵻������ָ�롣rect��һ��dataRect�ṹ�塣
���:				�޷���ֵ������ͨ��ֱ��ʹ��ָ�룬��������
����ֵ:
�����嵥:
����:
**************************************************************************************/

void arrayInsert(int* imageArray, int* subImageArray, dataRect* rect);
/**************************************************************************************
����:				����rect����Ƕ��һ����ά�������滻ԭ��������
����:               imageArray������׵�ַ��һ��Ҫǿ��(int*)ת��������subImageArray�Ǵ��
					�и�󷵻������ָ�롣rect��һ��dataRect�ṹ�塣
���:				�޷���ֵ������ͨ��ֱ��ʹ��ָ�룬��������
����ֵ:
�����嵥:
����:
**************************************************************************************/


template<unsigned N>
void mat2array4x4(Mat image, int (&imageArray)[N])
/**************************************************************************************
����:				�������mat��ʽ��imageת����һά���飬ת���Ĳ�������ÿ��4x4С��Ϊ��λ
����:               mat��ʽ��image
				    imageArray��һ��һά���飬���С��image.rows*image.cols
���:				
����ֵ:
�����嵥:
����:
**************************************************************************************/
{
	//ʹ��k����¼һά������±�
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
				
				k = k + 16;		//ÿ����16����Ҳ����һ��4x4С�飩kҪ��16
		}
	}
}

template<unsigned N>
void array2mat4x4(Mat image, int(&imageArray)[N])
/**************************************************************************************
����:				�������һά����ת����mat��ת���Ĳ�������ÿ��4x4С��Ϊ��λ
����:               mat��ʽ��image
					
					imageArray��һ��һά���飬���С��image.rows*image.cols
���:
����ֵ:
�����嵥:
����:
**************************************************************************************/
{
	int k = 0;		//ʹ��k����¼һά������±�
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

				k = k + 16;		//ÿ����16����Ҳ����һ��4x4С�飩kҪ��16
		}
	}
}