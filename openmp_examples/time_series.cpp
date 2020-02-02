#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;
int main (void)
{
    int updateAVectorsElements = 0;
    vector<int> firstArray = {1, 2, 3, 4, 5};
    vector<int> secondArray = {6, 7, 8, 9, 10};


    for (int i = 0; i < size; i++) {
         //a element for each thread in core.
        int newElementTotal[4] = {0, 0, 0, 0};
        int thisLoopsTotal = 0;
        #pragma omp parallel
        {

            int threadNum = omp_get_thread_num();
            int nestedVectorSize = static_cast<int>(vectorOfVectors[threadNum].size());

            for (int indexInNestedVertex = 0; indexInNestedVertex < nestedVectorSize; indexInNestedVertex++) {
                //peforms update of vectors contents, so within this parallel region, the threads update
                //their own position.
                vectorOfVectors[threadNum][indexInNestedVertex] += updateAVectorsElements;
                //calculates total of each thread's vector's content. Assigns this to the threads element
                //within the newElementTotal array.
                newElementTotal[threadNum] += vectorOfVectors[threadNum][indexInNestedVertex];
            }
        }

        //calculates total of all of the totals of each vector.
        for (int elementTotalIndex = 0; elementTotalIndex < size; elementTotalIndex++) {
           thisLoopsTotal += newElementTotal[elementTotalIndex];
       }

        //update vectors with a new element, informing them of the results
        //of the vectors which were just updated. Allowing each vector to 
        //understand where the other threads are.
       for (int index = 0; index < size; index++) {
           vectorOfVectors[index].push_back(thisLoopsTotal);
       }


    return 0;
}
