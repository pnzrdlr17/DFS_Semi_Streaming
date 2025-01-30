#include "algo_runner.h"

AlgorithmResult runAlgorithm(ll n, ll m, const string& filePath, int algorithm, char algo_variant, ll k) {
    AlgorithmResult result = {0, Tree()};
    ifstream fileStream(filePath);

    if (!fs::exists(filePath)) {
        cerr << "Error: File does not exist: " << filePath << endl;
        exit(1);
    }
    if (!fs::is_regular_file(filePath)) {
        cerr << "Error: Path is not a file: " << filePath << endl;
        exit(1);
    }
    if(!fileStream.good()) {
        cerr << "Error opening file: " << filePath << endl;
        fileStream.close();
        exit(1);
    }

    // Reset file stream helper
    auto resetFileStream = [&fileStream]() {
        fileStream.clear();
        fileStream.seekg(0);
    };

    switch (algorithm) {
        case 0: { // Simple DFS
            DFSSimp dfs(n, (algo_variant == '1') ? 1 : 0);
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
            if (algo_variant != '0' && n * k >= m) { 
                // When k is sufficient to store all the edges -> Use classicalDFS instead
                // This would be part of H1 heuristic, hence not included in kPath0
                Tree* dfsTree = classicalIterativeDFS(n, m, filePath);
                result.passCount = 1;
                result.T = *dfsTree;
                break;
            }

            kPathBase* dfs = nullptr;
            switch (algo_variant) {
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
            if (algo_variant != '0' && n * k >= m) { 
                // When k is sufficient to store all the edges -> Use classicalDFS instead
                // This would be part of H1 heuristic, hence not included in kLev0
                Tree* dfsTree = classicalIterativeDFS(n, m, filePath);
                result.passCount = 1;
                result.T = *dfsTree;
                break;
            }

            kLevBase* dfs = nullptr;
            switch (algo_variant) {
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
            cerr << "Invalid algorithm\n";
            fileStream.close();
            exit(1);
    }

    fileStream.close();
    return result;
}