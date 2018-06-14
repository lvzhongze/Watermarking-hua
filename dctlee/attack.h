#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
//#include <opencv2/imgproc.hpp>
using namespace cv;
double generateGaussianNoise(double mu, double sigma);
cv::Mat addGaussianNoise(cv::Mat &image);
Mat addSalt(const Mat srcImage, int n);
Mat addCut(const cv::Mat& image, int x1, int y1, int x2, int y2);
Mat addRotation(const Mat srcImage,double angle, double ratio);
double getAngle(const Mat image1, const Mat image2);
