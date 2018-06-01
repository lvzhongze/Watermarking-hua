#pragma once
//#include "hls_linear_algebra.h"
const int N = 4;

typedef float MATRIX_IN_a;
typedef float MATRIX_OUT_a;
void dct2d4x4(MATRIX_IN_a data[N][N], int blockSize);
void idct2d4x4(MATRIX_IN_a data[N][N], int blockSize);
