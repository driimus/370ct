#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>

// Shared buffer for transferring data from producers to consumers.
class Buffer {
	std::deque<char> buffer;
	const int size = 32;
	bool full;

	std::mutex mtx;
	std::condition_variable condVar;

public:
	void write(char c);
	char read();
};

// Producer transfers one character at a time to the consumer.
class Producer {
public:
	void pass_control_to_consumer();
	void send();
};

// Consumer displays each line as it is built up, character by character.
//
// Adds each completed line to the poem and displays the updated contents.
class Consumer {
	vector<std::string> poem;
	std::string verse;

public:
	void pass_control_to_producer();
	void receive();
	void update_poem();
	// Displays the poem in its current state.
	void print_poem();
	// Mentions that the whole poem is loaded and displays it.
	void done();
};
