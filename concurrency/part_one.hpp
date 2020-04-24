#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

// Throws an error if file cannot be opened.
void checkFileAccess(std::ifstream &file) {
	// Terminate the process if file cannot be opened
	if (!file) {
		std::cerr << "ERR: Could not access file.\n";
		exit(EXIT_FAILURE);
	}
}

// Reads all the lines in a file and returns them as a vector.
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
