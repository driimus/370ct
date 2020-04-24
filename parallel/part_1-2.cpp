#include "omp.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>

void printSysInfo() {
	// Determine physical memory size
	long RAM = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);

	std::cout << "Physical core count: " << omp_get_num_procs() << std::endl;
	system("cat /proc/cpuinfo | grep MHz");
	std::cout << "RAM amount: " << RAM << '\n';

	printf("Home directory size: "); fflush(stdout);
	system("du -s /home 2>/dev/null");
}

auto main() -> int {
	printSysInfo();

	#pragma omp parallel for schedule(runtime)
	for (int i = 0; i < 10; ++i)
		printf("Thread %d processes iteration %d.\n", omp_get_thread_num(), i);
	return 0;
};
