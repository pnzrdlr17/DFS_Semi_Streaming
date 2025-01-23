/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `large_twitch_edges.csv` file directly as input to this program.
 * 3. Compile the program using the following command:
 *    g++ -o twitch_parser twitch_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *    ./twitch_parser <path_to_large_twitch_edges.csv>
 * 5. You should get an output file with the name `output_twitch_graph.edg` in accordance with the required format.
*/

/*
    **Graph Verification** -- as of 22-01-2025
    * 1. Contains N=168114 nodes
    * 2. Contains M=6797557 edges
    * 3. No self-loops found
    * 4. No duplicate edges found
    ! 5. Nodes labelled from 0 to 168113 (N-1)
        ? This is fixed by the below code and the output file has the nodes labelled from 1 to 168114.
    * 6. The verification logic is commented out currently and it only generates the output file.
*/

#include <iostream>
#include <fstream>
#include <cstring>
// #include <set>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N = 168114; // Number of nodes
const ll M = 6797557; // Number of edges

inline pll getEdgs(string &s) {
	ll u, v;
	int i = s.find(',');
	u = stoll(s.substr(0, i));
	v = stoll(s.substr(i + 1));
	if (u > v) swap(u, v);
	return {u, v};
}

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

    string outputFileName = "output_twitch_graph.edg";
    ofstream outfile(outputFileName);


    string s;
    pll p;
    ll u, v, line = 1;
    /*
    set<ll> nodes;
    set<pll> edges;
    */

    getline(infile, s); // Skip the first line of the file as it has meta data

    while (getline(infile, s)) {
        p = getEdgs(s);
        u = p.first, v = p.second;
        /*

		nodes.insert(u);
		nodes.insert(v);

		if (u == v) {
            cout << "Self loop found at line: " << line << " with node: " << u << endl;
		}
		if (edges.find(p) != edges.end()) {
            cout << "Duplicate edge found at line: " << line << " with nodes: " << u << ' ' << v << endl;
		}
		else edges.insert(p);
        */

        outfile << p.first + 1ll << " " << p.second + 1ll << endl; // Puts the nodes in the range 1 to N
        line++;
    }

    /*
    if (nodes.size() != N) {
        cout << "Number of nodes mismatched: " << nodes.size() << " instead of " << N << endl;
    }

    if (edges.size() != M) {
        cout << "Number of edges mismatched: " << edges.size() << " instead of " << M << endl;
    }

    ll minLabel = *nodes.begin(), maxLabel = *nodes.rbegin();

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

    infile.close();
    outfile.close();

    cout << "Output written to " << outputFileName << endl;

	return 0;
}
