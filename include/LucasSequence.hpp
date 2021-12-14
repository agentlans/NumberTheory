#ifndef _LUCASSEQUENCE
#define _LUCASSEQUENCE

#include "Int.hpp"
#include "Matrix.hpp"

class LucasSequence {
public:
    void set(const Int& p, const Int& q, const Int& mod) {
        // Set up matrices for Lucas sequence calculation
        mat0 = {1, p, 0, 2};
        mat1 = {p, q, 1, 0};
        // Negate the q
        Int::neg(mat1.b);
        // Set the modulus
        me.set_mod(mod);
        mm.set_mod(mod);
        reset();
    }
    void reset() {
        mult = {1, 0, 0, 1};
        result = mat0;
    }
    // Computes the nth term of the Lucas sequence
    // Important: after calling this, n is permanently set!
    //     Call reset() to reset n and redo calculation.
    void calculate_nth_term(const Int& n) {
        Int n1 = n;
        n1.decf(); // n1 = n - 1
        me(mult, mat1, n1);
        // Now mult = (mat1)^(n-1)
        // Calculate the the nth term
       update_result();
    }
    // Turns n -> 2n
    void double_n() {
        // Current exponent is n-1. Double it to get n-2.
        mm(mult, mult, mult); // Square mult
        mm(mult, mult, mat1); // Multiply by matrix again to get 2n-1.
        update_result();
    }
    // Get U_n and V_n of Lucas sequence
    const Int& get_u() const {
        return result.a;
    }
    const Int& get_v() const {
        return result.b;
    }
private:
    void update_result() {
        mm(result, mult, mat0);
    }
    Matrix mat0;
    Matrix mat1;
    Matrix mult;
    Matrix result;
    MatrixExpt me;
    MatrixMul mm;
};

#endif