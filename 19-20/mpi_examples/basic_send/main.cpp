#include <iostream>
#include "mpi.h"
#include <cstring>
int main(int argc, char** argv) {

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
int rank,size, namelen;
  int send_num = 5;
  int received = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);
  int dest = 10; 
  if (rank==0) {
    MPI_Send(&send_num, dest, MPI_INT, 1, 0, MPI_COMM_WORLD);
    std::cout << "> " <<node_name<<" sent " << send_num << "  to next node in line"<< std::endl;
  } else if(rank == dest){
     MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     std::cout << "> " << received << " received by "<< node_name<< std::endl;
  }
  MPI_Finalize();
}
