#include <iostream>
#include <cassert>

#include "Random.hpp"
#include "PrimeProver.hpp"
#include "LucasProbablePrime.hpp"
#include "Stopwatch.hpp"

// icpx -O3 GoldStandard.cpp -lflint -lgmp

int main() {
    Int n;
    PrimeProver pp;
    LucasExtraStrongProbableTester lpt;

    Stopwatch lucas_sw, gold_sw;

    //Int max_n;
    //Int::pow(max_n, 10, 10);

    Random rand;

    // Counts Lucas pseudoprimes
    long num_pseudoprimes = 0;
    long num_primes = 0;
    while (num_primes < 10) {
        rand.sample_odd(n, 2048);

        gold_sw.start();
        bool is_prime = pp.test(n);
        gold_sw.stop();

        lucas_sw.start();
        bool is_lucas_prp = lpt.test(n);
        lucas_sw.stop();

        if (is_prime) {
            num_primes++;
            std::cout << num_primes << " prime numbers found." << std::endl;
        }
        assert(!is_prime || is_lucas_prp); // prime => Lucas PRP
        
        // Composite number passing as prime
        if (!is_prime && is_lucas_prp) {
            num_pseudoprimes++;
            //std::cout << n << std::endl;
        }
    }
    std::cout << "Number of pseudoprimes: " << num_pseudoprimes << std::endl;
    std::cout << "Primality test average time: " << gold_sw.average_time() << std::endl;
    std::cout << "Probable test average time: " << lucas_sw.average_time() << std::endl;
    return 0;
}
