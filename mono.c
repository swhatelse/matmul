#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include"common.h"

#define SM (CLS / sizeof(int))

void mono(int *A, int *B, int *C){
  int *rC, *rA, *rB;
  for(int i = 0; i < N; i += SM){
    for(int j = 0; j < N; j += SM){
      for(int k = 0; k < N; k += SM){
        rC = &C[i*N+j];
        rA = &A[i*N+k];
        for(int i2 = 0; i2 < SM; ++i2, rC += N, rA += N){
          rB = &B[k*N+j];
          for(int k2 = 0; k2 < SM; ++k2, rB += N){
            for(int j2 = 0; j2 < SM; ++j2){
              rC[j2] += rA[k2] * rB[j2];
            }
          }
        }
      }
    }
  }
}

int main(int argc, char** argv){
  int *A, *B, *C;
          
  A = malloc(sizeof(int)*N*N);
  B = malloc(sizeof(int)*N*N);
  C = malloc(sizeof(int)*N*N);

  fill(A);
  fill(B);
  zerofill(C);

  mono(A,B,C);

  free(A);
  free(B);
  free(C);

  return 0;
}
