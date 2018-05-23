#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include "basicData.h"
#include "dct.h"
#include "mark.h"

#define N 800
#define M 200

using namespace cv;
using namespace std;
int imageArray0[N][N];
int imageArray1[N][N];
int imageA[800 * 800] = { 0 };
int waterMarkArray[M][M];


int main()
{
	
	/******************************************************************************************
	//main
	vector<Mat> imageMat, waterMarketMat;
	Mat image0, image1,image2, mark0;
	Mat waterMarketMat0;
	Mat image = imread("1.jpg");
	Mat waterMarket = imread("01.jpg");
	dctParameter* para = new dctParameter;
	para->dctNum = 4;
	cout << para->dctNum << endl;

	split(image, imageMat);							//imageMat为分离后的mat，imageMat[0]是第一个通道。
	split(waterMarket, waterMarketMat);
	image0 = imageMat[0];
	
	image1 = imageMat[0];
	//Mat* pimage = image0;
	mark0 = waterMarketMat[0];

	mat2array((int*)imageArray0, image0);
	mat2array((int*)imageArray1, image1);
	mat2array((int*)waterMarkArray, mark0);
	
	
	int flag = dctEmbed((int*)imageArray0, (int*)waterMarkArray, para);
	int flag1 = dctExtra((int*)imageArray1, (int*)imageArray0, (int*)waterMarkArray, para);
	array2mat((int*)imageArray0, image0);
	array2mat((int*)waterMarkArray, mark0);
	imshow("带有水印的一通道图像", image0);
	imshow("水印", mark0);
	imageMat[0] = image0;
	merge(imageMat, image2);
	imshow("带有水印的图像", image2);
	//main
	******************************************************************************************/
	





	//以下是各种函数的测试

	//getPNSR函数测试double getPSNR(const Mat& I1, const Mat& I2)
	Mat image0(2, 2, CV_8U);
	image0.at<uchar>(0, 0) = 1;
	image0.at<uchar>(0, 1) = 2;
	image0.at<uchar>(1, 0) = 3;
	image0.at<uchar>(1, 1) = 4;

	Mat image1(2, 2, CV_8U);
	image1.at<uchar>(0, 0) = 1;
	image1.at<uchar>(0, 1) = 2;
	image1.at<uchar>(1, 0) = 3;
	image1.at<uchar>(1, 1) = 1;

	double pnsr = getPSNR(image0, image1);
	cout << pnsr << endl;
	
	/*******************************************************************************************
	//void dct2d4x4(short int data[16], short int dataout[16])测试代码段
	short int data[16] = { -97,-96,-95,-82,-95,-95,-94,-71,-96,-96,-94,-61,-95,-95,-95,-57 };
	short int dataDct[16] = { 0 };
	dct2d4x4oneD(data, dataDct);
	idct2d4x4oneD(dataDct, data);
	for (int i = 0; i < 16; i++)
		cout << data[i] << endl;
	********************************************************************************************/


	/*******************************************************************************************
	//mat2oneDarray与oneDarray2mat测试
	Mat image0(2, 2, CV_8U);
	image0.at<uchar>(0, 0) = 1;
	image0.at<uchar>(0, 1) = 2;
	image0.at<uchar>(1, 0) = 3;
	image0.at<uchar>(1, 1) = 4;
	Mat image = imread("1.jpg");
	
	mat2oneDarray(imageA, image);
	oneDarray2mat(imageA, image);
	imshow("水印", image);
	cout << "mat: " << endl;
	for (int i = 0; i < image0.rows; i++) {
		for (int j = 0; j < image0.cols; j++) {
			cout << image0.at<uchar>(i, j) << ' ';
		}
		cout << endl;
	}
	int image0Array[4] = { 0 };
	cout << "original array: " << endl;
	for (int i = 0; i < 4; i++)
		cout << image0Array[i] << ' ';
	cout << endl;
	cout << "mat2array: " << endl;
	mat2oneDarray(image0Array, image0);
	for (int i = 0; i < 4; i++)
		cout << image0Array[i] << ' ';
	cout << endl;
	******************************************************************************************/

	/*******************************************************************************************
	//NC函数测试
	int ao[2][2] = { {1,1},{1,1} };
	int ar[2][2] = { {1,1},{1,1} };
	double nc = NC(ao, ar);
	cout << "nc: " << nc << endl;
	//NC函数测试
	****************************************************************************/

	/*******************************************************************************************
	//arraySplit函数测试
	int data[8][8] = { 0 };
	int data1[3][2] = { 0 };
	for (int i = 0; i < 8; i++)
	{
	for (int j = 0; j < 8; j++)
	{
	data[i][j] = i*j;
	}
	}
	for (int i = 0; i < 8; i++)
	{
	for (int j = 0; j < 8; j++)
	{
	cout << data[i][j] << ' ';
	}
	cout << endl;
	}
	dataRect* rect = new dataRect{2,5,2,4,8};
	cout << "rect.rowsBegin: " << rect->rowsBegin << endl;
	cout << "rect.rowsEnd: " << rect->rowsEnd << endl;
	cout << "rect.cilsBegin: " << rect->colsBegin << endl;
	cout << "rect.colsEnd: " << rect->colsEnd << endl;
	cout << "rect.cols: " << rect->cols << endl;
	arraySplit((int *)data, (int*) data1, rect);
	for (int i = 0; i < 3; i++)
	{
	for (int j = 0; j < 2; j++)
	{
	cout << data1[i][j] << ' ';
	}
	cout << endl;
	}
	waitKey();
	//arraySplit函数测试
	****************************************************************************/

	/***************************************************************************
	//arrayInseert函数测试
	int data[8][8] = { 0 };
	int data1[2][3] = { 0 };
	for (int i = 0; i < 2; i++)
	{
	for (int j = 0; j < 3; j++)
	{
	data1[i][j] = 1;
	}
	}
	cout << "插入之前" << endl;
	for (int i = 0; i < 8; i++)
	{
	for (int j = 0; j < 8; j++)
	{
	cout << data[i][j] << ' ';
	}
	cout << endl;
	}
	cout << "要插入的数组" << endl;
	for (int i = 0; i < 2; i++)
	{
	for (int j = 0; j < 3; j++)
	{
	cout << data1[i][j] << ' ';
	}
	cout << endl;
	}
	dataRect* rect = new dataRect{ 1,3,1,4,8 };

	arrayInsert((int*)data, (int*)data1, rect);
	cout << "插入之后的数组" << endl;
	for (int i = 0; i < 8; i++)
	{
	for (int j = 0; j < 8; j++)
	{
	cout << data[i][j] << ' ';
	}
	cout << endl;
	}
	*******************************************************************************************/
	waitKey();
	return 0;
}