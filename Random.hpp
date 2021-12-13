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
private:
    gmp_randstate_t state;
};

#endif