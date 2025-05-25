//
// Created by l6808 on 24.04.2025.
//

#ifndef OIAKP_CHECKCSA_H
#define OIAKP_CHECKCSA_H


#include <cstdint>

class CheckCSA {
public:
    // Sprawdza dla kazdego i czy csaR[i] == A[i] + B[i]
    // Wypelnia tablice ok[i] (true jesli zgodne)
    static void verify(const uint32_t* A,
                const uint32_t* B,
                const uint32_t* csaR,
                bool* ok,
                int N);
};


#endif //OIAKP_CHECKCSA_H
