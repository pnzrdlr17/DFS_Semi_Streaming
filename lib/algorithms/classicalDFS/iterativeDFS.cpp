#include "iterativeDFS.h"

Tree* classicalIterativeDFS(ll n, ll m, const string& filePath) {
    Tree* dfsTree = new Tree(n + 1);
    ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        cerr << "Error opening file: " << strerror(errno) << endl;
        exit(1);
    }

    vector<ll> adjList[n + 1];

    string line;
    ll u, v;
    while (getline(fileStream, line)) {
        istringstream iss(line);
        if (!(iss >> u >> v)) {
            cerr << "Error: Malformed or incomplete line: " << line << endl;
            break; // Exit loop if edge format is invalid
        }
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    fileStream.close();

    ll node = 1;// Start from node 1 // or maybe the first node in the graph
    stack<ll> dfsStack;
    bool visited[n + 1];
    memset(visited, false, sizeof(visited));

    dfsStack.push(node);
    visited[node] = true;

    while (!dfsStack.empty()) {
        node = dfsStack.top();
        dfsStack.pop();

        for (ll neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dfsTree->addEdge(node, neighbor);
                dfsStack.push(neighbor);
            }
        }
    }

    return dfsTree;
}