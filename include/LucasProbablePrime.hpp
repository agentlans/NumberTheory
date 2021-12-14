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
    const Int& get_p() const {
        return p;
    }
    const Int& get_q() const {
        return q;
    }
    const Int& get_delta_n() const {
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

// See Robert Baillie (https://cs.stackexchange.com/users/74793/robert-baillie), 
// More details about the Baillie–PSW test, URL (version: 2017-07-11): https://cs.stackexchange.com/q/77811
class BonusCheck {
public:
    template <class PQFinder>
    void set(const PQFinder& pqf, const Int& n) {
        // two_q = 2*Q (mod n)
        Int::mul(two_q, pqf.get_q(), 2);
        Int::mod(two_q, two_q, n);
    }
    bool check(const LucasSequence& ls) {
        return (ls.get_v() == two_q);
    }
private:
    Int two_q;
};

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
        if (ls.get_u() == 0) {
            // Perform the bonus check
            bc.set(pqf, n);
            if (bc.check(ls)) {
                return true;
            }
        }
        return false;
    }
private:
    PQFinder<0> pqf;
    LucasSequence ls;
    BonusCheck bc;
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
        bool temp = false;
        if (ls.get_u() == 0) {
            temp = true;
        }
        // Check V_(d*2^i) = 0
        for (size_t i = 0; i < s; ++i) {
            if (!temp && ls.get_v() == 0) {
                temp = true;
            }
            ls.double_n();
        }
        if (!temp) return false;
        // Check V_(d*2^s) = V_(n+1)
        bc.set(pqf, n);
        return (bc.check(ls));
    }
private:
    PQFinder<-1> pqf;
    LucasSequence ls;
    size_t s;
    Int d;
    BonusCheck bc;
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
        bool temp = false;
        // Check U_d = 0
        if (ls.get_u() == 0) {
            // and V_d = +2 or -2
            Int::sub(n2, n, 2);
            if (!temp) {
                if (ls.get_v() == 2 || ls.get_v() == n2) {
                    temp = true;
                }
            }
        }
        // Check V_(d*2^i) = 0
        for (size_t i = 0; i < s-1; ++i) {
            if (!temp && ls.get_v() == 0) {
                temp = true;
            }
            ls.double_n();
        }
        if (!temp) return false;
        ls.double_n();
        bc.set(pqf, n);
        return (bc.check(ls));
    }
private:
    PQFinder<1> pqf;
    LucasSequence ls;
    size_t s;
    Int d;
    Int n2;
    BonusCheck bc;
};

#endif