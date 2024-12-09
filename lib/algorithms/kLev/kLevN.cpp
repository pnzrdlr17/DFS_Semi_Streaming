// with one pass heuristic + with marked/unmarked + with nk space correction (backedges thing)
// with total nk space + with top path

// new code starts from below: klev with heuristic of adding more levels utilizing total nk space
// and added marked and unmarked criteria as well
// and added top path KLev Heuristic

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

class kLevN: public kLevBase{

    int limit_k, star_vertex;
    vector<int> is_stared;
    set<pair<pii, edg>> set_backEdges;

    void add_back_edge(int x, edg e) {

        if(LA.level(x) >= limit_k) return;
        if(T.par(x) != -1 && is_stared[T.par(x)] == 1) return;

        if(set_backEdges.size() >= T.getSize()*k){
            pair<pii, edg> pr = *set_backEdges.begin();
            limit_k = min(limit_k, (-pr.first.first)); 
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
                backEdge[it].clear(); 
            }
        }

        if(LA.level(x) < limit_k){
            backEdge[x].push_back(e);
            set_backEdges.insert({{-LA.level(x), x}, e});
        }
    }

    list<edg> reroot(int x, int y) {
        int z, t;
        list<edg> tmp_list;
        if(x == y) return tmp_list;
        z = T.par(y);
        T.remEdge(z, y);

        while(x!=y){
            tmp_list.splice(tmp_list.end(), backEdge[y]);
            for(auto &it:backEdge[y]){
                set_backEdges.erase({{-LA.level(y), y}, it});
            }
            backEdge[y].clear();
            t = T.par(z);
            if(t != -1) T.remEdge(t, z);
            T.addEdge(y, z);
            y = z;
            z = t;
        }
        return tmp_list;
    }

    void check_subtree(int x, int level_x) {
        int prev_level = LA.level(x);
        for(auto &it: backEdge[x]){
            set_backEdges.erase({{-prev_level, x}, it});
            if(level_x < limit_k) set_backEdges.insert({{-level_x, x}, it});
        }
        if(level_x >= limit_k) backEdge[x].clear();

        if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || level_x >= limit_k){ //(sri) suggestion here - 3.
            marked[x] = 1;
        }

        for(auto &it: T.getChild(x)){
            check_subtree(it, level_x+1);
        }
        // }
    }

    // remove backEdges of vertex x;
    void remove_backEdges(int x) {
        for(auto &ch: T.getChild(x)) {
            for(auto &it: backEdge[ch]) {
                set_backEdges.erase({{-LA.level(ch), ch}, it});
            }
            backEdge[ch].clear();
        }
    }

public:

    kLevN (int size, int space_optimality) {
        // cout<<"star vertex heuristic algo"<<endl;
        pass = 0;
        k = space_optimality;
        star_vertex = 0; //(sri) added here.

        backEdge.resize(size+1);
        comp.resize(size+1, 0);
        compEdg.resize(size+1);
        comp_size.resize(size+1, 0);
        next_root.resize(size+1, 0);
        marked.resize(size+1, 0);
        is_stared.resize(size+1, 0); //(sri) added here.

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
        is_stared[0] = 1; //(sri) added here.
        compEdg[0] = {-1, 0};

        LA = LevelAnc(T);
        visited[0] = 1;
        vis_cnt = 1;
    }


    void prePass(){
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

    void addEdge(int x, int y){
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

                if(lca == y){
                    if(x != anc_x) add_back_edge(anc_x, e);
                    continue;
                }

                int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

                for(auto &it: backEdge[anc_y]){ 
                    set_backEdges.erase({{-LA.level(anc_y), anc_y}, it});
                    add_back_edge(anc_x, it);
                }
                backEdge[anc_y].clear();
                add_back_edge(anc_x, edg(anc_y, T.par(anc_y)));


                if(T.par(anc_y) != -1){
                    T.remEdge(T.par(anc_y), anc_y);
                }

                queue.splice(queue.end(), reroot(anc_y, y));


                if(x != -1) T.addEdge(x, y);

                int level_y  = (T.par(y) != -1)? LA.level(T.par(y))+1 : 1;
                check_subtree(y, level_y); // the levels may change and the set needs to be recalculated.
                LA.updateT(y);

                if(star_vertex == lca){ //(sri) review here.
                    int curr = lca;
                    while(T.getChild(curr).size() == 1){
                        star_vertex = *T.getChild(curr).begin();
                        is_stared[star_vertex] = 1;
                        remove_backEdges(star_vertex);
                        curr = star_vertex;
                    }
                }
            }
        }
    }

    int postPass(){
        for(int a = 0; a < T.getSize(); a++){
            if(comp_size[a] != 0 && visited[a] == 0){
                if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);

                visited[compEdg[a].second] = 1;
                vis_cnt++;
                comp_size[a] = 0;
                comp[a] = 0;
                next_root[a] = 0;
                
                updateComp(compEdg[a].second, compEdg[a].second, 0);
                LA.updateT(compEdg[a].second); 
            }
        }
        
        set_backEdges.clear();

        if(vis_cnt == T.getSize()) return 1;
        else return 0;
    }

};