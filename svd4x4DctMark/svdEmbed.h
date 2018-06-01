#ifndef SVDEMBED_H
#define SVDEMBED_H
#include "hls_linear_algebra.h"
#include "dct.h"
const int N1 = 800;
const int N2 = 200;

typedef int MATRIX_IN;
typedef int MATRIX_OUT;

void svdEmbed(MATRIX_IN imageArray[N1][N1],MATRIX_IN waterMarkArray[N2][N2],MATRIX_OUT svdImageArray[N1][N1],float k);
void svdExtract(MATRIX_IN imageArray[N1][N1],MATRIX_IN svdImageArray[N1][N1],MATRIX_OUT waterMarkArrayIsvd[N2][N2],float k);
#endif
