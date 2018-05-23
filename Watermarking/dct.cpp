#include"dct.h"
void dct8x8(int data[8])
{
	int datatmp[8];
	datatmp[0] = data[0] + data[7];
	datatmp[1] = data[1] + data[6];
	datatmp[2] = data[2] + data[5];
	datatmp[3] = data[3] + data[4];
	datatmp[4] = data[3] - data[4];
	datatmp[5] = data[2] - data[5];
	datatmp[6] = data[1] - data[6];
	datatmp[7] = data[0] - data[7];

	data[0] = datatmp[0] + datatmp[3];
	data[1] = datatmp[1] + datatmp[2];
	data[2] = datatmp[1] - datatmp[2];
	data[3] = datatmp[0] - datatmp[3];

	data[0] += data[1];                    //// data[0] = X0  
	data[1] = -data[1] + ((data[0]) >> 1);     /// data[1] = X4  

	data[3] = data[3] - (data[2] >> 1) - (data[2] >> 3);
	data[2] += data[3];
	data[3] = data[3] - (data[2] >> 1) - (data[2] >> 3);
	// data[2] = X2    data[3] = X6  

	datatmp[5] = datatmp[5] - (datatmp[6] >> 1) + (datatmp[6] >> 4);
	datatmp[6] = datatmp[6] + (datatmp[5] >> 1) + (datatmp[5] >> 2);
	datatmp[5] = -datatmp[5] + (datatmp[6] >> 1) - (datatmp[6] >> 4);

	data[4] = datatmp[4] + datatmp[5];
	data[5] = datatmp[4] - datatmp[5];
	data[6] = -datatmp[6] + datatmp[7];
	data[7] = datatmp[6] + datatmp[7];

	data[7] = data[7] - (data[4] >> 1) - (data[4] >> 2) - (data[4] >> 4);
	data[4] = data[4] + data[7];
	data[7] = data[7] - (data[4] >> 1) - (data[4] >> 2) - (data[4] >> 4);
	// data[4] = X1      data[7] = X7  

	data[6] = data[6] - (data[5] >> 2);
	data[5] = data[5] + (data[6] >> 1);
	data[6] = data[6] - (data[5] >> 2);
	// data[5] = X3    data[7] = X5  

	/*   datatmp[0] = data[0];            datatmp[1] = data[2];
	datatmp[2] = data[1];    datatmp[3] = data[3];
	datatmp[4] = data[4];    datatmp[5] = data[6];
	datatmp[6] = data[5];    datatmp[7] = data[7];
	*/
	datatmp[0] = data[0];    datatmp[1] = data[4];
	datatmp[2] = data[2];    datatmp[3] = data[6];
	datatmp[4] = data[1];    datatmp[5] = data[5];
	datatmp[6] = data[3];    datatmp[7] = data[7];

	int i;
	for (i = 0; i < 8; i++)  data[i] = datatmp[i];
}

void idct8x8(int data[8])
{
	int datatmp[8];
	int i;
	for (i = 0; i < 8; i++)  datatmp[i] = data[i];
	data[0] = datatmp[0];    data[1] = datatmp[2];
	data[2] = datatmp[4];    data[3] = datatmp[6];
	data[4] = datatmp[1];    data[5] = datatmp[3];
	data[6] = datatmp[5];    data[7] = datatmp[7];

	datatmp[1] = -data[2] + (data[0] >> 1);
	datatmp[0] = data[0] - datatmp[1];

	datatmp[3] = data[3] + (data[1] >> 1) + (data[1] >> 3);
	datatmp[2] = data[1] - datatmp[3];
	datatmp[3] = datatmp[3] + (datatmp[2] >> 1) + (datatmp[2] >> 3);

	datatmp[6] = data[5] + (data[6] >> 2);
	datatmp[5] = data[6] - (datatmp[6] >> 1);
	datatmp[6] = datatmp[6] + (datatmp[5] >> 2);

	datatmp[7] = data[7] + (data[4] >> 1) + (data[4] >> 2) + (data[4] >> 4);
	datatmp[4] = data[4] - datatmp[7];
	datatmp[7] = datatmp[7] + (datatmp[4] >> 1) + (datatmp[4] >> 2) + (datatmp[4] >> 4);
	// four inverse lifting step  

	data[0] = (datatmp[0] + datatmp[3]) >> 1;
	data[3] = (datatmp[0] - datatmp[3]) >> 1;
	data[1] = (datatmp[1] + datatmp[2]) >> 1;
	data[2] = (datatmp[1] - datatmp[2]) >> 1;

	data[4] = (datatmp[4] + datatmp[5]) >> 1;
	data[5] = (datatmp[4] - datatmp[5]) >> 1;
	data[6] = (-datatmp[6] + datatmp[7]) >> 1;
	data[7] = (datatmp[6] + datatmp[7]) >> 1;
	// four inverse butterfly  

	data[5] = -data[5] + (data[6] >> 1) - (data[6] >> 4);
	data[6] = data[6] - (data[5] >> 1) - (data[5] >> 2);
	data[5] = data[5] + (data[6] >> 1) - (data[6] >> 4);

	/////////////////  
	datatmp[0] = (data[0] + data[7]) >> 1;
	datatmp[1] = (data[1] + data[6]) >> 1;
	datatmp[2] = (data[2] + data[5]) >> 1;
	datatmp[3] = (data[3] + data[4]) >> 1;
	datatmp[4] = (data[3] - data[4]) >> 1;
	datatmp[5] = (data[2] - data[5]) >> 1;
	datatmp[6] = (data[1] - data[6]) >> 1;
	datatmp[7] = (data[0] - data[7]) >> 1;

	//int i;  
	for (i = 0; i < 8; i++) data[i] = datatmp[i];
}

