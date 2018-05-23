#include"mark.h"
#include<iostream>
#define ratio 0.12			//block4x4[xx][yy] = block4x4[xx][yy] * (1 + a*ratio)
#define xx 2				
#define yy 1

//8x8水印可调参数
#define ratio11 0.03
#define ratio12 0.03
#define ratio21 0.03
#define ratio22 0.03
#define xx1 1
#define xx2 2
#define yy1 3
#define yy2 2

template<class T>
inline T square(T val) {
	return val*val;
}
int dctEmbed( int* imageArray, int* waterMarkArray, dctParameter* para)
{
	float block4x4[4][4] = { 0 };
	int block8x8[8][8] = { 0 };
	int a = 0;
	double a11 = 0;
	double a12 = 0;
	double a21 = 0;
	double a22 = 0;
	
	if (para->disorderPara == nothing) {
		if (para->dctNum == 4) {
			//开始做水印嵌入
			printf("开始水印嵌入\n");
			for (int i = 0; i < (para->waterMarkM); i++) 
			{
				for (int j = 0; j < (para->waterMarkN); j++) 
				{
					int x = 4 * i;
					int y = 4 * j;
					dataRect* rect = new dataRect{x,x+4,y,y+4,800};
					//从原imageArray中取块
					arraySplit(imageArray, (int*)block4x4, rect);
					//dct运算
					dct2d4x4((int(*) [4]) block4x4, 4);
					if (*(waterMarkArray+i*200+j) >= 128) {
						a = -1;
					}
					else {
						a = 1;
					}
					block4x4[xx][yy] = block4x4[xx][yy] * (1 + a*ratio);
					//对处理之后的block做逆dct变换
					idct2d4x4((int(*)[4]) block4x4, 4);
					
					//将嵌入的block赋给原图
					arrayInsert(imageArray,(int*) block4x4, rect);
					free(rect);
				}
			}
			printf("水印嵌入结束\n");
			return 0;
		}
		else {
			//开始做水印嵌入
			printf("开始水印嵌入\n");
			for (int i = 0; i < (para->waterMarkM/2); i++)
			{
				for (int j = 0; j < (para->waterMarkN/2); j++)
				{
					int x = 8 * i;
					int y = 8 * j;
					//从原imageArray中取块
					dataRect* rect = new dataRect{ x,x + 8,y,y + 8,800 };
					arraySplit(imageArray, (int*)block8x8, rect);
					//dct运算
					dct2d8x8(block8x8, 8, 8);
					//以下做dct系数嵌入
					if (*(waterMarkArray + i * 200 + j) >= 128) {
						a11 = -1;
					}
					else {
						a11 = 1;
					}
					if (*(waterMarkArray + i * 200 + j+1) >= 128) {
						a12 = -1;
					}
					else {
						a12= 1;
					}
					if (*(waterMarkArray + i * 400 + j) >= 128) {
						a21 = -1;
					}
					else {
						a21 = 1;
					}
					if (*(waterMarkArray + i * 400 + j+1) >= 128) {
						a22 = -1;
					}
					else {
						a22 = 1;
					}
					block8x8[xx1][yy1] = block8x8[xx1][yy1] * (1 + a11*ratio11);
					block8x8[xx1][yy2] = block8x8[xx1][yy2] * (1 + a12*ratio12);
					block8x8[xx2][yy1] = block8x8[xx2][yy1] * (1 + a21*ratio21);
					block8x8[xx2][yy2] = block8x8[xx2][yy2] * (1 + a22*ratio22);
					//对处理之后的block做逆dct变换
					idct2d8x8(block8x8 , 8, 8);
					//将嵌入的block赋给原图
					arrayInsert(imageArray, (int*)block8x8, rect);
					free(rect);
				}
			}
			printf("水印嵌入结束\n");
			return 0;
		}
	}
	else if (para->disorderPara == arnold) {
		return 0;
	}
	else {
		return 0;
	}
}

