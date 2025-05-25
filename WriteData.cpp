#include "include/WriteData.h"
#include <fstream>

static void toBinary(uint32_t x, char* buf) {
    buf[32] = '\0';
    for(int i = 31; i >= 0; --i)
        buf[31 - i] = ((x >> i) & 1) ? '1' : '0';
}

void WriteData::save(const char* filename,
                     const uint32_t* A,
                     const uint32_t* B,
                     const uint32_t* csaR,
                     const bool* csaOk,
                     const uint32_t* etaR,
                     const double* OE,
                     const double* ACC,
                     const Timer& tCSA,
                     const Timer& tETA,
                     int N) {
    std::ofstream out(filename);
    out << "a,b,csa,ok_csa,eta,OE,ACC,czas_CSA_ns,czas_ETA_ns\n";
    char bufA[33], bufB[33], bufC[33], bufE[33];
    for(int i = 0; i < N; ++i) {
        toBinary(A[i], bufA);
        toBinary(B[i], bufB);
        toBinary(csaR[i], bufC);
        toBinary(etaR[i], bufE);
        out << bufA << ','
            << bufB << ','
            << bufC << ','
            << (csaOk[i] ? "TAK" : "NIE") << ','
            << bufE << ','
            << OE[i] << ','
            << ACC[i] << ','
            << tCSA.get(i) << ','
            << tETA.get(i) << '\n';
    }
}


