#include "include/AdderEta.h"

uint32_t AdderEta::add(uint32_t a, uint32_t b) {
    // 1) Dokladna czesc: ripple-carry od bit20 do bit31
    uint32_t hi_sum = csa.add(a >> INAC, b >> INAC) << INAC;
    // UWAGA: NIE wyciagamy tu carry_out, bo NIE wpywamy go na dolna czesc

    // 2) Niedokladna czesc: niezaleznie, zawsze z carry_in=0
    uint32_t lo_a = a & LO_MASK;
    uint32_t lo_b = b & LO_MASK;

    // 3) Maska par 1+1
    uint32_t both = lo_a & lo_b;

    // 4) Prefix-OR do uzyskania CTL (w dol)
    uint32_t ctl = both;
    ctl |= ctl >> 1;
    ctl |= ctl >> 2;
    ctl |= ctl >> 4;
    ctl |= ctl >> 8;
    ctl |= ctl >> 16;
    // ctl[i]=1 dla bitow od pierwszej pary both w dol

    // 5) Budujemy wynik dolnej czesci:
    //    carry_in=0 => zwykly XOR to (lo_a^lo_b)
    //    gdy ctl=1 => wymuszone 1
    uint32_t lo_sum = ((lo_a ^ lo_b) & ~ctl) | ctl;

    // 6) Scal wynik
    return hi_sum | lo_sum;
}

