#include <iostream>
#include <unistd.h> // for sleep(). Only available on Linux.

#include "Stopwatch.hpp"

int main() {
    Stopwatch sw;
    std::cout << "Count to 10." << std::endl;
    for (int i = 0; i < 10; ++i) {
        sw.start();
        std::cout << i+1 << std::endl;
        sleep(1);
        sw.stop();
    }
    std::cout << "Total time: " << sw.total_time() << " seconds" << std::endl;
    std::cout << "Average time: " << sw.average_time() << " seconds" << std::endl;
    return 0;
}