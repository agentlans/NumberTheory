#ifndef _TRIALDIVISION
#define _TRIALDIVISION

#include <vector>
#include "Int.hpp"

class TrialDivision {
public:
    // Generate list of primes <= prime_limit
    TrialDivision(unsigned long prime_limit) {
        Int p = 2;
        unsigned long pui;
        while (p <= prime_limit) {
            p.get(pui);
            primes.push_back(pui);
            p.next_prime();
        }
        // Save the largest p^2
        Int::mul(p2, primes.back(), primes.back());
    }
    // Tests whether n might be prime by dividing
    // n against smaller primes
    bool test(const Int& n) {
        if (n < 2) return false;
        // See whether n > p^2
        bool small_n = false;
        if (n <= p2) {
            Int::sqrt(sq, n);
            small_n = true;
        }
        for (const auto& p : primes) {
            if (small_n && sq < p) {
                break;
            }
            if (n.divisible(p)) {
                return false;
            }
        }
        return true;
    }
private:
    std::vector<unsigned long> primes;
    Int p2;
    Int sq;
};

#endif