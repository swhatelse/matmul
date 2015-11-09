#include "common.h"

void fill(int *array){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      array[i*N+j] = rand() % 10;
    }
  }
}

void zerofill(int *array){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      array[i*N+j] = 0;
    }
  }
}

void display(int *array){
 for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      printf("%d ", array[i*N+j]);
    }
    printf("\n");
  }
}
