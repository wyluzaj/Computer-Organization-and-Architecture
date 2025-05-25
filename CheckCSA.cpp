#include "include/CheckCSA.h"
#include <cstdint>

void CheckCSA::verify(const uint32_t* A,
                      const uint32_t* B,
                      const uint32_t* csaR,
                      bool* ok,
                      int N) {
    for(int i = 0; i < N; ++i) {
        uint32_t expect = A[i] + B[i];  // modulo 2^32
        ok[i] = (csaR[i] == expect);
    }
}

