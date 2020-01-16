#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"

typedef struct {
  char hostName[MPI_MAX_PROCESSOR_NAME];
  int  id;
}hostStruct;


MPI::Datatype  createMpiWordType(){
    //how many data types in the struct
    const int count = 2; 
    //type of every different block of data
    MPI::Datatype typesInStruct[count] = {MPI::CHAR,MPI::INT};
    //how many elements per block 
    int arrayBlockLengths [count] = {12,1};
    //Now we need to specify starting memory location of each block, *relative to the start of the struct only*
    // it's a bit of a tedious process, but neccesary. 
    MPI::Aint objAddress, address1,address2;
    MPI::Aint arrayDisplacements[count];	
    hostStruct sbuf;//Just has to be a struct instance but not
                    // the one you're actually sending, since we only need those locations,
                    // which, since this is a static struct, will always be the same
    objAddress = MPI::Get_address(&sbuf);
    address1 = MPI::Get_address(&sbuf.hostName);
    address2 = MPI::Get_address(&sbuf.id);
    arrayDisplacements[0] = address1 - objAddress;
    arrayDisplacements[1] = address2 - objAddress;
    // now we create the MPI equivilent datatype using the data we just collected
    MPI::Datatype mpiHostStruct;
    mpiHostStruct = MPI::Datatype::Create_struct(count,arrayBlockLengths,arrayDisplacements,typesInStruct);
    // and commit it the the Communicator, so it can be used accross the entire cluster
    mpiHostStruct.Commit();
    return mpiHostStruct;
  }



int main(int argc, char** argv) {
  int com_size, rank, namelen;
 hostStruct receive;
  memset(receive.hostName, 0, MPI_MAX_PROCESSOR_NAME);
  MPI_Init(NULL,NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Comm_size(MPI_COMM_WORLD, &com_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  memset(node_name, 0, MPI_MAX_PROCESSOR_NAME);
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);
  
  //Create an instance of the datatype you built
  MPI::Datatype mpiHostStruct = createMpiWordType();

  if (rank==0) {
    // Startup informative text
    std::cout <<  std::endl; 
    std::cout << "> #############################" << std::endl; 
    std::cout << "> # This program does nothing #" << std::endl;
    std::cout << "> #############################" << std::endl << std::endl; 
  }
 
  MPI_Finalize();
  return 0;
}
