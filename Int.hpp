#ifndef _BIGINT
#define _BIGINT

#include <iostream>
#include <gmp.h>
#include <string>
#include <cstdlib>

// Arbitrary precision integer
class Int {
public:
    Int() {
        mpz_init(rop);
    }
    ~Int() {
        mpz_clear(rop);
    }
    Int(unsigned long n) {
        mpz_init_set_ui(rop, n);
    }
    Int(const Int& other) {
        mpz_init_set(rop, other.rop);
    }
    const mpz_t& x() const {
        return rop;
    }
    mpz_t& x() {
        return rop;
    }
    // Overriding assignment operators
    void operator=(unsigned long n) {
        mpz_set_ui(rop, n);
    }
    void operator=(const Int& other) {
        mpz_set(rop, other.rop);
    }
    void set(const std::string str, int base=10) {
        int err = mpz_set_str(rop, str.c_str(), base);
        if (err) {
            throw "Error setting int from string.";
        }
    }
    void get(unsigned long& ul) const {
        ul = mpz_get_ui(rop);
    }
    void get(std::string& s) const {
        char* out = mpz_get_str(NULL, 10, rop);
        s = std::string(out);
        free(out);
    }
    // Comparison operators
    bool operator>(unsigned x) const {
        return (mpz_cmp_ui(rop, x) > 0);
    }
    bool operator<(unsigned x) const {
        return (mpz_cmp_ui(rop, x) < 0);
    }
    bool operator==(unsigned x) const {
        return (mpz_cmp_ui(rop, x) == 0);
    }
    bool operator<=(unsigned x) const {
        return (mpz_cmp_ui(rop, x) <= 0);
    }

    bool operator>(const Int& x) const {
        return (mpz_cmp(rop, x.rop) > 0);
    }
    bool operator<(const Int& x) const {
        return (mpz_cmp(rop, x.rop) < 0);
    }
    bool operator==(const Int& x) const {
        return (mpz_cmp(rop, x.rop) == 0);
    }
    bool operator<=(const Int& x) const {
        return (mpz_cmp(rop, x.rop) <= 0);
    }
    // Negates the number z
    static void neg(Int& z) {
        mpz_neg(z.rop, z.rop);
    }
    // Sets diff = a - b
    static void sub(Int& diff, const Int& a, const Int& b) {
        mpz_sub(diff.rop, a.rop, b.rop);
    }
    static void sub(Int& diff, const Int& a, long b) {
        if (b > 0) {
            mpz_sub_ui(diff.rop, a.rop, b);
        } else {
            // Subtract a negative number
            mpz_add_ui(diff.rop, a.rop, std::abs(b));
        }
    }
    // Sets out = out - a*b
    static void submul(Int& out, const Int& a, unsigned long b) {
        mpz_submul_ui(out.rop, a.rop, b);
    }
    // Sets prod = a*b
    static void mul(Int& prod, const Int& a, const Int& b) {
        mpz_mul(prod.rop, a.rop, b.rop);
    }
    static void mul(Int& prod, const Int& a, unsigned long b) {
        mpz_mul_ui(prod.rop, a.rop, b);
    }

    // Multiplicative identity
    static Int mul_identity() {
        return 1;
    }
    // Right shift
    void right_shift(size_t num_bits = 1) {
        mpz_tdiv_q_2exp(rop, rop, num_bits);
    }
    // Whether number is even. Note: also applies to
    // two's complement numbers.
    bool is_even() const {
        return (mpz_tstbit(rop, 0) == 0);
    }
    // Increments number by delta
    void incf(size_t delta=1) {
        mpz_add_ui(rop, rop, delta);
    }
    // Decrements number by delta
    void decf(size_t delta=1) {
        mpz_sub_ui(rop, rop, delta);
    }

    bool divisible(const Int& d) const {
        return mpz_divisible_p(rop, d.rop);
    }
    bool is_perfect_square() const {
        return mpz_perfect_square_p(rop);
    }
    bool is_probable_prime() const {
        return mpz_probab_prime_p(rop, 15);
    }
    // Sets number to be the next prime number
    void next_prime() {
        mpz_nextprime(rop, rop);
    }

    static void gcd(Int& out, const Int& a, const Int& b) {
        mpz_gcd(out.rop, a.rop, b.rop);
    }
    static void pow(Int& out, unsigned long a, unsigned long b) {
        mpz_ui_pow_ui(out.rop, a, b);
    }
    // Calculates and returns the Jacobi symbol (a|p)
    static int jacobi(const Int& a, const Int& b) {
        return mpz_jacobi(a.rop, b.rop);
    }
    static void sqrt(Int& sq, const Int& n) {
        mpz_sqrt(sq.rop, n.rop);
    }
    

    friend std::ostream& operator<<(std::ostream& os, const Int& z);
private:
    // GMP integer pointer wrapped by this class
    mpz_t rop;
};

// Output operator
std::ostream& operator<<(std::ostream& os, const Int& z) {
    std::string s;
    z.get(s);
    os << s;
    return os;
}

#endif