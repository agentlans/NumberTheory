#include <iostream>

#include "FermatProbablePrime.hpp"

int main() {
    MillerRabinProbableTester fpt;
    Int i;
    for (; i < 100; i.incf()) {
        if (fpt.test(i)) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}