#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>  
#include "stdio.h"


int main (void)
{
#pragma omp parallel
{
 std::cout << "thread_num: " << omp_get_thread_num() << std::endl;
};


return 0;
};
