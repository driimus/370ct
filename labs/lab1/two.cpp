#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <vector>
#include <unistd.h>

void loadPoemFromFile(std::vector<std::string> &verses, std::string filename) {
	std::ifstream poem;
	poem.open(filename);

	std::string verse;
	while(std::getline(poem, verse)) {
		verses.push_back(verse);
	}

	poem.close();
}

int incrementLine(int &line) {
	line = line + 1;
}

void printLine(std::string &line) {
	std::cout << line << std::endl;
	sleep(1);
}

void printPoem(std::vector<std::string> &poem) {
	int pos = 0;

	while(pos < poem.size()) {
		std::thread incrementer(incrementLine, std::ref(pos));
		std::thread printer(printLine, std::ref(poem[pos]));
		incrementer.join();
		printer.join();
	}
}

int main() {
	std::vector<std::string> verses;
	loadPoemFromFile(verses, "caged_bird.txt");
	printPoem(verses);
	return 0;
}
