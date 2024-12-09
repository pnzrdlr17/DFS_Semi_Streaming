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

    int pass, k, art_root, vis_cnt;

    vector<int> visited, next_root, comp, comp_size, marked; // marked only unused in kLev1
    vector<edg> compEdg;
    vector<list<edg>> backEdge;

    virtual list<edg> reroot(int x, int y) = 0;

    // implementation slightly different in kLevY hence overridden there
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

    // Default Common implementation for all derived classes
    int addEdgeS(list<edg> &edgAdd) {
        pass++;
        prePass();
        for(auto &it: edgAdd){
            addEdge(it.first, it.second);
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