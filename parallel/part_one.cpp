#include "omp.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>

auto main() -> int {
	long RAM = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);

	std::cout << "Core count: " << omp_get_num_procs() << std::endl;
	system("cat /proc/cpuinfo | grep MHz");
	std::cout << "RAM: " << RAM << '\n';
	system("du -s /home");
	#pragma omp parallel
	{
	};


return 0;
};
