#include "omp.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <random>

auto getRandInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

auto getRandomDir() -> std::pair<int, int> {
	bool increment = getRandInt(0,9) > 7;

	return {
		getRandInt(0, 3),
		increment ? 1 : -1
	};
}

void display(std::vector<std::vector<int>> vectors, int step) {
	std::cout << "\nAt step: " << step << '\n';

	for (int i=0; i<vectors.size(); ++i) {
		std::cout << "Vector " << i << ": ";

		// Print out coordinates
		for (int coord : vectors[i])
			std::cout << coord << ' ';

		std::cout << '\n';
	}
}

auto main() -> int {

	std::vector<std::vector<int>> vectors = {
		{5, 14, 10},
		{7, -8, -14},
		{-2, 9, 8},
		{15, -6, 3},
		{12, 4, -5},
		{4, 20, 17},
		{-16, 5, -1},
		{-11, 3, 16},
		{3, 10, -19},
		{-16, 7, 4}
	};

	for (int i=0; i<10; ++i) {

		// iterate through vectors
		#pragma omp parallel for schedule(runtime)
		for(auto &vect: vectors) {
			// Pick a random coord
			std::pair<int, int> newDir = getRandomDir();

			// Increment or decrement it
			vect[newDir.first] = vect[newDir.first] + newDir.second;
		}

		if (i%5 == 4) {
			// Display the progress of the entire set at 5 and 10 steps
			display(vectors, i+1);
		}

	}

	return 0;
};