void dct2d8x8(int(*data)[8], int height, int width)
{
	int nheight, nwidth;
	int i, j, k, l;
	int ni, nj;

	int datatmp[8];
	nheight = height >> 3;
	nwidth = width >> 3;

	ni = 0;
	for (i = 0; i < nheight; i++)
	{
		nj = 0;
		for (j = 0; j < nwidth; j++)
		{
			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
					datatmp[l] = data[ni + k][nj + l];
				dct8x8(datatmp);
				for (l = 0; l < 8; l++)
					data[ni + k][nj + l] = datatmp[l];
			}

			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
					datatmp[l] = data[ni + l][nj + k];
				dct8x8(datatmp);
				for (l = 0; l < 8; l++)
					data[ni + l][nj + k] = datatmp[l];
			}
			nj = nj + 8;
		}
		ni = ni + 8;

	}
}

void idct2d8x8(int(*data)[8], int height, int width)
{
	int nheight, nwidth;
	int i, j, k, l;
	int ni, nj;

	int datatmp[8];
	nheight = height >> 3;
	nwidth = width >> 3;

	ni = 0;
	for (i = 0; i<nheight; i++)
	{
		nj = 0;
		for (j = 0; j<nwidth; j++)
		{
			for (k = 0; k<8; k++)
			{
				for (l = 0; l<8; l++)
					datatmp[l] = data[ni + l][nj + k];
				idct8x8(datatmp);
				for (l = 0; l<8; l++)
					data[ni + l][nj + k] = datatmp[l];
			}
			for (k = 0; k<8; k++)
			{

				for (l = 0; l<8; l++)
					datatmp[l] = data[ni + k][nj + l];
				idct8x8(datatmp);
				for (l = 0; l<8; l++)
					data[ni + k][nj + l] = datatmp[l];
			}
			nj = nj + 8;
		}
		ni = ni + 8;
	}
}

void dct2d4x4(int (*data)[4], int blockSize)
{
	
	//水平变换,左乘cf
	int m5[4] = { 0 };
	for (int j = 0; j < blockSize; j++) 
	{
		//蝶形计算
		for (int i = 0; i < 2; i++) 
		{
			int i1 = 3 - i;
			m5[i] = data[i][j] + data[i1][j];
			m5[i1] = data[i][j] - data[i1][j];
		}
		data[0][j] = m5[0] + m5[1];
		data[2][j] = m5[0] - m5[1];
		data[1][j] = m5[3] * 2 + m5[2];
		data[3][j] = m5[3] - m5[2] * 2;
	}
	//垂直变换右乘cft
	for (int i = 0; i < blockSize; i++)
	{
		//蝶形计算
		for (int j = 0; j < 2; j++)
		{
			int j1 = 3 - j;
			m5[j] = data[i][j] + data[i][j1];
			m5[j1] = data[i][j] - data[i][j1];
		}
		data[i][0] = m5[0] + m5[1];
		data[i][2] = m5[0] - m5[1];
		data[i][1] = m5[3] * 2 + m5[2];
		data[i][3] = m5[3] - m5[2] * 2;
	}
}
void dct2d4x4oneD(short int data[16], short int dataout[16])
{
	short int m0 = 0;
	short int m1 = 0;
	short int m2 = 0;
	short int m3 = 0;
	int i = 0;
	int j = 0;
	for (j = 0; j < 4; j++) {
		m0 = data[j] + data[3 * 4 + j];
		m3 = data[j] - data[3 * 4 + j];
		m1 = data[1 * 4 + j] + data[2 * 4 + j];
		m2 = data[1 * 4 + j] - data[2 * 4 + j];

		data[j] = m0 + m1;
		data[2 * 4 + j] = m0 - m1;
		data[1 * 4 + j] = m3 * 2 + m2;
		data[3 * 4 + j] = m3 - m2 * 2;
	}
	
	for (i = 0; i < 4; i++) {
		m0 = data[i * 4] + data[i * 4 + 3];
		m3 = data[i * 4] - data[i * 4 + 3];
		m1 = data[i * 4 + 1] + data[i * 4 + 2];
		m2 = data[i * 4 + 1] - data[i * 4 + 2];

		data[i * 4] = m0 + m1;
		data[i * 4 + 2] = m0 - m1;
		data[i * 4 + 1] = m3 * 2 + m2;
		data[i * 4 + 3] = m3 - m2 * 2;
	}
	for (i = 0; i < 16; i++)
		dataout[i] = data[i];
}


