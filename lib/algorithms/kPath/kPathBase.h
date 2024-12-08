#ifndef KPATHBASE_H
#define KPATHBASE_H

#include <bits/stdc++.h>
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
    virtual int addEdgeS(list<edg> edges) = 0;

    // Default Common implementation for all derived classes
    Tree getT() const {
        return T;
    }
    int getPass() const {
        return pass;
    }
};

#endif // KPATHBASE_H