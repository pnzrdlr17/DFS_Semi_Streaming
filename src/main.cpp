#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include "./algo_runner.cpp"
#include "../lib/verifydfs.cpp"
#define ll long long int
using namespace std;

ll n, m, k = 1;
int algorithm;
char variant = '0';
string filePath;
ifstream fileStream;

void parseArgs(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <n> <m> <filepath> <algorithm> <variant> <k>\n";
        exit(1);
    }

    n = stoll(argv[1]);
    m = stoll(argv[2]);
    filePath = argv[3];
    algorithm = stoi(argv[4]);

    if (algorithm == 0 || algorithm == 2 || algorithm == 3) {
        if (argc < 6) {
            cerr << "Usage: <n> <m> <filepath> <algorithm> <variant> <k>\nVariant must be specified for simp(0), kPath(2) and kLev(3) algorithms\n";
            exit(1);
        }
        variant = argv[5][0];
    }

    if (algorithm == 2 || algorithm == 3) {
        if (argc < 7) {
            cerr << "Usage: <n> <m> <filepath> <algorithm> <variant> <k>\nk must be specified for kPath(2) and kLev(3) algorithms\n";
            exit(1);
        }
        k = stoll(argv[6]);
    }

    /*
    Algorithm codes:
    0 - Simple DFS {only two variants 0 and 1}  {doesn't need k}
    1 - Improved DFS {doesn't have a variant}   {doesn't need k}
    2 - kPath DFS {needs k}
    3 - kLev DFS {needs k}
    */
}

int main(int argc, char *argv[]) {

    parseArgs(argc, argv);

    AlgorithmResult result = runAlgorithm(n, m, filePath, algorithm, variant, k);
    //TODO fix n, m, k to ll in all algorithm files

    cout << "PassCount: " << result.passCount << "\n";

    return 0;
}