#ifndef KPATHBASE_H
#define KPATHBASE_H
#include <cstring>
#include <fstream>
#include <sstream>
#include "../../tree.cpp"
#define edg pair<int, int>
using namespace std;

class kPathBase {

protected:
    int n;
    Tree T;
    int pass;
    int visC;
    vector<int> visited;
    int sopt;
    vector<list<pair<int,int>>> saved_edges;
    vector<list<int>> compL;
    vector<int> comp;
    vector<pair<int,int>> compEdge;
    vector<int> level;
    vector<int> processed;
    /*
    vector<list<edg>> sptree;
    vector<set<edg>> sptree;
    */

public:
    virtual ~kPathBase() {}

    virtual void prepass() = 0;
    virtual void post_processing(int compN) = 0;
    virtual void processComp(int compN) = 0;
    virtual void process_edge(int u, int v) = 0;
    virtual void addEdge(int x, int y) = 0;
    virtual int postpass() = 0;

    /* Default Common implementation for all derived classes */

    virtual int addEdgeS(list<edg>& edges) { // overridden in kPath0
        prepass();
        for(auto it=edges.begin();it!=edges.end();it++){
            addEdge(it->first,it->second);
        }
        return postpass();
    }

    virtual int processEdgeStream(ifstream& fileStream) { // overridden in kPath0
        prepass();
        // ? Heuristic H1
        for (int i = 1; i < n; ++i) // Add artificial edges (disconnected graph connections)
            addEdge(0, i);

        if (!fileStream.is_open()) {
            cerr << "Error opening file: " << strerror(errno) << endl;
            return 0;
        }

        string line;
        while (getline(fileStream, line)) {
            istringstream iss(line);
            int e1, e2;
            if (!(iss >> e1 >> e2)) {
                cerr << "Error: Malformed or incomplete line: " << line << endl;
                break; // Exit loop if edge format is invalid
            }
            addEdge(e1, e2);
        }

        return postpass();
    }

    Tree getT() const {
        return T;
    }
    int getPass() const {
        return pass;
    }
};

#endif // KPATHBASE_H