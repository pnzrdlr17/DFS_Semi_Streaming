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
    vector<vector<GraphStats>> graphStats; // Graph-related statistics (component size etc.)
    // {for each iteration we would have a vector of GraphStats, i.e. same values of n, m but different seed per iteration}
};

ll calculateM(ll n, int sparsity);

string getExperimentLabel(int experiment_type);

ExpResult experimentFramework(bool runMode, int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm = 0, int algo_variant = 0, ll k = 0);

void prepareExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token);

void runExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int algo_variant, ll k);

#endif // EXPERIMENT_H