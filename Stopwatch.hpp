#ifndef _STOPWATCH
#define _STOPWATCH

#include <chrono>

class Stopwatch {
public:
    typedef std::chrono::steady_clock Clock;
    typedef Clock::duration Duration;
    Stopwatch() : t(Duration(0)) {}
    // Start timing
    void start() {
        t0 = Clock::now();
    }
    // Stop timing
    void stop() {
        auto t1 = Clock::now();
        auto diff = (t1 - t0);
        t += diff;
        num_laps++;
    }
    // Returns the total time and average time in seconds
    double total_time() {
        return convert_to_seconds(t);
    }
    double average_time() {
        return total_time() / num_laps;
    }
private:
    double convert_to_seconds(const Duration& d) {
        typedef std::chrono::duration<double> DDuration;
        DDuration ts = std::chrono::duration_cast<DDuration>(d);
        return ts.count();
    }
    unsigned long num_laps = 0;
    Clock::duration t;
    std::chrono::time_point<Clock> t0;
};

#endif