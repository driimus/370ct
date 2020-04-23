#include "omp.h"
#include "mpi.h"

#include <random>
#include <algorithm>


auto getRandomInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

auto calculate(int num, int op) -> int {
	switch (op) {
	case 0:
		num += getRandomInt(15, 60);
		break;
	case 1:
		num -= getRandomInt(1, 15);
		break;
	case 2:
		num *= getRandomInt(2, 9);
		break;
	case 3:
		num /= getRandomInt(2, 5);
		break;
	}
	return num;
}

auto main() -> int {
	MPI_Init(NULL, NULL);

	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	std::vector<int> nodes;
	for (int i = 1; i < world_size; ++i) nodes.push_back(i);

	// Data that is passed between nodes.
	int data[3] = {
		getRandomInt(10, 99), 				// initial number
		getRandomInt(0, 3),						// initial arithmetic operator
		getRandomInt(world_size, 15)	// amount of iterations
	};

	if (world_rank == 0) {
		std::cout << "Initial: " << data[0] << std::endl;
		int to = getRandomInt(1, world_size - 1);

		MPI_Send(&data, 3, MPI_INT, to, 0, MPI_COMM_WORLD);
	} else {
		while (true) {
			MPI_Status status;
			MPI_Recv(&data, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			if (data[2] == 0) break; // If flagged for termination, exit loop.

			data[0] = calculate(data[0], data[1]);
			data[1] = (data[1] + 1) % 4;	// Pick another arithmetic operation
			--data[2];	// Decrement remaining amount of iterations.

			// Copy of node indices
			std::vector<int> temp(nodes);
			// Flag previous and current nodes as visited.
			temp[status.MPI_SOURCE - 1] = 0;
			temp[world_rank - 1] = 0;

			for (int v:temp) std::cout<<v<<' ';
			std::cout<<' '<<world_rank<<status.MPI_SOURCE<<std::endl;

			// If enough iterations have passed.
			if (data[2] == 0) {
				std::cout << "Final: " << data[0] << std::endl;
				// Notify other nodes to terminate.
				for (int i = 1; i < world_size; ++i) {
					if (i == world_rank) continue;
					MPI_Send(&data, 3, MPI_INT, i, 0, MPI_COMM_WORLD);
				}
				// Terminate process on current node.
				break;
			} else {
				// Send to a random next node.
				std::random_shuffle(temp.begin(), temp.end());
				int to = 0;
				for (int v:temp) if (v) {to = v; break;}
				std::cout << "Node " << world_rank << ": " << data[0]
				          << ". From " << prev
				          << ", passing to node " << temp[to] << std::endl;
				MPI_Send(&data, 3, MPI_INT, temp[to], 0, MPI_COMM_WORLD);
			}
		}
	}

	MPI_Finalize();

	return 0;
};
