#include "experiment.h"
#define ll long long int
using namespace std;

extern const string randomGraphsDirectory;

inline ll calculateM (ll n, int sparsity) {
    switch (sparsity) {
        case 0: return min(2ll * n, (n * (n - 1ll)) / 2);
        case 1: return min(5ll * n, (n * (n - 1ll)) / 2);
        case 2: return n * log2(n);
        case 3: return n * sqrt(n);
        case 4: return (n * (n - 1ll)) / 2;
        default: {
            cerr << "Invalid sparsity\nSparsity: 0 - 2*N, 1 - 5*N, 2 - N*log2(N), 3 - N*sqrt(N), 4 - N*(N-1)/2\n";
            exit(1);
        }
    }
}

inline string getExperimentLabel(int experiment_type) {
    switch (experiment_type) {
        case 0: return "VARN";
        case 1: return "VARM";
        case 2: return "VARK";
        case 3: return "FIXNM";
        default: {
            cerr << "Invalid experiment type\n";
            exit(1);
        }
    }
}

// runMode: 0 - prepare, 1 - run
ExpResult experimentFramework(bool runMode, int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int variant, ll k)  {
    ExpResult expr;
    AlgorithmResult result;
    string current_file;
    vector<AlgorithmStats> algoStats;
    vector<vector<GraphStats>> graphStats;

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
            runMode ? algoStats.resize(testCount) : graphStats.resize(iterations, vector<GraphStats>(testCount));

            for (int itr = 0, i; itr < iterations; ++itr) {
                i = 0; // counter for the current graph (current_n, current_m)
                current_n = 10;
                step = 10;
                while (current_n <= n) {
                    current_m = calculateM(current_n, sparsity);

                    if (runMode) {
                        if (itr == 0) algoStats[i] = {current_n, 0, 0, 0}; // (current_x, avgPasses, avgHeight, maxPasses)

                        current_file = randomGraphsDirectory + generate_file_name(current_n, current_m, graph_type, seeds[itr]);

                        if (!file_exists(current_file)) {
                            cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                            exit(1);
                        }

                        result = runAlgorithm(current_n, current_m, current_file, algorithm, variant, k);

                        algoStats[i].avgPasses += result.passCount;
                        algoStats[i].avgHeight += result.T.getHeight(0);
                        if (result.passCount > algoStats[i].maxPasses) algoStats[i].maxPasses = result.passCount;
                    }
                    else {
                        // cout << "Generating random graph for n = " << current_n << " m = " << current_m << " seed = " << seeds[itr] << endl;
                        generateRandomGraph(current_n, current_m, seeds[itr], graph_type);
                        graphStats[itr][i] = getGraphStats(current_n, current_m, seeds[itr], sparsity, graph_type);
                    }

                    if (current_n >= 100) step = 50;
                    current_n += step;
                    i++;
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    algoStats[i].avgPasses /= iterations;
                    algoStats[i].avgHeight /= iterations;
                }
                expr.algorithmStats = algoStats;
            }
            else {
                expr.graphStats = graphStats;
            }

            break;
        }
        case 1: { // VARM
            ll m = calculateM(n, sparsity), current_m;
            testCount = (m < 1000) ? (m - 100) / 100 + 1 :
                        (m < 20000) ? 9 + (m - 1000) / 1000 + 1 :
                        (m < 100000) ? 9 + 19 + (m - 20000) / 10000 + 1 :
                        (9 + 19 + 8 + (m - 100000) / 100000 + 1);
            runMode ? algoStats.resize(testCount) : graphStats.resize(iterations, vector<GraphStats>(testCount));

            for (int itr = 0, i; itr < iterations; ++itr) {
                i = 0; // counter for the current graph (n, current_m)
                current_m = 100;
                step = 100;
                while (current_m <= m) {

                    if (runMode) {
                        if (itr == 0) algoStats[i] = {current_m, 0, 0, 0}; // (current_x, avgPasses, avgHeight, maxPasses)

                        current_file = randomGraphsDirectory + generate_file_name(n, current_m, graph_type, seeds[itr]);

                        if (!file_exists(current_file)) {
                            cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                            exit(1);
                        }

                        result = runAlgorithm(n, current_m, current_file, algorithm, variant, k);

                        algoStats[i].avgPasses += result.passCount;
                        algoStats[i].avgHeight += result.T.getHeight(0);
                        if (result.passCount > algoStats[i].maxPasses) algoStats[i].maxPasses = result.passCount;
                    }
                    else {
                        generateRandomGraph(n, current_m, seeds[itr], graph_type);
                        graphStats[itr][i] = getGraphStats(n, current_m, seeds[itr], sparsity, graph_type);
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
                    algoStats[i].avgPasses /= iterations;
                    algoStats[i].avgHeight /= iterations;
                }
                expr.algorithmStats = algoStats;
            }
            else {
                expr.graphStats = graphStats;
            }

            break;
        }
        case 2: { // VARK
            ll m = calculateM(n, sparsity), current_k;
            testCount = (k < 40) ? k : (k < 100) ? (39 + (k - 40 + 5) / 5) : (39 + 12 + (k - 100 + 50) / 50);
            runMode ? algoStats.resize(testCount) : graphStats.resize(iterations, vector<GraphStats>(1));

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
                        if (itr == 0) algoStats[i] = {current_k, 0, 0, 0}; // (current_x, avgPasses, avgHeight, maxPasses)

                        result = runAlgorithm(n, m, current_file, algorithm, variant, current_k);

                        algoStats[i].avgPasses += result.passCount;
                        algoStats[i].avgHeight += result.T.getHeight(0);
                        if (result.passCount > algoStats[i].maxPasses) algoStats[i].maxPasses = result.passCount;

                        if (k >= 40) step = 5;
                        if (k >= 100) step = 50;
                        current_k += step;
                        i++;
                    }
                }
                else {
                    generateRandomGraph(n, m, seeds[itr], graph_type);
                    graphStats[itr][0] = getGraphStats(n, m, seeds[itr], sparsity, graph_type);
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    algoStats[i].avgPasses /= iterations;
                    algoStats[i].avgHeight /= iterations;
                }
                expr.algorithmStats = algoStats;
            }
            else {
                expr.graphStats = graphStats;
            }

            break;
        }
        case 3: { // FIXNM
            ll m = calculateM(n, sparsity);
            testCount = 1;
            runMode ? algoStats.resize(testCount) : graphStats.resize(iterations, vector<GraphStats>(testCount));

            for (int itr = 0; itr < iterations; ++itr) {
                if (runMode) {
                    current_file = randomGraphsDirectory + generate_file_name(n, m, graph_type, seeds[itr]);

                    if (!file_exists(current_file)) {
                        cerr << "File not found: " << current_file << endl << "Run PREP_EXP with same args before trying RUN_EXP" << endl;
                        exit(1);
                    }

                    result = runAlgorithm(n, m, current_file, algorithm, variant, k);

                    algoStats[0].avgPasses += result.passCount;
                    algoStats[0].avgHeight += result.T.getHeight(0);
                    if (result.passCount > algoStats[0].maxPasses) algoStats[0].maxPasses = result.passCount;
                }
                else {
                    generateRandomGraph(n, m, seeds[itr], graph_type);
                    graphStats[itr][0] = getGraphStats(n, m, seeds[itr], sparsity, graph_type);
                }
            }

            if (runMode) {
                for (int i = 0; i < testCount; ++i) {
                    algoStats[i].avgPasses /= iterations;
                    algoStats[i].avgHeight /= iterations;
                }
                expr.algorithmStats = algoStats;
            }
            else {
                expr.graphStats = graphStats;
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
    ExpResult result = experimentFramework(0, experiment_type, n, sparsity, graph_type, iterations, seed_token);

    cout << "Experiment Type: " << getExperimentLabel(experiment_type) << endl << "Graph Stats: \n";

    int i = 0;
    for (const auto& iterationStats : result.graphStats) {
        cout << "Iteration " << ++i << ":\n";
        for (const auto& stats : iterationStats) {
            cout << "n=" << stats.n << " m=" << stats.m
                // << " seed=" << stats.seed
                << " sparsity=" << stats.sparsity
                << " graph_type=" << stats.graph_type << " maxCompSize=" << stats.maxCompSize
                << " numComps=" << stats.numComps << " meanCompSize=" << stats.meanCompSize
                << " stdDevCompSize=" << stats.stdDevCompSize << "\n";
        }
    }

    // TODO: use if-else to write cout or write to file
}

void runExperiment(int experiment_type, ll n, int sparsity, string graph_type, int iterations, ll seed_token, int algorithm, int variant, ll k) {
    ExpResult result = experimentFramework(1, experiment_type, n, sparsity, graph_type, iterations, seed_token, algorithm, variant, k);
    vector<AlgorithmStats> algorithmStats = result.algorithmStats;

    cout << "Experiment Type: " << getExperimentLabel(experiment_type) << endl << "Average Passes: \n";

    for (int i = 0; i < algorithmStats.size(); ++i) {
        cout << algorithmStats[i].current_x << " " << algorithmStats[i].avgPasses << "\n";
    }

    // TODO: write to file / console
}