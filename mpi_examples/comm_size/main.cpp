#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"



int main(int argc, char** argv) {
  int com_size, rank;
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &com_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // only displayed on one node
  if (rank==0) {
    std::cout <<  std::endl; 
    std::cout << "> ###################" << std::endl; 
    std::cout << ">  Comm Size " << com_size <<std::endl;
    std::cout << "> ###################" << std::endl << std::endl; 
  }
  MPI_Finalize();
  
  return 0;
}
