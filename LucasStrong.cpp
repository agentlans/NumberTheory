#include <iostream>

#include "LucasProbablePrime.hpp"

int main() {
    LucasExtraStrongProbableTester lespt;
    LucasStrongProbableTester lspt;

    // List the numbers that pass the strong and extra strong tests
    for (int i = 0; i < 100000; ++i) {
        if (lspt.test(i) && lespt.test(i)) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
