#include "mpi.h"
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
	MPI_INIT(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);
	// printSysInfo();

	return 0;
};
