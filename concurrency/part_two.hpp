#pragma once

#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

void sleep(int sec);
// Passes control between printing thread and incrementing thread
void pass_control(std::unique_lock<std::mutex> &lck);
void increment_line(int &line, int size);
void print_line(int &line, std::vector<std::string> &poem);
// Spawns new threads that print out all elements of a given vector
void print_poem(std::vector<std::string> &poem);
