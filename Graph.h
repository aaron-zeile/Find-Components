/*** Graph.h ***/
/*** Aaron Zeile ***/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define INF -100
#define NIL 0
#define UNDEF  -1
#define FORMAT "%d"

// EXPORTED TYPES ----------------
typedef struct GraphObj* Graph;
typedef int GraphElement;
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
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
