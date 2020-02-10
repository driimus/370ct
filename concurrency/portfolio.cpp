#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "part_one.hpp"
#include "part_two.hpp"

int main() {
	std::vector<std::string> toTheRain;
	toTheRain = getFileContents("to_the_rain.txt");
	print_poem(toTheRain);

	return 0;
}
