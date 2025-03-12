/*
Assignment 4
Student Name:   Annie Liu
Student ID:     1266956
Due Date:       November 29th, 2024
Course:         CIS*2520
*/

#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{  
    /* File validation*/
    FILE * fp = fopen(filename, "r");
    if (fp == NULL){
        printf("The file could not be opened.\n");
        return NULL;
    }

    char fileLine[MAX_VERTICES*2];
    int numVertices = 0;
    Graph * graph = malloc(sizeof(struct Graph));

    // reads a line from the file
    while(fgets(fileLine,MAX_VERTICES*2,fp) != NULL){
        graph->adjList[numVertices] = createNode(numVertices+1); // first node is initiated here with the vertex number (1-based)

        char * token = strtok(fileLine," ");
        int i = 0;
        while (token != NULL){
            graph->adjMatrix[numVertices][i] = atoi(token); // adjacency matrix created with tokens
            token = strtok(NULL, " ");
            i++;
        }
        numVertices++;
    }
    graph->numVertices = numVertices;

    fclose(fp);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex) // !
{
    Node * node = malloc(sizeof(Node));
    node->next = NULL;
    node->vertex = vertex;
    return node;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    printf("Adjacency List:\n");
    // for loop goes through vertices and then neighbouring vertices of each vertex
    for (int i = 0; i < graph->numVertices; i++){
        printf("Vertex %d:", graph->adjList[i]->vertex);
        Node * node = graph->adjList[i]->next;
        while(node != NULL){
            printf(" -> %d ", node->vertex);
            printf("(%d)", graph->adjMatrix[i][(node->vertex)-1] );
            node = node->next;
        }
        printf(" NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++){
        for (int j = 0; j < graph->numVertices; j++){
            if (graph->adjMatrix[i][j] != 0){ // if a weighted edge exists
                Node * node = createNode(j+1); // create a node with 1 base
                Node * travel = graph->adjList[i];
                while (travel->next != NULL){ // travel through linked list and add to the end of it
                    travel = travel->next;
                }
                travel->next = node;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    int queue[MAX_VERTICES] = {0}; // queue for keeping track of unvisited vertices
    int front = 0, rear = 0;

    int visitedSet[MAX_VERTICES] = {0};
    visitedSet[startVertex-1] = 1;
    
    // initialize queue
    queue[rear++] = startVertex;

    while (front < rear){ // while there are items in queue
        int curVertex = queue[front++];
        printf("%d ", curVertex);

        Node * travel = graph->adjList[curVertex-1];
        while (travel!=NULL){ // travels through neighbours of the current vertex and if not visited, add them to queue and set as visited
            int neighbour = travel->vertex;
            if (visitedSet[neighbour-1] == 0){
                queue[rear++] = neighbour;
                visitedSet[neighbour-1] = 1;
            }
            travel = travel->next;
        }
    }
    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    int stack[MAX_VERTICES] = {0};
    int top = -1;

    int visitedSet[MAX_VERTICES] = {0}; // index = vertex, 0 = false, 1 = true
    stack[++top] = startVertex;

    while (top != -1){
        int curVertex = stack[top--];
        int neighbours[MAX_VERTICES];
        int neighbourCount = 0;

        if (visitedSet[curVertex-1] == 0){ // if vertex not yet visited, set as visited and print it
            printf("%d ", curVertex);
            visitedSet[curVertex-1] = 1;
        }
        Node * travel = graph->adjList[curVertex-1];

        while (travel != NULL){
            if (visitedSet[travel->vertex-1] == 0){
                neighbours[neighbourCount++] = travel->vertex; // added to an array to visit in ascending order;
            }
            travel = travel->next;
        }
        for (int i = neighbourCount - 1; i > -1; i--){ // adds neighbours in reverse order so when popped from stack they're ascending
            stack[++top] = neighbours[i];
        }
    }
    printf("\n");
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    startVertex--;

    int distances[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};


    for (int i = 0; i < graph->numVertices; i++){ // initializes all distances as inf
        distances[i] = INT_MAX;
    }
    distances[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++){
        int minDistance = INT_MAX, minIndex = -1;

        for (int j = 0; j < graph->numVertices; j++){
            if (visited[j] == 0 && distances[j] <= minDistance){ // if vertex is unvisited and has a shorter distance, it is set as the new minimum distance and index is saved
                minDistance = distances[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) break; //  if no shorter distance is found then distance all vertices are visited
        visited[minIndex] = 1;

        for (int j = 0; j < graph->numVertices; j++){ // checks distance of all unvisited neighbours
            if (visited[j] == 0 && graph->adjMatrix[i][j] != 0 && distances[i] != INT_MAX && distances[i] + graph->adjMatrix[i][j] < distances[j]){ // if there exists a shorter distance, it is added
                distances[j] = distances[i] + graph->adjMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < graph->numVertices; i++){ // prints pathing
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex+1, i+1, distances[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++){ // iterates through all linked list heads of afjList and frees them
        Node * curNode = (graph->adjList)[i];
        Node * nextNode;
        while(curNode != NULL){
            nextNode = curNode->next;
            free(curNode);
            curNode = nextNode;
        }
    }
    free(graph); // finally, frees graph itself
}
