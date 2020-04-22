#include "load_file.hpp"
#include "omp.h"
#include "mpi.h"


auto main() -> int {
	MPI_Init(NULL, NULL);


	bool finished = false;
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	std::vector<std::string> poem = getFileContents('to_the_rain.txt');
	std::string line;
	if (rank == 0) {
		for (int i = 0; i < poem.size(); ++i) {
			MPI_Send(&poem[i].c_str(), poem[i].size(), MPI_CHAR, i+1, 0, MPI_COMM_WORLD);
			std::cout << " Sent " << poem[i] << " to node " << i+1 << std::endl;
		}
	} else {
		std::cout << " hello from " << node_name << std::endl;
		MPI_Recv(&line, 50, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// processing
		std::cout << "> " << line << " Received" << std::endl;

		// MPI_Send(&send_num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		// std::cout << "> " << node_name << " Sent " << send_num << "  To  node" << dest << std::endl;
		finished = true;
	}

	if (rank == 0 && finished) {
		std::cout << " hello from src" << std::endl;
		// MPI_Recv(&received, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}


	MPI_Finalize();

	return 0;
};
