#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <random>
#include <algorithm>
#define ll long long int
using namespace std;

extern const string randomGraphsDirectory;

class Segtree {
public:
    ll size;
    vector<ll> val;

    Segtree(ll n);

    void set(ll i, ll v);
    void set(ll i, ll v, ll x, ll lx, ll rx);

    ll get(ll l, ll r);
    ll get(ll l, ll r, ll x, ll lx, ll rx);
};

string generate_file_name(ll n, ll m, const string& type, ll seed);

bool file_exists(const string& filePath);

ll select_node_by_degree(const vector<ll>& values, mt19937& rng);

void generate_power_law_graph(ll n, ll m, ll seed, string &filePath);

void generate_uniform_graph(ll n, ll m, ll seed, string &filePath);

ll select_node_by_probability(Segtree& st, ll n, mt19937& rng, ll total_weight);

void generate_power_law_graph_old(ll n, ll m, ll seed, string &filePath);

void generate_uniform_graph_old(ll n, ll m, ll seed, string &filePath);

string generateRandomGraph(ll n, ll m, ll seed_token, string graph_type);

#endif // GRAPH_GEN_H