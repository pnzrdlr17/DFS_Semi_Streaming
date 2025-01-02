#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include "./algo_runner.cpp"
#include "./graph_generator.cpp"
#include "../lib/verifydfs.cpp"
#define ll long long int
using namespace std;

enum Mode {
    RUN_ALGO,  // Running the algorithm
    GEN_GRAPH  // Generating a graph
};

Mode mode = RUN_ALGO;
ll n, m, k = 1, seed_token = 42;
int algorithm;
char variant = '0';
string filePath, graph_type = "POWLAW";
ifstream fileStream;

 /*
Algorithm codes:
0 - Simple DFS {only two variants 0 and 1}  {doesn't need k}
1 - Improved DFS {doesn't have a variant}   {doesn't need k}
2 - kPath DFS {needs k}
3 - kLev DFS {needs k}
*/

void parseArgs(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <mode> <args>\nModes: RUN_ALGO, GEN_GRAPH\n";
        exit(1);
    }

    string modeStr = argv[1];
    if (modeStr == "RUN_ALGO") {
        mode = RUN_ALGO;
    } else if (modeStr == "GEN_GRAPH") {
        mode = GEN_GRAPH;
    } else {
        cerr << "Invalid mode: " << modeStr << "\nModes: RUN_ALGO, GEN_GRAPH\n";
        exit(1);
    }


    if (mode == RUN_ALGO) {
        if (argc < 6) {
            cerr << "Usage: " << argv[0] << "<mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <variant> <k>\n";
            exit(1);
        }

        n = stoll(argv[2]);
        m = stoll(argv[3]);
        filePath = argv[4];
        algorithm = stoi(argv[5]);

        if (algorithm == 0 || algorithm == 2 || algorithm == 3) {
            if (argc < 7) {
                cerr << "Usage: <mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <variant> <k>\nVariant must be specified for simp(0), kPath(2) and kLev(3) algorithms\n";
                exit(1);
            }
            variant = argv[6][0];
        }

        if (algorithm == 2 || algorithm == 3) {
            if (argc < 8) {
                cerr << "Usage: <mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <variant> <k>\nk must be specified for kPath(2) and kLev(3) algorithms\n";
                exit(1);
            }
            k = stoll(argv[7]);
        }
    }
    else if (mode == GEN_GRAPH) {
        if (argc < 4) {
            cerr << "Usage: " << argv[0] << "<mode:GEN_GRAPH> <n> <m> <seed> <graph_generation_type>\n";
            exit(1);
        }

        n = stoll(argv[2]);
        m = stoll(argv[3]);

        if (argc > 4) seed_token = stoll(argv[4]);
        if (argc > 5) graph_type = argv[5];
    }
}

int main(int argc, char *argv[]) {

    parseArgs(argc, argv);

    if (mode == RUN_ALGO) {
        AlgorithmResult result = runAlgorithm(n, m, filePath, algorithm, variant, k);
        //TODO fix n, m, k to ll in all algorithm files

        cout << "PassCount: " << result.passCount << "\n";
    }
    else if (mode == GEN_GRAPH) {
        filePath = generateRandomGraph(n, m, seed_token, graph_type);

        cout << "Generated graph at: " << filePath << "\n";
    }

    return 0;
}