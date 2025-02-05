#ifndef KLEVBASE_H
#define KLEVBASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "../../tree.cpp"
#include "../../levelAnc.cpp"
#define edg pair<int, int>
#define pii pair<int, int>
using namespace std;


class kLevBase {

protected:
    Tree T;
    LevelAnc LA;

    int n, pass, k, art_root, vis_cnt;

    vector<int> visited, next_root, comp, comp_size, marked; // marked only unused in kLev1
    vector<edg> compEdg;
    vector<list<edg>> backEdge;

    virtual list<edg> reroot(int x, int y) = 0;

    // implementation slightly different in kLev0x hence overridden there
    int updateComp(int x, int root, int flag) {
        int cnt = 0;
        if(flag) cnt++;

        backEdge[x].clear();
        for(auto &it: T.getChild(x)){
            if(flag == 0){
                if(marked[it] == 0){
                    visited[it] = 1;
                    vis_cnt++;
                    comp[it] = 0;
                    comp_size[it] = 0;
                    next_root[it] = 0;
                    updateComp(it, it, 0);
                }
                else{
                    comp[it] = it;
                    next_root[it] = 1;
                    compEdg[it] = edg(x, it);
                    visited[it] = 1;
                    vis_cnt++;
                    marked[it] = 0;
                    comp_size[it] = updateComp(it, it, 1);
                }
            }
            else{
                comp[it] = root;
                marked[it] = 0;
                cnt += updateComp(it, root, 1);
            }
        }
        return cnt;
    }


public:
    virtual ~kLevBase() {}
    virtual void addEdge(int x, int y) = 0;
    virtual void prePass() = 0;
    virtual int postPass() = 0;

    /* Default Common implementation for all derived classes */

    int addEdgeS(list<edg> &edgAdd) {
        pass++;
        prePass();
        for(auto &it: edgAdd){
            addEdge(it.first, it.second);
        }
        return postPass();
    }

    int processEdgeStream(ifstream& fileStream) {
        pass++;
        prePass();
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

        return postPass();
    }

    Tree getT() const {
        return T;
    }

    int getPass() const {
        return pass;
    }
};

#endif // KLEVBASE_H