#include "omp.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <random>

enum axes : int { X = 0, Y, Z };

using std::vector;

auto getRandomInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

auto getRandomDirection() -> std::pair<int, int> {
	bool increment = getRandomInt(0,9) > 5;

	return {
		getRandomInt(0, 2),
		increment ? 1 : -1
	};
}

auto getCentroid(vector<vector<int>> particles) -> vector<int> {
	vector<int> centroid(3);

	for (int coord=0; coord<centroid.size(); ++coord) {
		// reduce into sum of each coord
		#pragma omp parallel for shared(centroid[coord], particles) reduction(+: centroid[coord])
		for (int i=0; i<particles.size(); ++i) {
			centroid[coord] += particles[i][coord];
		}

		// divide by vect count
		centroid[coord] /= 10;
	}

	return centroid;
}

void display(vector<vector<int>> vectors) {
	for (int i=0; i<vectors.size(); ++i) {
		std::cout << "Particle " << i+1 << ": ";

		// Print out coordinates
		for (int coord : vectors[i])
			std::cout << coord << ' ';

		std::cout << '\n';
	}
}

void randomlyMoveParticles(vector<vector<int>> &particles) {
	for (int i=0; i<10; ++i) {

		// Iterate through all the particles
		#pragma omp parallel for schedule(runtime)
		for(auto &vect: particles) {
			// Pick a random direction to move in by 1 step
			std::pair<int, int> newDir = getRandomDirection();

			// Increment or decrement it
			vect[newDir.first] = vect[newDir.first] + newDir.second;
		}

		if (i%5 == 4) {
			// Display the progress of the entire set at 5 and 10 steps
			std::cout << "\nAt step " << i+1 << ":\n";
			display(particles);
		}

	}
}

void moveParticle(vector<int>& particle, vector<int>& distance, int axis) {
	// Move the particle on this axis
	particle[axis] += distance[axis] > 0 ? 1 : -1;
	// Update the remaining distance
	distance[axis] += distance[axis] > 0 ? -1 : 1;
}

void moveParticlesTowardsCentroid(vector<vector<int>>& particles, vector<vector<int>>& distances) {

	for (int i=0; i<10; ++i) {
		// Iterate through all the vectors
		#pragma omp parallel for schedule(runtime)
		for(int idx=0; idx<particles.size(); ++idx) {

			// Move one step closer on one of the axes if needed.
			if (distances[idx][X]) {
				moveParticle(particles[idx], distances[idx], X);
			}
			else if (distances[idx][Y]) {
				moveParticle(particles[idx], distances[idx], Y);
			}
			else if(distances[idx][Z]) {
				moveParticle(particles[idx], distances[idx], Z);
			}
		}
	}

}

void getDistancesToCentroid(vector<vector<int>>& particles, vector<int>& centroid) {
	// Iterate through all the particles
	#pragma omp parallel for schedule(runtime)
	for(auto &part: particles) {
		for(int coord=0; coord<3; ++coord)
			part[coord] = centroid[coord] - part[coord];
	}
}

auto main() -> int {

	vector<vector<int>> particles = {
		{    5,   14,   10 },
		{    7,   -8,  -14 },
		{   -2,    9,    8 },
		{   15,   -6,    3 },
		{   12,    4,   -5 },
		{    4,   20,   17 },
		{  -16,    5,   -1 },
		{  -11,    3,   16 },
		{    3,   10,  -19 },
		{  -16,    7,    4 }
	};

	// Display the original state of the particles
	std::cout << "\nOriginal state: \n";
	display(particles);

	randomlyMoveParticles(particles);

	vector<int> centroid = getCentroid(particles);
	std::cout<<"\nLocated centre at: "
		<<centroid[X]<<' '
		<<centroid[Y]<<' '
		<<centroid[Z]<<'\n';

	// Get the original distance from each particle to the centroid.
	vector<vector<int>> distances(particles.begin(), particles.end());
	getDistancesToCentroid(distances, centroid);

	std::cout<<"\nInitial distances from centroid:\n";
	display(distances);

	moveParticlesTowardsCentroid(particles, distances);


	std::cout<<"\nFinal distances from centroid:\n";
	display(distances);

	return 0;
};
