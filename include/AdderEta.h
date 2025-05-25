
#ifndef OIAKP_ADDERETA_H
#define OIAKP_ADDERETA_H


#include <cstdint>
#include "CarrySkipAdder.h"

class AdderEta {
public:
    CarrySkipAdder csa;
    int       INAC;
    uint32_t  LO_MASK;
    //INAC - liczba bitów niedokładnej części
    AdderEta(int inac) : INAC(inac), LO_MASK((1u<<INAC)-1) {}
    uint32_t add(uint32_t a, uint32_t b);
};
#endif //OIAKP_ADDERETA_H
