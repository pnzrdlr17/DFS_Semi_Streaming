/*
    **Instructions to run the program**
 * 1. Download the file as mentioned in graph_sources.md and extract it.
 * 2. Use the `out.dblp-author` file directly as input to this program.
 * 3. Compile the program using the following command:
 *      g++ -o dblp_parser dblp_parser.cpp
 * 4. Run the program with the path to the CSV file as an argument:
 *      ./dblp_parser <path_to_out.dblp-author>
 * 5. OR compile and run at once using:
 *      g++ -o dblp_parser dblp_parser.cpp && ./dblp_parser <path_to_out.dblp-author>
 * 6. You should get an output file with the name `output_roadnetCA_graph.edg` in accordance with the required format.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>

const ll N1 = 1965206; // Number of nodes on left side

void generateOutputFile(ifstream& infile) {
    string outputFileName = "output_dblp_graph.edg";
    ofstream outfile(outputFileName);

    ll u, v;
    map<ll, ll> nodes1, nodes2;
    vector<pll> edges;
    set<pll> edgeSet;

    while (infile >> u >> v) {
        nodes1.insert({u, 0});
        nodes2.insert({v, 0});
        if (u == v) continue; // Skip self-loops
        pll p = (u <= v) ? make_pair(u, v) : make_pair(v, u);
        if (edgeSet.find(p) == edgeSet.end()) {
            edgeSet.insert(p);
            edges.push_back(p);
        }
    }
    infile.close();

    ll e = 1;
    for (auto& [node, label] : nodes1) nodes1[node] = e++;
    for (auto& [node, label] : nodes2) nodes2[node] = e++;

    for (auto& [u, v] : edges) outfile << nodes1[u] << ' ' << nodes2[v] << endl;

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
    for (int i = 0; i < 2; ++i) getline(infile, s); // Skip the first 2 lines of the file as they have meta data

    /*This generates the output file in the required format*/
    generateOutputFile(infile);

	return 0;
}