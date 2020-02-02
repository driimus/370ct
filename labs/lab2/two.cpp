#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <mutex>

std::mutex mtx;

void loadPoemFromFile(std::vector<std::string> &verses, std::string filename) {
	std::ifstream poem;
	poem.open(filename);

	std::string verse;
	while(std::getline(poem, verse)) {
		verses.push_back(verse);
	}

	poem.close();
}

int incrementLine(int &line, int size) {
	while(true) {
		sleep(1);
		if (mtx.try_lock()) {
			line = (line + 1 == size) ? 0 : line + 1;
			mtx.unlock();
		}
	}
}

void printLine(int &pos, std::vector<std::string> &poem) {
	int last = -1;
	while(true) {
		if (mtx.try_lock() && last != pos) {
			std::cout << pos << ' ' << poem[pos] << std::endl;
			last = pos;
			mtx.unlock();
		}
		sleep(1);
	}
}
void handleInput() {
	char choice;
	while(std::cin >> choice) {
		switch(choice) {
			case 'r':
				std::cout<<"Resuming..."<<std::endl;
				mtx.unlock();
				break;
			case 'p':
				std::cout<<"Pausing..."<<std::endl;
				mtx.lock();
				break;
			case 'x':
				std::cout<<"Exiting..."<<std::endl;
				exit(0);
				break;
		}
	}
}

void printPoem(std::vector<std::string> &poem) {
	int pos = 0;
	std::thread incrementer(incrementLine, std::ref(pos), poem.size());
	std::thread printer(printLine, std::ref(pos), std::ref(poem));
	std::thread menu(handleInput);
	menu.join();
	incrementer.join();
	printer.join();
}

int main() {
	std::vector<std::string> verses;
	loadPoemFromFile(verses, "caged_bird.txt");
	printPoem(verses);
	return 0;
}
