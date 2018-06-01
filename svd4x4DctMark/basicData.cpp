#include"basicData.h"

void mat2array(int* imageArray, Mat mat)
{
	for (int i = 0; i < mat.rows; i++) 
	{
		for (int j = 0; j < mat.cols; j++) 
		{
			*(imageArray+i*mat.rows+j) = (int)mat.at<uchar>(i, j);
		}
	}
}


void array2mat(int* imageArray, Mat mat) 
{
	for (int i = 0; i < mat.rows; i++)
	{
		for (int j = 0; j < mat.cols; j++) 
		{
			//*(imageArray + i*mat.rows + j) = (int)mat.at<uchar>(i, j);
			mat.at<uchar>(i, j) = uchar(*(imageArray + i*mat.cols + j));
		}
	}
}

void arraySplit(int* imageArray,int* subImageArray,dataRect* rect)
{
	int rowsNum = rect->rowsEnd - rect->rowsBegin;
	int colsNum = rect->colsEnd - rect->colsBegin;
	for (int i = 0; i < rowsNum; i++) 
	{
		for (int j = 0; j < colsNum; j++)
		{
			//std::cout<<*(imageArray + (i + rect->rowsBegin)*rect->cols + rect->colsBegin + j)<<std::endl;
			*(subImageArray + i*colsNum + j) = *(imageArray + (i + rect->rowsBegin)*rect->cols + rect->colsBegin + j);
		}
	}
}

void arrayInsert(int* imageArray, int* subImageArray, dataRect* rect)
{
	int rowsNum = rect->rowsEnd - rect->rowsBegin;
	//std::cout << "rowsNum: " << rowsNum << std::endl;
	int colsNum = rect->colsEnd - rect->colsBegin;
	//std::cout << "colsNum: " << colsNum << std::endl;
	for (int i = 0; i < rowsNum; i++)
	{
		for (int j = 0; j < colsNum; j++)
		{
			
			*(imageArray + (i + rect->rowsBegin)*rect->cols + rect->colsBegin + j) = *(subImageArray + i*colsNum + j);
			//*(imageArray + (i + rect->rowsBegin)*(rect->cols) + rect->colsBegin + j) = *(subImageArray + i*colsNum + j);
		}
	}
}