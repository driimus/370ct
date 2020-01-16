#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>

using namespace std;
int main (void)
{

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 10; i++) {
        for (int ii = 0; ii < 10; ii++) {
            total += somethingYoumade[i][ii];
	}
    }


    cout << // print result of calculation in collapsed region
    cout << total << endl;

    return 0;
}
