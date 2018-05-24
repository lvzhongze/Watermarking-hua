#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>  
//Ğı×ª
void myrotateImage(IplImage* img, IplImage *img_rotate, int degree);

//¸ßË¹ÔëÉù
cv::Mat addGaussianNoise(cv::Mat &image);

//½·ÑÎÔëÉù
void salt(cv::Mat& image, int n);

//¼ôÇĞ
void cut(cv::Mat& image, int x1, int y1, int x2, int y2);