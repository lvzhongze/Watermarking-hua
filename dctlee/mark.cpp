
#include "dct.h"
#include "mark.h"
//#include "basicdata.h"


int dctEmbedOneArray(int imageArrayOneD0[800*800], int dctImageArrayOneD0[800*800], int waterMarkArrayOneD[200*200],int A,int B,int thresh_hold)
{
	//ˮӡ����
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
	
	//printf("��ʼǶ��ˮӡ\n");
	dctEmbedOneArray_label0:for (int i = 0; i < 200 * 200; i++)
	{ //��ÿ��4x4���飬��dct�任��
		for (int j = 0; j < 16; j++)
		{
			data[j] = imageArrayOneD0[i * 16 + j];
		}
		//dct
		dct2d4x4oneD(data, dctData);
		//�Ƚ�ÿ��һά����[5][10]���Ĵ�С��ԭ����BLOCK��2��2����BLOCK��3.3����
		if (waterMarkArrayOneD_arnold[i] >= 128) //w(i,j)=1
		{
			if (dctData[14] > dctData[15])
			{
				my_swap(dctData[14], dctData[15]); //����������
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
				my_swap(dctData[14], dctData[15]);//����
			}
			if (dctData[14] - dctData[15] < thresh_hold)
			{
				dctData[14]= dctData[14]+ thresh_hold / 2;
				dctData[15]= dctData[15]- thresh_hold / 2;
			}
		}
		//��dct
		idct2d4x4oneD(dctData,data);
		for (int j = 0; j < 16; j++)
		{
			dctImageArrayOneD0[i * 16 + j] = data[j];
		}
	
	}
	//printf("ˮӡǶ�����\n");
	return 0;
	
}




int dctExtraOneArray(int imageArrayOneD1[800 * 800],int A,int B,int tiqu_watermark[200 * 200])
{
	short int data[16] = { 0 };
	short int dctData[16] = { 0 };

	// ˮӡ���м���������ڷ����ҵõ����յ�tiqu_watermark
	int tiqu_tmp[200 * 200];
	for (int i = 0; i < 200 * 200; i++)
	{
		tiqu_tmp[i] = 0;
	}

	//printf("��ʼ��ȡˮӡ\n");
	for (int i = 0; i < 200 * 200; i++)
	{

		//ÿ���������4x4����
		for (int j = 0; j < 16; j++)
		{
			data[j]=imageArrayOneD1[i * 16 + j];
		}

		//��dct
		dct2d4x4oneD(data, dctData);

		//��ȡˮӡ
		if (dctData[14] > dctData[15])
		{
			tiqu_tmp[i] = 0;
		}
		else
		{
			tiqu_tmp[i] = 255;
		}

	}
	//ˮӡ������
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
	//printf("��ȡˮӡ����\n");
	return 0;
}


