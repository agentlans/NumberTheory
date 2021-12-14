#ifndef _EXPONENT
#define _EXPONENT

#include "Int.hpp"

// Generic exponentiation by squaring.
// Multiplier must have operator() that multiplies 
//    variables of type T.
template <class T, class Multiplier>
class Exponentiation {
public:
    void set_multiplier(const Multiplier& xm) {
        m = xm;
    }
    // out = base^exponent
    void operator()(T& out, const T& base, const Int& exponent) {
        n = exponent;
        x = base;
        if (n == 0) {
            out = T::mul_identity();
            return;
        }
        y = T::mul_identity();
        while (n > 1) {
            if (n.is_even()) {
                m(x, x, x); // x = x*x
            } else {
                m(y, x, y); // y = x*y
                m(x, x, x); // x = x*x
            }
            n.right_shift();
        }
        m(out, x, y); // out = x*y
    }
private:
    Multiplier m;
    Int n;
    T y;
    T x;
};

#endif