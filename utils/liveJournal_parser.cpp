/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `com-lj.ungraph.txt` file directly as input to this program.
 * 3. Compile the program using the following command:
 *    g++ -o liveJournal_parser liveJournal_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *    ./liveJournal_parser <path_to_com-lj.ungraph.txt>
 * 5. You should get an output file with the name `output_liveJournal_graph.edg` in accordance with the required format.
*/

/*
    **Graph Verification** -- as of 22-01-2025
    * 1. Contains N=3997962 nodes
    * 2. Contains M=34681189 edges
    * 3. No self-loops found
    * 4. No duplicate edges found
    ! 5. Nodes labelled from 0 to 4036537 (instead of 1 to 3997962)
        ? This is fixed by the below code and the output file has the nodes labelled from 1 to 3997962.
    * 6. The verification logic is commented out currently and it only generates the output file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N = 3997962; // Number of nodes
const ll M = 34681189; // Number of edges

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

    string outputFileName = "output_liveJournal_graph.edg";
    ofstream outfile(outputFileName);


    string s;
    ll u, v, e = 0;
    vector<pll> edges;
    map<ll, ll> nodes;
    /*
    ll line = 1;
    pll p;
    set<pll> duplicate_edges;
    */

    for (int i = 0; i < 4; ++i) getline(infile, s); // Skip the first 4 lines of the file as they have meta data

    while (infile >> u >> v) {
        // Putting the nodes in map with default mapping
        nodes[u] = 0;
		nodes[v] = 0;

        edges.push_back({u, v});

        /*
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
        */
    }

    infile.close();

    /*
    if (nodes.size() != N) {
        cout << "Number of nodes mismatched: " << nodes.size() << " instead of " << N << endl;
    }

    if (edges.size() != M) {
        cout << "Number of edges mismatched: " << edges.size() << " instead of " << M << endl;
    }

    ll minLabel = nodes.begin()->first, maxLabel = nodes.rbegin()->first;

    if (minLabel != 1 || maxLabel != N) {
        cout << "Nodes not labelled from 1 to " << N << endl;
        if (maxLabel - minLabel + 1 == N) {
            cout << "Nodes labelled continuously, adding "<< 1ll - minLabel << " would fix it" << endl;
        }
        else {
            cout << "Nodes not labelled continuously, needs to be re-mapped" << endl;
        }
    }

    cout << "Verification completed" << endl;
    */

    e = 1;
    for (auto& node : nodes) node.second = e++; // Renumbering the nodes consecutively from 1 to N

    for (auto& edge : edges) outfile << nodes[edge.first] << ' ' << nodes[edge.second] << endl;

    outfile.close();

    cout << "Output written to " << outputFileName << endl;

	return 0;
}