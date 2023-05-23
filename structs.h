#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 25

// Structura pentru nodul din lista de adiacență
typedef struct AdjListNode {
    int dest;
    int distance;
    float scor;
    struct AdjListNode *next;
} AdjListNode;

// Structura pentru lista de adiacență
typedef struct AdjList {
    AdjListNode *head;
    int depth;
} AdjList;

// Structura pentru graful cu liste de adiacență
typedef struct Graph {
    int *component;
    int num_vertices;
    int num_components;
    char **node_names;
    int comoara;
    AdjList *array;
} Graph;

// Structura min heap node
typedef struct MinHeapNode {
    int v;
    float dist;
} MinHeapNode;

// Structura min heap
typedef struct MinHeap {

    int size;
    int capacity;

    // Necesar pentru decreaseKey()
    int *pos;
    MinHeapNode **array;
} MinHeap;

AdjListNode *newAdjListNode(int dest, int distance);
Graph *createGraph(int num_vertices);
void addEdge(Graph *graph, int src, int dest, int distance);
void addEdge2(Graph *graph, int src, int dest, int distance);
void freeGraph(Graph *graph);
Graph *Citire();
Graph *Citire2();
int primMST(FILE *out, Graph *graph);
int findMinKey(int key[], int mstSet[], int numVertices);
void assignComponents(Graph *graph);
void exploreComponent(Graph *graph, int vertex, int *visited, int component);
Graph *createSubgraph(Graph *graph, int subgraphStart, int num);
int cmpfunc(const void *a, const void *b);
int dijkstra(Graph *graph, int src, int dest, int path[], int *k);
bool isInMinHeap(MinHeap *minHeap, int v);
void decreaseKey(MinHeap *minHeap, int v, float dist);
MinHeapNode *extractMin(MinHeap *minHeap);
int isEmpty(MinHeap *minHeap);
void minHeapify(MinHeap *minHeap, int idx);
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);
MinHeap *createMinHeap(int capacity);
MinHeapNode *newMinHeapNode(int v, float dist);
int getIndexSrc(Graph *graph);
void freeMinHeap(MinHeap *minHeap);
int getIndexDest(Graph *graph);
bool isPathExists(Graph *graph, int src, int dest, bool visited[]);