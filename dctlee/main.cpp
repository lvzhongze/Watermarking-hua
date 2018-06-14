#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include "mark.h"
#include "basicdata.h"
#include "attack.h"
#include <string>

#define N 800
#define M 200
#define thresh_hold 2
#define A 5
#define B 7
//#define B 1//置乱的代数epoch
using namespace cv;
using namespace std;

enum Attack{GaussianNoise,rotation,salt,cut,nothing};
Attack attack = nothing;
int salt_num = 100;
double rotateAngle = 15;
double ratio = 1;
bool correction = nothing;

int imageArrayOneD0[N*N];
int imageArrayOneD1[N*N];
int waterMarkArrayOneD[M * M];
int dctImageArrayOneD0[N*N];
int tiqu_watermark[M*M];
int dctImageArrayAttack[N*N];




double getNC(cv::Mat mark0, cv::Mat mark1)
{
	double fenzi = 0.0; //·Ö×Ó
			double fenmu = 0.0;//·ÖÄ¸
			double fenmu1 = 0.0;
			double fenmu2 = 0.0;
			double result = 0.0;
			//Mat square_mark(200,200,CV_8UC1); //Ê¹ÓÃ*¼ÆËã¾ØÕóÓë±êÁ¿Ïà³Ë£¬¾ØÕóÓë¾ØÕóÏà³Ë£»
			fenzi = mark0.dot(mark1);

			fenmu1 = mark0.dot(mark0);
			fenmu2 = mark1.dot(mark1);
			fenmu = sqrt(fenmu1)*sqrt(fenmu2);

			result= fenzi / fenmu;
			return result;
}

double getPNSR(const cv::Mat& I1, const cv::Mat& I2)
{
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
}

string to_String(int n)
{
    int m = n;
    char s[1];
    char ss[1];
    int i=0,j=0;
    if (n < 0)// ´¦Àí¸ºÊý
    {
        m = 0 - m;
        j = 1;
        ss[0] = '-';
    }
    while (m>0)
    {
        s[i++] = m % 10 + '0';
        m /= 10;
    }
    s[i] = '\0';
    i = i - 1;
    while (i >= 0)
    {
        ss[j++] = s[i--];
    }
    ss[j] = '\0';
    return ss;
}

int main()
{
	for(int i=9;i<=9;i++){
		string si = to_String(i)+".jpg";
		/**************   1.读入，显示原始图像***************************/
		vector<Mat> imageMat, watermarkMat,imageOrMat,watermarkOrMat;
		Mat image0, image1, image2, mark0,mark1,image1Attack,imageOr1;


		Mat image=imread(si);
		Mat watermark=imread("01.jpg");
		Mat watermarkOr=imread("011.jpg");
		Mat imageOr=imread(si);
		//cout << image.size() << endl;
		split(image, imageMat);
		split(imageOr, imageOrMat);
		//cout << imageMat.size() << endl;
		waitKey(0);
		//cout << imageMat << endl;
		split(watermark, watermarkMat);
		split(watermarkOr, watermarkOrMat);

		image0 = imageMat[0];
		image1 = imageMat[1];
		imageOr1 = imageOrMat[0];

		mark0 = watermarkMat[0];
		mark1 = watermarkOrMat[0];


		//imshow("Img", image0);
		//imshow("watermark", mark0);
		/*******************   2.水印的嵌入，显示，评价    ******************************/

	    //将二维Mat转化成一维数组，方面水印嵌入
		mat2array4x4(image0, imageArrayOneD0);	//image0:原始载体图像的第一维通道
		mat2array4x4(mark0, waterMarkArrayOneD);//mark0:原始水印的第一维通道


		//嵌入
		dctEmbedOneArray(imageArrayOneD0, dctImageArrayOneD0, waterMarkArrayOneD,A,B,thresh_hold);



		array2mat4x4(image1,dctImageArrayOneD0);
		//显示嵌入后的图像
		//imshow("dctMat: ", image1);
		//对image1进行攻击
		if(attack==nothing){
			image1Attack = image1;
		}else if(attack==GaussianNoise){
			image1Attack = addGaussianNoise(image1);
		}else if(attack==salt){
			image1Attack = addSalt(image1, salt_num);
		}else if(attack==cut){
			// addCut(const cv::Mat& image, int x1, int y1, int x2, int y2)
			image1Attack = addCut(image1,0,0,160,160);
		}else if(attack==rotation){
			image1Attack = addRotation(image1, rotateAngle, ratio);
		}


		mat2array4x4(image1Attack, dctImageArrayAttack);

		//评价
		double pnsr = getPNSR(imageOr1, image1Attack);
		std::cout <<"pnsr: " << pnsr << std::endl;
		/**********************   3.水印的提取，显示，评价 **********************************/


		//提取水印
		dctExtraOneArray(dctImageArrayAttack,A,B,tiqu_watermark);

		//显示
		//Mat mark_wu(200, 200, CV_8UC1);
		array2mat4x4(mark0, tiqu_watermark);
		imshow("mark1", mark1);
		imshow("mark0", mark0);


		//评价
		double nc = getNC(mark0, mark1);
		std::cout << "nc: " << nc << std::endl;
		/**********************   4.攻击    *****************************/
	}

	waitKey();
	return 0;
}
