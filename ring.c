#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include"common.h"

int main(int argc, char **argv){
  int my_rank;
  int nbNode;
  char s[] = "pouet";

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nbNode);
  
  int next = (my_rank + 1) % nbNode;
  int prev = (my_rank - 1) % nbNode;

  if(my_rank != 0) {
    MPI_Recv(s, strlen(s), MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Node %d Received %s\n", my_rank, s);
  }

  if(my_rank == 0 || my_rank < nbNode){
    MPI_Send(s, strlen(s), MPI_CHAR, next, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
