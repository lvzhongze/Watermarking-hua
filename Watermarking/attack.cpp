#include "attack.h"

//��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩

void myrotateImage(IplImage* img, IplImage *img_rotate, int degree)
{
	//��ת����Ϊͼ������  
	CvPoint2D32f center;
	center.x = float(img->width / 2.0 + 0.5);
	center.y = float(img->height / 2.0 + 0.5);
	//�����ά��ת�ķ���任����  
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	cv2DRotationMatrix(center, degree, 1, &M);
	//�任ͼ�񣬲��ú�ɫ�������ֵ  
	cvWarpAffine(img, img_rotate, &M, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
}


//mu��˹������ƫ�ƣ�sigma��˹�����ı�׼��  
double generateGaussianNoise(double mu, double sigma)
{
	//����Сֵ��numeric_limits<double>::min()�Ǻ���,���ر����������double������Сֵ  
	const double epsilon = std::numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�ٹ����˹�������x  
	if (!flag) return z1 * sigma + mu;
	//�����������  
	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������x  
	z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
	return z0 * sigma + mu;
}

cv::Mat addGaussianNoise(cv::Mat &image)
{
	cv::Mat result = image.clone();
	int channels = image.channels();
	int rows = image.rows, cols = image.cols * image.channels();
	//�ж�ͼ��������  
	if (result.isContinuous()) cols = rows * cols, rows = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//��Ӹ�˹����  
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