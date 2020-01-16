#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>

void thread1(std::string whatever)
{
  std::cout << "thread1 says: " << whatever << std::endl;
}


int main (void){

  std::thread t1(thread1,"Frappucino is just ice cream with extra steps");
 t1.join(); // This join after thread launch is important, since without it, if your main function exits with tasks still on the stack there will be unpredictable behaviour, possibly crashes.
return 0;
}
