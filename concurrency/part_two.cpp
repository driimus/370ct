#include "part_two.hpp"

std::mutex mtx;
std::condition_variable condVar;
std::atomic<bool> printed = false;

void sleep(int sec) {
	std::this_thread::sleep_for(std::chrono::seconds(sec));
}

void pass_control() {
	printed = !printed;
	condVar.notify_all();
}

void increment_line(int &line, int size) {
	std::unique_lock<std::mutex> lck(mtx);

	// Wait for the current line to be printed
	while (!printed) { condVar.wait(lck); }

	lck.unlock();
	++line;
	pass_control();
	if (line < size) increment_line(line, size);
}

void print_line(int &line, std::vector<std::string> &poem) {
	std::unique_lock<std::mutex> lck(mtx);

	// Wait for the next line
	while (printed) { condVar.wait(lck); }

	lck.unlock();
	std::cout << poem[line] << '\n';

	// Delay printing by one second
	sleep(1);
	pass_control();
	if (line < poem.size()) print_line(line, poem);
}

void print_poem(std::vector<std::string> &poem) {
	int line = 0;
	std::thread incrementer(increment_line, std::ref(line), poem.size());
	std::thread printer(print_line, std::ref(line), std::ref(poem));
	incrementer.join();
	printer.join();
}
