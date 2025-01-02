/*
// without one pass + with marked/unmarked heuristic + with nk space correction (backedges thing)
// without total nk space + without top path

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// using namespace std;
// #include "../lib/levelAnc.cpp"

// #define edg pair<int, int>

// class k_lev{
//     Tree T;
//     LevelAnc LA;

//     int pass;
//     int k;
//     int art_root;
//     int vis_cnt;
//     vector<int> visited;

//     vector<int> next_root;
//     vector<edg> compEdg;
//     vector<list<int>> compL; 
//     vector<int> comp, comp_size;
//     vector<list<edg>> backEdge;
//     vector<int> marked;

//     void makeTree(int x, int y){
//         if( (visited[x]==1 && visited[y]==0) || (visited[y]==1 && visited[x]==0)){
//             if(visited[x] == 0) swap(x, y);

//             if(compEdg[comp[y]].first==-1 || LA.level(x)>LA.level(compEdg[comp[y]].first)){
//                 reroot(compEdg[comp[y]].second, y);
//                 compEdg[comp[y]] = edg(x, y);
//             }
//         }
//         else if(visited[x]==0 && visited[y]==0 && comp[x]!=comp[y]){
//             if(compL[comp[x]].size() < compL[comp[y]].size()){
//                 swap(x, y);
//             }
            
//             if(compEdg[comp[x]].first == -1 || (compEdg[comp[y]].first != -1 && 
//                 LA.level(compEdg[comp[y]].first) > LA.level(compEdg[comp[x]].first))){
//                 reroot(compEdg[comp[x]].second, x);
//                 T.addEdge(y, x);
//                 LA.updateT(x);
//                 compEdg[comp[x]] = compEdg[comp[y]];
//             }
//             else{
//                 reroot(compEdg[comp[y]].second, y);
//                 T.addEdge(x, y);
//                 LA.updateT(y);
//             }
//             int comp_y = comp[y];
//             for(auto it = compL[comp_y].begin(); it != compL[comp_y].end(); ){
//                 compL[comp[x]].push_back(*it);
//                 comp[*it] = comp[x];
//                 it = compL[comp_y].erase(it);
//             }
//         }
//     }

//     list<edg> reroot(int x, int y){
//         int z, t;
//         list<edg> tmp_list;
//         if(x == y) return tmp_list;

//         z = T.par(y);
//         T.remEdge(z, y);
        
//         while(x!=y){
//             tmp_list.splice(tmp_list.end(), backEdge[y]);
//             backEdge[y].clear(); 
//             t = T.par(z);
//             if(t != -1) T.remEdge(t, z);
//             T.addEdge(y, z);
//             y = z;
//             z = t;
//         }
//         return tmp_list;
//     }

//     void mark_vertices(int x){
//         if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || LA.level(x) > k)
//             marked[x] = 1;

//         if(LA.level(x) > k)
//             backEdge[x].clear();

//         for(auto &it: T.getChild(x)){
//             mark_vertices(it);
//         }
//     }

//     int updateComp(int x, int root, int flag){
//         int cnt = 0;
//         if(flag) cnt++;
//         backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             if(flag == 0){
//                 if(marked[it] == 1){
//                     comp[it] = it;
//                     next_root[it] = 1;
//                     compEdg[it] = edg(x, it);
//                     visited[it] =  1;
//                     vis_cnt++;
//                     comp_size[it] = updateComp(it, it, 1);
//                     marked[it] = 0;
//                 }
//                 else{
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp[it] = 0;
//                     comp_size[it] = 0;
//                     next_root[it] = 0; 
//                     updateComp(it, it, 0);
//                 }
//             }
//             else{
//                 comp[it] = root;
//                 cnt += updateComp(it, root, 1);
//                 marked[it] = 0;
//             }
//         }
//         return cnt;
//     }

// public:

//     k_lev(int size, int space_optimality){
//         pass = 0;
//         k = space_optimality;
        
//         backEdge.resize(size+1);
//         marked.resize(size+1, 0);
//         comp.resize(size+1, 0);
//         compEdg.resize(size+1);
//         comp_size.resize(size+1, 0);
//         next_root.resize(size+1, 0);
//         compL.resize(size+1);

//         T = Tree(size+1);
//         visited.resize(size+1, 0);
//         art_root = 0;
//         T.setRoot(art_root);
        
//         LA = LevelAnc(T);
//         visited[0] = 1;
//         vis_cnt = 1;
//     }

//     int addEdgeS(list<edg> &edgAdd){
//         pass++;
//         pre_pass();
//         for(auto &it: edgAdd){
//             addEdge(it.first, it.second);
//         }
//         return post_pass();
//     }

//     void pre_pass(){
//          for(int a = 0; a<T.getSize(); a++){
//             if(pass == 1){ 
//                 if(visited[a] == 0) compL[a].push_back(a); 
//                 comp[a] = a;
//                 compEdg[a] = edg(-1, a); 
//             }
//             else if(next_root[a] == 1 && comp_size[comp[a]] != 0){ 
//                 if(compEdg[comp[a]].first != -1) T.remEdge(compEdg[comp[a]].first, a);
//                 LA.updateT(a); 
//                 visited[a] = 0;
//                 vis_cnt--;
//             }
//         }
//     }

//     void addEdge(int x, int y){
//         if(pass == 1){
//             makeTree(x, y);
//         }
//         else if(visited[x] == 0 && visited[y] == 0){
//             list<edg> queue;
//             queue.push_back(edg(x, y));

//             while(!queue.empty()){
//                 edg e = queue.front(); queue.pop_front();
//                 x = e.first, y = e.second;

//                 if(LA.level(x) < LA.level(y)){
//                     swap(x, y);
//                 }

//                 int lca = LA.lca(x, y);
//                 int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);

//                 if(lca == y){
//                     if(LA.level(anc_x) <= k && marked[anc_x] == 0 && x != anc_x)
//                         backEdge[anc_x].push_back(e);
//                     continue;
//                 }
                
//                 int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

//                 if(LA.level(anc_x) <= k && marked[anc_x] == 0){
//                     backEdge[anc_x].splice(backEdge[anc_x].end(), backEdge[anc_y]);
//                     backEdge[anc_x].push_back(edg(anc_y, T.par(anc_y)));
//                 }

//                 if(T.par(anc_y) != -1){
//                     T.remEdge(T.par(anc_y), anc_y);
//                 }
                
//                 queue.splice(queue.end(), reroot(anc_y, y));

//                 if(x != -1) T.addEdge(x, y);
//                 LA.updateT(y);
//                 mark_vertices(y); 
//             }
//         }
//     }

//     int post_pass(){
//         for(int a=0; a<T.getSize(); a++){
//             if(pass == 1){
//                 if(!compL[a].empty()){ 
//                     if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);
//                     visited[compEdg[a].second] = 1;
//                     vis_cnt++;
//                     next_root[compEdg[a].second] = 1;
//                     LA.updateT(compEdg[a].second);
//                     comp_size[a] = compL[a].size();
//                     compL[a].clear();
//                 }
//             }
//             else if(next_root[a] == 1 && visited[a] == 0){ // visited[a] == 0 is must here
//                     if(compEdg[comp[a]].first != -1) T.addEdge(compEdg[comp[a]].first, a);
//                     visited[a] = 1;
//                     vis_cnt++;
//                     LA.updateT(a); 
//                     comp_size[comp[a]] = 0; 
//                     comp[a] = 0;
//                     next_root[a] = 0;
//                     updateComp(a, a, 0);
//             }
//         }
//         if(vis_cnt == T.getSize()) return 1;
//         else return 0;
//     }


//     int getPass()
//     {
//         return pass;
//     }

//     Tree getT()
//     {
//         return T;
//     }
// };


// with one pass heuristic + with marked/unmarked + without nk space correction (backedges thing)
// without total nk space + without top path

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// using namespace std;
// #include "../lib/levelAnc.cpp"

// #define edg pair<int, int>

// class k_lev{
//     Tree T;
//     LevelAnc LA;

//     int pass;
//     int k;
//     int art_root;
//     int vis_cnt;
//     vector<int> visited;

//     vector<int> next_root;
//     // vector<list<int>> compL;
//     vector<edg> compEdg;
//     vector<int> comp, comp_size;
//     vector<list<edg>> backEdge;
//     vector<int> marked;

//     int first; 

//     list<edg> reroot(int x, int y){
//         int z, t;
//         list<edg> tmp_list;
//         if(x == y) return tmp_list;

//         z = T.par(y);
//         T.remEdge(z, y);
        
//         while(x!=y){
//             if(z != x) tmp_list.splice(tmp_list.end(), backEdge[z]);
//             backEdge[z].clear();
//             t = T.par(z);
//             if(t != -1) T.remEdge(t, z);
//             T.addEdge(y, z);
//             y = z;
//             z = t;
//         }
//         return tmp_list;
//     }

//     void mark_vertices(int x){
//         if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || LA.level(x) > k)
//             marked[x] = 1;
//         if(marked[x] == 1)
//             backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             mark_vertices(it);
//         }
//     }

//     int updateComp(int x, int root, int flag){
//         int cnt = 0;
//         if(flag) cnt++;
//         backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             if(flag == 0){
//                 if(marked[it] == 1){
//                     comp[it] = it;
//                     next_root[it] = 1;
//                     compEdg[it] = edg(x, it);
//                     visited[it] =  1;
//                     vis_cnt++;
//                     comp_size[it] = updateComp(it, it, 1);
//                     marked[it] = 0;
//                 }
//                 else{
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp[it] = 0;
//                     comp_size[it] = 0;
//                     next_root[it] = 0; // ig not needed
//                     updateComp(it, it, 0);
//                 }
//             }
//             else{
//                 comp[it] = root;
//                 cnt += updateComp(it, root, 1);
//                 marked[it] = 0;
//             }
//         }
//         return cnt;
//     }

// public:

//     k_lev(int size, int space_optimality){
//         pass = 0;
//         k = space_optimality;
        
//         backEdge.resize(size+1);
//         marked.resize(size+1, 0);
//         comp.resize(size+1, 0);
//         compEdg.resize(size+1);
//         comp_size.resize(size+1, 0);
//         next_root.resize(size+1, 0);

//         T = Tree(size+1);
//         visited.resize(size+1, 0);
//         art_root = 0;
//         T.setRoot(art_root);
        
//         for(int i=1; i<=size; i++){ //(sri) i<size is changed to <=
//             T.addEdge(0, i);
//             comp[i] = 0;
//         }
//         comp_size[0] = size+1;
//         next_root[0] = 1;
//         compEdg[0] = {-1, 0};

//         LA = LevelAnc(T);
//         visited[0] = 1;
//         vis_cnt = 1;
//     }

//     int addEdgeS(list<edg> &edgAdd){
//         pre_pass();
//         for(auto &it: edgAdd){
//             addEdge(it.first, it.second);
//         }
//         pass++;
//         return post_pass();
//     }

//     void pre_pass(){
//         for(int a = 0; a<T.getSize(); a++){
//             if(comp_size[a]){
// 				// printf("A Component %d:%lu;(%d,%d)\n", a, comp_size[a], compEdg[a].first, compEdg[a].second);
//             }                
//         }
//         for(int a = 0; a<T.getSize(); a++){
//             if(next_root[a] == 1 && comp_size[a] != 0){
//                 if(compEdg[a].first != -1) T.remEdge(compEdg[a].first, compEdg[a].second);
//                 LA.updateT(compEdg[a].second);
//                 visited[a] = 0;
//                 vis_cnt--;
//             }
//         }
//     }

//     void addEdge(int x, int y){
//         if(visited[x] == 0 && visited[y] == 0){
//             // printf("Add edge (%d,%d)=%d,%d\n", x, y, visited[x], visited[y]);

//             list<edg> queue, tmp_queue;
//             queue.push_back(edg(x, y));

//             while(!queue.empty()){
//                 edg e = queue.front(); queue.pop_front();
//                 x = e.first, y = e.second;

//                 if(LA.level(x) < LA.level(y)){
//                     swap(x, y);
//                 }

//                 int lca = LA.lca(x, y);
//                 int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);


//                 if(lca == y){
//                     if(!marked[anc_x] && x != anc_x) // (sri) second condition is added 
//                         backEdge[anc_x].push_back(e);
//                     continue;
//                 }
                
//                 int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

//                 if(!marked[anc_x]){
//                     backEdge[anc_x].splice(backEdge[anc_x].end(), backEdge[anc_y]);
//                     backEdge[anc_x].push_back(edg(anc_y, T.par(anc_y)));
//                 }

//                 if(T.par(anc_y) != -1){
//                     T.remEdge(T.par(anc_y), anc_y);
//                 }
                
//                 queue.splice(queue.end(), reroot(anc_y, y));

//                 if(x != -1) T.addEdge(x, y);
//                 LA.updateT(y);
//                 mark_vertices(y); 
//             }
//         }
//     }

//     int post_pass(){
//         for(int a=0; a<T.getSize(); a++){
//             if(comp_size[a] != 0 && visited[a] == 0){
// 				// printf("B Component %d:%lu;(%d,%d) %d\n", a, comp_size[a], compEdg[a].first, compEdg[a].second, comp[a]);
//                 if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);
//                 visited[compEdg[a].second] = 1;
//                 vis_cnt++;
//                 LA.updateT(compEdg[a].second);
//                 comp_size[a] = 0;
//                 comp[a] = 0;
//                 next_root[a] = 0;
//                 updateComp(compEdg[a].second, compEdg[a].second, 0);
//             }
//         }
//         // cout<<"post_pass"<<endl;
//         // T.printT(0);
//         if(vis_cnt == T.getSize()) return 1;
//         else return 0;
//     }

//     int getPass()
//     {
//         return pass;
//     }

//     Tree getT()
//     {
//         return T;
//     }
// };



// with one pass heuristic + with marked/unmarked + with nk space correction (backedges thing)
// without total nk space + without top path


// some important points:
// at the beginning of a pass, unvisited components are formed.
// the new root of the tree for this component is fixed in previous pass which is visited but will make it unvisited in prepass() function.
// all the vertices of the component are labeled with root vertex mentioned above.

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// using namespace std;
// #include "../lib/levelAnc.cpp"

// #define edg pair<int, int>

// class k_lev{
//     Tree T;
//     LevelAnc LA;

//     int pass;
//     int k;
//     int art_root;
//     int vis_cnt;
//     vector<int> visited;

//     vector<int> next_root;
//     // vector<list<int>> compL;
//     vector<edg> compEdg;
//     vector<int> comp, comp_size;
//     vector<list<edg>> backEdge;
//     vector<int> marked;

//     int first; 

//     list<edg> reroot(int x, int y){
//         int z, t;
//         list<edg> tmp_list;
//         if(x == y) return tmp_list;

//         z = T.par(y);
//         T.remEdge(z, y);
        
//         while(x!=y){
//             if(z != x) tmp_list.splice(tmp_list.end(), backEdge[z]);
//             backEdge[z].clear();
//             t = T.par(z);
//             if(t != -1) T.remEdge(t, z);
//             T.addEdge(y, z);
//             y = z;
//             z = t;
//         }
//         return tmp_list;
//     }

//     void mark_vertices(int x){
//         if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || LA.level(x) > k)
//             marked[x] = 1;

//         // if(marked[x] == 1) //change here
//         //     backEdge[x].clear();

//         if(LA.level(x) > k)
//             backEdge[x].clear();

//         for(auto &it: T.getChild(x)){
//             mark_vertices(it);
//         }
//     }

//     int updateComp(int x, int root, int flag){
//         int cnt = 0;
//         if(flag) cnt++;
//         backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             if(flag == 0){
//                 if(marked[it] == 1){
//                     comp[it] = it;
//                     next_root[it] = 1;
//                     compEdg[it] = edg(x, it);
//                     visited[it] =  1;
//                     vis_cnt++;
//                     comp_size[it] = updateComp(it, it, 1);
//                     marked[it] = 0;
//                 }
//                 else{
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp[it] = 0;
//                     comp_size[it] = 0;
//                     next_root[it] = 0; // ig not needed
//                     updateComp(it, it, 0);
//                 }
//             }
//             else{
//                 comp[it] = root;
//                 cnt += updateComp(it, root, 1);
//                 marked[it] = 0;
//             }
//         }
//         return cnt;
//     }

// public:

//     k_lev(int size, int space_optimality){
//         pass = 0;
//         k = space_optimality;
        
//         backEdge.resize(size+1);
//         marked.resize(size+1, 0);
//         comp.resize(size+1, 0);
//         compEdg.resize(size+1);
//         comp_size.resize(size+1, 0);
//         next_root.resize(size+1, 0);

//         T = Tree(size+1);
//         visited.resize(size+1, 0);
//         art_root = 0;
//         T.setRoot(art_root);
        
//         for(int i=1; i<=size; i++){ //(sri) i<size is changed to <=
//             T.addEdge(0, i);
//             comp[i] = 0;
//         }
//         comp_size[0] = size+1;
//         next_root[0] = 1;
//         compEdg[0] = {-1, 0};

//         LA = LevelAnc(T);
//         visited[0] = 1;
//         vis_cnt = 1;
//     }

//     int addEdgeS(list<edg> &edgAdd){
//         pre_pass();
//         for(auto &it: edgAdd){
//             addEdge(it.first, it.second);
//         }
//         pass++;
//         return post_pass();
//     }

//     void pre_pass(){
//         for(int a = 0; a<T.getSize(); a++){
//             if(comp_size[a]){
// 				// printf("A Component %d:%lu;(%d,%d)\n", a, comp_size[a], compEdg[a].first, compEdg[a].second);
//             }                
//         }
//         for(int a = 0; a<T.getSize(); a++){
//             if(next_root[a] == 1 && comp_size[a] != 0){
//                 if(compEdg[a].first != -1) T.remEdge(compEdg[a].first, compEdg[a].second);
//                 LA.updateT(compEdg[a].second); // this is important, as it reassigns the levels with compEdg[a].second as level 0.
//                 visited[a] = 0;
//                 vis_cnt--;
//             }
//         }
//     }

//     void addEdge(int x, int y){
//         if(visited[x] == 0 && visited[y] == 0){
//             // printf("Add edge (%d,%d)=%d,%d\n", x, y, visited[x], visited[y]);

//             list<edg> queue, tmp_queue;
//             queue.push_back(edg(x, y));

//             while(!queue.empty()){
//                 edg e = queue.front(); queue.pop_front();
//                 x = e.first, y = e.second;

//                 if(LA.level(x) < LA.level(y)){
//                     swap(x, y);
//                 }

//                 int lca = LA.lca(x, y);
//                 int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);


//                 // if(lca == y){
//                 //     if(!marked[anc_x] && x != anc_x) // (sri) second condition is added //(change here)
//                 //         backEdge[anc_x].push_back(e);
//                 //     continue;
//                 // }

//                 if(lca == y){
//                     if(LA.level(anc_x) <= k && x != anc_x)
//                         backEdge[anc_x].push_back(e);
//                     continue;
//                 }
                
//                 int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

//                 // if(!marked[anc_x]){ // change here
//                 //     backEdge[anc_x].splice(backEdge[anc_x].end(), backEdge[anc_y]);
//                 //     backEdge[anc_x].push_back(edg(anc_y, T.par(anc_y)));
//                 // }

//                 if(LA.level(anc_x) <= k){
//                     backEdge[anc_x].splice(backEdge[anc_x].end(), backEdge[anc_y]);
//                     backEdge[anc_x].push_back(edg(anc_y, T.par(anc_y)));
//                 }

//                 if(T.par(anc_y) != -1){
//                     T.remEdge(T.par(anc_y), anc_y);
//                 }
                
//                 queue.splice(queue.end(), reroot(anc_y, y));

//                 if(x != -1) T.addEdge(x, y);
//                 LA.updateT(y);
//                 mark_vertices(y); 
//             }
//         }
//     }

//     int post_pass(){
//         for(int a=0; a<T.getSize(); a++){
//             if(comp_size[a] != 0 && visited[a] == 0){
// 				// printf("B Component %d:%lu;(%d,%d) %d\n", a, comp_size[a], compEdg[a].first, compEdg[a].second, comp[a]);
//                 if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);
//                 visited[compEdg[a].second] = 1;
//                 vis_cnt++;
//                 LA.updateT(compEdg[a].second); //(sri) necessary?
//                 comp_size[a] = 0;
//                 comp[a] = 0;
//                 next_root[a] = 0;
//                 updateComp(compEdg[a].second, compEdg[a].second, 0);
//             }
//         }
//         // cout<<"post_pass"<<endl;
//         // T.printT(0);
//         if(vis_cnt == T.getSize()) return 1;
//         else return 0;
//     }

//     int getPass()
//     {
//         return pass;
//     }

//     Tree getT()
//     {
//         return T;
//     }
// };


// with one pass heuristic + without marked/unmarked + with nk space correction (backedges thing)
// with total nk space + without top path


// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// using namespace std;
// #include "../lib/levelAnc.cpp"

// #define edg pair<int, int>
// #define pii pair<int, int>

// class k_lev{
//     Tree T;
//     LevelAnc LA;

//     int pass;
//     int k;
//     int art_root;
//     int vis_cnt;
//     int limit_k; //(sri)
//     vector<int> visited;

//     vector<int> next_root;
//     vector<edg> compEdg;
//     vector<int> comp, comp_size;
//     vector<list<edg>> backEdge;

//     set<pair<pii, edg>> set_backEdges;

//     void add_back_edge(int x, edg e){
//         //things we need to do while adding a backedge to a vertex; //to do
//         if(LA.level(x) >= limit_k) return;

//         if(set_backEdges.size() >= T.getSize()*k){
//             pair<pii, edg> pr = *set_backEdges.begin();
//             limit_k = min(limit_k, (-pr.first.first)); // (doubt) what is the reason for level-1? (changed here 1)
//             auto it = set_backEdges.begin();
//             set<int> removed_vertices;
//             while(it != set_backEdges.end()){
//                 int curr_level = -(*it).first.first;
//                 if(curr_level >= limit_k){
//                     removed_vertices.insert((*it).first.second);
//                     it = set_backEdges.erase(it);
//                 }
//                 else break;
//             }

//             for(auto &it: removed_vertices){
//                 backEdge[it].clear(); //(sri) check for errors. hint: expand if clear() won't work
//             }
//         }

//         if(LA.level(x) < limit_k){
//             backEdge[x].push_back(e);
//             set_backEdges.insert({{-LA.level(x), x}, e});
//         }
//     }

//     list<edg> reroot(int x, int y){ //review later //to do
//         int z, t;
//         list<edg> tmp_list;
//         if(x == y) return tmp_list;
//         //(doubt) not adding backedges of y to tmp_list...???
//         z = T.par(y);
//         T.remEdge(z, y);
            
//         while(x!=y){
//             tmp_list.splice(tmp_list.end(), backEdge[y]);
//             for(auto &it:backEdge[y]){
//                 set_backEdges.erase({{-LA.level(y), y}, it});
//             }
//             backEdge[y].clear();
//             // if(z != x){ //(sri) changed here - 2.
//             //     tmp_list.splice(tmp_list.end(), backEdge[z]);
//             //     for(auto &it: backEdge[z]){
//             //         set_backEdges.erase({{-LA.level(z), z}, it});
//             //     }
//             //     backEdge[z].clear();
//             // }
//             t = T.par(z);
//             if(t != -1) T.remEdge(t, z);
//             T.addEdge(y, z);
//             y = z;
//             z = t;
//         }
//         return tmp_list;
//     }

//     void check_subtree(int x, int level_x){
//         // subtree got changed and some levels might change;
//         int prev_level = LA.level(x);
//         if(prev_level < limit_k){
//             for(auto &it: backEdge[x]){
//                 set_backEdges.erase({{-prev_level, x}, it});
//                 if(level_x < limit_k) set_backEdges.insert({{-level_x, x}, it});
//             }
//             if(level_x >= limit_k) backEdge[x].clear(); //(sri) clear works;

//             for(auto &it: T.getChild(x)){
//                 check_subtree(it, level_x+1);
//             }
//         }
//         else return;
//     }

//     int updateComp(int x, int root, int flag){
//         int cnt = 0;
//         if(flag) cnt++;
        
//         backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             if(flag == 0){
//                 if(LA.level(it) < limit_k - 1){
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp[it] = 0;
//                     comp_size[it] = 0;
//                     next_root[it] = 0; //(sri) ig not needed
//                     updateComp(it, it, 0);
//                 }
//                 else{
//                     comp[it] = it;
//                     next_root[it] = 1;
//                     compEdg[it] = edg(x, it);
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp_size[it] = updateComp(it, it, 1);
//                 }
//             }
//             else{
//                 comp[it] = root;
//                 cnt += updateComp(it, root, 1);
//             }
//         }
//         return cnt;
//     }
    
// public:
    
//     k_lev(int size, int space_optimality){
//         pass = 0;
//         k = space_optimality;
        
//         backEdge.resize(size+1);
//         comp.resize(size+1, 0);
//         compEdg.resize(size+1);
//         comp_size.resize(size+1, 0);
//         next_root.resize(size+1, 0);

//         T = Tree(size+1);
//         visited.resize(size+1, 0);
//         art_root = 0;
//         T.setRoot(art_root);

//         for(int i=1; i<=size; i++){
//             T.addEdge(0, i);
//             comp[i] = 0;
//         }

//         comp_size[0] = size+1;
//         next_root[0] = 1;
//         compEdg[0] = {-1, 0};

//         LA = LevelAnc(T);
//         visited[0] = 1;
//         vis_cnt = 1;
//     }

//     int addEdgeS(list<edg> &edgAdd){
//         prepass();
//         for(auto &it: edgAdd){
//             addEdge(it.first, it.second);
//         }
//         pass++;
//         return post_pass();
//     }

//     void prepass(){
//         limit_k = INT_MAX;
//         for(int a=0; a<T.getSize(); a++){
//             if(next_root[a] == 1 && comp_size[a] != 0){
//                 if(compEdg[a].first != -1) T.remEdge(compEdg[a].first, compEdg[a].second);
//                 LA.updateT(compEdg[a].second);
//                 visited[a] = 0;
//                 vis_cnt--;
//             }
//         }
//     }

//     void addEdge(int x, int y){
//         if(visited[x] == 0 && visited[y] == 0){
//             list<edg> queue;
//             queue.push_back(edg(x, y));

//             while(!queue.empty()){
//                 edg e = queue.front(); queue.pop_front();
//                 x = e.first, y = e.second;

//                 if(LA.level(x) < LA.level(y)){
//                     swap(x, y);
//                 }

//                 int lca = LA.lca(x, y);
//                 int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);

//                 // cout<<"point 1"<<endl;

//                 if(lca == y){
//                     if(x != anc_x) add_back_edge(anc_x, e);
//                     continue;
//                 }

//                 // cout<<"point 2"<<endl;

//                 int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

//                 // if(LA.level(anc_x) < limit_k){ (sri) changed here - 2
//                     for(auto &it: backEdge[anc_y]){ //(doubt) adding the backEdges of anc_y but, not reviewing them from anc_y to anc_x in set_backedges and also not erasing the backEdges list of anc_y
//                         set_backEdges.erase({{-LA.level(anc_y), anc_y}, it});
//                         add_back_edge(anc_x, it);
//                     }
//                     backEdge[anc_y].clear();
//                     add_back_edge(anc_x, edg(anc_y, T.par(anc_y)));
//                 // }

//                 // cout<<"point 3"<<endl;

//                 if(T.par(anc_y) != -1){
//                     T.remEdge(T.par(anc_y), anc_y);
//                 }

//                 queue.splice(queue.end(), reroot(anc_y, y));

//                 // cout<<"point 4"<<endl;

//                 if(x != -1) T.addEdge(x, y);

//                 int level_y  = (T.par(y) != -1)? LA.level(T.par(y))+1 : 1;
//                 check_subtree(y, level_y); // the levels may change and the set needs to be recalculated.
//                 LA.updateT(y);
//             }

//         }
//     }

//     int post_pass(){
//         // after processing all the edges; //to do
//         for(int a = 0; a < T.getSize(); a++){
//             if(comp_size[a] != 0 && visited[a] == 0){
//                 if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);


//                 visited[compEdg[a].second] = 1;
//                 vis_cnt++;
//                 // LA.updateT(compEdg[a].second); //(sri) necessary? //(doubt) this will ruin the algo  kadha?
//                 comp_size[a] = 0;
//                 comp[a] = 0;
//                 next_root[a] = 0;
                
//                 // updateComp(compEdg[a].second, compEdg[a].second, 0);
//                 updateComp(compEdg[a].second, compEdg[a].second, 0);
//                 LA.updateT(compEdg[a].second); //(sri) moved to down.
//             }
//         }
        
//         set_backEdges.clear();

//         if(vis_cnt == T.getSize()) return 1;
//         else return 0;
//     }

//     int getPass()
//     {
//         return pass;
//     }

//     Tree getT()
//     {
//         return T;
//     }

// };


// with one pass heuristic + with marked/unmarked + with nk space correction (backedges thing)
// with total nk space + without top path

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// using namespace std;
// #include "../lib/levelAnc.cpp"

// #define edg pair<int, int>
// #define pii pair<int, int>

// class k_lev{
//     Tree T;
//     LevelAnc LA;

//     int pass;
//     int k;
//     int art_root;
//     int vis_cnt;
//     int limit_k; //(sri)
//     vector<int> visited;

//     vector<int> next_root;
//     vector<edg> compEdg;
//     vector<int> comp, comp_size;
//     vector<list<edg>> backEdge;

//     set<pair<pii, edg>> set_backEdges;
//     vector<int> marked;

//     void add_back_edge(int x, edg e){
//         //things we need to do while adding a backedge to a vertex; //to do
//         if(LA.level(x) >= limit_k) return;

//         if(set_backEdges.size() >= T.getSize()*k){
//             pair<pii, edg> pr = *set_backEdges.begin();
//             limit_k = min(limit_k, (-pr.first.first)); // (doubt) what is the reason for level-1? (changed here 1)
//             auto it = set_backEdges.begin();
//             set<int> removed_vertices;
//             while(it != set_backEdges.end()){
//                 int curr_level = -(*it).first.first;
//                 if(curr_level >= limit_k){
//                     removed_vertices.insert((*it).first.second);
//                     it = set_backEdges.erase(it);
//                 }
//                 else break;
//             }

//             for(auto &it: removed_vertices){
//                 backEdge[it].clear(); //(sri) check for errors. hint: expand if clear() won't work
//             }
//         }

//         if(LA.level(x) < limit_k){
//             backEdge[x].push_back(e);
//             set_backEdges.insert({{-LA.level(x), x}, e});
//         }
//     }

//     list<edg> reroot(int x, int y){ //review later //to do
//         int z, t;
//         list<edg> tmp_list;
//         if(x == y) return tmp_list;
//         //(doubt) not adding backedges of y to tmp_list...???
//         z = T.par(y);
//         T.remEdge(z, y);
            
//         while(x!=y){
//             tmp_list.splice(tmp_list.end(), backEdge[y]);
//             for(auto &it:backEdge[y]){
//                 set_backEdges.erase({{-LA.level(y), y}, it});
//             }
//             backEdge[y].clear();
//             // if(z != x){ //(sri) changed here - 2.
//             //     tmp_list.splice(tmp_list.end(), backEdge[z]);
//             //     for(auto &it: backEdge[z]){
//             //         set_backEdges.erase({{-LA.level(z), z}, it});
//             //     }
//             //     backEdge[z].clear();
//             // }
//             t = T.par(z);
//             if(t != -1) T.remEdge(t, z);
//             T.addEdge(y, z);
//             y = z;
//             z = t;
//         }
//         return tmp_list;
//     }

//     void check_subtree(int x, int level_x){ // subtree got changed and some levels might change;
//         int prev_level = LA.level(x);
//         // if(prev_level < limit_k){ //(sri) changed here - 3.
//         for(auto &it: backEdge[x]){
//             set_backEdges.erase({{-prev_level, x}, it});
//             if(level_x < limit_k) set_backEdges.insert({{-level_x, x}, it});
//         }
//         if(level_x >= limit_k) backEdge[x].clear(); //(sri) clear works;

//         if(marked[x] || (T.par(x) != -1 && marked[T.par(x)]) || level_x >= limit_k){ //(sri) suggestion here - 3.
//             marked[x] = 1;
//         }

//         for(auto &it: T.getChild(x)){
//             check_subtree(it, level_x+1);
//         }
//         // }
//     }

//     int updateComp(int x, int root, int flag){
//         int cnt = 0;
//         if(flag) cnt++;
        
//         backEdge[x].clear();
//         for(auto &it: T.getChild(x)){
//             if(flag == 0){
//                 if(marked[it] == 0){ //(sri) changed here - 3.
//                     visited[it] = 1;
//                     vis_cnt++;
//                     comp[it] = 0;
//                     comp_size[it] = 0;
//                     next_root[it] = 0; //(sri) ig not needed
//                     updateComp(it, it, 0);
//                 }
//                 else{
//                     comp[it] = it;
//                     next_root[it] = 1;
//                     compEdg[it] = edg(x, it);
//                     visited[it] = 1;
//                     vis_cnt++;
//                     marked[it] = 0;
//                     comp_size[it] = updateComp(it, it, 1);
//                 }
//             }
//             else{
//                 comp[it] = root;
//                 marked[it] = 0;
//                 cnt += updateComp(it, root, 1);
//             }
//         }
//         return cnt;
//     }
    
// public:
    
//     k_lev(int size, int space_optimality){
//         pass = 0;
//         k = space_optimality;
        
//         backEdge.resize(size+1);
//         comp.resize(size+1, 0);
//         compEdg.resize(size+1);
//         comp_size.resize(size+1, 0);
//         next_root.resize(size+1, 0);
//         marked.resize(size+1, 0);

//         T = Tree(size+1);
//         visited.resize(size+1, 0);
//         art_root = 0;
//         T.setRoot(art_root);

//         for(int i=1; i<=size; i++){
//             T.addEdge(0, i);
//             comp[i] = 0;
//         }

//         comp_size[0] = size+1;
//         next_root[0] = 1;
//         compEdg[0] = {-1, 0};

//         LA = LevelAnc(T);
//         visited[0] = 1;
//         vis_cnt = 1;
//     }

//     int addEdgeS(list<edg> &edgAdd){
//         prepass();
//         for(auto &it: edgAdd){
//             addEdge(it.first, it.second);
//         }
//         pass++;
//         return post_pass();
//     }

//     void prepass(){
//         limit_k = INT_MAX;
//         for(int a=0; a<T.getSize(); a++){
//             if(next_root[a] == 1 && comp_size[a] != 0){
//                 if(compEdg[a].first != -1) T.remEdge(compEdg[a].first, compEdg[a].second);
//                 LA.updateT(compEdg[a].second);
//                 visited[a] = 0;
//                 vis_cnt--;
//             }
//         }
//     }

//     void addEdge(int x, int y){
//         if(visited[x] == 0 && visited[y] == 0){
//             list<edg> queue;
//             queue.push_back(edg(x, y));

//             while(!queue.empty()){
//                 edg e = queue.front(); queue.pop_front();
//                 x = e.first, y = e.second;

//                 if(LA.level(x) < LA.level(y)){
//                     swap(x, y);
//                 }

//                 int lca = LA.lca(x, y);
//                 int anc_x = LA.la(x, LA.level(x) - LA.level(lca) - 1);

//                 // cout<<"point 1"<<endl;

//                 if(lca == y){
//                     if(x != anc_x) add_back_edge(anc_x, e);
//                     continue;
//                 }

//                 // cout<<"point 2"<<endl;

//                 int anc_y = LA.la(y, LA.level(y) - LA.level(lca) - 1);

//                 // if(LA.level(anc_x) < limit_k){ (sri) changed here - 2
//                     for(auto &it: backEdge[anc_y]){ //(doubt) adding the backEdges of anc_y but, not reviewing them from anc_y to anc_x in set_backedges and also not erasing the backEdges list of anc_y
//                         set_backEdges.erase({{-LA.level(anc_y), anc_y}, it});
//                         add_back_edge(anc_x, it);
//                     }
//                     backEdge[anc_y].clear();
//                     add_back_edge(anc_x, edg(anc_y, T.par(anc_y)));
//                 // }

//                 // cout<<"point 3"<<endl;

//                 if(T.par(anc_y) != -1){
//                     T.remEdge(T.par(anc_y), anc_y);
//                 }

//                 queue.splice(queue.end(), reroot(anc_y, y));

//                 // cout<<"point 4"<<endl;

//                 if(x != -1) T.addEdge(x, y);

//                 int level_y  = (T.par(y) != -1)? LA.level(T.par(y))+1 : 1;
//                 check_subtree(y, level_y); // the levels may change and the set needs to be recalculated.
//                 LA.updateT(y);
//             }

//         }
//     }

//     int post_pass(){
//         // after processing all the edges; //to do
//         for(int a = 0; a < T.getSize(); a++){
//             if(comp_size[a] != 0 && visited[a] == 0){
//                 if(compEdg[a].first != -1) T.addEdge(compEdg[a].first, compEdg[a].second);


//                 visited[compEdg[a].second] = 1;
//                 vis_cnt++;
//                 // LA.updateT(compEdg[a].second); //(sri) necessary? //(doubt) this will ruin the algo  kadha?
//                 comp_size[a] = 0;
//                 comp[a] = 0;
//                 next_root[a] = 0;
                
//                 // updateComp(compEdg[a].second, compEdg[a].second, 0);
//                 updateComp(compEdg[a].second, compEdg[a].second, 0);
//                 LA.updateT(compEdg[a].second); //(sri) moved to down.
//             }
//         }
        
//         set_backEdges.clear();

//         if(vis_cnt == T.getSize()) return 1;
//         else return 0;
//     }

//     int getPass()
//     {
//         return pass;
//     }

//     Tree getT()
//     {
//         return T;
//     }

// };


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
using namespace std;
#include "../lib/levelAnc.cpp"

#define edg pair<int, int>
#define pii pair<int, int>

class k_lev{
    Tree T;
    LevelAnc LA;

    int pass;
    int k;
    int art_root;
    int vis_cnt;
    int limit_k; 
    int star_vertex; //(sri) added here.
    
    vector<int> visited;

    vector<int> next_root;
    vector<edg> compEdg;
    vector<int> comp, comp_size;
    vector<list<edg>> backEdge;

    set<pair<pii, edg>> set_backEdges;
    vector<int> marked;
    vector<int> is_stared; //(sri) added here.

    void add_back_edge(int x, edg e){

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

    list<edg> reroot(int x, int y){ 
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

    void check_subtree(int x, int level_x){ 
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

    int updateComp(int x, int root, int flag){
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
    
    // remove backEdges of vertex x;
    void remove_backEdges(int x){
        for(auto &ch: T.getChild(x)){
            for(auto &it: backEdge[ch]){
                set_backEdges.erase({{-LA.level(ch), ch}, it});
            }
            backEdge[ch].clear();
        }
    }

public:
    
    k_lev(int size, int space_optimality){
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

    int addEdgeS(list<edg> &edgAdd){
        prepass();
        for(auto &it: edgAdd){
            addEdge(it.first, it.second);
        }
        pass++;
        return post_pass();
    }

    void prepass(){
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

    int post_pass(){
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

    int getPass()
    {
        return pass;
    }

    Tree getT()
    {
        return T;
    }

};
*/