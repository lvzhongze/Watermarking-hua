#include "svdEmbed.h"
#include "svd.h"
#include "dct.h"
void svdEmbed(MATRIX_IN imageArray[N1][N1],MATRIX_IN waterMarkArray[N2][N2],MATRIX_OUT svdImageArray[N1][N1],float k)
{
	for(int i=0;i<200;i++){
		for(int j=0;j<200;j++){
			int x=4*i;
			int y=4*j;
			float temArray[4][4];
			//float temArrayf[4][4];
			float S[4][4];
			float U[4][4];
			float V[4][4];
			float US[4][4];
			float USV[4][4];
			//取块
			for(int a=0;a<4;a++){
				for(int b=0;b<4;b++){
					temArray[a][b]=(float)imageArray[x+a][y+b];
				}
			}
			dct2d4x4(temArray, 4);

			//S是奇异值矩阵，对角线，从小到大排布
			svd_top(temArray,S,U,V);
			//在最大的那个奇异值上添加水印信息
			if(waterMarkArray[i][j]>128){
				waterMarkArray[i][j]=1;
			}else{
				waterMarkArray[i][j]=0;
			}
			//printf("%f",S[4][4]);
			for(int dd=0;dd<4;dd++){
				S[dd][dd] = S[dd][dd]+waterMarkArray[i][j]*k;
			}

			//printf("%f",S[4][4]);
			//重构得到USV U*S*V
			hls::matrix_multiply<hls::NoTranspose, hls::NoTranspose, A_ROWS, A_ROWS, A_ROWS, A_COLS, A_ROWS, A_COLS, float, float>(U, S, US);
			hls::matrix_multiply<hls::NoTranspose, hls::ConjugateTranspose, A_ROWS, A_COLS, A_COLS, A_COLS, A_ROWS, A_COLS, float, float>(US, V, USV);

			//对得到的USV做dct逆变换
			idct2d4x4(USV, 4);
			for(int a=0;a<4;a++){
				for(int b=0;b<4;b++){
					svdImageArray[x+a][y+b]=USV[a][b];
				}
			}
		}
	}
}

void svdExtract(MATRIX_IN imageArray[N1][N1],MATRIX_IN svdImageArray[N1][N1],MATRIX_OUT waterMarkArrayIsvd[N2][N2],float k)
{
	for(int i=0;i<200;i++){
			for(int j=0;j<200;j++){
				int x=4*i;
				int y=4*j;
				float temArray0[4][4],temArray1[4][4];
				float S0[4][4],S1[4][4];
				float U0[4][4],U1[4][4];
				float V0[4][4],V1[4][4];
				float US0[4][4],US1[4][4];
				float USV0[4][4],USV1[4][4];
				//取块
				for(int a=0;a<4;a++){
					for(int b=0;b<4;b++){
						temArray0[a][b]=(float)imageArray[x+a][y+b];
					}
				}
				for(int a=0;a<4;a++){
					for(int b=0;b<4;b++){
						temArray1[a][b]=(float)svdImageArray[x+a][y+b];
					}
				}
				//取完块首先做dct变换再做奇异值分解
				dct2d4x4(temArray0, 4);
				dct2d4x4(temArray1, 4);
				//S是奇异值矩阵，对角线，从小到大排布
				svd_top(temArray0,S0,U0,V0);
				svd_top(temArray1,S1,U1,V1);
				//printf("S1%f\n",S1);
				//printf("S0%f\n",S0);
				//重构waterMark
				int flag=0;
				for(int dd=0;dd<4;dd++){
					float a = (float)waterMarkArrayIsvd[i][j];
					a = (S1[dd][dd]-S0[dd][dd])/(float)k;
					if(a*a - (a-1)*(a-1) > 0){
						flag = flag+1;
					}
				}
				if(flag>=2){
					waterMarkArrayIsvd[i][j]=255;
				}else{
					waterMarkArrayIsvd[i][j]=0;
				}
			}
		}
}


