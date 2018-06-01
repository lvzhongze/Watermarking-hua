#include "dct.h"
void dct2d4x4(MATRIX_IN_a data[N][N], int blockSize)
{

	//Ë®Æ½±ä»»,×ó³Ëcf
	int m5[4] = { 0 };
	for (int j = 0; j < blockSize; j++)
	{
		//µûÐÎ¼ÆËã
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
	//´¹Ö±±ä»»ÓÒ³Ëcft
	for (int i = 0; i < blockSize; i++)
	{
		//µûÐÎ¼ÆËã
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

void idct2d4x4(MATRIX_IN_a data[N][N], int blockSize)
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
