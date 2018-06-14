#pragma once

//#include <math.h>
//using namespace cv;

//«∂»Î
int dctEmbedOneArray(int imageArrayOneD0[800 * 800], int dctImageArrayOneD0[800 * 800], int waterMarkArrayOneD[200 * 200], int A, int B, int thresh_hold);
//double getPNSR(const cv::Mat& I1, const cv::Mat& I2); //PNSR



//Ã·»°
int dctExtraOneArray(int imageArrayOneD1[800 * 800], int A, int B, int tiqu_watermark[200 * 200]);
//double getNC(cv::Mat mark0, cv::Mat mark1);////NC
template< typename T>
void my_swap(T &a, T &b)
{
	T ch;
	ch = a;
	a = b;
	b = ch;
}
