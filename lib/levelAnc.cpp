#include<vector>
#include<list>
#include<cstdio>
#include "tree.cpp"

// #include"Logger.h"
using namespace std;

#ifndef LEVEL_ANC
#define LEVEL_ANC

class LevelAnc
{
Tree *T;
vector<int> lev;		// Level   Root 1;
vector<vector<int> > ancstr;	// Ancestor at level 1,2,4,..., levels above			

/* 
Updates level, LCA, LA info of vertex with index x
Assumes value of par(x) are updated
Param: <x> index of vertex whose ancestor information is updated
Return:	1 if success
	0 else
*/
int update(int x)	
	{
	// #ifndef FAST
	// if(!(*T).validV(x))// || ((*T).par(x)==-1 && (*T).root()!=x) )
	// 	ERR_MSGR("LevelAnc::update Invalid Args\n",0);
	// #endif

		
	if((*T).par(x)==-1)
		{
		lev[x] = 1;
		ancUp(x,0,-1);
		}
	else
		{
		int i,y = (*T).par(x);
		lev[x] = lev[y]+1;
		ancUp(x,0,y);

		for(i=1;(1<< i) < lev[x] ; i++)
			ancUp(x,i,  ancstr[   ancstr[x][i-1]   ] [i-1]  );

		ancUp(x,i,-1);
		}
	return 1;			
	}


/* 
Update the ancestor entry corresponding to 2^i to z 
given it has atleast i-1 entries
*/
void ancUp(int x, int i, int z)
	{
	if(ancstr[x].size()== (unsigned int) i ) ancstr[x].push_back(z);
	else ancstr[x][i]=z;
	}

public:
/*
Find the End of broom Stick (which has >1 children)
starting in subtree T(<x>).
Level of (x) gives the height of broom Stick.
Param: <x> root of tree T(x)
Return:<y> The end of broom Stick
*/
int broomEnd(int x) const
	{
	
	int y= x;
	while((*T).getChild(y).size()==1)
		y = (*T).getChild(y).front();			
	return y;
	}
/*
Constructor: Empty Constructor
*/
LevelAnc(){};
/*
Constructor: Makes the data structure of the corresponding size
Param:	<size> Size of the tree
*/
LevelAnc(Tree& Tmp)
	{
	T = &Tmp;
	ancstr.resize((*T).getSize());
	lev.resize((*T).getSize(),-1);
	updateT((*T).getRoot());
	}	
	
/* 
Updates the size of data if vertex is added.
*/
void addVertex()
	{
	vector<int> tmp;		
	ancstr.push_back(tmp);
	lev.push_back(-1);
	}



/* 
Updates level, LCA, LA info of vertices in subtree 
rooted at vertex with index x
Assumes values of its parents are updated.
Param: <x> index of root of subtree
Return:	1 if success
	-1 else
*/
int updateT(int x)	
	{
		
	update(x);

	list<int> :: const_iterator it;
	list<int> adj = (*T).getChild(x);

	for(it= adj.begin(); it!= adj.end(); it++)
		updateT(*it);
	return 1;			
	}
	
/*
Return Level of vertex with index x
Param: <x> index of the vertex
Return:	Level of the vertex if valid
	-1 if invalid
*/
int level(int x )
	{
	return lev[x];
	}
	
/*
Level ancestor of vertex at level Level(x)-k
Param: <x> index of the vertex, <k> corresponding level
Return: LA of vertex with index x at level Level(x)-k
	-1 if invalid
*/
int la(int x,int k)
	{
       
	int dist;
	for(dist=0;(1<<dist)<=k;dist++);
	dist--;

	while(k)
		{
		int i;
		for(i=dist;(1<<i)>k;i--);
		x = ancstr[x][i];
		k -= (1<<i);
		dist = i-1;
		}

	return x;
	}


/*
LCA of vertices with index x and y
Param: <x>, <y> index of vertices whose LCA required.
Return: Corresponding LCA
	-1 if invalid
*/
int lca(int x,int y )
	{
		
	if(lev[x] > lev[y])
		x = la(x,lev[x]-lev[y]);
	else if(lev[x]<lev[y])
		y = la(y,lev[y]-lev[x]);
	
        int dist;
	for(dist=0;(1<<dist)<=lev[x];dist++);
	dist--;

	while(x!=y)
		{
		while((1<<dist)>lev[x]) dist--;
		if((*T).par(x) == (*T).par(y))  {x=y=(*T).par(x);}
		else 
			{
			int i;
			for(i=dist;ancstr[x][i]==ancstr[y][i];i--);

			x=ancstr[x][i];
			y=ancstr[y][i];	
			dist = i-1;						
			}
		}
	return x;
	}

		
};
#endif
