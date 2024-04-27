#include <bits/stdc++.h>
using namespace std;
#include "levelAnc.cpp"

#include "tree.cpp"

#define edg pair<int, int>



bool isAncestor(int x,int y, Tree T){
    if(x==-1) return false;
    if(x==y) return true;
    else return isAncestor(T.par(x),y,T);
}

bool isDescendant(int x, int y, Tree T){
    if(x==y) return true;
    bool b=false;

    list<int> &child=T.getChild(x);
    for(auto it=child.begin();it!=child.end();it++){
        b=b || (isDescendant(*it,y,T));
    }
    return b;
}

bool verifyDFS(list<edg> &edges, Tree T){
    LevelAnc LA(T);
    // updateT(0);
    for(auto it=edges.begin();it!=edges.end();it++){
        int x=it->first;
        int y=it->second;
        int levelx = LA.level(x), levely = LA.level(y);
        if(levelx == levely) return 0;
        if(levelx < levely){
            swap(x, y);
            swap(levelx, levely);
        }
        if(LA.la(x, levelx - levely) != y) return 0;
        
        // if(isAncestor(x,y,T) || isDescendant(x,y,T)) continue;
        // else return false;
    }

    return 1;
}