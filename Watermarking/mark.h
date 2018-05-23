#pragma once
#include"basicData.h"
#include"dct.h"
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
enum disorder{nothing,arnold};

struct dctParameter {
	int imageM=800;				//输入图像像素点的行数
	int imageN=800;				//输入图像像素点的列数
	int waterMarkM=200;			//水印像素点的行数
	int waterMarkN=200;			//水印像素点的列数
	disorder disorderPara = nothing;	//置乱方法的选择参数，默认不做置乱
	int dctNum = 4;			//dct变换的参数，默认4x4
};

int dctEmbed(int* imageArray, int* waterMarkArray, dctParameter* para);
/**************************************************************************************
描述:				此函数为水印嵌入操作
输入:               imageArray原图像，一般要强制(int*)转换而来；waterMarkArray是水印图像；
					para是dct变换的输入参数，类型为dctParameter，初始值为	
					imageM=800;				//输入图像像素点的行数
					imageN=800;				//输入图像像素点的列数
					waterMarkM=200;			//水印像素点的行数
					waterMarkN=200;			//水印像素点的列数
					disorderPara = nothing;	//置乱方法的选择参数，默认不做置乱
					dctNum = 4;			//dct变换的参数，默认4x4
输出:				无返回值，imageArray为带有水印的图像。
返回值:
调用清单:			void arraySplit(int* imageArray, int* subImageArray, dataRect* rect)
					void dct2d4x4(int(*data)[4],int blockSize)
					void idct2d4x4(int(*data)[4],int blockSize)
其他:
**************************************************************************************/

int dctExtra(int* imageArray, int* afterDctImageArray, int* waterMarkArray, dctParameter* para);
/**************************************************************************************
描述:				此函数为水印提取操作
输入:               imageArray原图像；afterDctImageArray是嵌入水印之后的图像；
					waterMarkArray是水印图像或者相同大小的数组即可；
					para是dct变换的输入参数，类型为dctParameter。
输出:				提取的水印waterMarkArray。
返回值:
调用清单:			void arraySplit(int* imageArray, int* subImageArray, dataRect* rect)
					void dct2d4x4(int(*data)[4],int blockSize)
其他:
**************************************************************************************/

template<unsigned M, unsigned N>
double getNC(const int(&arrayo)[M][N], const int(&arrayr)[M][N])
{
	double numerator = 0;			//分子
	double denominator = 0;			//分母
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			numerator += arrayo[i][j] * arrayr[i][j];
			denominator += arrayo[i][j] * arrayo[i][j];
		}
	}
	return numerator / denominator;
}

/*
double getPSNR(const Mat& I1, const Mat& I2)
{
	Mat s1;
	absdiff(I1, I2, s1);       // |I1 - I2|
	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
	s1 = s1.mul(s1);           // |I1 - I2|^2

	Scalar s = sum(s1);         // sum elements per channel

	double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

	if (sse <= 1e-10) // for small values return zero
		return 0;
	else
	{
		double  mse = sse / (double)(I1.channels() * I1.total());
		double psnr = 10.0*log10((255 * 255) / mse);
		return psnr;
	}
}
*/
double getPSNR(const Mat& I1, const Mat& I2);

void rotateImage(IplImage* img, IplImage *img_rotate, int degree);