#ifndef ALGO_RUNNER_H
#define ALGO_RUNNER_H

#include "../lib/algorithms/simp.cpp"
#include "../lib/algorithms/improv.cpp"
#include "../lib/algorithms/kLev/kLev0.cpp"
#include "../lib/algorithms/kLev/kLev0x.cpp"
#include "../lib/algorithms/kLev/kLev1.cpp"
#include "../lib/algorithms/kLev/kLev1y.cpp"
#include "../lib/algorithms/kLev/kLev2.cpp"
#include "../lib/algorithms/kLev/kLevN.cpp"
#include "../lib/algorithms/kPath/kPath0.cpp"
#include "../lib/algorithms/kPath/kPath1.cpp"
#include "../lib/algorithms/kPath/kPath1x.cpp"
#include "../lib/algorithms/kPath/kPath2.cpp"
#include "../lib/algorithms/kPath/kPathN.cpp"
#define ll long long int

struct AlgorithmResult {
    ll passCount;
    Tree T;
};

AlgorithmResult runAlgorithm(ll n, ll m, const std::string& filePath, int algorithm, char variant = '0', ll k = 1);

#endif // ALGO_RUNNER_H