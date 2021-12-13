#include <iostream>
#include "TrialDivision.hpp"

int main() {
    TrialDivision td(10); // Primes up to 10
    // Print possible primes.
    // Note some composite numbers like 121
    // that aren't divisible by any prime < 10
    for (int i = 0; i < 1000; ++i) {
        if (td.test(i)) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
