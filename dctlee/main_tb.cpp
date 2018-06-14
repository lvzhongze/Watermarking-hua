#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mark.h"
#include "basicData.h"
#include <string>
#include "attack.h"

#define N 800
#define M 200
#define thresh_hold 10
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
bool correction = false;

int imageArrayOneD0[N*N];
int imageArray0[N*N];
int imageArray1[N*N];
int dctImageArrayAttackOneD0[N*N];

int imageArrayOneD1[N*N];
int waterMarkArrayOneD[M * M];
int waterMarkArray0[M*M];
int dctImageArrayOneD0[N*N];
int tiqu_watermark[M*M];

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
	for(int i=1;i<=1;i++){
		string si = to_String(i)+".jpg";
		vector<Mat> imageMat, waterMarkMat,waterMarkMatOr;
		Mat dctImageAttack,waterMark00,image0,dctImage0,waterMark0, imageSVD, waterMark1,result,image1,svdImage0Attack,svdImage0IAttack;
		Mat image = imread(si);
		Mat waterMark = imread("03.jpg");
		Mat waterMarkOr = imread("033.jpg");


		split(image, imageMat);
		split(waterMark, waterMarkMat);
		split(waterMarkOr, waterMarkMatOr);
		image0 = imageMat[0];
		image1 = imageMat[0];
		dctImageAttack = imageMat[0];

		waterMark0 = waterMarkMat[0];
		waterMark00 = waterMarkMat[0];

		waterMark1 = waterMarkMatOr[0];
		mat2array4x4(image0,imageArray0);
		mat2array4x4(image0,imageArray1);
		mat2array4x4(waterMark0,waterMarkArray0);


		dctEmbedOneArray(imageArray0, dctImageArrayOneD0, waterMarkArray0,A,B,thresh_hold);
		array2mat4x4(dctImage0,dctImageArrayOneD0);
		if(attack==nothing){
			dctImageAttack = dctImage0;
		}else if(attack==GaussianNoise){
			dctImageAttack = addGaussianNoise(dctImage0);
		}else if(attack==salt){
			dctImageAttack = addSalt(dctImage0, salt_num);
		}else if(attack==cut){
			// addCut(const cv::Mat& image, int x1, int y1, int x2, int y2)
			dctImageAttack = addCut(dctImage0,0,0,160,160);
		}else if(attack==rotation){
			dctImageAttack = addRotation(dctImage0, rotateAngle, ratio);
		}

		//array2mat4x4(dctImageAttack, dctImageArrayAttackOneD0);


		double pnsr = getPNSR(image1, dctImageAttack);
		cout << si << "pnsr: " << pnsr << endl;
		//imshow("waterMark", waterMark);
		//imshow("svdImage0IAttack", svdImage0Attack);

		mat2array4x4(dctImageAttack, dctImageArrayAttackOneD0);

		dctExtraOneArray(dctImageArrayAttackOneD0,A,B,tiqu_watermark);
		//svdExtract(imageArray1,svdImageArrayAttack,waterMarkArrayIsvd,embedding_strength);
		array2mat4x4(waterMark00, tiqu_watermark);
		//array2mat((int *)waterMarkArrayIsvd,waterMark0);
		double nc = getNC(waterMark00,waterMark1);
		cout << si << "nc: " << nc << endl;
		imshow("waterMark0", waterMark00);
		imshow("waterMark1", waterMark1);
	}

	/*
	vector<Mat> imageMat, waterMarkMat,waterMarkMatOr,svdImage;
	Mat image0,svdImage0,waterMark0, imageSVD, waterMark1,result,image1,svdImage0Attack,svdImage0IAttack;
	Mat image = imread("3.jpg");
	Mat waterMark = imread("01.jpg");
	Mat waterMarkOr = imread("02.jpg");
	imshow("Ô­Í¼", image);
	//svdEmbed(float imageArray[800][800],float waterMarkArray[200][200],float svdImageArray[800][800])
	split(image, imageMat);
	split(waterMark, waterMarkMat);
	split(waterMarkOr, waterMarkMatOr);
	image0 = imageMat[0];
	image1 = imageMat[0];
	svdImage0 = imageMat[0];

	waterMark0 = waterMarkMat[0];
	//
	waterMark1 = waterMarkMatOr[0];
	mat2array((int *)imageArray0,image0);
	mat2array((int *)imageArray1,image0);
	mat2array((int *)waterMarkArray0,waterMark0);

	//svdË®Ó¡Ç¶Èë
	svdEmbed(imageArray0,waterMarkArray0,svdImageArray,embedding_strength);
	array2mat((int *)svdImageArray,svdImage0);

	//¹¥»÷
	if(attack==nothing){
		svdImage0Attack = svdImage0;
	}else if(attack==GaussianNoise){
		svdImage0Attack = addGaussianNoise(svdImage0);
	}else if(attack==salt){
		svdImage0Attack = addSalt(svdImage0, 800*80);
	}else if(attack==cut){
		// addCut(const cv::Mat& image, int x1, int y1, int x2, int y2)
		svdImage0Attack = addCut(svdImage0,0,0,100,250);
	}else if(attack==rotation){
		svdImage0Attack = addRotation(svdImage0, rotateAngle, ratio);
	}
	imshow("svdImage0Attack", svdImage0Attack);
	imshow("svdImage0", svdImage0);

	//¹¥»÷µÄÐÞÕý
	if(attack==rotation && correction){
		//ÖØ¹¹Ë®Ó¡ svdExtract(MATRIX_IN imageArray[N1][N1],MATRIX_IN svdImageArray[N1][N1],MATRIX_OUT waterMarkArrayIsvd[N2][N2],float k)
		//double getAngle(const Mat image1, const Mat image2)
		rotateAngle = getAngle(svdImage0,svdImage0Attack);
		cout << "rotateAngle " << rotateAngle << endl;
		svdImage0IAttack = addRotation(svdImage0Attack, rotateAngle, ratio);
		imshow("svdImage0IAttack", svdImage0IAttack);
	}else if(!correction){
		svdImage0IAttack = svdImage0Attack;
	}
	double pnsr = getPNSR(image1, svdImage0IAttack);
	cout << "pnsr: " << pnsr << endl;
	imshow("waterMark", waterMark);
	//imshow("svdImage0IAttack", svdImage0Attack);

	//ÖØ¹¹Ë®Ó¡ svdExtract(MATRIX_IN imageArray[N1][N1],MATRIX_IN svdImageArray[N1][N1],MATRIX_OUT waterMarkArrayIsvd[N2][N2],float k)
	mat2array((int *)svdImageArrayAttack,svdImage0IAttack);
	svdExtract(imageArray1,svdImageArrayAttack,waterMarkArrayIsvd,embedding_strength);

	array2mat((int *)waterMarkArrayIsvd,waterMark0);
	double nc = getNC(waterMark0,waterMark1 );
	cout << "nc: " << nc << endl;
	imshow("waterMark0", waterMark0);




	imshow("waterMark1", waterMark1);
	*/
	waitKey(0);
	return 0;
}
