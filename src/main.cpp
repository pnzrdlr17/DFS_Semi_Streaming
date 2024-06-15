#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include "simp.cpp"
#include "improv.cpp"
#include "k_lev.cpp"
#include "kpath.cpp"
#include "../lib/verifydfs.cpp"
#include "comp_params.cpp"

using namespace std;

#define ll long long int
#define edg pair<int, int>

// #define PRINTTREE
#define VERIFYDFS
// #define PRINTREALHEIGHT
// #define PRINTREALCOMPSIZEPARAMS
#define PRINTRANDHEIGHT
#define PRINTRANDCOMPSIZEPARAMS

#ifdef REAL
int n, m, algoType, opt, spaceOpt;
string filePath;
#else
int n, m, spars, tst, algoType, opt, spaceOpt;
#endif


#define GET_SPOPT(x) 	\
	if(argc>x) spaceOpt= atoi(argv[x]);

#ifdef REAL
	#define GET_ARGS() 	\
	n = atoi(argv[1]); \
    m = atoi(argv[2]); \
    filePath = argv[3]; \
    algoType = atoi(argv[4]); \
    opt = atoi(argv[5]); \
	GET_SPOPT(6)

#else
	#define GET_ARGS() 	\
	n = atoi(argv[1]); \
    spars = atoi(argv[2]); \
    tst = atoi(argv[3]); \
    algoType = atoi(argv[4]); \
    opt = atoi(argv[5]); \
	GET_SPOPT(6)
#endif




list<edg> edgS;


int edgSpars(int n,int i)
{
    int ans =0;
    if(i==0) ans = 2*n;
    if(i==1) ans = 5*n;
    if(i==2) ans = n*log2(n);
    if(i==3) ans = n*sqrt(n);
    if(i>3) ans = n*(n-1)/2;
    return ans;
}


int findsimpDFS()
{   

    DFSSimp simpdfs = DFSSimp(n, opt);

    while (1)
    {

        int ans = simpdfs.addEdgeS(edgS);
        if (ans)
            break;
    }

    #ifdef PRINTTREE
    cout << "TREE : " << endl;
    simpdfs.getT().printT(0);
    printf("\n");
    #endif

    #ifdef PRINTREALHEIGHT
    cout << "HEIGHT : " << endl;
    cout << simpdfs.getT().getHeight(0);
    printf("\n");
    #endif


    #ifdef VERIFYDFS
    if(verifyDFS(edgS,simpdfs.getT())) cout << "VALID DFS Tree" << endl;
    else cout << "INVALID DFS Tree" << endl;
    #endif

    return simpdfs.getPass();
}

int findimprovDFS()
{

    DFSImprov improvdfs = DFSImprov(n);

    while (1)
    {

        int ans = improvdfs.addEdgeS(edgS);
        if (ans)
            break;
    }

    #ifdef PRINTTREE
    cout << "TREE : " << endl;
    improvdfs.getT().printT(0);
    printf("\n");
    #endif

    #ifdef PRINTREALHEIGHT
    cout << "HEIGHT : " << endl;
    cout << improvdfs.getT().getHeight(0);
    printf("\n");
    #endif

    #ifdef VERIFYDFS
    if(verifyDFS(edgS,improvdfs.getT())) cout << "VALID DFS Tree" << endl;
    else cout << "INVALID DFS Tree" << endl;
    #endif

    return improvdfs.getPass();
}

int findkpathDFS()
{
    k_path kPathDFS = k_path(n, spaceOpt);

    while(1)
    {
        int ans = kPathDFS.addEdgeS(edgS);
        if(ans) break;
    }

    #ifdef PRINTTREE
    cout << "TREE : " << endl;
    kPathDFS.getT().printT(0);
    printf("\n");
    #endif

    #ifdef PRINTREALHEIGHT
    cout << "HEIGHT : " << endl;
    cout << kPathDFS.getT().getHeight(0);
    printf("\n");
    #endif
    
    #ifdef VERIFYDFS
    if(verifyDFS(edgS,kPathDFS.getT())) cout << "VALID DFS Tree" << endl;
    else cout << "INVALID DFS Tree" << endl;
    #endif

    return kPathDFS.getPass();
}

