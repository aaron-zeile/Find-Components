/*** Graph.c ***/
/*** Aaron Zeile ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

// STRUCTS -------------------------------------------------------------------------

// Graph object struct
typedef struct GraphObj {
	// ints
	int order;
	int size;
	int label;
	// arrays
	List *neighbors;
	char *color;
	int *parent;
	int *distance;
	int *disc_time;
	int *fin_time;
} GraphObj;

// CONSTRUCTOR-DESTRUCTORS -----------------------------------------------------------
// creates a new graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	assert(G != NULL);

	G->order = n;
	G->size = NIL;
	G->label = NIL;	

	G->neighbors = calloc(n+1, sizeof(List));	
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->disc_time = calloc(n+1, sizeof(int));
	G->fin_time = calloc(n+1, sizeof(int));

	// fill in default states
	for (int i = 1; i < n+1; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->neighbors[i] = newList();
		G->disc_time[i] = UNDEF;
		G->fin_time[i] = UNDEF;
	}

	return G;
}

// frees the memory associated with graph
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		// free all lists in neighbors array
		for (int i = 1; i < getOrder(*pG)+1; i++) {
			freeList(&(*pG)->neighbors[i]);
		}

		// free all arrays
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free((*pG)->disc_time);
		free((*pG)->fin_time);
		(*pG)->neighbors = NULL;
		(*pG)->color = NULL;
		(*pG)->parent = NULL;
		(*pG)->distance = NULL;

		// free graph
		free(*pG);
		*pG = NULL;
	}
}

// ACCESS FUNCTIONS -------------------------------------------------------------------
// returns the order of the graph
int getOrder(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error. Trying getOrder of NULL list.\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}
// returns size of the graph
int getSize(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error. Trying getSize of NULL list.\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
// returns the most recent source of the graph, as used in BFS
int getSource(Graph G) {
	return G->label;
}
// returns the parent of u
int getParent(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getParent with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}
// returns the distance from most recent souce to u
int getDist(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getDist with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}
// appends shortest path from source to u into L
void getPath(List L, Graph G, int u) {
	if (getSource(G) == NIL) {
		printf("No shortest path because source is NIL.\n");
		return;
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getPath with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}

	// if u is source	
	if (u == getSource(G)) {
		append(L, u);
		return;
	}
	
	// if source is unreachable
	if (G->parent[u] == NIL) {
		if (length(L) > 0) {
			clear(L);
		}
		append(L, NIL);
		return;
	}

	// recursion
	getPath(L, G, G->parent[u]);
	append(L, u);
}
// returns discover time of vertex u
int getDiscover(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getDiscover with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->disc_time[u];
}
// returns finishing time of vertex u
int getFinish(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getFinish with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->fin_time[u];
}
	
// MANIPULATION PROCEDURES --------------------------------------------------------------
void makeNull(Graph G) {
	// go through each vertex and delete edges
	for (int i = 1; i < getOrder(G)+1; i++) {
		List L = G->neighbors[i];
		if (length(L) > 0) {
			clear(L);
			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->distance[i] = INF;
		}
	}
	// reset graph info
	G->size = NIL;
}

// use addArc twice and dec size once
void addEdge(Graph G, int u, int v) {	
// preconditions ------------------------------------
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. trying addEdge with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Error. trying addEdge with v out of bounds.\n");
		exit(EXIT_FAILURE);
	}
// adding to adjacency lists -----------------------
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// adds v to u's adjacency list
void addArc(Graph G, int u, int v) {
// preconditions ------------------------------------
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with v out of bounds.\n");
		exit(EXIT_FAILURE);
	}	
// adding v to u's adj list -------------------------
	List L = G->neighbors[u];
	// if adj list is empty, simply append
	if (!(length(L) > 0)) {
		append(L, v);
		G->size++;
		return;
	}
	// start at front of list
	moveFront(L);
	// traverse list to correct insertion point
	while (index(L) != -1 && v > get(L)) {
		moveNext(L);
	}
	// if we went past the back
	if (index(L) == -1) {
		append(L, v);
	}
	// if still in list
	else {
		insertBefore(L, v);
	}
	G->size++;
}

// performs BFS algorithm on G with source s
void BFS(Graph G, int s) {
// precondition ------------------------------------
	if (s < 1 || s > getOrder(G)) {
		fprintf(stderr, "Error. Trying BFS with s out of bounds.\n");
		exit(EXIT_FAILURE);
	}
// BFS ---------------------------------------------
	// set default states
	for (int i = 1; i < getOrder(G)+1; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	// set source of G
	G->label = s;
	G->distance[s] = 0;

	// create queue and append source
	List Q = newList();
	append(Q, s);

	// while queue is not empty
	while (length(Q) > 0) {
		// get first in queue
		int x = front(Q);

		// start at the first neighbor of x
		List L = G->neighbors[x];
		moveFront(L);
		// iterate through the neighbor list
		while (index(L) != -1) {
			// get current neighbor
			int neighbor = get(L);
			// if current neighbor has not been visited,
			// update its information
			if (G->color[neighbor] == 'w') {
				G->color[neighbor] = 'g';
				G->distance[neighbor] = G->distance[x] + 1;
				G->parent[neighbor] = x;
				append(Q, neighbor); // add this neighbor to queue
			}
			// move to the next neighbor
			moveNext(L);
		}
		// after all neighbors have been visited,
		// black out x and delete it from queue
		G->color[x] = 'b';
		deleteFront(Q);
	}
	freeList(&Q);
}

void Visit(Graph G, List S, int curr, int *time) {
	// save discovery time of current vertex
	G->disc_time[curr] = ++(*time);
	G->color[curr] = 'g';
	
	// iterate through neighbors of current vertex
	List L = G->neighbors[curr];

	// visit every neighbor
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		int neighbor = get(L);
		if (G->color[neighbor] == 'w') {
			G->parent[neighbor] = curr;
			Visit(G, S, neighbor, time);
		}	
	}
	// black out when finished
	G->color[curr] = 'b';
	// increment for finishing time
	G->fin_time[curr] = ++(*time);	

	// "append" vertex to second half of list
	// and delete front of prev list
	insertAfter(S, curr);
	deleteFront(S);
}

void DFS(Graph G, List S) {
	// precondition
	if (length(S) != getOrder(G)) {
		fprintf(stderr, "Error. Trying DFS with incorrect list length.\n");
		exit(EXIT_FAILURE);
	}

	// set default states
	for (int i = 1; i < getOrder(G)+1; i++) {
		G->color[i] = 'w';
		G->disc_time[i] = UNDEF;
		G->fin_time[i] = UNDEF;
		G->parent[i] = NIL;
	}
	
	int t = 0;
	// make copy for iteration
	List C = copyList(S);
	// set cursor to back of list
	moveBack(S);
	// visit vertices
	for (moveFront(C); index(C) >= 0; moveNext(C)) {
		int curr = get(C);
		if (G->color[curr] == 'w') {
			Visit(G, S, curr, &t);
		}
	}
	// free copy
	freeList(&C);
}

// OTHERS -------------------------------------------------------------------------
void printGraph(FILE* out, Graph G) {
	// print adjacency lists
	for (int i = 1; i < getOrder(G)+1; i++) {
		List L = G->neighbors[i];
		fprintf(out, FORMAT ": ", i);
		if (length(L) > 0) {
			printList(out, L);
		}
		else {
			fprintf(out, "\n");
		}
	}	
}

Graph transpose(Graph G) {
	Graph T = newGraph(getOrder(G));

	for (int i = 1; i < getOrder(G)+1; i++) {
		List N = G->neighbors[i];
		moveFront(N);
		while (index(N) != -1) {
			addArc(T, get(N), i);
			moveNext(N);
		}
	}

	return T;
}
Graph copyGraph(Graph G) {
	
	int o = getOrder(G);
	Graph C = newGraph(o);

	for (int i = 1; i < o+1; i++) {
		C->color[i] = G->color[i];
		C->parent[i] = G->parent[i];
		C->distance[i] = G->distance[i];
		C->disc_time[i] = G->disc_time[i];
		C->fin_time[i] = G->fin_time[i];
		
		List N = G->neighbors[i];
		List L = C->neighbors[i];
		for (moveFront(N); index(N) >= 0; moveNext(N)) {
			append(L, get(N));
		}
	}

	return C;
}
