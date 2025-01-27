/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `human_gene2.mtx` file directly as input to this program.
 * 3. Compile the program using the following command:
 *      g++ -o belcastro_parser belcastro_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *      ./belcastro_parser <path_to_human_gene2.mtx>
 * 5. OR compile and run at once using:
 *      g++ -o belcastro_parser belcastro_parser.cpp && ./belcastro_parser <path_to_human_gene2.mtx>
 * 6. You should get an output file with the name `output_belcastro_graph.edg` in accordance with the required format.
*/

/*
    **Graph Description**
    * 1. The Belcastro Human Gene graph is given in the Matrix Market format.
    * 2. Skipping the metadata, the graph is given as a weighted adjacency matrix.
    * 3. Each line has 3 values, (u, v, w) where there is an edge from u to v with weight w which ranges from 0 to 1.
    * 4. There are 14,340 edges as self-loops which will be excluded from the output.
    * 5. The expected output is supposed to be an edge list with 14,022 nodes and 9,027,024 edges (not as mentioned in the source).
    * 6. The edge weights are not considered and so all the edges are included without any filtering.
*/

/*
    **Graph Verification** -- as of 28-01-2025
    * 1. Contains N=14022 nodes (excluding nodes with only a self-loop)
    * 2. Contains M=9027024 edges (excluding self-loops)
    * 3. Self-loops found and excluded in the generateOutputFile function
    * 4. No duplicate edges found
    ! 5. Post exclusion of nodes with only a self - loop, Nodes labelled from 25 to 14340 (instead of 1 to 14022)
        ? This is fixed by the below code and the output file has the nodes labelled from 1 to 14022.
    * 6. The verification logic is commented out currently and it only generates the output file.
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

const ll N = 14022; // Number of nodes (excluding nodes with only a self-loop)
const ll M = 9027024; // Number of edges (excluding self-loops)

bool verifyNodes(ifstream& infile) {
    set<ll> nodes;
    bool flag = true;

    ll u, v;
    double w;
    while (infile >> u >> v >> w) {
        if (u == v) continue; // Skipping self-loops
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
    ll u, v, line = 19, selfLoopCount = 0;
    double w;
    pll p;
    set<pll> edges;
    bool flag = true;

    while (infile >> u >> v >> w) {
        p = (u <= v) ? make_pair(u, v) : make_pair(v, u);

        if (u == v) {
            // cout << "Self-loop found at line " << line << endl;
            selfLoopCount++;
            flag = false;
        }
        else if (edges.find(p) != edges.end()) {
            cout << "Duplicate edge found at line " << line << " with nodes: " << u << ' ' << v << endl;
            flag = false;
        }
        else edges.insert(p);
        line++;
    }

    infile.close();

    cout << selfLoopCount << " self - loops found\n";

    if (edges.size() != M) {
        cout << "Number of edges mismatched: " << edges.size() << " instead of " << M << endl;
        flag = false;
    }
    else cout << "Number of edges matched: " << M << endl;

    return flag;
}

void generateOutputFile(ifstream& infile) {
    string outputFileName = "output_belcastro_graph.edg";
    ofstream outfile(outputFileName);

    cout << "Re-mapping nodes from 1 to " << N << endl;


    ll u, v, e = 1;
    vector<pll> edges;
    map<ll, ll> nodes;
    double w;

    edges.reserve(M);

    while (infile >> u >> v >> w) {
        if (u == v) continue; // Skipping self-loops
        nodes.insert({u, 0});
        nodes.insert({v, 0});
        edges.emplace_back(u, v);
    }
    infile.close();

    for (auto& node : nodes) node.second = e++; // Renumbering the nodes consecutively from 1 to N    

    for (auto& edge : edges) outfile << nodes[edge.first] << ' ' << nodes[edge.second] << endl;
    outfile.close();

    cout << "Nodes re-mapped successfully" << endl;

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
    for (int i = 0; i < 18; ++i) getline(infile, s); // Skip the first 18 lines of the file as they have meta data

    /*This verifies the number of nodes, their continuous labelling*/
    // cout << "Verifying nodes...\n" << (verifyNodes(infile) ? "No issues found" : "Some issues found") << endl;


    /*This verifies the number of edges, self-loops, and duplicates (parallel edges)*/
    // cout << "Verifying edges...\n" << (verifyEdges(infile) ? "No issues found" : "Some issues found") << endl;

    /*This generates the output file in the required format, takes a parameter whether to relabel nodes 1-N */
    generateOutputFile(infile); // true for re-mapping nodes

	return 0;
}