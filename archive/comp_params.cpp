/*#include <bits/stdc++.h>
using namespace std;

#define ll long long int

#ifndef edg
    #define edg pair<ll, ll>
#endif

class dsu{
private:
    vector<ll> size, p;
    ll max_size, num_comps;

public:
    dsu(ll n){
        max_size = 1;
        num_comps = n;
        size.assign(n, 1LL);
        p.assign(n, 0LL);
        for(ll i=0; i<n; i++) p[i] = i;
    }

    ll get(ll a){
        if(a == p[a]) return a;
        return p[a] = get(p[a]);
    }

    void un(ll a, ll b){
        a = get(a);
        b = get(b);
        if(a == b) return;
        if(size[a] >= size[b]){
            p[b] = a;
            size[a] += size[b];
        }
        else{
            p[a] = b;
            size[b] += size[a];
        }
        num_comps--;
        max_size = max(max_size, max(size[a], size[b]));
    }

    ll get_max_size(){
        return max_size;
    }

    ll get_num_comps(){
        return num_comps;
    }

    ll get_size(ll a){
        return size[get(a)];
    }
};


// max_comp_size, num_comps, mean, standard_deviation

vector<double> get_all_params(ll n, list<edg> edgs){

    // cout << n << " " << edgs.size() << endl;
    dsu st(n);
    for(auto &it: edgs){
        ll u = it.first, v = it.second;
        // cout << u << " " << v << endl;
        if(u != 0 && v != 0){
            u--; v--;
            st.un(u, v);
        }
    }

    // cout << endl;

    vector<double> res;
    res.push_back(st.get_max_size()/(double)n * 100);
    res.push_back(st.get_num_comps());
    
    vector<ll> sizes;
    for(int i=0; i<n; i++){
        if(st.get(i) == i) sizes.push_back(st.get_size(i));
    }

    // cout<<"============="<<endl;
    // for(auto &it: sizes) cout<<it<<" ";
    // cout<<endl;
    // cout<<"============="<<endl;

    double sum = accumulate(sizes.begin(), sizes.end(), 0LL);
    double mean = sum/sizes.size();

    double std = 0;
    for(auto &it: sizes) std += pow(it - mean, 2);

    std = sqrt(std/sizes.size());
    res.push_back(mean);
    res.push_back(std);
    
    return res;
}*/