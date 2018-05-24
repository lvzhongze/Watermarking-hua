#include "attack.h"

//逆时针旋转图像degree角度（原尺寸）

void myrotateImage(IplImage* img, IplImage *img_rotate, int degree)
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


//mu高斯函数的偏移，sigma高斯函数的标准差  
double generateGaussianNoise(double mu, double sigma)
{
	//定义小值，numeric_limits<double>::min()是函数,返回编译器允许的double型数最小值  
	const double epsilon = std::numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量x  
	if (!flag) return z1 * sigma + mu;
	//构造随机变量  
	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量x  
	z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
	return z0 * sigma + mu;
}

cv::Mat addGaussianNoise(cv::Mat &image)
{
	cv::Mat result = image.clone();
	int channels = image.channels();
	int rows = image.rows, cols = image.cols * image.channels();
	//判断图像连续性  
	if (result.isContinuous()) cols = rows * cols, rows = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//添加高斯噪声  
			int val = result.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
			if (val < 0) val = 0;
			if (val > 255) val = 255;
			result.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return result;
}

void salt(cv::Mat& image, int n) {
	for (int k = 0; k<n; k++) {
		int i = rand() % image.cols;
		int j = rand() % image.rows;

		if (image.channels() == 1) {
			image.at<uchar>(j, i) = 255;
		}
		else {
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void cut(cv::Mat& image, int x1, int y1, int x2, int y2)
{
	int m = y2 - y1;
	int n = x2 - x1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			image.at<cv::Vec3b>(i+x1, j+y1)[0] = 0;
			image.at<cv::Vec3b>(i+x1, j+y1)[1] = 0;
			image.at<cv::Vec3b>(i+x1, j+y1)[2] = 0;
		}
	}
}