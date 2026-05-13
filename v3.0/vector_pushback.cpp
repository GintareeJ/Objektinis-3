#include <chrono>
#include <iostream>
#include <vector>
#include "vector.h"

double measurePushBackTime(size_t numElements, int& capacityChange) {
    Vector<int> vec;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numElements; ++i) {
            if (vec.size() == vec.capacity()) capacityChange++;
        vec.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

double measureStdVectorPushBackTime(size_t numElements, int& capacityChange) {
    std::vector<int> vec;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numElements; ++i) {
        if (vec.size() == vec.capacity()) capacityChange++;
        vec.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main()
{
    int notstdcapacitychange = 0;
    int stdcapacitychange = 0;
    int numElements[] = {        
        10000,
        100000,
        1000000,
        10000000,
        100000000
    };
    const int numTests = 3;
    for(int numEl : numElements) {
        double totalTimeCustom = 0;
        double totalTimeStd = 0;
        for(int i = 0; i < numTests; ++i) {
            totalTimeCustom += measurePushBackTime(numEl, notstdcapacitychange);
            totalTimeStd += measureStdVectorPushBackTime(numEl, stdcapacitychange);
        }
        std::cout<< "Elements: " << numEl << "\n";
        std::cout << "Vector " << (totalTimeCustom / numTests) << " seconds"<<" and changes "<<notstdcapacitychange<<"\n";
        std::cout << "Std vector " << (totalTimeStd / numTests) << " seconds"<<" and changes "<<stdcapacitychange<<"\n";
    }

}