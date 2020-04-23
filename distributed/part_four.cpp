#include "omp.h"
#include "mpi.h"

#include <random>


auto getRandomInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

// enum operations : int {
// 	ADD = 0,
// 	SUB,
// 	mul,
// 	div
// }

auto main() -> int {
	MPI_Init(NULL, NULL);

	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	std::vector<int> nodes;
	for (int i = 0; i < world_size; ++i) nodes.push_back(i);

	int initial = getRandomInt(10, 99);
	if (world_rank == 0) {
		std::cout << "Initial: " << initial << std::endl;
		int to = getRandomInt(1, world_size - 1);

		MPI_Send(&initial, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
		MPI_Recv(&initial, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		std::cout << "Final result: " << initial << std::endl;
	} else {
		// Copy of node indices
		std::vector<int> temp(nodes);

		MPI_Status status;
		MPI_Recv(&initial, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		initial += 2;

		std::cout << "Node " << world_rank << ": " << initial << std::endl;

		// Flag previous and current nodes as visited.
		int prev = status.MPI_SOURCE;
		temp[prev] = prev == world_size-1
								? getRandomInt(0, world_size-2)
								: prev + 1;
		temp[world_rank] = world_rank == world_size-1
											? getRandomInt(0, world_size-2)
											: world_rank + 1;

		// Send to a random next node.
		int to = getRandomInt(0, world_size - 1);
		MPI_Send(&initial, 1, MPI_INT, temp[to], 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
};
