#include "omp.h"
#include "mpi.h"
#include "load_file.hpp"

#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>


auto main() -> int {
	MPI_Init(NULL, NULL);

	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (rank == src) {
		MPI_Send(&send_num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		std::cout << "> " << node_name << " Sent " << send_num << "  To  node" << dest << std::endl;
	}

	if (rank == dest) {
		std::cout << " hello from " << node_name << std::endl;
		MPI_Recv(&received, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// processing
		std::cout << "> Number: " << received << " Received by " << node_name << std::endl;

		MPI_Send(&send_num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		std::cout << "> " << node_name << " Sent " << send_num << "  To  node" << dest << std::endl;
		cond = true;
	}

	if (rank ==  0 && cond == true) {
		std::cout << " hello from " << node_name << std::endl;
		MPI_Recv(&received, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}


	MPI_Finalize();

	return 0;
};
