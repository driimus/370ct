#include "part_one.hpp"

void checkFileAccess(std::ifstream &file) {
	// Terminate the process if file cannot be opened
	if (!file) {
		std::cerr << "ERR: Could not access file.\n";
		exit(EXIT_FAILURE);
	}
}

auto getFileContents(std::string filename) -> std::vector<std::string> {
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
