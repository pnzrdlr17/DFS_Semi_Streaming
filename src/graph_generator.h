#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <random>
#define ll long long int
using namespace std;

extern const string randomGraphsDirectory;

string generate_file_name(ll n, ll m, const string& type, ll seed);

bool file_exists(const string& filePath);

ll select_node_by_degree(const vector<ll>& values, mt19937& rng);

void generate_power_law_graph(ll n, ll m, ll seed, string &filePath);

void generate_uniform_graph(ll n, ll m, ll seed, string &filePath);

string generateRandomGraph(ll n, ll m, ll seed_token, string graph_type);

#endif // GRAPH_GEN_H