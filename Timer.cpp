#include "include/Timer.h"
#include <algorithm>
Timer::Timer(int N): times(new double[N]), size(N) {}
Timer::~Timer() { delete[] times; }

void Timer::start() {
    t0 = std::chrono::high_resolution_clock::now();
}

void Timer::stop(int idx) {
    auto t1 = std::chrono::high_resolution_clock::now();
    times[idx] = std::chrono::duration<double, std::nano>(t1 - t0).count();
}

double Timer::get(int idx) const { return times[idx]; }

double Timer::average(int N) const {
    double sum = 0;
    for(int i = 0; i < N; ++i) sum += times[i];
    return sum / N;
}

void Timer::reset() {
    std::fill(times, times + size, 0.0);
}
