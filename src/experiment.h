#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include <cmath>
#include <climits>
#include <random>
#include <cstring>
#include <vector>
#include "./graph_generator.h"
#include "./algo_runner.h"
#define ll long long int
using namespace std;

struct ExpResult {
    vector<AlgorithmStats> algorithmStats; // Algorithm-related statistics (average passes, tree height etc.)
    vector<GraphStats> graphStats;         // Graph-related statistics (component size etc.)
};

ll calculateM(ll n, int sparsity);

string getExperimentLabel(int experiment_type);

ExpResult experimentFramework(bool runMode, int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm = 0, int variant = 0, ll k = 0);

void prepareExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token);

void runExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int variant, ll k);

#endif // EXPERIMENT_H