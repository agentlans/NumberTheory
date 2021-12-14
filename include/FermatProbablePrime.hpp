#ifndef _FERMATPROB
#define _FERMATPROB

#include "Int.hpp"
#include "Random.hpp"

class FermatProbableTester {
public:
    // Returns true if n is a probable prime using Fermat's little theorem
    bool test(const Int& n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        // Pick a base a such that a > 1 and p doesn't divide a
        do {
            rand.sample(base, n);
        } while (base <= 1 || base.divisible(n));
        Int::sub(n1, n, 1); // n-1
        Int::pow_mod(result, base, n1, n); // base^(n-1) (mod n)
        return (result == 1);
    }
private:
    Int base;
    Int n1, result;
    Random rand;
};

class MillerRabinProbableTester {
public:
    // Returns true if n is a probable prime using
    // the Miller-Rabin test with a random base.
    bool test(const Int& n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n.is_even()) return false;
        // n > 2 is odd
        Int::sub(n1, n, 1); // n-1 = 2^s * d
        Int::factor_2(s, d, n1);
        // Pick 0 < a < n
        rand.sample_not_0(a, n);
        Int::pow_mod(result, a, d, n);
        if (result == 1) {
            return true;
        }
        for (size_t i = 0; i < s; ++i) {
            if (result == n1) { // result = -1 (mod n)
                return true;
            }
            // Square result (mod n)
            Int::mul(result, result, result);
            Int::mod(result, result, n);
        }
        return false;
    }
private:
    Random rand;
    Int n1;
    Int a;
    Int result;
    Int d;
    size_t s;
};

class MRSSProbableTester {
public:
    // Returns true if n is a probable prime using
    // the Miller-Rabin test with a random base and
    // the Solovay-Strassen test
    bool test(const Int& n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n.is_even()) return false;
        // n > 2 is odd
        Int::sub(n1, n, 1); // n-1 = 2^s * d
        Int::factor_2(s, d, n1);
        // Pick 2 <= a < n
        do {
            rand.sample(a, n);
        } while (a < 2);

        int j = Int::jacobi(a, n);
        if (j == 0) {
            // j has a common factor with n
            return false;
        }
        bool temp = false;
        Int::pow_mod(result, a, d, n);
        if (result == 1) {
            temp = true;
        }
        for (size_t i = 0; i < s; ++i) {
            if (!temp && result == n1) { // result = -1 (mod n)
                temp = true;
            }
            if (i == s-1) {
                //Int::pow_mod(ss, a, i, n);
                if (j == 1) {
                    ss = j;
                } else {
                    Int::sub(ss, n, 1);
                }
                if (!(result == ss)) {
                    return false;
                }
            }
            // Square result (mod n)
            Int::mul(result, result, result);
            Int::mod(result, result, n);
        }
        return temp;
    }
private:
    Random rand;
    Int n1;
    Int a;
    Int result;
    Int d;
    size_t s;
    Int ss;
};

#endif