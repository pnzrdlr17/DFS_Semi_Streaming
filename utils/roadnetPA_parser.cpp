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

/*
    **Graph Verification** -- as of 30-01-2025
    * 1. Contains N=1088092 nodes
    * 2. Contains M=1541893 edges (unique)
    * 3. No self-loops found
    * 4. No duplicate edges found
    ! 5. Nodes labelled from 0 to 1090919 (instead of 1 to 1088092)
        ? This is fixed by the below code and the output file has the nodes labelled from 1 to 1088092.
    ! 6. The graph has duplicate for each edge, so the actual number of edges is 1541893, but the file contains 3083796 edges
        ? Only one of the duplicate edges is considered while generating the output file, so M=1541893.
    * 7. The verification logic is commented out currently and it only generates the output file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <set>
#include <map>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N = 1088092; // Number of nodes
const ll M = 1541893; // Number of edges (unique)

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
    ll u, v, line = 5, duplicateEdges = 0;
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
            duplicateEdges++;
            flag = false;
        }
        else edges.insert(p);
        line++;
    }

    infile.close();

    cout << "Number of duplicate edges: " << duplicateEdges << endl;

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

    cout << "Re-mapping nodes from 1 to " << N << endl;

    ll u, v, e = 1;
    vector<pll> edges;
    set<pll> edgeSet;
    map<ll, ll> nodes;
    pll p;

    edges.reserve(M);

    while (infile >> u >> v) {
        nodes.insert({u, 0});
        nodes.insert({v, 0});
        p = (u <= v) ? make_pair(u, v) : make_pair(v, u);
        if (edgeSet.find(p) == edgeSet.end()) {
            edgeSet.insert(p);
            edges.emplace_back(u, v);
        }
    }
    infile.close();


    for (auto& node : nodes) node.second = e++; // Renumbering the nodes consecutively from 1 to N

    for (auto& edge : edges) outfile << nodes[edge.first] << ' ' << nodes[edge.second] << endl;

    outfile.close();

    cout << "Nodes re-mapped and duplicate edges removed successfully" << endl;
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
    // cout << "Verifying nodes..." << (verifyNodes(infile) ? "No issues found" : "Some issues found") << endl;

    /*This verifies the number of edges, self-loops, and duplicates (parallel edges)*/
    // cout << "Verifying edges..." << (verifyEdges(infile) ? "No issues found" : "Some issues found") << endl;

    /*This generates the output file in the required format*/
    generateOutputFile(infile);

	return 0;
}