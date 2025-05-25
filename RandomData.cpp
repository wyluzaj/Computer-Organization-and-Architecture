#include "include/RandomData.h"
#include <cstdlib>
#include <ctime>

void RandomData::generate(uint32_t* A, uint32_t* B, int N) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for(int i = 0; i < N; ++i) {
        uint32_t hi = (std::rand() & 0xFFFF) << 16;
        uint32_t lo =  std::rand() & 0xFFFF;
        A[i] = hi ^ lo;
        hi = (std::rand() & 0xFFFF) << 16;
        lo =  std::rand() & 0xFFFF;
        B[i] = hi ^ lo;
    }
}


