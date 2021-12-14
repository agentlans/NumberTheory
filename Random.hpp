#ifndef _RANDOM_
#define _RANDOM_

#include <ctime>
#include "Int.hpp"

// Random number generator from GMP
class Random {
public:
    Random() {
        gmp_randinit_default(state);
        gmp_randseed_ui(state, time(NULL));
    }
    ~Random() {
        gmp_randclear(state);
    }
    // Returns uniform random integer in [0,n)
    void sample(Int& out, const Int& max_num) {
        mpz_urandomm(out.x(), state, max_num.x());
    }
    void sample_not_0(Int& out, const Int& max_num) {
        do {
            sample(out, max_num);
        } while (out == 0);
    }
    // Uniformly sample an odd number <= n bits
    void sample_odd(Int& out, size_t n_bits) {
        mpz_urandomb(out.x(), state, n_bits-1);
        mpz_mul_2exp(out.x(), out.x(), 1); // Multiply by 2
        mpz_setbit(out.x(), 0); // Plus 1
    }
private:
    gmp_randstate_t state;
};

#endif