#include "simp.cpp"
#include "improv.cpp"
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

AlgorithmResult runAlgorithm(ll n, ll m, const std::string& filePath, int algorithm, char variant = '0', ll k = 1) {
    AlgorithmResult result = {0, Tree()};
    std::ifstream fileStream(filePath);

    // Reset file stream helper
    auto resetFileStream = [&fileStream]() {
        fileStream.clear();
        fileStream.seekg(0);
    };

    switch (algorithm) {
        case 0: { // Simple DFS
            DFSSimp dfs(n, (variant == '1') ? 1 : 0);
            while (true) {
                if (dfs.processEdgeStream(fileStream)) break;
                resetFileStream();
            }
            result.passCount = dfs.getPass();
            result.T = dfs.getT();
            break;
        }
        case 1: { // Improved DFS
            DFSImprov dfs(n);
            while (true) {
                if (dfs.processEdgeStream(fileStream)) break;
                resetFileStream();
            }
            result.passCount = dfs.getPass();
            result.T = dfs.getT();
            break;
        }
        case 2: { // kPath DFS
            kPathBase* dfs = nullptr;
            switch (variant) {
                case '0': dfs = new kPath0(n, k); break;
                case '1': dfs = new kPath1(n, k); break;
                case '2': dfs = new kPath2(n, k); break;
                case 'X': dfs = new kPath1x(n, k); break;
                default: dfs = new kPathN(n, k); break;
            }
            while (true) {
                if (dfs->processEdgeStream(fileStream)) break;
                resetFileStream();
            }
            result.passCount = dfs->getPass();
            result.T = dfs->getT();
            delete dfs;
            break;
        }
        case 3: { // kLev DFS
            kLevBase* dfs = nullptr;
            switch (variant) {
                case '0': dfs = new kLev0(n, k); break;
                case '1': dfs = new kLev1(n, k); break;
                case '2': dfs = new kLev2(n, k); break;
                case 'X': dfs = new kLev0x(n, k); break;
                case 'Y': dfs = new kLev1y(n, k); break;
                default: dfs = new kLevN(n, k); break;
            }
            while (true) {
                if (dfs->processEdgeStream(fileStream)) break;
                resetFileStream();
            }
            result.passCount = dfs->getPass();
            result.T = dfs->getT();
            delete dfs;
            break;
        }
        default:
            std::cerr << "Invalid algorithm\n";
            fileStream.close();
            exit(1);
    }

    fileStream.close();
    return result;
}