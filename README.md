# INTRODUCTION
This program reads an input file and uses it to create a directed graph. Then, it processes the graph and prints its adjacency list and strongly connected components to an output file.

# INPUT FORMAT
Input files to be utilized by the program are formatted as such:
- The first line will be a single integer indicating the number of vertices in the graph. 
- The following lines will consist of two integers (separated by a space), each representing a vertex, which indicates a directed edge connecting the two given vertices from the first vertex to the second. For example, a line "2 9" would indicate an edge going from vertex 2 to vertex 9.
- Finally, the file is terminated with another dummy line "0 0," letting the program know to stop reading.

# List.h
Header file containing the function prototypes for the list ADT.

# List.c
Contains bodies of each function for the list ADT.

# Graph.h
Header file containing the function prototypes for the graph ADT.

# Graph.c
Contains bodies of each function for the graph ADT.

# FindComponents.c
Reads data from input file and uses it to create a graph. Processes the graph and prints its adjacency list and strongly connected components to output file.
