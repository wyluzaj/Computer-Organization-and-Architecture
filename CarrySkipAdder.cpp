#include "include/CarrySkipAdder.h"    // laczymy z naglowkiem klasy

uint32_t CarrySkipAdder::add(uint32_t a, uint32_t b) {  // definicja metody add
    const int BLOCK_SIZE = 4;     // okreslamy rozmiar bloku do skip-owania
    uint32_t result = 0;          // zmienna na wynik sumowania
    uint32_t carry = 0;           // zmienna na przeniesienie (inicjalnie 0)

    for(int block = 0; block < 32; block += BLOCK_SIZE) {  // petla po blokach 4-bitowych
        bool p_block = true;      // flaga czy blok propaguje przeniesienie bez zmian

        for(int i = block; i < block + BLOCK_SIZE; ++i) {  // petla sprawdzajaca bity w bloku
            uint32_t ai = (a >> i) & 1;  // wyciagamy i-ty bit z a
            uint32_t bi = (b >> i) & 1;  // wyciagamy i-ty bit z b
            if((ai ^ bi) == 0) {         // jesli XOR bitow ==0 => nie propaguje
                p_block = false;         // blok nie jest w pelni propagujacy
                break;                   // wychodzimy wczesniej z petli
            }
        }

        if(p_block) {                // jesli blok w pelni propaguje
            for(int i = block; i < block + BLOCK_SIZE; ++i) {  // petla po bitach bloku
                uint32_t ai = (a >> i) & 1;  // odczyt bitu a
                uint32_t bi = (b >> i) & 1;  // odczyt bitu b
                uint32_t s = ai ^ bi ^ carry; // obliczamy sume bit-owa z przeniesieniem
                result |= (s << i);        // wstawiamy bit sumy do wyniku
                // carry sie nie zmienia w bloku propagujacym
            }
        } else {                     // jesli blok NIE propaguje w calosci
            for(int i = block; i < block + BLOCK_SIZE; ++i) {  // ripple-carry
                uint32_t ai = (a >> i) & 1;  // odczyt bitu a
                uint32_t bi = (b >> i) & 1;  // odczyt bitu b
                uint32_t s = ai ^ bi ^ carry; // suma bitowa
                result |= (s << i);        // zapisz bit do wyniku
                // aktualizacja przeniesienia wedlug wzoru logicznego
                carry = (ai & bi) | (ai & carry) | (bi & carry);
            }
        }
    }

    return result;    // zwracamy pelny wynik 32-bitowy
}


