#pragma once

#include <atomic>
#include <chrono>
#include <thread>
#include <deque>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>

// Shared buffer for transferring data from producers to consumers.
class Buffer {
	std::deque<char> buffer;
	// One character at a time
	const int size = 1;
	std::atomic<bool> full = false;

	std::mutex mtx;
	std::condition_variable condVar;

public:
	Buffer();
	void write(char c);
	char read();
};

// Producer transfers one character at a time to the consumer.
class Producer {
	Buffer &sharedBuff;
public:
	Producer(Buffer &buff);
	void send(std::string filename);
};

// Consumer displays each line as it is built up, character by character.
//
// Adds each completed line to the poem and displays the updated contents.
class Consumer {
	std::vector<std::string> poem;
	std::string verse;
	Buffer &sharedBuff;

public:
	Consumer(Buffer &buff);
	void receive();
	// Displays the poem in its current state.
	void print_poem();
	// Mentions that the whole poem is loaded and displays it.
	void done();
};
