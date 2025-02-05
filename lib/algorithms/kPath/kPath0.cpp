// kpath without one pass heuristic + with nk space correction + with duplicates
#include <algorithm>
#include <functional>
#include "../../tree.cpp"
#include "kPathBase.h"
#define edg pair<int, int>
using namespace std;

class kPath0 : public kPathBase{

    vector<list<edg>> sptree;

public:

    kPath0 (int size,int spaceOpt) {
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

        /*for(int i=1;i<=size;i++)
        {
            sptree[0].push_back({0,i});
        }

        for(int i=0;i<=size;i++)
        {
            compL[0].push_back(i);
        }*/
        // compEdge[0] = {-1,0};

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
        // cout<<"root is: "<<root<<endl;
        vector<list<int>> ed(n);

        sptree[compN].splice(sptree[compN].end(), saved_edges[compN]); 
        // cout<<"edges"<<endl;
        for(auto &it: sptree[compN]){
            int u = it.first, v = it.second;
            // cout<<u<<" "<<v<<endl;
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

        // for(int i=0; i<n; i++){
        //     cout<<"child of "<<i<<": "<<endl;
        //     for(auto &it: child[i]){
        //         cout<<it<<" ";
        //     }
        //     cout<<endl; 
        // }

        function<void(int, int)> add_dfs_tree = [&](int a, int b){
            // level[b] = level[a]+1;
            // cout<<a<<" "<<b<<endl;
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

        // cout<<"adding tree done"<<endl;
        // for(auto &it: compL[compN]){
        //     processed[it] = 1;
        //     visited[it] = 1;
        // }
        
        compL[compN].clear();
        sptree[compN].clear();
        saved_edges[compN].clear();
    }

    int postpass() {
        for(int i=0; i<n; i++)
        {
            if(visited[i] == 0 && processed[i] == 0){
                post_processing(comp[i]);
            }
        }
        if(visC == n) return 1;
        return 0;
    }

    void processComp(int compN) {
        int root = compEdge[compN].second;
        vector<list<int>> ed(n);

        // sptree[compN].splice(sptree[compN].end(), saved_edges[compN]); 
        list<edg> edge_set = sptree[compN]; 
        edge_set.splice(edge_set.end(), saved_edges[compN]);

        // for(auto &it: edge_set) cout<<it.first<<" "<<it.second<<endl;
        // cout<<"ending edge_set"<<endl;


        list<int> comp_list = compL[compN];

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

        // cout<<"longest_path"<<endl;
        // for(auto &it: longest_path) cout<<it<<" ";
        // cout<<"ending lp"<<endl;

        int tmp_parent = compEdge[compN].first;
        for(auto a: longest_path){
            if(T.par(a) != -1) T.remEdge(T.par(a), a);
            if(tmp_parent != -1) T.addEdge(tmp_parent, a);
            visited[a]++;
            visC++;
            tmp_parent = a;
        }

        compL[compN].clear();

        for(auto a: comp_list){
            comp[a] = a;
            compEdge[a] = {-1, a};
            compL[a].push_back(a);
            processed[a] = 1;
            // if(visited[a] == 0 && !sptree[a].empty()) sptree[a].clear(); 
            if(!sptree[a].empty()) sptree[a].clear();
        }

        // compL[compN].push_back(compN);
        // compEdge[compN] = {-1, compN};
        // processed[compN] = 1;

        for(auto &it: edge_set){
            int u = it.first, v = it.second;
            process_edge(u, v);
        }

        sptree[compN].clear();
        saved_edges[compN].clear();
    }

    void process_edge(int u, int v) {
        int U = comp[u];
        int V = comp[v];
        if (visited[u] && visited[v]) {}
        else if (visited[u] == 0 && visited[v] == 0) {

            if(U == V) return;
            int final_comp = (compL[U].size() > compL[V].size())? U:V;
            int small_comp = (U + V) - final_comp;

            if(compEdge[U].first == -1) compEdge[final_comp] = compEdge[V];
            else if(compEdge[V].first == -1 || level[compEdge[U].first] > level[compEdge[V].first]){
                compEdge[final_comp] = compEdge[U];
            }
            else compEdge[final_comp] = compEdge[V];

            for(auto it: compL[small_comp]){
                comp[it] = final_comp;
                compL[final_comp].push_back(it);
            }

            for(auto it: sptree[small_comp]) sptree[final_comp].push_back(it);
            sptree[final_comp].push_back({u, v});

            compL[small_comp].clear();
            sptree[small_comp].clear();
        }
        else
        {
            if(visited[v]){
                swap(u, v);
                swap(V, U);
            }
            if(compEdge[V].first == -1 || level[compEdge[V].first] < level[u]) compEdge[V] = {u, v};
        }
    }

    void addEdge(int x, int y) {
        // cout<<x<<" "<<y<<endl;
        if(processed[x]==1 && processed[y]==1)
        {
            process_edge(x, y);
        }
        else if(visited[x]==0 && visited[y]==0)
        {
            saved_edges[comp[x]].push_back({x,y});
            if(saved_edges[comp[x]].size() >= compL[comp[x]].size()*(sopt - 1))
            {
                // cout<<"inside processComp"<<endl;
                processComp(comp[x]);
            }
        }
    }

    int addEdgeS(list<edg>& edges) override {
        prepass();
        if(pass == 1)
        {
            visC = 1;
            visited[0] = 1;
            for(int i=1; i<n; i++)
            {
                comp[i] = i;
                compEdge[i] = {0,i};
                compL[i].push_back(i);
                processed[i] = 1;
            }
        }
        for(auto it=edges.begin();it!=edges.end();it++){
            addEdge(it->first,it->second);
        }

        return postpass();
    }

    int processEdgeStream(ifstream& fileStream) override { // No artifical root & edges here
        prepass();

        if(pass == 1)
        {
            visC = 1;
            visited[0] = 1;
            for(int i=1; i<n; i++)
            {
                comp[i] = i;
                compEdge[i] = {0,i};
                compL[i].push_back(i);
                processed[i] = 1;
            }
        }

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
};