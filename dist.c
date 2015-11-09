#include<stdio.h>
#include<mpi.h>
#include"common.h"

void fill2(int *array){
  for(int i = 0; i < 2N; i++){
    for(int j = 0; j < 2N; j++){
      array[i*2N+j] = rand() % 10;
    }
  }
}

int main (int argc, char** argv){
  int my_rank;
  int *AB, *C;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int nbNode;
  MPI_Comm_size(MPI_COMM_WORLD, &nbNode);

  if(my_rank == 0){
    // Master
    printf("I'm the master!\n");

    AB = malloc(sizeof(int)*2N*2N);
    C = malloc(sizeof(int)*N*N);
  
    fill2(AB);

  }
  else{
    // Workers
    printf("Yes the master.\n");
    C = malloc(sizeof(int)*N*N);
  }

  MPI_Scatter(A, N * N / nbNode, MPI_INT, C, N*N, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Finalize();
  return 0;
}
