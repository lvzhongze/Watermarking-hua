#pragma once
#include"basicData.h"
#include"dct.h"
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
enum disorder{nothing,arnold};

struct dctParameter {
	int imageM=800;				//����ͼ�����ص������
	int imageN=800;				//����ͼ�����ص������
	int waterMarkM=200;			//ˮӡ���ص������
	int waterMarkN=200;			//ˮӡ���ص������
	disorder disorderPara = nothing;	//���ҷ�����ѡ�������Ĭ�ϲ�������
	int dctNum = 4;			//dct�任�Ĳ�����Ĭ��4x4
};

int dctEmbed(int* imageArray, int* waterMarkArray, dctParameter* para);
/**************************************************************************************
����:				�˺���ΪˮӡǶ�����
����:               imageArrayԭͼ��һ��Ҫǿ��(int*)ת��������waterMarkArray��ˮӡͼ��
					para��dct�任���������������ΪdctParameter����ʼֵΪ	
					imageM=800;				//����ͼ�����ص������
					imageN=800;				//����ͼ�����ص������
					waterMarkM=200;			//ˮӡ���ص������
					waterMarkN=200;			//ˮӡ���ص������
					disorderPara = nothing;	//���ҷ�����ѡ�������Ĭ�ϲ�������
					dctNum = 4;			//dct�任�Ĳ�����Ĭ��4x4
���:				�޷���ֵ��imageArrayΪ����ˮӡ��ͼ��
����ֵ:
�����嵥:			void arraySplit(int* imageArray, int* subImageArray, dataRect* rect)
					void dct2d4x4(int(*data)[4],int blockSize)
					void idct2d4x4(int(*data)[4],int blockSize)
����:
**************************************************************************************/

int dctExtra(int* imageArray, int* afterDctImageArray, int* waterMarkArray, dctParameter* para);
/**************************************************************************************
����:				�˺���Ϊˮӡ��ȡ����
����:               imageArrayԭͼ��afterDctImageArray��Ƕ��ˮӡ֮���ͼ��
					waterMarkArray��ˮӡͼ�������ͬ��С�����鼴�ɣ�
					para��dct�任���������������ΪdctParameter��
���:				��ȡ��ˮӡwaterMarkArray��
����ֵ:
�����嵥:			void arraySplit(int* imageArray, int* subImageArray, dataRect* rect)
					void dct2d4x4(int(*data)[4],int blockSize)
����:
**************************************************************************************/

template<unsigned M, unsigned N>
double getNC(const int(&arrayo)[M][N], const int(&arrayr)[M][N])
{
	double numerator = 0;			//����
	double denominator = 0;			//��ĸ
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