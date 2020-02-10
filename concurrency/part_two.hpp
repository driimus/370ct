#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

void sleep(int sec);
void pass_control(std::unique_lock<std::mutex> &lck);
void increment_line(int &line, int size);
void print_line(int &line, std::vector<std::string> &poem);
void print_poem(std::vector<std::string> &poem);
