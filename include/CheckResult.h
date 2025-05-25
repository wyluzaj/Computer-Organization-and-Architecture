
#ifndef OIAKP_CHECKRESULT_H
#define OIAKP_CHECKRESULT_H


#include <cstdint>

class CheckResult {
    double MAA;
public:
    CheckResult(double maa = 95.0);
    void compute(const uint32_t* csaR, const uint32_t* etaR,
                 int N, double* OE, double* ACC, double& AP, double& avgOE,
                 double& avgACC);
};

#endif //OIAKP_CHECKRESULT_H
