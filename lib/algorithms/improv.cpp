#include <bits/stdc++.h>
#include "../tree.cpp"
#define edg pair<int, int>
using namespace std;

class DFSImprov
{
    int n;
    Tree T;              // DFS tree
    int pass;            // Number of Passes
    int visC;            // Visited Counter
    vector<int> visited; // Bit Vector for Visited in DFS

    int first;                 // for initial update of each pass
    vector<vector<int>> compL; // List of vertices in the ith component
    vector<int> comp;          // The component to which x belongs

    set<int> leaves;
    map<int, int> edgToLeaf;
    int dir;

public:
    DFSImprov(int size)
    {
        n = size + 1;
        T = Tree(size + 1);
        T.setRoot(0);
        pass = 0;
        visC = 1;
        visited.resize(size + 1, 0);
        visited[0] = 1;

        first = 1;
        compL.resize(size + 1);
        comp.resize(size + 1);

        dir=0;

        leaves.insert(0);
    }

    int addEdge(int x, int y)
    {

        if (first)
        {
            // code executes at the start of each pass;
            for (int i = 0; i < T.getSize(); i++)
            {
                if (visited[i] == 0)
                {
                    compL[i].push_back(i);
                    comp[i] = i;
                }
            }

            first = 0;
        }

        if (x == -1 && y == -1)
        {

            leaves.clear();

            // cout << "Pass No : " << pass+1 << endl;

            for (int i = 0; i < T.getSize(); i++)
            {
                if (!compL[i].empty())
                {
                    for (int j = 0; j < compL[i].size(); j++)
                    {
                        int vert = compL[i][j];

                        if (edgToLeaf.count(vert) != 0)
                        {
                            int leaf = edgToLeaf[vert];
                            T.addEdge(leaf, vert);
                            // cout << "leaf: " << leaf << " vert: " << vert << endl;
                            visited[vert]++;
                            visC++;
                            leaves.insert(vert);
                            break;
                        }
                    }
                }

                compL[i].clear();
            }

            pass++;
            first = 1;
            edgToLeaf.clear();

            // cout << pass << endl;
            // T.printT(0);
            // cout << endl;

            if (visC == T.getSize())
                return 1;
            else
                return 0;
        }
        else
        {

            if (visited[x] == 0 && visited[y] == 0 && comp[x] != comp[y])
            {

                if (compL[comp[x]].size() < compL[comp[y]].size())
                {
                    swap(x, y);
                }

                int z = comp[y];
                for (auto itc = compL[z].begin(); itc != compL[z].end(); itc++)
                {
                    compL[comp[x]].push_back(*itc);
                    comp[*itc] = comp[x];
                }
                compL[z].clear();

            }
            else
            {
                if ((visited[x] == 1 && visited[y] == 0) || (dir==0 && visited[x] == 0 && visited[y] == 1))
                {
                    int possLeaf = (visited[x] == 1 ? x : y);
                    int possVerToLeaf = (visited[x] == 0 ? x : y);

                    if (leaves.count(possLeaf) != 0)
                    {
                        edgToLeaf[possVerToLeaf] = possLeaf;
                    }
                }
            }

            return 0;
        }
    }

    int addEdgeS(list<edg> edges)
    {

        for (auto it = edges.begin(); it != edges.end(); it++)
        {
            addEdge(it->first, it->second);
        }
        return addEdge(-1, -1);
    }

    int processEdgeStream(ifstream& fileStream) {
        for (int i = 1; i < n; ++i) // Add artificial edges (disconnected graph connections)
            addEdge(0, i);

        if (!fileStream.is_open()) {
            cerr << "Error opening file: " << strerror(errno) << endl;
            return 1;
        }

        string line;
        while (getline(fileStream, line)) {
            istringstream iss(line);
            int e1, e2;
            if (!(iss >> e1 >> e2)) {
                cerr << "Error: Malformed or incomplete line: " << line << endl;
                break; // Exit loop if edge format is invalid
            }
            addEdge(e1, e2);
        }

        return addEdge(-1, -1);
    }

    int getPass()
    {
        return pass;
    }

    Tree getT()
    {
        return T;
    }
};