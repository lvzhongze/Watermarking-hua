#pragma once
template<class T>
void dct8x8(int data[8]);
void idct8x8(int data[8]);
void dct2d8x8(int(*data)[8], int height, int width);
void idct2d8x8(int(*data)[8], int height, int width);

void dct2d4x4(int(*data)[4], int blockSize);
void dct2d4x4oneD(short int data[16],short int dataout[16]);
void idct2d4x4(int(*data)[4], int blockSize);
void idct2d4x4oneD(short int data[16], short int dataout[16]);