int dctExtra(int* imageArray, int* afterDctImageArray, int* waterMarkArray, dctParameter* para)
{
	int block4x4Image[4][4] = { 0 };
	int block4x4After[4][4] = { 0 };
	int block8x8Image[8][8] = { 0 };
	int block8x8After[8][8] = { 0 };
	double a = 0;
	double a11 = 0;
	double a12 = 0;
	double a21 = 0;
	double a22 = 0;
	if (para->disorderPara == nothing) {
		if (para->dctNum == 4) {
			for (int i = 0; i < (para->waterMarkM); i++){
				for (int j = 0; j < (para->waterMarkN); j++){
					int x = 4 * i;
					int y = 4 * j;
					dataRect* rect = new dataRect{ x,x + 4,y,y + 4,800 };
					//从原imageArray中取块
					//void arraySplit(int* imageArray,int* subImageArray,dataRect* rect)
					arraySplit(imageArray, (int*)block4x4Image, rect);
					arraySplit(afterDctImageArray, (int*)block4x4After, rect);
					
					dct2d4x4(block4x4Image, 4);
					dct2d4x4(block4x4After, 4);
					a = (float)block4x4After[xx][yy] / (float)block4x4Image[xx][yy]-1;
					a = a / ratio;
					if (square(a-1)-square(a+1)<0) {
						*(waterMarkArray+i*200+j) = 0;
					}
					else {
						*(waterMarkArray + i * 200 + j) = 255;
					}
				}
			}
			return 0;
		}
		else {
			for (int i = 0; i < (para->waterMarkM/2); i++) { 
				for (int j = 0; j < (para->waterMarkN/2); j++) {
					int x = 8 * i;
					int y = 8 * j;
					dataRect* rect = new dataRect{ x,x + 8,y,y + 8,800 };
					//从原imageArray中取块
					//void arraySplit(int* imageArray,int* subImageArray,dataRect* rect)
					arraySplit(imageArray, (int*)block8x8Image, rect);
					arraySplit(afterDctImageArray, (int*)block8x8After, rect);

					dct2d8x8(block8x8Image, 8, 8);
					dct2d8x8(block8x8After, 8, 8);

					a11 = (double)block8x8After[xx1][yy1] / (double)block8x8Image[xx1][yy1] - 1;
					a11 = a11 / ratio11;
					if (square(a11 - 1) - square(a11 + 1)<0) {
						*(waterMarkArray + i * 200 + j) = 0;
					}
					else {
						*(waterMarkArray + i * 200 + j) = 255;
					}
					a12 = (double)block8x8After[xx1][yy2] / (double)block8x8Image[xx1][yy2] - 1;
					a12 = a12 / ratio12;
					if (square(a12 - 1) - square(a12 + 1)<0) {
						*(waterMarkArray + i * 200 + j+1) = 0;
					}
					else {
						*(waterMarkArray + i * 200 + j+1) = 255;
					}
					a21 = (double)block8x8After[xx2][yy1] / (double)block8x8Image[xx2][yy1] - 1;
					a21 = a21 / ratio21;
					if (square(a21 - 1) - square(a21 + 1)<0) {
						*(waterMarkArray + i * 400 + j) = 0;
					}
					else {
						*(waterMarkArray + i * 400 + j) = 255;
					}
					a22 = (double)block8x8After[xx2][yy2] / (double)block8x8Image[xx2][yy2] - 1;
					a22 = a22 / ratio22;
					if (square(a22 - 1) - square(a22 + 1)<0) {
						*(waterMarkArray + i * 400 + j+1) = 0;
					}
					else {
						*(waterMarkArray + i * 400 + j+1) = 255;
					}
				}
			}
			return 0;
		}
	}
	else if (para->disorderPara == arnold) {
		return 0;
	}
	else {
		return 0;
	}
}


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

void rotateImage(IplImage* img, IplImage *img_rotate, int degree)
{
	//旋转中心为图像中心  
	CvPoint2D32f center;
	center.x = float(img->width / 2.0 + 0.5);
	center.y = float(img->height / 2.0 + 0.5);
	//计算二维旋转的仿射变换矩阵  
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	cv2DRotationMatrix(center, degree, 1, &M);
	//变换图像，并用黑色填充其余值  
	cvWarpAffine(img, img_rotate, &M, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
}