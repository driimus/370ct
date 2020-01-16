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
 int multiplier;
 int list[16]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
 #pragma omp parallel for schedule (dynamic,2) private(multiplier)
 for (int count=0; count<16;++count)
     {
      std::this_thread::sleep_for(std::chrono::seconds(2));
     }
 return 0;
}
