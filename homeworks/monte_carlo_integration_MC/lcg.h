#ifndef LCG_H
#define LCG_H

#include <cstdint>

class LCG {
private:
    uint64_t seed;
    uint64_t a;
    uint64_t c;
    uint64_t m;

public:
    LCG(uint64_t seed_,
        uint64_t a_ = 1664525,
        uint64_t c_ = 1013904223,
        uint64_t m_ = (1ULL << 32));

    double operator()(); // returns uniform (0,1)
};

#endif