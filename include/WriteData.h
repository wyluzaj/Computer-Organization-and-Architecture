//
// Created by l6808 on 23.04.2025.
//

#ifndef OIAKP_WRITEDATA_H
#define OIAKP_WRITEDATA_H


#include <cstdint>
#include "Timer.h"

class WriteData {
public:
    // Dodano tablice csaOk oznaczajaca poprawnosc CSA
    void save(const char* filename,
              const uint32_t* A,
              const uint32_t* B,
              const uint32_t* csaR,
              const bool* csaOk,
              const uint32_t* etaR,
              const double* OE,
              const double* ACC,
              const Timer& tCSA,
              const Timer& tETA,
              int N);
};


#endif //OIAKP_WRITEDATA_H
