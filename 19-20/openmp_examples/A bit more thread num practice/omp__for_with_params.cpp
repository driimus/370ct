#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <time.h>

int main (void)
{
  // add the right pragma
 #define sqr ((x)*(x))
 int arr[10]= {2,3,4,5,6,7,8,9,10};
 #pragma omp parallel 
  {
    int i = omp_get_thread_num() 
                 std::cout << sqr(arr[i]) << std::endl;
  }     
 return 0;
}
