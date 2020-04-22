#include "load_file.hpp"
#include "omp.h"
#include "mpi.h"


auto receiveLine() -> std::string {
	MPI_Status status;
	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

	// Check for the length of the verse.
	int len;
	MPI_Get_count(&status, MPI_CHAR, &len);

	// Store the verse in a buffer.
	char temp[len];
	MPI_Recv(&temp, len, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

	// Return verse as a string.
	std::string res = temp;
	return res;
}

auto main() -> int {
	MPI_Init(NULL, NULL);


	bool finished = false;
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	std::vector<std::string> poem = getFileContents("to_the_rain.txt");
	std::string line;
	poem.resize(world_size - 1);

	if (world_rank == 0) {
		for (int i = 0; i < poem.size(); ++i) {
			MPI_Send(&poem[i][0], poem[i].size()+1, MPI_CHAR, i+1, 0, MPI_COMM_WORLD);
			// std::cout << " Sent " << poem[i] << " to node " << i+1 << std::endl;
		}
	} else {
		std::string line = receiveLine();

		// processing
		std::cout << "> " << line << " Received" << std::endl;
		finished = true;
	}

	if (world_rank == 0 && finished) {
		// std::cout << " hello from src" << std::endl;
	}

	MPI_Finalize();

	return 0;
};
