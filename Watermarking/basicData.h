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