/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `roadNet-PA.txt` file directly as input to this program.
 * 3. Compile the program using the following command:
 *      g++ -o roadnetPA_parser roadnetPA_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *      ./roadnetPA_parser <path_to_roadNet-PA.txt>
 * 5. OR compile and run at once using:
 *      g++ -o roadnetPA_parser roadnetPA_parser.cpp && ./roadnetPA_parser <path_to_roadNet-PA.txt>
 * 6. You should get an output file with the name `output_roadnetPA_graph.edg` in accordance with the required format.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N = 1088092; // Number of nodes
const ll M = 3083796; // Number of edges

bool verifyNodes(ifstream& infile) {
    set<ll> nodes;
    bool flag = true;

    ll u, v;
    while (infile >> u >> v) {
        nodes.insert(u);
        nodes.insert(v);
    }
    infile.close();

    if ((ll)nodes.size() != N) {
        cout << "Number of nodes mismatched: " << nodes.size() << " instead of " << N << endl;
        flag = false;
    }
    else cout << "Number of nodes matched: " << N << endl;

    ll minLabel = *nodes.begin(), maxLabel = *nodes.rbegin();

    if (minLabel != 1ll || maxLabel != N) {
        cout << "Nodes labelled from "<< minLabel << " to " << maxLabel << " instead of 1 to " << N << endl;
        if (maxLabel - minLabel + 1 == N) {
            cout << "Nodes labelled continuously, adding "<< 1ll - minLabel << " would fix it" << endl;
        }
        else {
            cout << "Nodes not labelled continuously, needs to be re-mapped" << endl;
        }
        flag = false;
    }
    else cout << "Nodes labelled from 1 to " << N << endl;

    cout << "Nodes Verification completed" << endl;

    return flag;
}

bool verifyEdges(ifstream& infile) {
    ll u, v, line = 5;
    pll p;
    set<pll> edges;
    bool flag = true;

    while (infile >> u >> v) {
        p = (u <= v) ? make_pair(u, v) : make_pair(v, u);

        if (u == v) {
            cout << "Self-loop found at line " << line << endl;
            flag = false;
        }

        if (edges.find(p) != edges.end()) {
            cout << "Duplicate edge found at line " << line << " with nodes: " << u << ' ' << v << endl;
            flag = false;
        }
        else edges.insert(p);
        line++;
    }

    infile.close();

    if (edges.size() != M) {
        cout << "Number of edges mismatched: " << edges.size() << " instead of " << M << endl;
        flag = false;
    }
    else cout << "Number of edges matched: " << M << endl;

    return flag;
}

void generateOutputFile(ifstream& infile) {
    string outputFileName = "output_roadnetPA_graph.edg";
    ofstream outfile(outputFileName);

    cout << "Relabelling nodes from 1 to " << N << endl;

    ll u, v;
    while (infile >> u >> v) {
        outfile << (u + 1ll) << ' ' << (v + 1ll) << endl;
    }

    infile.close();
    outfile.close();

    cout << "Added 1 to all node labels" << endl;
    cout << "Output written to " << outputFileName << endl;
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

    string s;
    for (int i = 0; i < 4; ++i) getline(infile, s); // Skip the first 4 lines of the file as they have meta data

    /*This verifies the number of nodes, their continuous labelling*/
    cout << "Verifying nodes..." << (verifyNodes(infile) ? "No issues found" : "Some issues found") << endl;

    /*This verifies the number of edges, self-loops, and duplicates (parallel edges)*/
    // cout << "Verifying edges..." << (verifyEdges(infile) ? "No issues found" : "Some issues found") << endl;

    /*This generates the output file in the required format*/
    // generateOutputFile(infile);

	return 0;
}