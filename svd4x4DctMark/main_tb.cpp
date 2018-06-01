#include"svdEmbed.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "svdEmbed.h"
#include "basicData.h"
#include <string>
using namespace cv;
using namespace std;
int imageArray0[800][800],imageArray1[800][800],waterMarkArray0[200][200],svdImageArray[800][800],waterMarkArrayIsvd[200][200];


double getNC(cv::Mat mark0, cv::Mat mark1)
{
	{
		double fenzi = 0.0; //分子
		double fenmu = 0.0;//分母

		Mat square_mark = mark0 * 2; //使用*计算矩阵与标量相乘，矩阵与矩阵相乘；
		for (int i = 0; i < mark0.rows; i++)
		{
			for (int j = 0; j < mark0.rows; j++)
			{
				fenzi += (double)mark0.at<uchar>(i, j);
				fenmu += (double)square_mark.at<uchar>(i, j);
			}
		}
		return fenzi / fenmu;

	}
}

double getPNSR(const cv::Mat& I1, const cv::Mat& I2)
{
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
}

int main()
{

	vector<Mat> imageMat, waterMarkMat;
	Mat image0,svdImage0,waterMark0, imageSVD, waterMark1,result,image1;
	Mat image = imread("8.jpg");
	Mat waterMark = imread("01.jpg");
	imshow("原图", image);
	//svdEmbed(float imageArray[800][800],float waterMarkArray[200][200],float svdImageArray[800][800])
	split(image, imageMat);
	split(waterMark, waterMarkMat);

	image0 = imageMat[0];
	image1 = imageMat[0];
	svdImage0 = imageMat[0];

	waterMark0 = waterMarkMat[0];
	waterMark1 = waterMarkMat[0];
	mat2array((int *)imageArray0,image0);
	mat2array((int *)imageArray1,image0);
	mat2array((int *)waterMarkArray0,waterMark0);

	//svd水印嵌入
	svdEmbed(imageArray0,waterMarkArray0,svdImageArray,5);
	array2mat((int *)svdImageArray,svdImage0);
	double pnsr = getPNSR(image1, svdImage0);
	cout << "pnsr: " << pnsr << endl;
	imshow("waterMark", waterMark);
	imshow("svdImage0", svdImage0);

	//重构水印 svdExtract(MATRIX_IN imageArray[N1][N1],MATRIX_IN svdImageArray[N1][N1],MATRIX_OUT waterMarkArrayIsvd[N2][N2],float k)
	svdExtract(imageArray1,svdImageArray,waterMarkArrayIsvd,5);

	array2mat((int *)waterMarkArrayIsvd,waterMark1);
	double nc = getNC(waterMark0,waterMark1 );
	cout << "nc: " << nc << endl;

	imshow("waterMark1", waterMark1);
	waitKey(0);
	return 0;
}
