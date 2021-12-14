#ifndef _LUCASPROBABLEPRIME
#define _LUCASPROBABLEPRIME

#include <iostream>

#include "Random.hpp"
#include "LucasSequence.hpp"

template <int fixed_q=0>
class PQFinder {
public:
    void set(const Int* n) {
        this->n = n;
    }
    // Finds P, Q for a given value of N.
    // Returns false if N isn't prime.
    bool find_pq() {
        bool redo = false;
        int trials = 0;
        do {
            rand.sample_not_0(p, *n);
            // If we have fixed q then use it
            if (fixed_q != 0) {
                q = (signed long) fixed_q;
            } else {
                // Find a random q
                do {
                    rand.sample_not_0(q, *n);
                } while (q.divisible(*n));
            }
            // Find d = p^2 - 4q
            Int::mul(d, p, p);
            Int::submul(d, q, 4);
            if (d == 0) {
                redo = true;
                continue;
            }

            j = Int::jacobi(d, *n);
            // If j = 0 then d and n have a common factor
            if (j == 0) {
                Int::gcd(gcd, d, *n);
                if (!(gcd == 1 || gcd == *n)) {
                    return false;
                }
                redo = true;
            } else if (j == 1) {
                // If j = 1 for many p, then n may be a square
                if (trials == 3 && n->is_perfect_square()) {
                    return false;
                }
                redo = true;
            } else { // j = -1, exactly what we wanted
                redo = false;
            }
            trials++;
        } while (redo);
        // delta_n = n - j which in this case j = -1
        Int::add(delta_n, *n, 1);
        return true;
    }
    Int& get_p() {
        return p;
    }
    Int& get_q() {
        return q;
    }
    Int& get_delta_n() {
        return delta_n;
    }
private:
    Int p, q, delta_n;
    const Int* n;
    Int d, gcd;
    int j;
    Random rand;
};

bool is_odd_positive(const Int& n) {
    if (n < 2) {
        return false;
    } else if (n.is_even()) {
        return false;
    } else {
        return true;
    }
}

class LucasProbableTester {
public:
    bool test(const Int& n) {
        if (n == 2 || n == 3) return true;
        if (!is_odd_positive(n)) {
            return false;
        }
        // Find P, Q for this N.
        pqf.set(&n);
        if (!pqf.find_pq()) {
            return false;
        }
        // Set up Lucas sequence
        ls.set(pqf.get_p(), pqf.get_q(), n);
        ls.calculate_nth_term(pqf.get_delta_n());
        // Look at the U term of the sequence
        return (ls.get_u() == 0);
    }
private:
    PQFinder<0> pqf;
    LucasSequence ls;
};

class LucasStrongProbableTester {
public:
    bool test(const Int& n) {
        if (n == 2 || n == 3) return true;
        if (!is_odd_positive(n)) {
            return false;
        }
        // Find P, Q for this N.
        pqf.set(&n);
        if (!pqf.find_pq()) {
            return false;
        }
        Int::factor_2(s, d, pqf.get_delta_n());
        // Set up Lucas sequence
        ls.set(pqf.get_p(), pqf.get_q(), n);
        ls.calculate_nth_term(d);
        // Check U_d = 0
        if (ls.get_u() == 0) {
            return true;
        }
        // Check V_(d*2^i) = 0
        for (size_t i = 0; i < s; ++i) {
            if (ls.get_v() == 0) {
                return true;
            }
            ls.double_n();
        }
        return false;
    }
private:
    PQFinder<-1> pqf;
    LucasSequence ls;
    size_t s;
    Int d;
};

class LucasExtraStrongProbableTester {
public:
    bool test(const Int& n) {
        if (n == 2 || n == 3) return true;
        if (!is_odd_positive(n)) {
            return false;
        }
        // Find P, Q for this N.
        pqf.set(&n);
        if (!pqf.find_pq()) {
            return false;
        }
        Int::factor_2(s, d, pqf.get_delta_n());
        // Set up Lucas sequence
        ls.set(pqf.get_p(), pqf.get_q(), n);
        ls.calculate_nth_term(d);
        // Check U_d = 0
        if (ls.get_u() == 0) {
            // and V_d = +2 or -2
            Int::sub(n2, n, 2);
            if (ls.get_v() == 2 || ls.get_v() == n2) {
                return true;
            }
        }
        // Check V_(d*2^i) = 0
        for (size_t i = 0; i < s-1; ++i) {
            if (ls.get_v() == 0) {
                return true;
            }
            ls.double_n();
        }
        return false;
    }
private:
    PQFinder<1> pqf;
    LucasSequence ls;
    size_t s;
    Int d;
    Int n2;
};

#endif