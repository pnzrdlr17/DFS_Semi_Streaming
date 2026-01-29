#ifndef VERIFYDFS_H
#define VERIFYDFS_H

#include "tree.cpp"
#include "levelAnc.cpp"
#include <list>
#include <utility>

bool isAncestor(int x, int y, Tree T);
bool isDescendant(int x, int y, Tree T);
bool verifyDFS(std::list<std::pair<int, int>>& edges, Tree T);

#endif // VERIFYDFS_H
