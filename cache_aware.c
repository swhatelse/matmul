#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include"common.h"

#define SM (CLS / sizeof(int))

void naive(int *A, int *B, int *C){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      for(int k = 0; k < N; k++){
        C[i*N+j] += A[i*N+k] * B[k*N+j];
      }
    }
  }
}


int check(int *A, int *B){
  int diff = 0;
  for( int i = 0; i < N; i++){
    for( int j = 0; j < N; j++){
      if(A[i*N+j] != B[i*N+j]){
        diff++;
      }
    }
  }
  return diff;
}

void multi(int *A, int *B, int *C){
#pragma omp parallel shared(A, B, C)
  {
  int *rC, *rA, *rB;
  int i, j, k, i2, j2, k2;
#pragma omp for schedule(guided)
    for( i = 0; i < N; i += SM){
      for( j = 0; j < N; j += SM){
        for( k = 0; k < N; k += SM){
          rC = &C[i*N+j];
          rA = &A[i*N+k];
          for( i2 = 0; i2 < SM; ++i2, rC += N, rA += N){
            rB = &B[k*N+j];
            for( k2 = 0; k2 < SM; ++k2, rB += N){
              for( j2 = 0; j2 < SM; ++j2){
                rC[j2] += rA[k2] * rB[j2];
              }
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
  multi(A,B,C);

#ifdef CHECK
  int* Cref = malloc(sizeof(int)*N*N);
  zerofill(Cref);
  naive(A,B,Cref);
  if(check(Cref,C) != 0){
    printf("Erreur!\n");
  }
  else{
    printf("Ok!\n");
  }
  free(Cref);
#endif

  free(A);
  free(B);
  free(C);

  return 0;
}
