#include "LCG.h"


char LCG::next() {
    seed = (a * seed + c) % m;
    return static_cast<char>(seed % 128);
}

LCG::LCG(const unsigned int seed, const unsigned int a, const unsigned int c,
         const unsigned int m)
    : seed(seed), a(a), c(c), m(m) {
}
