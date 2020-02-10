#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void checkFileAccess(std::ifstream &file);
auto getFileContents(std::string filename) -> std::vector<std::string>;
