#ifndef _PRIMEPROVER
#define _PRIMEPROVER

#include <flint/fmpz.h>
#include "Int.hpp"

class PrimeProver {
public:
    // Returns true iff n is a prime number
    bool test(const Int& n) {
        num = PTR_TO_COEFF(n.x());
        return fmpz_is_prime(&num);
    }
private:
    fmpz num;
};

#endif