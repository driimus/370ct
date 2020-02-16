#include "part_two.hpp"

std::mutex mtx;
std::condition_variable condVar;
bool printed = false;

void increment_line(unsigned &line, unsigned size) {
	while(line < size) {

		// Wait for the current line to be printed
		std::unique_lock<std::mutex> lck(mtx);
		while (!printed) { condVar.wait(lck); }

		// Increment index if there is a next line
		lck.unlock();
		++line;

		// Unblock printing thread by flagging the line as NOT PRINTED
		lck.lock();
		printed = false;
		lck.unlock();
		condVar.notify_all();
		// if (line + 1 == size) break;
	}
}

void print_line(unsigned &line, std::vector<std::string> &poem) {
	std::cout << '\n';

	while(true) {
		// Wait for the next line
		std::unique_lock<std::mutex> lck(mtx);
		while (printed) { condVar.wait(lck); }

		// Print indented line
		if (line >= poem.size()) break;
		lck.unlock();
		std::cout << '\t' << poem[line];

		// Unblock incrementing thread by flagging the line as PRINTED
		lck.lock();
		printed = true;
		lck.unlock();
		condVar.notify_all();
	}

	std::cout << '\n';
}

void print_poem(std::vector<std::string> poem) {
	unsigned line = 0;
	std::thread incrementer(increment_line, std::ref(line), poem.size());
	std::thread printer(print_line, std::ref(line), std::ref(poem));
	incrementer.join();
	printer.join();
}
