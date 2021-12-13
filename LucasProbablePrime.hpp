#ifndef _LUCASPROBABLEPRIME
#define _LUCASPROBABLEPRIME

#include "Random.hpp"
#include "LucasSequence.hpp"

class LucasProbablePrimeTester {
public:
    bool test(const Int& n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n.is_even()) return false;

        // Pick P and Q randomly
        int pq_trials = 0;
        do {
            rand.sample_not_0(p, n);
            do {
                rand.sample_not_0(q, n);
            } while (q.divisible(n));

            Int::mul(d, p, p);
            Int::submul(d, q, 4); // d = p^2 - 4q
            j = Int::jacobi(d, n);

            if (j == 0) return false;
            pq_trials++;

            // If so many trials...
            if (pq_trials == 3) {
                // Check if n is a perfect square
                if (n.is_perfect_square()) {
                    return false;
                }
            }
        } while (j == 1);

        Int::sub(delta_n, n, j);
        // Set up Lucas sequence
        ls.set(p, q, n);
        ls.calculate_nth_term(delta_n);
        // Look at the U term of the sequence
        ls.get_u(u);
        return (u == 0);
    }
private:
    Int p, q, d, delta_n, u;
    int j;
    LucasSequence ls;
    Random rand;
};

#endif