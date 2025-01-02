#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include "../tree.cpp"
#define edg pair<int, int>
using namespace std;

class DFSSimp
{
    int n;
    Tree T;    // DFS tree
    int opt;   // with or without heuristic
    int pass;  // Number of Passes
    int currV; // Currently traversed Vertex
    int visC;  // Visited Counter
    int flag;
    int dir;
    vector<int> visited;    // Bit Vector for Visited in DFS
    vector<int> neighbours; // Lowest Neighbours of Single Insert

public:
    DFSSimp(int size, int optimality)
    {
        n = size + 1;
        T = Tree(size + 1);
        T.setRoot(0);
        pass = 0;
        currV = 0;
        visC = 1;
        visited.resize(size + 1, 0);
        visited[currV] = 1;
        flag = 0;
        opt = optimality;
        neighbours.resize(size + 1, -1);
        dir = 0;
    }

    int addEdge(int x, int y)
    {

        if (x == -1 && y == -1)
        {
            pass++;

            if (flag == 0)
            {

                while (currV != 0 && neighbours[currV] == -1)
                    currV = T.par(currV);

                if (neighbours[currV] == -1)
                    return 1;
                else
                {
                    int v_new = neighbours[currV];
                    T.addEdge(currV, v_new);
                    visited[v_new] = 1;
                    currV = v_new;
                    visC++;
                }
            }

            flag = 0;
            for (int i = 0; i < neighbours.size(); i++)
            {
                neighbours[i] = -1;
            }

            if (visC == T.getSize())
                return 1;
            return 0;
        }

        else
        {

            if (opt == 1 || (opt == 0 && flag == 0))
            {
                if ((currV == x && visited[y] == 0) || (dir==0 && currV == y && visited[x] == 0))
                {
                    int v_new = (currV == x ? y : x);
                    T.addEdge(currV, v_new);
                    visited[v_new] = 1;
                    currV = v_new;
                    flag = 1;
                    visC++;
                }
                else
                {

                    if (visited[x] == 1 && visited[y] == 0)
                        neighbours[x] = y;
                    if (dir==0 && visited[y] == 1 && visited[x] == 0)
                        neighbours[y] = x;
                }
            }
        }

        return 0;
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