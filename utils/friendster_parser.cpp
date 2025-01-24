/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `com-friendster.ungraph.txt` file directly as input to this program.
 * 3. Compile the program using the following command:
 *      g++ -o friendster_parser friendster_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *      ./friendster_parser <path_to_com-friendster.ungraph.txt>
 * 5. OR compile and run at once using:
 *      g++ -o friendster_parser friendster_parser.cpp && ./friendster_parser <path_to_com-friendster.ungraph.txt>
 * 6. You should get an output file with the name `output_friendster_graph.edg` in accordance with the required format.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N = 65608366; // Number of nodes
const ll M = 1806067135; // Number of edges

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    string outputFileName = "output_friendster_graph.edg";
    ofstream outfile(outputFileName);


    string s;
    ll u, v, e = 0;
    vector<pll> edges;
    map<ll, ll> nodes;
    ll line = 1;
    pll p;
    set<pll> duplicate_edges;

    for (int i = 0; i < 4; ++i) getline(infile, s); // Skip the first 4 lines of the file as they have meta data

    while (infile >> u >> v) {
        // Putting the nodes in map with default mapping
        nodes[u] = 0;
		nodes[v] = 0;

        edges.push_back({u, v});


        if (u == v) {
            cout << "Self-loop found at line " << line << endl;
        }
        if (u > v) swap(u, v);
        p = {u, v};
        if (duplicate_edges.find(p) != duplicate_edges.end()) {
            cout << "Duplicate edge found at line " << line << " with nodes: " << u << ' ' << v << endl;
        }
        else duplicate_edges.insert(p);
        line++;

    }

    infile.close();


    if (nodes.size() != N) {
        cout << "Number of nodes mismatched: " << nodes.size() << " instead of " << N << endl;
    }

    if (edges.size() != M) {
        cout << "Number of edges mismatched: " << edges.size() << " instead of " << M << endl;
    }

    ll minLabel = nodes.begin()->first, maxLabel = nodes.rbegin()->first;

    if (minLabel != 1 || maxLabel != N) {
        cout << "Nodes not labelled from "<< minLabel << " to " << maxLabel << " instead of 1 to " << N << endl;
        if (maxLabel - minLabel + 1 == N) {
            cout << "Nodes labelled continuously, adding "<< 1ll - minLabel << " would fix it" << endl;
        }
        else {
            cout << "Nodes not labelled continuously, needs to be re-mapped" << endl;
        }
    }
    else cout << "Nodes labelled from 1 to " << N << endl;

    cout << "Verification completed" << endl;


    e = 1;
    for (auto& node : nodes) node.second = e++; // Renumbering the nodes consecutively from 1 to N

    for (auto& edge : edges) outfile << nodes[edge.first] << ' ' << nodes[edge.second] << endl;

    outfile.close();

    cout << "Output written to " << outputFileName << endl;

	return 0;
}