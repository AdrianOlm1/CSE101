/***
* Adrian Olmos
* amolmos
* 2024 Winter CSE101 PA2
* Graph.h
* Contains function prototypes and type definitions for the Graph ADT used by the FindPath program.
***/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include<stdbool.h>
#include "List.h"

#define NIL -1
#define INF -2

#define WHITE 0
#define BLACK 1
#define GRAY 2

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void listIns(List l, int a);
#endif
