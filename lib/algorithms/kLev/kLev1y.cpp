// with one pass heuristic + with marked/unmarked + without nk space correction (backedges thing)
// without total nk space + without top path

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

class kLev1y : public kLevBase{

    int first;

    list<edg> reroot(int x, int y) {
        int z, t;
        list<edg> tmp_list;
        if(x == y) return tmp_list;

        z = T.par(y);
        T.remEdge(z, y);
        
        while(x!=y){
            if(z != x) tmp_list.splice(tmp_list.end(), backEdge[z]);
            backEdge[z].clear();
            t = T.par(z);
            if(t != -1) T.remEdge(t, z);
            T.addEdge(y, z);
            y = z;
            z = t;
        }
        return tmp_list;
    }

    void mark_vertices(int x) {
        if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || LA.level(x) > k)
            marked[x] = 1;
        if(marked[x] == 1)
            backEdge[x].clear();
        for(auto &it: T.getChild(x)){
            mark_vertices(it);
        }
    }

public:

    kLev1y (int size, int space_optimality) {
        pass = 0;
        k = space_optimality;

        backEdge.resize(size+1);
        marked.resize(size+1, 0);
        comp.resize(size+1, 0);
        compEdg.resize(size+1);
        comp_size.resize(size+1, 0);
        next_root.resize(size+1, 0);

        T = Tree(size+1);
        visited.resize(size+1, 0);
        art_root = 0;
        T.setRoot(art_root);

        for(int i=1; i<=size; i++){ //(sri) i<size is changed to <=
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
        for(int a = 0; a<T.getSize(); a++){
            if(comp_size[a]){
				// printf("A Component %d:%lu;(%d,%d)\n", a, comp_size[a], compEdg[a].first, compEdg[a].second);
            }                
        }
        for(int a = 0; a<T.getSize(); a++){
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
            // printf("Add edge (%d,%d)=%d,%d\n", x, y, visited[x], visited[y]);

            list<edg> queue, tmp_queue;
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
                    if(!marked[anc_x] && x != anc_x) // (sri) second condition is added 
                        backEdge[anc_x].push_back(e);
                    continue;
                }
                
                int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

                if(!marked[anc_x]){
                    backEdge[anc_x].splice(backEdge[anc_x].end(), backEdge[anc_y]);
                    backEdge[anc_x].push_back(edg(anc_y, T.par(anc_y)));
                }

                if(T.par(anc_y) != -1){
                    T.remEdge(T.par(anc_y), anc_y);
                }
                
                queue.splice(queue.end(), reroot(anc_y, y));

                if(x != -1) T.addEdge(x, y);
                LA.updateT(y);
                mark_vertices(y); 
            }
        }
    }

    int postPass() {
        for(int a=0; a<T.getSize(); a++){
            if(comp_size[a] != 0 && visited[a] == 0){
				// printf("B Component %d:%lu;(%d,%d) %d\n", a, comp_size[a], compEdg[a].first, compEdg[a].second, comp[a]);
                if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);
                visited[compEdg[a].second] = 1;
                vis_cnt++;
                LA.updateT(compEdg[a].second);
                comp_size[a] = 0;
                comp[a] = 0;
                next_root[a] = 0;
                updateComp(compEdg[a].second, compEdg[a].second, 0);
            }
        }
        // cout<<"post_pass"<<endl;
        // T.printT(0);
        if(vis_cnt == T.getSize()) return 1;
        else return 0;
    }
};
