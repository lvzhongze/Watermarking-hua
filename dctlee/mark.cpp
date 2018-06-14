
#include "dct.h"
#include "mark.h"
//#include "basicdata.h"


int dctEmbedOneArray(int imageArrayOneD0[800*800], int dctImageArrayOneD0[800*800], int waterMarkArrayOneD[200*200],int A,int B,int thresh_hold)
{
	//水印置乱
	int N = 200;
	int waterMarkArrayOneD_arnold[200 * 200];
	for (int i = 0; i < 200 * 200; i++)
	{
		waterMarkArrayOneD_arnold[i] = 0;
	}

	dctEmbedOneArray_label1:for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int x = (i + B*j) % N;
			int y = (A*i + (A*B + 1)*j) % N;
			if (x < 0)
			{
				x = x + 200;
			}
			if (y < 0)
			{
				y = y + 200;
			}
			waterMarkArrayOneD_arnold[200 * x + y] = waterMarkArrayOneD[200 * i + j];
		}
	}
	short int data[16] = { 0 };
	short int dctData[16] = { 0 };
	
	//printf("开始嵌入水印\n");
	dctEmbedOneArray_label0:for (int i = 0; i < 200 * 200; i++)
	{ //对每个4x4方块，做dct变换等
		for (int j = 0; j < 16; j++)
		{
			data[j] = imageArrayOneD0[i * 16 + j];
		}
		//dct
		dct2d4x4oneD(data, dctData);
		//比较每个一维数组[5][10]个的大小（原来的BLOCK（2，2）与BLOCK（3.3））
		if (waterMarkArrayOneD_arnold[i] >= 128) //w(i,j)=1
		{
			if (dctData[14] > dctData[15])
			{
				my_swap(dctData[14], dctData[15]); //交换两个数
			}

			if (dctData[15] - dctData[14] < thresh_hold)
			{
				dctData[14] = dctData[14] - thresh_hold / 2;
				dctData[15]= dctData[15]+ thresh_hold / 2;
			}
		}
		
		else
		{//w(i,j)=0
			if (dctData[14] <= dctData[13])
			{
				my_swap(dctData[14], dctData[15]);//交换
			}
			if (dctData[14] - dctData[15] < thresh_hold)
			{
				dctData[14]= dctData[14]+ thresh_hold / 2;
				dctData[15]= dctData[15]- thresh_hold / 2;
			}
		}
		//逆dct
		idct2d4x4oneD(dctData,data);
		for (int j = 0; j < 16; j++)
		{
			dctImageArrayOneD0[i * 16 + j] = data[j];
		}
	
	}
	//printf("水印嵌入结束\n");
	return 0;
	
}




int dctExtraOneArray(int imageArrayOneD1[800 * 800],int A,int B,int tiqu_watermark[200 * 200])
{
	short int data[16] = { 0 };
	short int dctData[16] = { 0 };

	// 水印的中间变量，用于反置乱得到最终的tiqu_watermark
	int tiqu_tmp[200 * 200];
	for (int i = 0; i < 200 * 200; i++)
	{
		tiqu_tmp[i] = 0;
	}

	//printf("开始提取水印\n");
	for (int i = 0; i < 200 * 200; i++)
	{

		//每个待处理的4x4方块
		for (int j = 0; j < 16; j++)
		{
			data[j]=imageArrayOneD1[i * 16 + j];
		}

		//作dct
		dct2d4x4oneD(data, dctData);

		//提取水印
		if (dctData[14] > dctData[15])
		{
			tiqu_tmp[i] = 0;
		}
		else
		{
			tiqu_tmp[i] = 255;
		}

	}
	//水印反置乱
	int N = 200;
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int x = ((A*B + 1)*i - B*j) % N;
			int y = (j - A*i) % N;
			if (x < 0)
			{
				x = x + 200;
			}
			if (y < 0)
			{
				y = y + 200;
			}
			tiqu_watermark[200 * x + y] = tiqu_tmp[200 * i + j];
		}
	}
	//printf("提取水印结束\n");
	return 0;
}


