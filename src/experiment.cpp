#include "experiment.h"
#define ll long long int
using namespace std;

extern const string randomGraphsDirectory;

inline ll calculateM (ll n, int sparsity) {
    switch (sparsity) {
        case 0: return 2ll * n;
        case 1: return 5ll * n;
        case 2: return n * log2(n);
        case 3: return n * sqrt(n);
        case 4: return (n * (n - 1ll)) / 2;
        default: {
            cerr << "Invalid sparsity\nSparsity: 0 - 2*N, 1 - 5*N, 2 - N*log2(N), 3 - N*sqrt(N), 4 - N*(N-1)/2\n";
            exit(1);
        }
    }
}

// runMode: 0 - prepare, 1 - run
ExpResult experimentFramework(bool runMode, int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int variant, ll k)  {
    ExpResult expr;
    AlgorithmResult result;
    string current_file;

    ll step, testCount, seeds[iterations];
    mt19937_64 rng(seed_token);
    uniform_int_distribution<ll> dist(1, LLONG_MAX);
    for (ll i = 0; i < iterations; ++i) {
        seeds[i] = dist(rng);
    }

    switch (experiment_type) {
        case 0: { // VARN
            ll current_m, current_n;
            testCount = (n < 100) ? (n / 10) : (9 + (n - 100 + 50) / 50);
            vector<pair<ll, double>> avgPass(testCount), maxPass(testCount), avgHeight(testCount);// TODO: make use of ifdef to declare variables conditionally

            for (int itr = 0, i; itr < iterations; ++itr) {
                i = 0; // counter for the current graph (current_n, current_m)
                current_n = 10;
                step = 10;
                while (current_n <= n) {
                    current_m = calculateM(current_n, sparsity);
                    if (itr == 0) {
                        avgPass[i] = {current_n, 0};
                        maxPass[i] = {current_n, 0};
                        avgHeight[i] = {current_n, 0};
                    }

                    if (runMode) {
                        current_file = randomGraphsDirectory + generate_file_name(current_n, current_m, graph_type, seeds[itr]);

                        if (!file_exists(current_file)) {
                            cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                            exit(1);
                        }

                        result = runAlgorithm(current_n, current_m, current_file, algorithm, variant, k);

                        avgPass[i].second += result.passCount;
                        avgHeight[i].second += result.T.getHeight(0);
                        if (result.passCount > maxPass[i].second) maxPass[i].second = result.passCount;
                    }
                    else {
                        generateRandomGraph(current_n, current_m, seeds[itr], graph_type);
                    }

                    if (current_n >= 100) step = 50;
                    current_n += step;
                    i++;
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    avgPass[i].second /= iterations;
                    avgHeight[i].second /= iterations;
                }
                expr.avgPasses = avgPass;
            }

            break;
        }
        case 1: { // VARM
            ll m = calculateM(n, sparsity), current_m;
            testCount = (m < 1000) ? (m - 100) / 100 + 1 :
                        (m < 20000) ? 9 + (m - 1000) / 1000 + 1 :
                        (m < 100000) ? 9 + 19 + (m - 20000) / 10000 + 1 :
                        (9 + 19 + 8 + (m - 100000) / 100000 + 1);
            vector<pair<ll, double>> avgPass(testCount), maxPass(testCount), avgHeight(testCount);// TODO: make use of ifdef to declare variables conditionally

            for (int itr = 0, i; itr < iterations; ++itr) {
                i = 0; // counter for the current graph (n, current_m)
                current_m = 100;
                step = 100;
                while (current_m <= m) {
                    if (itr == 0) {
                        avgPass[i] = {current_m, 0};
                        maxPass[i] = {current_m, 0};
                        avgHeight[i] = {current_m, 0};
                    }

                    if (runMode) {
                        current_file = randomGraphsDirectory + generate_file_name(n, current_m, graph_type, seeds[itr]);

                        if (!file_exists(current_file)) {
                            cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                            exit(1);
                        }

                        result = runAlgorithm(n, current_m, current_file, algorithm, variant, k);

                        avgPass[i].second += result.passCount;
                        avgHeight[i].second += result.T.getHeight(0);
                        if (result.passCount > maxPass[i].second) maxPass[i].second = result.passCount;
                    }
                    else {
                        generateRandomGraph(n, current_m, seeds[itr], graph_type);
                    }

                    if (current_m >= 1000) step = 1000;
                    if (current_m >= 20000) step = 10000;
                    if (current_m >= 100000) step = 100000;
                    current_m += step;
                    i++;
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    avgPass[i].second /= iterations;
                    avgHeight[i].second /= iterations;
                }
                expr.avgPasses = avgPass;
            }
            break;
        }
        case 2: { // VARK
            ll m = calculateM(n, sparsity), current_k;
            testCount = (k < 40) ? k : (k < 100) ? (39 + (k - 40 + 5) / 5) : (39 + 12 + (k - 100 + 50) / 50);
            vector<pair<ll, double>> avgPass(testCount), maxPass(testCount), avgHeight(testCount);// TODO: make use of ifdef to declare variables conditionally


            for (int itr = 0, i; itr < iterations; ++itr) {
                if (runMode) {
                    i = 0;
                    current_k = 1;
                    step = 1;
                    current_file = randomGraphsDirectory + generate_file_name(n, m, graph_type, seeds[itr]);

                    if (!file_exists(current_file)) {
                        cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                        exit(1);
                    }

                    while (current_k <= k) {
                        if (itr == 0) {
                            avgPass[i] = {current_k, 0};
                            maxPass[i] = {current_k, 0};
                            avgHeight[i] = {current_k, 0};
                        }

                        result = runAlgorithm(n, m, current_file, algorithm, variant, current_k);

                        avgPass[i].second += result.passCount;
                        avgHeight[i].second += result.T.getHeight(0);
                        if (result.passCount > maxPass[i].second) maxPass[i].second = result.passCount;

                        if (k >= 40) step = 5;
                        if (k >= 100) step = 50;
                        current_k += step;
                        i++;
                    }
                }
                else {
                    generateRandomGraph(n, m, seeds[itr], graph_type);
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    avgPass[i].second /= iterations;
                    avgHeight[i].second /= iterations;
                }
                expr.avgPasses = avgPass;
            }
            break;
        }
        default: {
            cerr << "Invalid experiment type\n";
            exit(1);
        }
    }

    return expr;
}

void prepareExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token) {
    experimentFramework(0, experiment_type, n, sparsity, graph_type, iterations, seed_token);
}

vector<pair<ll, double>> runExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int variant, ll k) {
    ExpResult result = experimentFramework(1, experiment_type, n, sparsity, graph_type, iterations, seed_token, algorithm, variant, k);
    return result.avgPasses;
}