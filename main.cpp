#include <iostream>
#include <algorithm>
#include "include/RandomData.h"
#include "include/CarrySkipAdder.h"
#include "include/AdderEta.h"
#include "include/Timer.h"
#include "include/CheckResult.h"
#include "include/CheckCSA.h"
#include "include/WriteData.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
namespace fs = std::filesystem;


int main() {
    // lista liczebności i podziałów
    std::vector<int> Ns   = {10000, 50000, 100000, 200000, 1000000};
    std::vector<int> INACs= {4,8,12,16,20,24,28};

    const std::string summaryFile = "summary1.csv";
    bool file_empty = !fs::exists(summaryFile) || fs::file_size(summaryFile)==0;
    std::ofstream sumOut(summaryFile, std::ios::app);
    if(file_empty) {
        sumOut << "Liczebnosc INAC CSA[ns] ETA[ns] Korzysc sr_OE sr_ACC AP(ACC>=MAA) min_ACC max_ACC D_ACC\n"; //plik_wynikowy\n";
    }

    for(int N : Ns) {
        // alokacja i przygotowanie danych (możesz zrobić raz i reuse, ale tu dla czytelności każdorazowo)
        auto A    = new uint32_t[N];
        auto B    = new uint32_t[N];
        auto csaR = new uint32_t[N];
        auto etaR = new uint32_t[N];
        auto OE   = new double[N];
        auto ACC  = new double[N];
        auto ok   = new bool[N];

        RandomData rnd; rnd.generate(A,B,N);
        CheckResult checker(95.0);

        for(int inac : INACs) {
            AdderEta eta(inac);          // tworzysz ETA z tym inac
            CarrySkipAdder csa{};
            Timer tCSA(N), tETA(N);
            tCSA.reset();
            tETA.reset();
            // 1) pomiary
            for(int i=0;i<N;++i) {

                tCSA.start();
                csaR[i] = csa.add(A[i],B[i]);
                tCSA.stop(i);

                tETA.start();
                etaR[i] = eta.add(A[i],B[i]);
                tETA.stop(i);
            }
            // 2) weryfikacja CSA
            CheckCSA::verify(A,B,csaR,ok,N);
            int errors=0; for(int i=0;i<N;++i) if(!ok[i]) ++errors;

            // 3) compute OE, ACC, AP, avgOE, avgACC
            double AP, avgOE, avgACC;
            checker.compute(csaR, etaR, N, OE, ACC, AP, avgOE, avgACC);

            double minACC = ACC[0];
            double maxACC = ACC[0];
            std::unordered_map<int,int> freq;

            for(int i = 0; i < N; ++i) {
                if(ACC[i] < minACC) minACC = ACC[i];
                if(ACC[i] > maxACC) maxACC = ACC[i];
                int a = static_cast<int>(std::round(ACC[i]));  // zaokrąglamy do % jako int
                ++freq[a];
            }

// znajdź dominantę (tryb)
            int modeACC = freq.begin()->first;
            int maxCount = freq.begin()->second;
            for(auto &p : freq) {
                if(p.second > maxCount) {
                    maxCount = p.second;
                    modeACC = p.first;
                }
            }


//            // 4) zapisz szczegółowy plik
//            std::string resultFile = "results_" + std::to_string(inac) +
//                                     "_" + std::to_string(N) + ".csv";
//            WriteData writer;
//            writer.save(resultFile.c_str(),
//                        A,B,csaR,ok,etaR,OE,ACC,tCSA,tETA,N);

            double t_csa = tCSA.average(N);
            double t_eta = tETA.average(N);
            double speedup = (t_csa - t_eta) / t_csa * 100.0;

            std::cout
                    << "  INAC:              " << inac  << "\n"
                    << "  Testow:            " << N            << "\n"
                    << "  Bledy CSA:         " << errors   << "\n"
                    << "  Sr. czas CSA:      " << tCSA.average(N) << " ns\n"
                    << "  Sr. czas ETA:      " << tETA.average(N) << " ns\n"
                    << "  Korzysc czasowa:   " << speedup << " %\n"
                    << "  sr_OE:             " << avgOE        << "\n"
                    << "  sr_ACC:            " << avgACC       << " %\n"
                    << "  AP (ACC>=95%):     " << (AP * 100)  << " %\n\n";
                  //  << "  Zapisano do:       " << resultFile  << "\n\n";

            // 5) dopisz podsumowanie do summary.csv
            sumOut
                    << N << ' '
                    << inac << ' '
                    << tCSA.average(N) << ' '
                    << tETA.average(N) << ' '
                    << speedup << ' '
                    << avgOE  << ' '
                    << avgACC << ' '
                    << (AP*100) << ' '
                    << minACC  << ' '
                    << maxACC  << ' '
                    << modeACC << '\n';
                 //   << resultFile << '\n';
        }

        // posprzątaj
        delete[] A; delete[] B;
        delete[] csaR; delete[] etaR;
        delete[] OE; delete[] ACC; delete[] ok;
    }

    sumOut.close();
    return 0;
}