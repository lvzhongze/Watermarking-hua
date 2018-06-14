#include "attack.h"
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
			int val = result.ptr<uchar>(i)[j] + generateGaussianNoise(0, 0.01) * 32;
			if (val < 0) val = 0;
			if (val > 255) val = 255;
			result.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return result;
}

Mat addSalt(const Mat srcImage, int n) {
	Mat dstImage = srcImage.clone();
	    for (int k = 0; k < n; k++)
	    {
	        //随机取值行列
	        int i = rand() % 800;
	        int j = rand() % 800;
	        //图像通道判定
	        if (dstImage.channels() == 1)
	        {
	            dstImage.at<uchar>(i, j) = 255;       //盐噪声
	        }
	        else
	        {
	            dstImage.at<Vec3b>(i, j)[0] = 255;
	            dstImage.at<Vec3b>(i, j)[1] = 255;
	            dstImage.at<Vec3b>(i, j)[2] = 255;
	        }
	    }
	    for (int k = 0; k < n; k++)
	    {
	        //随机取值行列
	        int i = rand() % 800;
	        int j = rand() % 800;
	        //图像通道判定
	        if (dstImage.channels() == 1)
	        {
	            dstImage.at<uchar>(i, j) = 0;     //椒噪声
	        }
	        else
	        {
	            dstImage.at<Vec3b>(i, j)[0] = 0;
	            dstImage.at<Vec3b>(i, j)[1] = 0;
	            dstImage.at<Vec3b>(i, j)[2] = 0;
	        }
	    }
	    return dstImage;
}

Mat addCut(const cv::Mat& image, int x1, int y1, int x2, int y2)
{
	Mat dstImage = image.clone();
	int m = y2 - y1;
	int n = x2 - x1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			dstImage.at<cv::Vec3b>(i+x1, j+y1)[0] = 0;
			dstImage.at<cv::Vec3b>(i+x1, j+y1)[1] = 0;
			dstImage.at<cv::Vec3b>(i+x1, j+y1)[2] = 0;
		}
	}
	return dstImage;
}

Mat addRotation(const Mat srcImage,double angle, double ratio)
{
	Mat MoveImage(srcImage.rows,srcImage.cols,CV_8UC3,Scalar(0,0,0));
	Point2f center(srcImage.cols/2,srcImage.rows/2);//中心
	Mat M = getRotationMatrix2D(center,angle,ratio);//计算旋转的仿射变换矩阵
	warpAffine(srcImage,MoveImage,M,Size(srcImage.cols,srcImage.rows));
	//circle(MoveImage,center,2,Scalar(255,0,0));
	return MoveImage;
}


double getAngle(const Mat image1, const Mat image2)
{
	double angleGet = 0;
	double m10=0;
	double m01=0;
	double ma10=0;
	double ma01=0;
	//计算m10
	for(int i=0;i<image1.rows;i++){
		for(int j=0;j<image1.cols;j++){
			m10 = m10+i*(double)image1.at<uchar>(i,j);
		}
	}
	//计算m01
	for(int i=0;i<image1.rows;i++){
		for(int j=0;j<image1.cols;j++){
			m01 = m01+j*(double)image1.at<uchar>(i,j);
		}
	}

	//计算ma10
	for(int i=0;i<image2.rows;i++){
		for(int j=0;j<image2.cols;j++){
			ma10 = m10+i*(double)image2.at<uchar>(i,j);
		}
	}
	//计算ma01
	for(int i=0;i<image2.rows;i++){
		for(int j=0;j<image2.cols;j++){
			ma01 = m01+j*(int)image2.at<uchar>(i,j);
		}
	}

	angleGet = asin((ma01*m10-ma10*m01)/(m10*m10+m01*m01));
	return angleGet*180;
}

