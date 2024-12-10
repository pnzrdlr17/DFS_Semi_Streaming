// with one pass heuristic + without marked/unmarked + with nk space correction (backedges thing)
// with total nk space + without top path
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "../../levelAnc.cpp"
#include "kLevBase.h"

using namespace std;

#define edg pair<int, int>
#define pii pair<int, int>

class kLev0x: public kLevBase{

    int limit_k;
    set<pair<pii, edg>> set_backEdges;

    void add_back_edge(int x, edg e) {
        //things we need to do while adding a backedge to a vertex; //to do
        if(LA.level(x) >= limit_k) return;

        if(set_backEdges.size() >= T.getSize()*k){
            pair<pii, edg> pr = *set_backEdges.begin();
            limit_k = min(limit_k, (-pr.first.first)); // (doubt) what is the reason for level-1? (changed here 1)
            auto it = set_backEdges.begin();
            set<int> removed_vertices;
            while(it != set_backEdges.end()){
                int curr_level = -(*it).first.first;
                if(curr_level >= limit_k){
                    removed_vertices.insert((*it).first.second);
                    it = set_backEdges.erase(it);
                }
                else break;
            }

            for(auto &it: removed_vertices){
                backEdge[it].clear(); //(sri) check for errors. hint: expand if clear() won't work
            }
        }

        if(LA.level(x) < limit_k){
            backEdge[x].push_back(e);
            set_backEdges.insert({{-LA.level(x), x}, e});
        }
    }

    list<edg> reroot(int x, int y) { //review later //to do
        int z, t;
        list<edg> tmp_list;
        if(x == y) return tmp_list;
        //(doubt) not adding backedges of y to tmp_list...???
        z = T.par(y);
        T.remEdge(z, y);
            
        while(x!=y){
            tmp_list.splice(tmp_list.end(), backEdge[y]);
            for(auto &it:backEdge[y]){
                set_backEdges.erase({{-LA.level(y), y}, it});
            }
            backEdge[y].clear();
            // if(z != x){ //(sri) changed here - 2.
            //     tmp_list.splice(tmp_list.end(), backEdge[z]);
            //     for(auto &it: backEdge[z]){
            //         set_backEdges.erase({{-LA.level(z), z}, it});
            //     }
            //     backEdge[z].clear();
            // }
            t = T.par(z);
            if(t != -1) T.remEdge(t, z);
            T.addEdge(y, z);
            y = z;
            z = t;
        }
        return tmp_list;
    }

    void check_subtree(int x, int level_x) {
        // subtree got changed and some levels might change;
        int prev_level = LA.level(x);
        if(prev_level < limit_k){
            for(auto &it: backEdge[x]){
                set_backEdges.erase({{-prev_level, x}, it});
                if(level_x < limit_k) set_backEdges.insert({{-level_x, x}, it});
            }
            if(level_x >= limit_k) backEdge[x].clear(); //(sri) clear works;

            for(auto &it: T.getChild(x)){
                check_subtree(it, level_x+1);
            }
        }
        else return;
    }

    int updateComp(int x, int root, int flag) {
        int cnt = 0;
        if(flag) cnt++;

        backEdge[x].clear();
        for(auto &it: T.getChild(x)){
            if(flag == 0){
                if(LA.level(it) < limit_k - 1){
                    visited[it] = 1;
                    vis_cnt++;
                    comp[it] = 0;
                    comp_size[it] = 0;
                    next_root[it] = 0; //(sri) ig not needed
                    updateComp(it, it, 0);
                }
                else{
                    comp[it] = it;
                    next_root[it] = 1;
                    compEdg[it] = edg(x, it);
                    visited[it] = 1;
                    vis_cnt++;
                    comp_size[it] = updateComp(it, it, 1);
                }
            }
            else{
                comp[it] = root;
                cnt += updateComp(it, root, 1);
            }
        }
        return cnt;
    }


public:

    kLev0x (int size, int space_optimality) {
        n = size+1;
        pass = 0;
        k = space_optimality;

        backEdge.resize(size+1);
        comp.resize(size+1, 0);
        compEdg.resize(size+1);
        comp_size.resize(size+1, 0);
        next_root.resize(size+1, 0);

        T = Tree(size+1);
        visited.resize(size+1, 0);
        art_root = 0;
        T.setRoot(art_root);

        for(int i=1; i<=size; i++){
            T.addEdge(0, i);
            comp[i] = 0;
        }

        comp_size[0] = size+1;
        next_root[0] = 1;
        compEdg[0] = {-1, 0};

        LA = LevelAnc(T);
        visited[0] = 1;
        vis_cnt = 1;
    }


    void prePass() {
        limit_k = INT_MAX;
        for(int a=0; a<T.getSize(); a++){
            if(next_root[a] == 1 && comp_size[a] != 0){
                if(compEdg[a].first != -1) T.remEdge(compEdg[a].first, compEdg[a].second);
                LA.updateT(compEdg[a].second);
                visited[a] = 0;
                vis_cnt--;
            }
        }
    }

    void addEdge(int x, int y) {
        if(visited[x] == 0 && visited[y] == 0){
            list<edg> queue;
            queue.push_back(edg(x, y));

            while(!queue.empty()){
                edg e = queue.front(); queue.pop_front();
                x = e.first, y = e.second;

                if(LA.level(x) < LA.level(y)){
                    swap(x, y);
                }

                int lca = LA.lca(x, y);
                int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);

                // cout<<"point 1"<<endl;

                if(lca == y){
                    if(x != anc_x) add_back_edge(anc_x, e);
                    continue;
                }

                // cout<<"point 2"<<endl;

                int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

                // if(LA.level(anc_x) < limit_k){ (sri) changed here - 2
                    for(auto &it: backEdge[anc_y]){ //(doubt) adding the backEdges of anc_y but, not reviewing them from anc_y to anc_x in set_backedges and also not erasing the backEdges list of anc_y
                        set_backEdges.erase({{-LA.level(anc_y), anc_y}, it});
                        add_back_edge(anc_x, it);
                    }
                    backEdge[anc_y].clear();
                    add_back_edge(anc_x, edg(anc_y, T.par(anc_y)));
                // }

                // cout<<"point 3"<<endl;

                if(T.par(anc_y) != -1){
                    T.remEdge(T.par(anc_y), anc_y);
                }

                queue.splice(queue.end(), reroot(anc_y, y));

                // cout<<"point 4"<<endl;

                if(x != -1) T.addEdge(x, y);

                int level_y  = (T.par(y) != -1)? LA.level(T.par(y))+1 : 1;
                check_subtree(y, level_y); // the levels may change and the set needs to be recalculated.
                LA.updateT(y);
            }

        }
    }

    int postPass() {
        // after processing all the edges; //to do
        for(int a = 0; a < T.getSize(); a++){
            if(comp_size[a] != 0 && visited[a] == 0){
                if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);


                visited[compEdg[a].second] = 1;
                vis_cnt++;
                // LA.updateT(compEdg[a].second); //(sri) necessary? //(doubt) this will ruin the algo  kadha?
                comp_size[a] = 0;
                comp[a] = 0;
                next_root[a] = 0;

                // updateComp(compEdg[a].second, compEdg[a].second, 0);
                updateComp(compEdg[a].second, compEdg[a].second, 0);
                LA.updateT(compEdg[a].second); //(sri) moved to down.
            }
        }

        set_backEdges.clear();

        if(vis_cnt == T.getSize()) return 1;
        else return 0;
    }
};