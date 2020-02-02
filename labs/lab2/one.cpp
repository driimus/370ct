#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>

void thread1(std::string whatever) {
	std::cout << "thread1 says: " << whatever << std::endl;
}

void printGivenInt(int num) {
	std::cout << "The integer is: " << num << "\n";
}

int main() {

	std::thread t2(printGivenInt, 2);
	std::thread t3(printGivenInt, 3);
	t2.join();
	t3.join();
	return 0;
}
