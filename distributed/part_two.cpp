#include "load_file.hpp"
#include "omp.h"
#include "mpi.h"

#include <sstream>
#include <algorithm>
#include <random>


auto getRandomInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

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

auto jumbleWords(std::string& verse) -> std::vector<int> {
	std::string temp;
	std::stringstream ss(verse);

	// Split verse into words.
	std::vector<std::string> words;
	while (ss >> temp) words.push_back(temp + " ");

	// Shuffle words around.
	std::vector<int> positions;
	for (int i=0; i<words.size(); ++i) positions.push_back(i);
	std::random_shuffle(positions.begin(), positions.end());

	// Build jumbled verse and return it.
	std::string jumbledVerse;
	for (int pos : positions) jumbledVerse += words[pos] + ' ';
	verse = jumbledVerse;
	return positions;
}

auto main() -> int {
	MPI_Init(NULL, NULL);


	bool finished = false;
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	std::string line;
	std::vector<int> positions;
	std::vector<std::string> poem = getFileContents("to_the_rain.txt");
	poem.resize(world_size - 1);

	if (world_rank == 0) {
		for (int i = 0; i < poem.size(); ++i) {
			MPI_Send(&poem[i][0], poem[i].size()+1, MPI_CHAR, i+1, 0, MPI_COMM_WORLD);
		}
	}
	else {
		line = receiveLine();
		positions = jumbleWords(line);

		std::cout << "> " << line << " Received" << std::endl;
	}

	// Part 3
	int matches = 0;
	for (int i = 1; i <= world_size-1; ++i) {
		while (!finished) {
			if (world_rank == i) {
				// Send two random indices.
				int temp[2] = {
					getRandomInt(0, positions.size()-1),
					getRandomInt(0, positions.size()-1)
				};
				while (temp[0] == temp[1]) temp[1] = getRandomInt(0, positions.size()-1);

				MPI_Send(&temp, 2, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

				// Get result
				MPI_Recv(&finished, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				std::cout << finished << '\t' << world_rank << std::endl;
				// std::cout<< temp[0] << temp[1] << '\t';
			} else if (world_rank == 0) {
				// receive indices
				int temp[2];
				MPI_Recv(&temp, 2, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				// compare positions
				bool match = abs(temp[0] - temp[1]) == 1;
				// if (match) ++matches;
				std::cout<< matches <<std::endl;

				// send result
				MPI_Send(&match, 1, MPI_C_BOOL, i, 0, MPI_COMM_WORLD);
				// if (matches == world_size-2) break;
			}

			// if (world_rank == i) {
			// }
		}
		// finished = false;
	}

	MPI_Finalize();

	return 0;
};
