#include <iostream>

#include "LucasProbablePrime.hpp"
#include "Stopwatch.hpp"

int main() {
    LucasProbablePrimeTester lpt;

    Int end;
    Int::pow(end, 2, 4096);

    const long trials = 1000;

    Random rand;
    Int n;
    long count = 0;

    Stopwatch sw;
    // Sample random integers in range and test for primality
    for (long i = 0; i < trials; ++i) {
        rand.sample(n, end);
        sw.start();
        if (lpt.test(n)) {
            count++;
        }
        sw.stop();
    }

    std::cout << "Estimated proportion of Lucas probable primes up to " << 
        end << ": " << std::endl;
    std::cout << count << "/" << trials << std::endl;
    std::cout << "Average time per number tested: " << 
        sw.average_time() << "s" << std::endl;
    return 0;
}