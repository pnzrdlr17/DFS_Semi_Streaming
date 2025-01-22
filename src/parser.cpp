#include "parser.h"
using namespace std;

// Declare global variables as extern
extern Mode mode;
extern ll n, m, k, seed_token;
extern int algorithm, experiment_type, sparsity, iterations;
extern char algo_variant;
extern string filePath, graph_type, modesText;
extern ifstream fileStream;

/*
Algorithm codes:
0 - Simple DFS {only two variants 0 and 1}  {doesn't need k}
1 - Improved DFS {doesn't have a algo_variant}   {doesn't need k}
2 - kPath DFS {needs k}
3 - kLev DFS {needs k}
*/

/*
Experiment types:
0 - VARN
1 - VARM
2 - VARK
3 - FIXNM {for a fixed N and M, run the algorithm by creating different graphs using different seeds}
*/

/*
Sparsity: M based on N
0 - 2*N
1 - 5*N
2 - N*log2(N)
3 - N*sqrt(N)
4 - N*(N-1)/2
*/

// TODO: Add type safes for each of the arguments and return the info in error message
// TODO: Try using a library for parsing command line arguments
Mode parseArgs(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <mode> <args>" << endl << modesText << endl;
        exit(1);
    }

    Mode mode;

    string modeStr = argv[1];
    if (modeStr == "RUN_ALGO") {
        mode = RUN_ALGO;
    } else if (modeStr == "GEN_GRAPH") {
        mode = GEN_GRAPH;
    } else if (modeStr == "RUN_EXP") {
        mode = RUN_EXP;
    } else if (modeStr == "PREP_EXP") {
        mode = PREP_EXP;
    } else {
        cerr << "Invalid mode: " << modeStr << endl << modesText << endl;
        exit(1);
    }

    switch (mode) {
        case RUN_ALGO: {
            if (argc < 6) {
                cerr << "Usage: " << argv[0] << " <mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <algo_variant> <k>\n";
                exit(1);
            }

            n = stoll(argv[2]);
            m = stoll(argv[3]);

            if (m > (n * (n - 1)) / 2) {
                cerr << "Invalid number of edges (m), must not be more than n*(n-1)/2\n";
                exit(1);
            }

            filePath = argv[4];
            algorithm = stoi(argv[5]);

            if (algorithm == 0 || algorithm == 2 || algorithm == 3) {
                if (argc < 7) {
                    cerr << "Usage: <mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <algo_variant> <k>\nVariant must be specified for simp(0), kPath(2) and kLev(3) algorithms\n";
                    exit(1);
                }
                algo_variant = argv[6][0];
            }

            if (algorithm == 2 || algorithm == 3) {
                if (argc < 8) {
                    cerr << "Usage: <mode:RUN_ALGO> <n> <m> <filepath> <algorithm> <algo_variant> <k>\nk must be specified for kPath(2) and kLev(3) algorithms\n";
                    exit(1);
                }
                k = stoll(argv[7]);
            }
            break;
        }
        case GEN_GRAPH: {
            if (argc < 4) {
                cerr << "Usage: " << argv[0] << " <mode:GEN_GRAPH> <n> <m> <seed> <graph_generation_type>\n";
                exit(1);
            }

            n = stoll(argv[2]);
            m = stoll(argv[3]);

            if (m > (n * (n - 1)) / 2) {
                cerr << "Invalid number of edges (m), must not be more than n*(n-1)/2\n";
                exit(1);
            }

            if (argc > 4) seed_token = stoll(argv[4]);
            if (argc > 5) graph_type = argv[5];
            break;
        }
        case PREP_EXP: {
            if (argc < 7) {
                cerr << "Usage: " << argv[0] << " <mode:PREP_EXP> <exp_type> <N> <sparsity> <graph_type> <Iterations> <seed?>\n";
                exit(1);
            }

            experiment_type = stoi(argv[2]);
            n = stoll(argv[3]);
            sparsity = stoi(argv[4]);
            graph_type = argv[5];
            iterations = stoi(argv[6]);

            if (argc > 7) seed_token = stoll(argv[7]);
            break;
        }
        case RUN_EXP: {
            if (argc < 9) {
                cerr << "Usage: " << argv[0] << " <mode:RUN_EXP> <exp_type> <N> <sparsity> <graph_type> <Iterations> <seed> <algorithm> <algo_variant> <k>\n";
                exit(1);
            }

            experiment_type = stoi(argv[2]);
            n = stoll(argv[3]);
            sparsity = stoi(argv[4]); // TODO: Add check for range of values [1, 5]
            graph_type = argv[5];
            iterations = stoi(argv[6]);
            seed_token = stoll(argv[7]);

            algorithm = stoi(argv[8]);

            if (algorithm == 0 || algorithm == 2 || algorithm == 3) {
                if (argc < 10) {
                    cerr << "Usage: <mode:RUN_EXP> <exp_type> <N> <sparsity> <Iterations> <seed> <algorithm> <algo_variant> <k>\nVariant must be specified for simp(0), kPath(2) and kLev(3) algorithms\n";
                    exit(1);
                }
                algo_variant = argv[9][0];
            }

            if (algorithm == 2 || algorithm == 3) {
                if (argc < 11) {
                    cerr << "Usage: <mode:RUN_EXP> <exp_type> <N> <sparsity> <Iterations> <seed> <algorithm> <algo_variant> <k>\nk must be specified for kPath(2) and kLev(3) algorithms\n";
                    exit(1);
                }
                k = stoll(argv[10]);
            }
            break;
        }
        default:
            cerr << "Invalid mode\n";
            exit(1);
    }

    return mode;
}