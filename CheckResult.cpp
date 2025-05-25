#include "include/CheckResult.h"
#include <cmath>

CheckResult::CheckResult(double maa): MAA(maa) {}

void CheckResult::compute(const uint32_t* csaR, const uint32_t* etaR,
                          int N, double* OE, double* ACC, double& AP,double& avgOE,
                          double& avgACC) {
    int ok = 0;
    double sumOE = 0.0;
    double sumACC = 0.0;

    for(int i = 0; i < N; ++i) {
        uint32_t c = csaR[i], e = etaR[i];
        //overall error
        OE[i] = std::fabs(static_cast<double>(e) - c);
        sumOE += OE[i];
        //accuracy
        if(c == 0) {
            ACC[i] = (e == 0 ? 100.0 : 0.0);
        } else {
            ACC[i] = (1.0 - OE[i] / c) * 100.0;
        }
        sumACC += ACC[i];
        // Licz liczbę próbek spełniających MAA
        if(ACC[i] >= MAA) {
            ++ok;
        }
    }
    // Średnie metryki
    avgOE = sumOE / N;
    avgACC = sumACC / N;
    // Acceptance Probability
    AP = static_cast<double>(ok) / N;
}



