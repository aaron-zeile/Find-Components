/*** FindComponents.c ***/
/*** Aaron Zeile ***/
/*** ID: azeile ***/
/*** pa3 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {
	// if not two command line arguments
	if (argc != 3) {
		fprintf(stderr, "Error. Must have exactly 2 command line arguments.\n");
		exit(EXIT_FAILURE);
	}

	char line[MAX_LEN];
	char tokenBuffer[MAX_LEN];
	char *token;
	int token_count = 0;
	int vertex[2];

	// open files for reading and writing
	FILE *in = fopen(argv[1], "r");
	if (!in) {
		fprintf(stderr, "Error. Couldn't open input file.\n");
		exit(EXIT_FAILURE);
	}

	FILE *out = fopen(argv[2], "w");
	if (!out) {
		fprintf(stderr, "Error. Couldn't open output file.\n");
		exit(EXIT_FAILURE);
	}

	// read first line to get n
	int n = atoi(fgets(line, MAX_LEN, in));
	Graph G = newGraph(n);

// load and print adjacency list ---------------------------------------------------------
	while (atoi(fgets(line, MAX_LEN, in)) != 0)  {
	      	// get tokens in this line
	      	tokenBuffer[0] = '\0';
		token_count = 0;

      		// get first token
      		token = strtok(line, " \n");
      
      		while (token) { // we have a token
         		// update token buffer
         		strcat(tokenBuffer, "   ");
         		strcat(tokenBuffer, token);
         		strcat(tokenBuffer, " \n");

         		// get next token
			vertex[token_count] = atoi(token);
			token_count++;
      			token = strtok(NULL, " \n");
      		}

      		// print tokens in this line
		addArc(G, vertex[0], vertex[1]);
   	}	
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

// perform DFS twice ----------------------------------------------------------------------
	// Create stack
	List S = newList();
	for (int i = 1; i < n+1; i++) {
		append(S, i);
	}

	// First DFS call fills stack in
	// order of decreasing finish times
	DFS(G, S);

	// Get transpose of graph G
	Graph T = transpose(G);
	
	// Second DFS call processes stack
	// and gives the SSCs
	DFS(T, S);
	
// find and print strongly connected components -------------------------------------------

	// get number of SCCs and append nodes with no parent
	int counter = 0;
	for (int i = 1; i < n+1; i++) {
		int parent = getParent(T, i);
		if (parent == NIL) {
			counter++;
		}
	}

	// print SCCs
	fprintf(out, "\nG contains " FORMAT " strongly connected components:\n", counter);

	moveBack(S);
	for (int i = 1; i < counter+1; i++) {
		List C = newList();
		while (index(S) >= 0) {
			int curr = get(S);
			int parent = getParent(T, curr);
			prepend(C, curr);
			movePrev(S);
			if (parent == NIL) {
				break;
			}
		}
		fprintf(out, "Component " FORMAT ": ", i);
		printList(out, C);
		freeList(&C);
	}
	
// free all heap memory -------------------------------------------------------------------
	fclose(in);
	fclose(out);
	freeList(&S);
	freeGraph(&T);
	freeGraph(&G);
  return 0;
}
