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
  int dest = 1;//atoi(argv[2]); // change to command line inputs again if you want to vary these
  int src = 0; //atoi(argv[1]);
  if (rank == src) {   
    MPI_Send(&send_num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    std::cout << "> " <<node_name<<" Sent " << send_num << "  To ... ? "<< std::endl;
  } else if(rank == dest){
     MPI_Recv(&received, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     std::cout << "> Number: " << received << " Received by "<< node_name<< std::endl;
  }
  MPI_Finalize();
}

