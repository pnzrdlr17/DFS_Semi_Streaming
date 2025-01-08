#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include "./algo_runner.h"
#include "./graph_generator.h"
#include "./parser.h"
#include "./experiment.h"
#define ll long long int
#define endl '\n'
using namespace std;

/*
Modes:
RUN_ALGO: Run the given algorithm for the given (filepath) graph
GEN_GRAPH: Generate a random graph with the given parameters
PREP_EXP: [Prerun for a particular type of experiment] -- generate all the required graphs in advance
RUN_EXP: Run an experiment [VARN, VARM, VARK] with the given parameters
*/

Mode mode = RUN_ALGO;
ll n, m, k = 1, seed_token = 42;
int algorithm, experiment_type, sparsity, iterations;
char variant = '0';
string filePath, graph_type = "POWLAW";
ifstream fileStream;
string modesText = "Modes: RUN_ALGO, GEN_GRAPH, RUN_EXP, PREP_EXP\n";
const string randomGraphsDirectory = "./input/random_graphs/";

/*
Algorithm codes:
0 - Simple DFS {only two variants 0 and 1}  {doesn't need k}
1 - Improved DFS {doesn't have a variant}   {doesn't need k}
2 - kPath DFS {needs k}
3 - kLev DFS {needs k}
*/

/*
Experiment types:
0 - VARN
1 - VARM
2 - VARK
*/

/*
Sparsity: M based on N
0 - 2*N
1 - 5*N
2 - N*log2(N)
3 - N*sqrt(N)
4 - N*(N-1)/2
*/

int main(int argc, char *argv[]) {

    mode = parseArgs(argc, argv);

    switch (mode) {
        case RUN_ALGO: {
            AlgorithmResult result = runAlgorithm(n, m, filePath, algorithm, variant, k);
            // TODO fix n, m, k to ll in all algorithm files
            cout << "PassCount: " << result.passCount << "\n";
            break;
        }
        case GEN_GRAPH: {
            filePath = generateRandomGraph(n, m, seed_token, graph_type);
            cout << "Generated graph at: " << filePath << "\n";
            break;
        }
        case PREP_EXP: {
            prepareExperiment(experiment_type, n, sparsity, graph_type, iterations, seed_token);
            cout << "Seed: " << seed_token << "\n";
            break;
        }
        case RUN_EXP: { //TODO: Add a check that file exists otherwise ask the user to call prep_exp
            vector<pair<ll,double>> avgPasses = runExperiment(experiment_type, n, sparsity, graph_type, iterations, seed_token, algorithm, variant, k);

            cout << "Experiment Type: " << experiment_type << endl << " Average Passes: \n";
            for (int i = 0; i < avgPasses.size(); ++i) {
                cout << avgPasses[i].first << " " << avgPasses[i].second << "\n";
            }
            break;
        }
        default:
            cerr << "Invalid mode: " << mode << endl << modesText << endl;
            exit(1);
    }

    return 0;
}