
#ifndef OIAKP_CARRYSKIPADDER_H
#define OIAKP_CARRYSKIPADDER_H

#include <cstdint>            // wczytujemy definicje uint32_t

class CarrySkipAdder {        // deklaracja klasy CSA
public:                       // sekcja publiczna
    uint32_t add(uint32_t a, uint32_t b);  // metoda dodajaca dwie liczby 32-bitowe
};
#endif //OIAKP_CARRYSKIPADDER_H