void idct2d4x4(int(*data)[4], int blockSize)
{
	int m5[4] = { 0 };
	for (int j = 0; j < blockSize; j++) {
		m5[0] = data[0][j] + data[2][j];
		m5[1] = data[0][j] - data[2][j];
		m5[2] = 2 * data[1][j] + data[3][j];
		m5[3] = data[1][j] - 2 * data[3][j];
		
		data[0][j] = 5 * m5[0] + 2 * m5[2];
		data[1][j] = 5 * m5[1] + 2 * m5[3];
		data[2][j] = 5 * m5[1] - 2 * m5[3];
		data[3][j] = 5 * m5[0] - 2 * m5[2];
		data[0][j] /= 20;
		data[1][j] /= 20;
		data[2][j] /= 20;
		data[3][j] /= 20;
		
			/*
		data[0][j] = m5[0]/4 + m5[2]/10;
		data[1][j] = m5[1]/4 + m5[3]/10;
		data[2][j] = m5[1]/4 - m5[3]/10;
		data[3][j] = m5[0]/4 - m5[2]/10;
		*/
	}

	for (int i = 0; i < blockSize; i++) {
		m5[0] = data[i][0] + data[i][2];
		m5[1] = data[i][0] - data[i][2];
		m5[2] = 2 * data[i][1] + data[i][3];
		m5[3] = data[i][1] - 2 * data[i][3];
		
		data[i][0] = 5 * m5[0] + 2 * m5[2];
		data[i][1] = 5 * m5[1] + 2 * m5[3];
		data[i][2] = 5 * m5[1] - 2 * m5[3];
		data[i][3] = 5 * m5[0] - 2 * m5[2];
		data[i][0] /= 20;
		data[i][1] /= 20;
		data[i][2] /= 20;
		data[i][3] /= 20;
		
			/*
		data[i][0] = (m5[0]/4) + m5[2]/10;
		data[i][1] = (m5[1]/4) + m5[3]/10;
		data[i][2] = (m5[1]/4) - m5[3]/10;
		data[i][3] = (m5[0]/4) - m5[2]/10;
		*/
	}
}
void idct2d4x4oneD(short int data[16], short int dataout[16])
{
	int m0 = 0;
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int j = 0;
	int i = 0;
	for (j = 0; j < 4; j++) {
		m0 = data[j] + data[2 * 4 + j];
		m1 = data[j] - data[2 * 4 + j];
		m2 = 2 * data[1 * 4 + j] + data[3 * 4 + j];
		m3 = data[1 * 4 + j] - 2 * data[3 * 4 + j];

		data[j] = 5 * m0 + 2 * m2;
		data[1 * 4 + j] = 5 * m1 + 2 * m3;
		data[2 * 4 + j] = 5 * m1 - 2 * m3;
		data[3 * 4 + j] = 5 * m0 - 2 * m2;

		data[j] /= 20;
		data[1 * 4 + j] /= 20;
		data[2 * 4 + j] /= 20;
		data[3 * 4 + j] /= 20;
	}
	for (i = 0; i < 4; i++) {
		m0 = data[i * 4] + data[i * 4 + 2];
		m1 = data[i * 4] - data[i * 4 + 2];
		m2 = 2 * data[i * 4 + 1] + data[i * 4 + 3];
		m3 = data[i * 4 + 1] - 2 * data[i * 4 + 3];

		data[i * 4] = 5 * m0 + 2 * m2;
		data[i * 4 + 1] = 5 * m1 + 2 * m3;
		data[i * 4 + 2] = 5 * m1 - 2 * m3;
		data[i * 4 + 3] = 5 * m0 - 2 * m2;

		data[i * 4] /= 20;
		data[i * 4 + 1] /= 20;
		data[i * 4 + 2] /= 20;
		data[i * 4 + 3] /= 20;
	}
	for (i = 0; i < 16; i++)
		dataout[i] = data[i];
}