int findklevDFS()
{
    
    k_lev kLevDFS = k_lev(n, spaceOpt);

    while(1){
        int ans = kLevDFS.addEdgeS(edgS);
        if(ans) break;
    }
    
    #ifdef PRINTTREE
    cout << "TREE : " << endl;
    kLevDFS.getT().printT(0);
    printf("\n");
    #endif

    #ifdef PRINTREALHEIGHT
    cout << "HEIGHT : " << endl;
    cout << kLevDFS.getT().getHeight(0);
    printf("\n");
    #endif

    #ifdef VERIFYDFS
    if(verifyDFS(edgS,kLevDFS.getT())) cout << "VALID DFS Tree" << endl;
    else cout << "INVALID DFS Tree" << endl;
    #endif

    return kLevDFS.getPass();
}


void getAllRandomEdges(int vertc,int edgec){


    edgS.clear();

    for (int i = 1; i <= vertc; i++)
    {
        edgS.push_back(edg(0, i));
    } // making disconnected graph connected

    int i,j,c=0;

    int (*edS)[2]=NULL;
    edS = (int (*)[2])calloc(vertc*vertc,sizeof(edS));

    c=0;
    for(i=1;i<=vertc;i++)
    {
        for(j=i+1;j<=vertc;j++)
        {
            if(i==j) continue;
            edS[c][0]=i;	edS[c][1]=j;
            c++;
        }
    }

    int e1,e2;
    while(c&&edgec)
    {
        i = rand()%(c);
        e1 = edS[c-1][0];
        e2 = edS[c-1][1];
        edS[c-1][0] = edS[i][0];
        edS[c-1][1] = edS[i][1];
        edS[i][0] = e1;	
        edS[i][1] = e2;	
        // edgS.push_back(edg(e1,e2));
        edgS.push_back(edg(edS[c-1][0],edS[c-1][1]));
        c--; edgec--;
    }
    
    free(edS);

    // cout << edgS.size() << endl;
    // for(auto it=edgS.begin();it!=edgS.end();it++){
    //     cout << "( "<<it->first << "," << it->second << " )" << ", ";
    // }
    // cout << endl;
}


class segtree{
public:
    ll size;
    vector<ll> val;

    segtree(ll n){
        size = 1;
        while(size < n) size*=2;
        val.assign(2*size, 0LL);
    }

    void set(ll i, ll v){
        set(i, v, 0, 0, size);
    }
    
    void set(ll i, ll v, ll x, ll lx, ll rx){
        if(lx == rx-1){
            val[x] = v;
            return;
        }
        ll mid = (lx+rx)/2;
        if(i < mid) set(i, v, 2*x+1, lx, mid);
        else set(i, v, 2*x+2, mid, rx);
        val[x] = val[2*x+1]+val[2*x+2];
    }

    ll get(ll l, ll r){
        return get(l, r, 0, 0, size);
    }

    ll get(ll l, ll r, ll x, ll lx, ll rx){
        if(rx <= l || r <= lx) return 0;
        if(l <= lx && rx <= r) return val[x];
        ll mid = (lx+rx)/2;
        return get(l, r, 2*x+1, lx, mid)+get(l, r, 2*x+2, mid, rx);
    }
};


int select_node_by_probability(segtree &st,ll num_vertices) {
  
    ll lval=st.get(0,num_vertices);
    double random_value = rand() % lval;

    ll fval=st.get(0,1);

    while(random_value<fval) random_value = rand() % lval;
    ll low=0;
    ll high=num_vertices-1;

    while(high-low>1){
        ll mid=(low+high)/2;
        if(random_value>=st.get(0,mid+1)) low=mid;
        else high=mid-1;
    }

    if(st.get(0,high+1)<=random_value) return high;
    if(st.get(0,low+1)<=random_value) return low;
    

    return num_vertices-1;
}




