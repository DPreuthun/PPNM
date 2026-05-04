#include "lcg.h"

LCG::LCG(uint64_t seed_, uint64_t a_, uint64_t c_, uint64_t m_)
    : seed(seed_), a(a_), c(c_), m(m_) {}

double LCG::operator()() {
    seed = (a * seed + c) % m;
    return static_cast<double>(seed) / static_cast<double>(m);
}