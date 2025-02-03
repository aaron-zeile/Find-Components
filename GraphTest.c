/*** Aaron Zeile ***
**** azeile ********
**** GraphTest.c ***
**** pa3 **********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
	
	Graph A = newGraph(8);
//	printf("discover time: " FORMAT "\n", getDiscover(A, 1));
//	printf("finish time: " FORMAT "\n", getFinish(A, 2));

	addArc(A, 1, 2);
	addArc(A, 2, 3);
	addArc(A, 2, 5);
	addArc(A, 2, 6);
	addArc(A, 3, 4);
	addArc(A, 3, 7);
	addArc(A, 4, 3);
	addArc(A, 4, 8);
	addArc(A, 5, 1);
	addArc(A, 5, 6);
	addArc(A, 6, 7);
	addArc(A, 7, 6);
	addArc(A, 7, 8);
	addArc(A, 8, 8);
	
	printf("regular graph:\n");
	printGraph(stdout, A);
	printf("\n");

	List L = newList();
	for (int i = 1; i < getOrder(A)+1; i++) {
		append(L, i);
	}
	DFS(A, L);

	for (int i = 1; i < getOrder(A)+1; i++) {
		printf("PARENT OF " FORMAT ": " FORMAT "\n", i, getParent(A, i));
	}

	printList(stdout, L);

//	Graph C = copyGraph(A);
//	printf("\ncopied graph:\n");
//	printGraph(stdout, C);
//	printf("\n");

	
//	for (int i = 1; i < getOrder(A)+1; i++) {
//		printf("PARENT OF " FORMAT ": " FORMAT "\n", i, getParent(C, i));
//	}

//	for (int i = 1; i < getOrder(A)+1; i++) {
//		printf("finish time of " FORMAT ": " FORMAT "\n", i, getFinish(A, i));
//	}

	Graph T = transpose(A);
	printf("transpose graph:\n");
	printGraph(stdout, T);
	printf("\n");
	
	DFS(T, L);
	
	for (int i = 1; i < getOrder(A)+1; i++) {
		printf("PARENT OF " FORMAT ": " FORMAT "\n", i, getParent(T, i));
	}

	printList(stdout, L);
//	printf("discover time: " FORMAT "\n", getDiscover(T, 1));
//	printf("finish time: " FORMAT "\n", getFinish(T, 2));

	freeList(&L);
	freeGraph(&A);
//	freeGraph(&C);
	freeGraph(&T);

  return 0;
}
