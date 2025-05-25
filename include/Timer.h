
#ifndef OIAKP_TIMER_H
#define OIAKP_TIMER_H


#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point t0;
    double* times;
    int size;
public:
    Timer(int N);
    ~Timer();
    void start();
    void stop(int idx);
    double get(int idx) const;
    double average(int N) const;
    void reset();
};

#endif //OIAKP_TIMER_H
