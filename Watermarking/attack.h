#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>  
//��ת
void myrotateImage(IplImage* img, IplImage *img_rotate, int degree);

//��˹����
cv::Mat addGaussianNoise(cv::Mat &image);

//��������
void salt(cv::Mat& image, int n);

//����
void cut(cv::Mat& image, int x1, int y1, int x2, int y2);