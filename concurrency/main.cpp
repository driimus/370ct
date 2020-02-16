#include "part_three.hpp"
// #include <thread>

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
