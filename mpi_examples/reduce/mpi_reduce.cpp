#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "mpi.h"

    float thingCalc (int i) {
        
        return sqrt(i);
        
    };
 
using namespace std;

int main(int argc, char *argv[]) {
    
    float my_thing;
    float my_sum;
    int myid;
    float sum;

    MPI_Init(&argc,&argv); 
    my_thing = 0.0;
    my_sum = 0.0;
    sum = 0.0;
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    int i;
    for (i=0; i<1000; i++) {
        my_sum += thingCalc(i);
    }
    
    MPI_Reduce(&my_sum,&sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    
    if (myid == 0) {
        std::cout <<"> Outcome of Reduction: "<<sum<<std::endl;
    }
    
    MPI_Finalize();
    
    return 0;
}
