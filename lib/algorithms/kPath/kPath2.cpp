// new code starts from below : n(k+1) to n(k) and no duplicates // final code
// kpath with one pass heuristic + with nk space correction + with no duplicates
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include "kPathBase.h"
#include "../../tree.cpp"
#define edg pair<int, int>
using namespace std;

class kPath2 : public kPathBase{

    vector<set<edg>> sptree;

public:

    kPath2 (int size,int spaceOpt) {
        n = size+1;
        visited.resize(size+1,0);
        saved_edges.resize(size+1);
        pass = 0;
        T = Tree(size+1);
        T.setRoot(0);
        visC = 0;
        sopt = spaceOpt;
        compL.resize(size+1);
        comp.resize(size+1,0);
        compEdge.resize(size+1);
        level.resize(size+1);
        processed.resize(size+1);
        sptree.resize(size+1);


        for(int i=1;i<=size;i++)
        {
            T.addEdge(0,i);
        }

        for(int i=1;i<=size;i++)
        {
            sptree[0].insert({0, i});
        }

        for(int i=0;i<=size;i++)
        {
            compL[0].push_back(i);
        }

        for(int i=0; i<=size; i++){
            compEdge[i] = {-1, i};
        }
    }

    void prepass() {
        pass++;
        for(int i=0; i<n; i++) processed[i] = 0;
    }

    void post_processing(int compN) {
        int root = compEdge[compN].second;
        vector<list<int>> ed(n);

        for(auto it = sptree[compN].begin(); it != sptree[compN].end(); ){
            saved_edges[compN].push_back(*it);
            it = sptree[compN].erase(it);
        }

        for(auto &it: saved_edges[compN]){
            int u = it.first, v = it.second;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }

        vector<int> dfs_visited(n);
        vector<list<int>> child(n);

        function<void(int)> dfs = [&](int ind) -> void{
            dfs_visited[ind] = 1;
            for(auto it:ed[ind]){
                if(dfs_visited[it]) continue;
                child[ind].push_back(it);
                dfs(it);
            }
        };

        dfs(root);

        function<void(int, int)> add_dfs_tree = [&](int a, int b){
            processed[b] = 1;
            visited[b] = 1;
            visC++;
            if(T.par(b) != -1) T.remEdge(T.par(b), b);
            if(a != -1) T.addEdge(a, b);
            for(auto it: child[b]){
                level[it] = level[b]+1;
                add_dfs_tree(b, it);
            }
        };

        if(compEdge[compN].first == -1) level[root] = 1;
        else level[root] = level[compEdge[compN].first]+1;

        add_dfs_tree(compEdge[compN].first, root);

        compL[compN].clear();
        saved_edges[compN].clear();
    }

    int postpass() {
        for(int i=0; i<n; i++)
        {
            if(visited[i] == 0 && processed[i] == 0){
                post_processing(comp[i]);
            }
        }
       // cout << pass << " " << visC << endl;
        if(visC == n) return 1;
        return 0;
    }

    void processComp(int compN) {
        int root = compEdge[compN].second;
        vector<list<int>> ed(n);

        list<edg> edge_set;
        for(auto it = sptree[compN].begin(); it != sptree[compN].end(); ){
            edge_set.push_back(*it);
            it = sptree[compN].erase(it);
        }

        for(auto it = saved_edges[compN].begin(); it!=saved_edges[compN].end(); ){
            edge_set.push_back(*it);
            it = saved_edges[compN].erase(it);
        }

        list<int> comp_list;
        for(auto it = compL[compN].begin(); it != compL[compN].end(); ){
            comp_list.push_back(*it);
            it = compL[compN].erase(it);
        }

        for(auto &it: edge_set){
            int u = it.first, v = it.second;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }

        vector<int> par(n, root);
        level[root] = (compEdge[compN].first == -1)? 1 : level[compEdge[compN].first]+1;
        int max_depth = level[root], depth_node = root;
        vector<int> dfs_visited(n, 0);

        function<void(int)> dfs = [&](int ind) ->void{
            dfs_visited[ind] = 1;
            for(auto it: ed[ind]){
                if(dfs_visited[it]) continue;
                par[it] = ind;
                level[it] = level[ind]+1;
                if(max_depth < level[it]){
                    max_depth = level[it];
                    depth_node = it;
                }
                dfs(it);
            }
        };

        dfs(root);

        int curr = depth_node;
        vector<int> longest_path = {curr};
        while(curr != par[curr]){
            curr = par[curr];
            longest_path.push_back(curr);
        }
        reverse(longest_path.begin(),longest_path.end());

        int tmp_parent = compEdge[compN].first;
        for(auto a: longest_path){
            if(T.par(a) != -1) T.remEdge(T.par(a), a);
            if(tmp_parent != -1) T.addEdge(tmp_parent, a);
            visited[a]++;
            visC++;
            tmp_parent = a;
        }

        for(auto a: comp_list){
            comp[a] = a;
            compEdge[a] = {-1, a};
            compL[a].push_back(a);
            processed[a] = 1;
        }

        for(auto &it: edge_set){
            int u = it.first, v = it.second;
            process_edge(u, v);
        }
    }

    void process_edge(int u, int v) {
        int U = comp[u];
        int V = comp[v];
        if(visited[u]^visited[v]){ // one is visited and other is not visited.
            if(visited[v]){
                swap(u, v);
                swap(V, U);
            }
            if(compEdge[V].first == -1 || level[compEdge[V].first] < level[u]) compEdge[V] = {u, v};
        }
        else if(visited[u] == 0 && visited[v] == 0)
        {

            if(U == V) return;
            int final_comp = (compL[U].size() > compL[V].size())? U:V;
            int small_comp = (U + V) - final_comp;

            if(compEdge[U].first == -1) compEdge[final_comp] = compEdge[V];
            else if(compEdge[V].first == -1 || level[compEdge[U].first] > level[compEdge[V].first]){
                compEdge[final_comp] = compEdge[U];
            }
            else compEdge[final_comp] = compEdge[V];

            for(auto it = compL[small_comp].begin(); it!=compL[small_comp].end(); ){
                comp[*it] = final_comp;
                compL[final_comp].push_back(*it);
                it = compL[small_comp].erase(it);
            }

            for(auto it = sptree[small_comp].begin(); it != sptree[small_comp].end(); ){
                sptree[final_comp].insert(*it);
                it = sptree[small_comp].erase(it);
            }
            // sptree[small_comp].insert({u, v}); //(sri) corrected
            sptree[final_comp].insert({u, v});
        }
    }

    void addEdge(int x, int y) {
        if(processed[x]==1 && processed[y]==1)
        {
            process_edge(x, y);
        }
        else if(visited[x]==0 && visited[y]==0)
        {
            if(sptree[comp[x]].find({x, y}) == sptree[comp[x]].end()) saved_edges[comp[x]].push_back({x,y}); 
            if(saved_edges[comp[x]].size()+sptree[comp[x]].size() >= compL[comp[x]].size()*sopt) 
            {
                processComp(comp[x]);
            }
        }
    }
};