#include "omp.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <limits>

#define DOUBLE_MAX std::numeric_limits<double>::max()

enum axes : int { X = 0, Y, Z };

using std::vector;

// Generates a random integer in the given range.
auto getRandomInt(int from, int to) -> int {
	std::uniform_int_distribution<int> range{from, to};
	std::random_device rnd;
	return range(rnd);
}

// Picks a random direction to move in by one unit, either forward or backward.
auto getRandomDirection() -> std::pair<int, int> {
	// 60% chance of decrementing the position.
	bool increment = getRandomInt(0, 9) > 5;

	return {
		getRandomInt(0, 2),	// random axis
		increment ? 1 : -1	// increment or decrement
	};
}

// Prints out space-separated coordinates of a 3D position.
void displayPosition(const vector<int> &position) {
	std::cout.width(5); std::cout << position[X] << ' ';
	std::cout.width(5); std::cout << position[Y] << ' ';
	std::cout.width(5); std::cout << position[Z] << '\n';
}

// Prints out the coordinates of every position from a given list.
void displayPositions(const vector<vector<int>>& positions) {
	for (unsigned i = 0; i < positions.size(); ++i) {
		std::cout << "Position " << i + 1 << ": ";
		displayPosition(positions[i]);
	}
}

// Moves every particle from a given list by one unit in a random direction.
void randomlyMoveParticles(vector<vector<int>> &particles) {
	// #pragma omp parallel for
	// {
		for (auto &particle : particles) {
			// Pick a random direction to move in by 1 step.
			std::pair<int, int> newDir = getRandomDirection();

			// Increment or decrement it.
			particle[newDir.first] = particle[newDir.first] + newDir.second;
		}
	// }
}

// Computes the geometric centre for all the given particles.
auto getCentroid(const vector<vector<int>>& particles) -> vector<int> {
	// Initialize centroid as Origin {X: 0, Y: 0, Z: 0}.
	vector<int> centroid(3);
	int amountOfParticles = particles.size();

	// The geometric center is the arithmetic mean of all the positions.
	for (unsigned axis = 0; axis < centroid.size(); ++axis) {
		// Calculate the sum for each axis.
		#pragma omp parallel for shared(centroid[axis], particles) reduction(+: centroid[axis])
		for (int i = 0; i < amountOfParticles; ++i) {
			centroid[axis] += particles[i][axis];
		}

		// Divide by total amount of particles to get the average.
		centroid[axis] /= amountOfParticles;
	}

	return centroid;
}

// Computes the distance between every given particle and a single position in the system.
auto getDistancesToCentroid(const vector<vector<int>>& particles, const vector<int>& centroid) -> vector<vector<int>> {
	// Initialize distances with Origin {X: 0, Y: 0, Z: 0} as centre.
	vector<vector<int>> distances(particles.begin(), particles.end());

	// Update distances for all the particles
	#pragma omp parallel for schedule(runtime)
	for (auto &distance : distances) {
		for (int axis = 0; axis < 3; ++axis)
			distance[axis] = centroid[axis] - distance[axis];
	}

	return distances;
}

// Moves a particle by one unit towards a point and updates the remaining distance.
void moveParticle(vector<int>& particle, vector<int>& distance, int axis) {
	// Move the particle on this axis
	particle[axis] += distance[axis] > 0 ? 1 : -1;
	// Update the remaining distance
	distance[axis] += distance[axis] > 0 ? -1 : 1;
}

// Moves each particle one unit closer to the centroid.
void moveParticlesTowardsCentroid(vector<vector<int>>& particles, vector<vector<int>>& distances) {
	#pragma omp parallel for schedule(runtime)
	for (unsigned idx = 0; idx < particles.size(); ++idx) {

		// Move one step closer on one of the axes if possible.
		if (distances[idx][X]) {
			moveParticle(particles[idx], distances[idx], X);
		} else if (distances[idx][Y]) {
			moveParticle(particles[idx], distances[idx], Y);
		} else if (distances[idx][Z]) {
			moveParticle(particles[idx], distances[idx], Z);
		}
	}
}

// Calculates the distance between two positions in a 3D coordinate plane.
auto getDistance(const vector<int>& p1, const vector<int>& p2) -> double {
	return sqrt(
	  pow( p1[X] - p2[X], 2 ) +
	  pow( p1[Y] - p2[Y], 2 ) +
	  pow( p1[Z] - p2[Z], 2 )
	);
}

// Displays the positions of a pair of particles.
void displayNeighbour(const vector<vector<int>>& particles, int particleIdx, int neighbourIdx) {
	std::cout << "Position " << particleIdx + 1;
	std::cout << " - closest neighbour is " << neighbourIdx + 1 << ":\n";
	displayPosition(particles[particleIdx]);
	displayPosition(particles[neighbourIdx]);
}

// Computes the closest neighbour for each individual partcle.
void findClosestNeighbours(const vector<vector<int>>& particles) {
	const int particleCount = particles.size();

	// Initialize minimum distances with an Infinite value.
	vector<double> mins(particleCount, DOUBLE_MAX);
	// Initialize closest neighbour indices with 0 as default.
	vector<int> neighbours(particleCount);

	for (int particleIdx = 0; particleIdx < particleCount; ++particleIdx) {
		// Find the closest neighbour of the current particle.
		for (int neighbourIdx = particleIdx + 1; neighbourIdx < particleCount; ++neighbourIdx) {
			double distance = getDistance(particles[particleIdx], particles[neighbourIdx]);

			// Update closest neighbour for both particles.
			if (distance < mins[particleIdx]) {
				mins[particleIdx] = distance;
				neighbours[particleIdx] = neighbourIdx;
			}
			if (distance < mins[neighbourIdx]) {
				mins[neighbourIdx] = distance;
				neighbours[neighbourIdx] = particleIdx;
			}
		}

		displayNeighbour(particles, particleIdx, neighbours[particleIdx]);
	}
}

auto main() -> int {

	// Original particle positions
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

	int step = 0;
	// Display the original state of the particles
	std::cout << "\nOriginal state: \n";
	displayPositions(particles);

	// Randomly move the particles for 10 steps.
	for (; step < 10; ++step) {
		randomlyMoveParticles(particles);

		// Display the progress of the entire set at 5 and 10 steps
		if (step % 5 == 4) {
			std::cout << "\nAt step " << step + 1 << ":\n";
			displayPositions(particles);
		}
	}

	// Work out the closest neighbour of each particle.
	std::cout << "\nClosest neighbours:\n";
	findClosestNeighbours(particles);

	// Calculate the geometric centre of all the particles.
	vector<int> centroid = getCentroid(particles);

	std::cout << "\nLocated centre at: ";
	displayPosition(centroid);

	// Get the original distance from each particle to the centroid.
	vector<vector<int>> distances = getDistancesToCentroid(particles, centroid);

	std::cout << "\nInitial distances from centroid:\n";
	displayPositions(distances);

	// Move the particles towards the centre for 10 steps.
	for (; step < 20; ++step) {
		moveParticlesTowardsCentroid(particles, distances);
	}

	std::cout << "\nFinal distances from centroid (after step 20):\n";
	displayPositions(distances);

	return 0;
};