void getAllPowLawRandomEdges(ll vertc,ll edgec){


    edgS.clear();

    for (int i = 1; i <= vertc; i++)
    {
        edgS.push_back(edg(0, i));
    } // making disconnected graph connected
  
    ll num_vertices =  vertc , num_edges = edgec ;
    

    vector<vector<ll>> graph(num_vertices,vector<ll> ());
    set<pair<ll,ll>> edge_visited;

    double exponent = 3;

    segtree st(num_vertices);

    ll val=0;
    for (ll j = 0; j < num_vertices; ++j) {      
            ll expval=graph[j].size()+1;
            val=(expval*expval*expval);
            st.set(j,val);
        }

    for (ll i = 0; i < num_edges; ++i) {

        ll node1 = select_node_by_probability(st,num_vertices);
        ll node2 = select_node_by_probability(st,num_vertices);

        if(node1 == node2 || edge_visited.count(make_pair(node1,node2))!=0) {
            i--;
        } else{
            graph[node1].push_back(node2);
            graph[node2].push_back(node1);
            edge_visited.insert(make_pair(node1,node2));
            edge_visited.insert(make_pair(node2,node1));
            
            ll node1_bf=st.get(node1,node1+1);
            ll eexp = (int)(ceil(pow(node1_bf,0.33)))+1;
            st.set(node1, eexp*eexp*eexp);

            ll node2_bf=st.get(node2,node2+1);
            eexp = (int)(ceil(pow(node2_bf,0.33)))+1;
            st.set(node2,eexp*eexp*eexp);

        }

    }

        set<pair<ll,ll>> edgs;
        set<ll> degrees;
        for (ll i = 0; i < num_vertices; ++i) {
            degrees.insert(graph[i].size());
            for (ll neighbor : graph[i]) {
                if(edgs.count(make_pair(neighbor,i))==0){
                    edgs.insert(make_pair(i,neighbor));
                }
            }
        }
        vector<pair<ll,ll>> edges(edgs.begin(),edgs.end());

        // cout << edges.size() << endl;
        for(int i=0;i<edges.size();i++){
            edgS.push_back(edg(edges[i].first,edges[i].second));
        }

        set<pair<ll,ll>> degreepairs;

        for(auto it=degrees.begin();it!=degrees.end();it++){
            ll reqdeg=*it;
            ll cnt=0;
            for(ll i=0;i<num_vertices;i++){
                if(graph[i].size()==reqdeg) cnt++;
            }
            degreepairs.insert(make_pair(reqdeg,cnt));

        }

        // for(auto it=degreepairs.begin();it!=degreepairs.end();it++){
        //     cout << "Degree : " << it->first+1 << " No of vertices : " << it->second << endl;
        // }
        // cout << endl;

}

void getAllPowLawRandomEdgesV2(ll vertc,ll edgec,string vartype,ll tstcase){

    edgS.clear();

    for (int i = 1; i <= vertc; i++)
    {
        edgS.push_back(edg(0, i));
    } // making disconnected graph connected

    string fp="input/powlaw/";
    fp+=vartype;
    fp+='/';
    fp+=to_string(vertc);
    fp+="_";
    fp+=to_string(edgec);
    fp+="_";
    fp+=to_string(tstcase);

    // cout << fp << endl;
    

    ifstream file(fp);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fp << " " << strerror(errno) << endl;
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            string firstNode, secondNode;
            istringstream iss(line);
            iss >> firstNode >> secondNode;
            int e1 = stoi(firstNode);
            int e2 = stoi(secondNode);
            edgS.push_back(edg(e1, e2));
        }
    }

    // for(auto it:edgS){
    //     cout << "(" << it.first << "-" << it.second << "), " ;
    // }

    file.close();


}

