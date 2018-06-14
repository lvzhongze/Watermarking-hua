#include "dct.h"

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