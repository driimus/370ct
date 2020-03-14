#include "omp.h"
#include "mpi.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>

auto getClockSpeed() -> std::string {
	std::ifstream cpuInfo("/proc/cpuinfo");
	std::string clockSpeed;
	// Find the line where the clock speed is listed.
	while(getline(cpuInfo, clockSpeed)) {
		if (clockSpeed.find("cpu MHz", 0) != std::string::npos)
			break;
	}
	cpuInfo.close();
	// Return the first line containing CPU clock speeds.
	return clockSpeed.substr(clockSpeed.find(':') + 1);
}

auto main() -> int {
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	// Current node's CPU core count and clock speed.
	int node_core_count = omp_get_num_procs();

	// Reducer for determining total cluster core count.
	int total_core_count = 0;
	MPI_Reduce(&node_core_count, &total_core_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	std::string core_clock_speed = getClockSpeed();
	std::cout << processor_name << " - "
						<< node_core_count << " cores @"
						<< core_clock_speed << "MHz\n";

	// Determine physical memory size
	long RAM = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
	std::cout << processor_name << " - RAM: " << RAM << '\n';

	if (world_rank == 0) {
		std::cout << "Total node count: " << world_size << '\n';
		std::cout << "Total cluster core count: " << total_core_count << '\n';
	}

	MPI_Finalize();

	return 0;
};