void getAllRealEdges()
{   
    #ifdef REAL

    for (int i = 1; i <= n; i++)
    {
        edgS.push_back(edg(0, i));
    } // making disconnected graph connected

    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filePath << " " << strerror(errno) << endl;
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            string firstNode, secondNode;
            istringstream iss(line);
            iss >> firstNode >> secondNode;
            int e1 = stoi(firstNode);
            int e2 = stoi(secondNode);
            edgS.push_back(edg(e1, e2));
        }
    }

    // for(auto it:edgS){
    //     cout << "(" << it.first << "-" << it.second << "), " ;
    // }

    file.close();

    #endif
}

int main(int argc, char *argv[])
{

    GET_ARGS()

    #ifdef REAL

    getAllRealEdges();

    vector<double> all_params = get_all_params(n,edgS);

    int passCount=0;

    if (algoType == 0)
    {
        passCount =  findsimpDFS() ;
    }
    if (algoType == 1)
    {
        passCount =  findimprovDFS() ;
    }
    if (algoType == 2)
    {
        passCount =  findkpathDFS() ;
    }
    if (algoType == 3)
    {
        passCount =  findklevDFS() ;
    }

    #ifdef PRINTREALCOMPSIZEPARAMS

    cout << "MAX COMP SIZE : " << endl;
    cout << all_params[0] << endl;

    cout << "NO OF COMPONENTS : " << endl;
    cout << all_params[1] << endl;

    cout << "MEAN OF COMPONENTS SIZE : " << endl;
    cout << all_params[2] << endl;

    cout << "STANDARD DEVIATION OF COMPONENTS SIZE : " << endl;
    cout << all_params[3] << endl;
    #endif

    cout << n << " " << m << " " << passCount << endl;

    #else

    int DP = 0;

    #ifdef VARN
    DP=n/10;
    #endif

    #ifdef VARM
    DP=n*n/100;
    #endif

    #ifdef VARK
    DP=spaceOpt;
    #endif

    // cout << "DP Val " << DP << endl;

    double param[DP] = {0} ;                // Evaluated Param based on VarX
    double avgPass[DP] = {0}	;	// Average Number of Passes
    double maxPass[DP] = {0}; // Maximum Number of Passes

    #ifdef PRINTRANDHEIGHT
    double avgHeight[DP] = {0} ; // Height Parameter of DFS Tree
    #endif

    #ifdef PRINTRANDCOMPSIZEPARAMS
    double maxComp[DP] = {0}; // Max Comp Size Perc Parameter of Graph
    double numComp[DP] = {0}; // No of Components of Graph
    double meanComp[DP] = {0}; // Mean Comp Size of Graph
    double stdComp[DP] = {0} ; // Std Deviation of Comp Size of Graph
    #endif



    m=edgSpars(n,spars);

    int t=tst;
    int dp, step, vertCount, edgeCount, p;
    dp=0; step=0; vertCount=n; edgeCount = m; p = 0;
    int k=spaceOpt;

    while(t>0){
        dp=0;

        #ifdef VARN
	    step=10;
        cout << t << endl;
	    for(vertCount=10;vertCount<=n;vertCount+=step)
		{       
            cout << vertCount << endl;
			if(vertCount>=100) step=50;
            edgeCount=edgSpars(vertCount,spars);
            // getAllRandomEdges(vertCount,edgeCount);
            // getAllPowLawRandomEdges(vertCount,edgeCount);
            getAllPowLawRandomEdgesV2(vertCount,edgeCount,"VARN",t);
            // vector<double> all_params = get_all_params(vertCount,edgS);
	    #endif

	    #ifdef VARM
	    
        step=100;
	    for(edgeCount=100;edgeCount<=m;edgeCount+=step)
		{   
            cout << t << " " << edgeCount << endl;
			if(edgeCount>=1000) step=1000;
			// if(edgeCount>=10000) step=10000;
            if(edgeCount>=20000) step=10000;
			if(edgeCount>=100000) step=100000;
            // if(edgeCount>=2000 && edgeCount<=3500) step=100;
            // if(edgeCount>=4600 && edgeCount<=6500) step=100;
            // getAllRandomEdges(vertCount,edgeCount);
            // cout << edgeCount << endl;
            // getAllPowLawRandomEdges(vertCount,edgeCount);
            getAllPowLawRandomEdgesV2(vertCount,edgeCount,"VARM",t);
            // vector<double> all_params = get_all_params(vertCount,edgS);

	    #endif

	    #ifdef VARK
	    vertCount = n; edgeCount = m;
        // getAllRandomEdges(vertCount,edgeCount);
        // getAllPowLawRandomEdges(vertCount,edgeCount);
        getAllPowLawRandomEdgesV2(vertCount,edgeCount,"VARK",t);
        // vector<double> all_params = get_all_params(vertCount,edgS);
        #endif

        #ifdef VARK

        step=1;
        for(k=1;k<=spaceOpt;k+=step){

            cout << t << " " << k << endl;

            if(k>=40) step=5;
            if(k>=100) step=50;

        #endif

        int h = 0;
        int param_index= 3; // 0 - max_comp_size 1 - no of components 2-mean component size 3- std of comp sizes 


        if(algoType == 0){
            DFSSimp simpdfs = DFSSimp(vertCount, opt);
            while(1)
            {
                int ans = simpdfs.addEdgeS(edgS);
                if(ans) break;
            }
            p = simpdfs.getPass();
            h = simpdfs.getT().getHeight(0);
        }

        if(algoType == 1){
            DFSImprov improvdfs = DFSImprov(vertCount);
            while (1)
            {
                int ans = improvdfs.addEdgeS(edgS);
                if(ans) break;
            }
            p = improvdfs.getPass();
            h = improvdfs.getT().getHeight(0);
        }

        if(algoType == 2){
            k_path kPathDFS = k_path(vertCount, k);
            while(1)
            {
                int ans = kPathDFS.addEdgeS(edgS);
                if(ans) break;
            }
            p = kPathDFS.getPass();
            h = kPathDFS.getT().getHeight(0);
        }

        if(algoType == 3){
            k_lev kLevDFS = k_lev(vertCount, k);
            while(1){
                int ans = kLevDFS.addEdgeS(edgS);
                if(ans) break;
            }
            p = kLevDFS.getPass();
            h = kLevDFS.getT().getHeight(0);
        }

        // cout << vertCount << " " << edgeCount << " " << p << endl;

        #ifdef VARN
			param[dp] = vertCount;
			avgPass[dp] += p;
            avgHeight[dp] += h;
            // maxComp[dp] += all_params[0];
            // numComp[dp] += all_params[1];
            // meanComp[dp] += all_params[2];
            // stdComp[dp] += all_params[3];
			if(maxPass[dp]<p) maxPass[dp]=p;
			dp++;
		}
		#endif
		#ifdef VARM
			param[dp] = edgeCount;
			avgPass[dp] += p;
            avgHeight[dp] += h;
            // maxComp[dp] += all_params[0];
            // numComp[dp] += all_params[1];
            // meanComp[dp] += all_params[2];
            // stdComp[dp] += all_params[3];
			if(maxPass[dp]<p) maxPass[dp]=p;
			dp++;
		}
		#endif

		#ifdef VARK
			param[dp] = k;
			avgPass[dp] += p;
            avgHeight[dp] += h;
            // maxComp[dp] += all_params[0];
            // numComp[dp] += all_params[1];
            // meanComp[dp] += all_params[2];
            // stdComp[dp] += all_params[3];
			if(maxPass[dp]<p) maxPass[dp]=p;
			dp++;
		}
        #endif

        t--;

    }

	for(int i=0;i<dp;i++)
	{
		avgPass[i]/= tst;
        avgHeight[i]/=tst;
        // maxComp[i]/=tst;
        // numComp[i]/=tst;
        // meanComp[i]/=tst;
        // stdComp[i]/=tst;
		cout << param[i] << " " << avgPass[i] << " " << maxPass[i] << " " << avgHeight[i] << endl;
        // cout << avgHeight[i] << " " << maxComp[i] << " " << numComp[i] << " " << meanComp[i] << " " << stdComp[i] << endl;
	}
    #endif

    return 0;
}
