#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void checkFileAccess(std::ifstream &file) {
	if (!file) {
		std::cerr << "ERR: Could not access file.\n";
		exit(EXIT_FAILURE);
	}
}

std::vector<std::string> getFileContents(std::string filename) {
	std::vector<std::string> contents;

	std::ifstream file(filename);
	checkFileAccess(file);
	// Read and store every line from the file
	std::string line;
	while(std::getline(file, line)) {
		contents.push_back(line);
	}
	file.close();

	return contents;
}

int main() {
	std::vector<std::string> toTheRain;

	toTheRain = getFileContents("to_the_rain.txt");

	return 0;
}
