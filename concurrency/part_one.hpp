#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

// Throws an error if file cannot be opened.
void checkFileAccess(std::ifstream &file);
// Reads all the lines in a file and returns them as a vector.
auto getFileContents(std::string filename) -> std::vector<std::string>;
