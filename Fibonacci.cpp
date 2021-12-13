#include <iostream>

#include "Matrix.hpp"

int main() {
    Matrix mfib = {1, 1, 1, 0};
    Matrix out;

    MatrixExpt me;
    me.set_mod(100000);
    me(out, mfib, 1000000);
    std::cout << "The 1000000th Fibonacci number (mod 100000) is " << out.b << std::endl;
    return 0;
}
