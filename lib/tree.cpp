#include <bits/stdc++.h>
using namespace std;

#ifndef TREE_H
#define TREE_H

class Tree
{

    int treeSize;           // size of tree
    int root;               // root of tree
    vector<list<int>> adjL; // Adjacency List of children
    vector<int> parent;     // Parent
    vector<list<int>::iterator> parIt;

public:
    Tree()
    {
        // do nothing
    }

    Tree(int n)
    {
        treeSize = n;
        adjL.resize(n, list<int>()); // initialize with empty vector
        parent.resize(n, -1);
        parIt.resize(n);
    }

    int getSize()
    {
        return treeSize;
    }


    void setRoot(int r)
    {
        root = r;
    }

    int getRoot(){
        return root;
    }


    int par(int x)
    {
        return parent[x];
    }

    list<int> &getChild(int x)
    {
        return adjL[x];
    }

    void addEdge(int x, int y)
    {
        adjL[x].push_front(y);
        parIt[y] = adjL[x].begin();
        parent[y] = x;
    }

    void printT(int x)
    {

        for (auto it = adjL[x].begin(); it != adjL[x].end(); it++)
        {
            printf(" (%d)->(%d) ", x, *it);
            printT(*it);
        }
    }


    int remEdge(int x,int y)	
	{
        adjL[x].erase(parIt[y]);
        parent[y]=-1;
        return 1;
	}

    int getHeight(int x)
    {   
        int cnt=0;
        for (auto it = adjL[x].begin(); it != adjL[x].end(); it++)
        {
            cnt = max(cnt,getHeight(*it)+1);
        }
        return cnt;
    }
};


#endif