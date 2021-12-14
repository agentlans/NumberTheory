#ifndef _2X2MATRIX
#define _2X2MATRIX

#include "Int.hpp"
#include "Exponent.hpp"

// Routines to deal with 2 x 2 matrices (modulo a number).
// The relevant classes are Matrix, MatrixMul, and MatrixExpt.

/* a b 
   c d */
struct Matrix {
    Int a = 1;
    Int b = 0;
    Int c = 0;
    Int d = 1;
    static Matrix mul_identity() {
        return Matrix();
    }
};

// out = a*b + c*d
void mul_matrix_entry(Int& out, 
    const Int& a, const Int& b, const Int& c, const Int& d,
    const Int& mod) {
    Int::mul(out, a, b);
    Int::addmul(out, c, d);
    Int::mod(out, out, mod);
}

// out = m1 * m2 (mod m) where m1, m2 are matrices
// out shouldn't overlap with m1 and m2 !
void mul_matrix(Matrix& out, const Matrix& m1, const Matrix& m2, const Int& mod) {
    mul_matrix_entry(out.a, m1.a, m2.a, m1.b, m2.c, mod);
    mul_matrix_entry(out.b, m1.a, m2.b, m1.b, m2.d, mod);
    mul_matrix_entry(out.c, m1.c, m2.a, m1.d, m2.c, mod);
    mul_matrix_entry(out.d, m1.c, m2.b, m1.d, m2.d, mod);
}

// Multiplies matrices modulo a given modulus
class MatrixMul {
public:
    void set_mod(const Int& mod) {
        this->mod = mod;
    }
    // Calculates m1 * m2 and saves to out. Here, out can overlap with m1 or m2.
    void operator()(Matrix& out, const Matrix& m1, const Matrix& m2) {
        mul_matrix(prod, m1, m2, mod);
        out = prod;
    }
private:
    Matrix prod;
    Int mod = 1;
};

// base^n (mod m)
class MatrixExpt {
public:
    // Set the modulus for the multiplication
    void set_mod(const Int& mod) {
        MatrixMul mm;
        mm.set_mod(mod);
        expn.set_multiplier(mm);
    }
    // Sets out = base^n with the given mod
    void operator()(Matrix& out, const Matrix& base, const Int& n) {
        expn(out, base, n);
    }
private:
    Exponentiation<Matrix,MatrixMul> expn;
};

#endif