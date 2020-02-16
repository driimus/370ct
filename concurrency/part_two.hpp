#pragma once

#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

void increment_line(unsigned &line, unsigned size);
void print_line(unsigned &line, std::vector<std::string> &poem);
// Spawns new threads that print out all elements of a given vector
void print_poem(std::vector<std::string> poem);
