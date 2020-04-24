#include "part_one.hpp"
#include "part_two.hpp"
#include "part_three.hpp"

void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Buffer::Buffer() {}

void Buffer::write(char c) {
	std::unique_lock<std::mutex> lck(mtx);
	// Wait until buffer is cleared
	while (full) condVar.wait(lck);

	// Update buffer
	lck.unlock();
	buffer = c;

	// Unblock reading thread by updating the buffer's state
	lck.lock();
	full = true;
	lck.unlock();
	condVar.notify_all();
}

char Buffer::read() {
	// Wait until buffer is updated with a new character
	std::unique_lock<std::mutex> lck(mtx);
	while (!full) condVar.wait(lck);

	// Get character from the buffer
	lck.unlock();
	char c = buffer;

	// Unblock writing thread by updating the buffer's state
	lck.lock();
	full = false;
	lck.unlock();
	condVar.notify_all();

	return c;
}


Producer::Producer(Buffer &buff) : sharedBuff(buff) {};

void Producer::send(std::string filename) {
	std::ifstream file(filename);
	checkFileAccess(file);

	// Read and send file char by char
	char c;
	while (file.get(c)) {
		sharedBuff.write(c);
	}
	// Signal that we're done
	sharedBuff.write(EOF);
	file.close();
}


Consumer::Consumer(Buffer &buff) : sharedBuff(buff) {};

void Consumer::receive() {
	for (;;) {
		char c = sharedBuff.read();
		verse += c;

		if (c == std::char_traits<char>::eof()) {
			// Notify the user when finished
			std::cout << "\nDone receiving... Here's the poem:\n";
			print_poem(poem);
			// Exit upon completion
			return;
		}

		// Print each char with a delay
		sleep(30);
		std::cout << c;
		fflush(stdout);

		// Display updated poem after each line
		if (c == '\n') {
			poem.push_back(verse);
			verse.clear();
			print_poem(poem);
		}
	}
};

auto main() -> int {
	Buffer sharedBuff;
	Producer producer { sharedBuff };
	Consumer consumer { sharedBuff };

	std::thread prod(&Producer::send, &producer, "to_the_rain.txt");
	std::thread con(&Consumer::receive, &consumer);
	prod.join();
	con.join();

	return 0;
}
