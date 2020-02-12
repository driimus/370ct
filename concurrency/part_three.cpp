#include "part_one.hpp"
#include "part_three.hpp"

void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Buffer::Buffer() {}

void Buffer::write(char c) {
	std::unique_lock<std::mutex> lck(mtx);
	// Wait until buffer is cleared
	while (full) condVar.wait(lck);

	lck.unlock();
	buffer.push_back(c);

	full = true;
	condVar.notify_all();
}

auto Buffer::read() -> char {
	std::unique_lock<std::mutex> lck(mtx);
	// Wait until buffer is full
	while (!full) condVar.wait(lck);

	lck.unlock();
	char c = buffer.front();
	buffer.pop_front();

	full = false;
	condVar.notify_all();
	return c;
}


Producer::Producer(Buffer &buff) : sharedBuff(buff) {};

void Producer::send(std::string filename) {
	std::ifstream file(filename);
	checkFileAccess(file);

	// Read and send file char by char
	char c;
	while(file.get(c)) {
		sharedBuff.write(c);
	}
	// Signal that we're done
	sharedBuff.write(EOF);
	file.close();
}


Consumer::Consumer(Buffer &buff) : sharedBuff(buff) {};

void Consumer::receive() {
	for(;;) {
		char c = sharedBuff.read();
		verse += c;

		// Exit upon completion
		if (c == std::char_traits<char>::eof()) {
			done(); return;
		}

		// Print each char with a delay
		sleep(20);
		std::cout << c;
		fflush(stdout);

		// Display updated poem after each line
		if (c == '\n') {
			poem.push_back(verse);
			verse.clear();
			print_poem();
		}
	}
};

void Consumer::print_poem() {
	std::cout << '\n';
	for(auto& line:poem) std::cout << line;
	std::cout << '\n';
}

void Consumer::done() {
	std::cout << "\nDone receiving... Here's the poem:\n";
	print_poem();
}
