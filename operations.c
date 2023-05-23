#include "structs.h"

// Citire graf cerinta 1
Graph *Citire() {
    FILE *input_file = fopen("tema3.in", "r");
    if (input_file == NULL) {
        printf("Nu s-a putut deschide fisierul de intrare.\n");
        return NULL;
    }

    int num_vertices, num_edges;
    fscanf(input_file, "%d %d", &num_vertices, &num_edges);

    Graph *graph = createGraph(num_vertices);

    int i, j;
    int src_index = -1;
    int dest_index = -1;
    for (i = 0; i < num_edges; ++i) {
        char src[MAX_NAME_LENGTH];
        char dest[MAX_NAME_LENGTH];
        int distance;

        fscanf(input_file, "%s %s %d", src, dest, &distance);

        src_index = -1;
        dest_index = -1;

        for (j = 0; j < graph->num_vertices; ++j) {
            if (graph->node_names[j] == NULL) {
                graph->node_names[j] = strdup(src);
                src_index = j;
                break;
            }
            if (strcmp(graph->node_names[j], src) == 0) {
                src_index = j;
                break;
            }
        }

        for (j = 0; j < graph->num_vertices; ++j) {
            if (graph->node_names[j] == NULL) {
                graph->node_names[j] = strdup(dest);
                dest_index = j;
                break;
            }
            if (strcmp(graph->node_names[j], dest) == 0) {
                dest_index = j;
                break;
            }
        }

        if (src_index == -1 || dest_index == -1) {
            printf("Numele obiectivelor din fisierul de intrare nu corespund "
                   "cu nodurile din graf.\n");
            fclose(input_file);
            freeGraph(graph);
            return NULL;
        }

        addEdge(graph, src_index, dest_index, distance);
    }

    fclose(input_file);
    return graph;
}

// Citire graf cerinta 2
Graph *Citire2() {
    FILE *input_file = fopen("tema3.in", "r");
    if (input_file == NULL) {
        printf("Nu s-a putut deschide fisierul de intrare.\n");
        return NULL;
    }
    char src[MAX_NAME_LENGTH];
    char dest[MAX_NAME_LENGTH];
    int distance;
    int src_index = -1;
    int dest_index = -1;
    int i, j;
    int num_vertices, num_edges;
    fscanf(input_file, "%d %d", &num_vertices, &num_edges);

    Graph *graph = createGraph(num_vertices);
    for (i = 0; i < num_edges; ++i) {

        fscanf(input_file, "%s %s %d", src, dest, &distance);

        src_index = -1;
        dest_index = -1;

        for (j = 0; j < graph->num_vertices; ++j) {
            if (graph->node_names[j] == NULL) {
                graph->node_names[j] = strdup(src);
                src_index = j;
                break;
            }
            if (strcmp(graph->node_names[j], src) == 0) {
                src_index = j;
                break;
            }
        }

        for (j = 0; j < graph->num_vertices; ++j) {
            if (graph->node_names[j] == NULL) {
                graph->node_names[j] = strdup(dest);
                dest_index = j;
                break;
            }
            if (strcmp(graph->node_names[j], dest) == 0) {
                dest_index = j;
                break;
            }
        }

        if (src_index == -1 || dest_index == -1) {
            printf("Numele obiectivelor din fisierul de intrare nu corespund "
                   "cu nodurile din graf.\n");
            fclose(input_file);
            freeGraph(graph);
            return NULL;
        }

        addEdge2(graph, src_index, dest_index, distance);
    }
    for (i = 0; i < num_vertices; i++) {
        fscanf(input_file, "%s", src);
        for (j = 0; j < num_vertices; j++) {
            if (!strcmp(src, graph->node_names[j])) {
                fscanf(input_file, "%d", &graph->array[j].depth);
                break;
            }
        }
    }
    fscanf(input_file, "%d", &graph->comoara);
    fclose(input_file);
    return graph;
}

// Funcție pentru crearea unui nod nou în lista de adiacență
AdjListNode *newAdjListNode(int dest, int distance) {
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->distance = distance;
    newNode->next = NULL;
    return newNode;
}

// Funcție pentru adăugarea unei muchii în graf neorientat
void addEdge(Graph *graph, int src, int dest, int distance) {
    AdjListNode *newNode = newAdjListNode(dest, distance);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, distance);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Funcție pentru adăugarea unei muchii în graf orientat
void addEdge2(Graph *graph, int src, int dest, int distance) {
    AdjListNode *newNode = newAdjListNode(dest, distance);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Funcție pentru crearea unui graf cu num_vertices
Graph *createGraph(int num_vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;

    graph->node_names = (char **)malloc(num_vertices * sizeof(char *));
    graph->array = (AdjList *)malloc(num_vertices * sizeof(AdjList));
    graph->component = (int *)malloc(num_vertices * sizeof(int));

    int i;
    for (i = 0; i < num_vertices; ++i) {
        graph->node_names[i] = NULL;
        graph->array[i].head = NULL;
    }

    return graph;
}

void assignComponents(Graph *graph) {
    int numVertices = graph->num_vertices;
    int *visited = (int *)calloc(numVertices, sizeof(int));
    int component = 0, i;

    for (i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            component++;
            exploreComponent(graph, i, visited, component);
        }
    }
    graph->num_components = component;
    free(visited);
}

void exploreComponent(Graph *graph, int vertex, int *visited, int component) {
    visited[vertex] = 1;
    graph->component[vertex] = component;

    AdjListNode *crawl = graph->array[vertex].head;
    while (crawl != NULL) {
        int adjacentVertex = crawl->dest;
        if (!visited[adjacentVertex]) {
            exploreComponent(graph, adjacentVertex, visited, component);
        }
        crawl = crawl->next;
    }
}

Graph *createSubgraph(Graph *graph, int comp, int num) {
    Graph *subgraph = createGraph(num);
    int i;
    int src_index = -1;
    int dest_index = -1;
    int j, v, weight;
    char src[MAX_NAME_LENGTH], dest[MAX_NAME_LENGTH];
    subgraph->num_vertices = num;
    for (i = 0; i < graph->num_vertices; i++) {
        if (graph->component[i] == comp) {
            AdjListNode *crawl = graph->array[i].head;
            strcpy(src, graph->node_names[i]);
            while (crawl != NULL) {
                v = crawl->dest;
                strcpy(dest, graph->node_names[v]);
                weight = crawl->distance;
                src_index = -1;
                dest_index = -1;
                for (j = 0; j < subgraph->num_vertices; ++j) {
                    if (subgraph->node_names[j] == NULL) {
                        subgraph->node_names[j] = strdup(src);
                        src_index = j;
                        break;
                    }
                    if (strcmp(subgraph->node_names[j], src) == 0) {
                        src_index = j;
                        break;
                    }
                }

                for (j = 0; j < subgraph->num_vertices; ++j) {
                    if (subgraph->node_names[j] == NULL) {
                        subgraph->node_names[j] = strdup(dest);
                        dest_index = j;
                        break;
                    }
                    if (strcmp(subgraph->node_names[j], dest) == 0) {
                        dest_index = j;
                        break;
                    }
                }
                addEdge(subgraph, src_index, dest_index, weight);
                crawl = crawl->next;
            }
        }
    }
    return subgraph;
}

// Afișează arborele minim de acoperire folosind algoritmul lui Prim
int primMST(FILE *out, Graph *graph) {
    int numVertices = graph->num_vertices;
    int key[numVertices]; // Stochează valorile cheie utilizate pentru a alege
                          // muchiile de lungime minimă
    int mstSet[numVertices]; // Set pentru a urmări vârfurile incluse în
                             // arborele minim de acoperire
    int i, count, u, v, weight, totalWeight = 0;

    // Inițializează toate valorile cheie ca fiind infinit și mstSet ca fiind
    // fals (0)
    for (i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Primul vârf este întotdeauna rădăcina
    key[0] = 0;

    // Arborele minim de acoperire va avea numVertices - 1 muchii
    for (count = 0; count < numVertices; count++) {
        // Alegeți vârful cu cea mai mică valoare cheie din setul de vârfuri
        // care nu sunt încă incluse în arborele minim de acoperire
        u = findMinKey(key, mstSet, numVertices);

        // Adăugați vârful ales în arborele minim de acoperire
        mstSet[u] = 1;

        // Actualizați valorile cheie și părinții vârfurilor adiacente ale
        // vârfului selectat. Considerați doar vârfurile adiacente care nu sunt
        // încă incluse în arborele minim de acoperire
        AdjListNode *crawl = graph->array[u].head;
        while (crawl != NULL) {
            v = crawl->dest;
            weight = crawl->distance;

            if (mstSet[v] == 0 && weight < key[v]) {
                key[v] = weight;
            }

            crawl = crawl->next;
        }
    }

    // Afișează muchiile din arborele minim de acoperire
    for (i = 1; i < numVertices; i++) {
        totalWeight += key[i];
    }
    return totalWeight;
}

// Găsiți vârful cu cea mai mică valoare cheie într-un set de vârfuri care nu
// este încă inclus în arborele minim de acoperire
int findMinKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, min_index;
    int v;
    for (v = 0; v < numVertices; v++)
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

// Functie de comparare pentru qsort
int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

// Functie pentru alocare nod MinHead
MinHeapNode *newMinHeapNode(int v, float dist) {
    MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Funcție pentru verificarea existenței unui drum între doua noduri în graf
bool isPathExists(Graph *graph, int src, int dest, bool visited[]) {
    if (src == dest) {
        return true; // S-a găsit un drum între nodurile src și dest
    }

    visited[src] = true; // Se marchează nodul src ca vizitat

    // Se parcurg toate nodurile adiacente nodului src
    AdjListNode *curr = graph->array[src].head;
    while (curr != NULL) {
        int adjNode = curr->dest;

        // Dacă nodul adiacent nu a fost vizitat, se verifică dacă există drum
        if (!visited[adjNode]) {
            if (isPathExists(graph, adjNode, dest, visited)) {
                return true;
            }
        }

        curr = curr->next;
    }

    return false; // Nu s-a găsit un drum între nodurile src și dest
}

// Functie initializare MinHeap
MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap *minHeap) { return minHeap->size == 0; }

// Functie extragere minim din MinHeap
MinHeapNode *extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode *root = minHeap->array[0];
    MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap *minHeap, int v, float dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// Functie care verifica daca un nod se afla in MinHeap
bool isInMinHeap(MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

int dijkstra(Graph *graph, int src, int dest, int path[], int *k) {
    int V = graph->num_vertices;
    int u, v, index = 0;
    float dist[V];
    int distances[V];
    int parent[V];
    MinHeap *minHeap = createMinHeap(V);
    // Initializare minHeap
    for (v = 0; v < V; v++) {
        distances[v] = 0;
        dist[v] = INT_MAX;
        parent[v] = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    free(minHeap->array[src]);
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        MinHeapNode *minHeapNode = extractMin(minHeap);
        u = minHeapNode->v;
        free(minHeapNode);
        AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                pCrawl->scor + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->scor;
                distances[v] = distances[u] + pCrawl->distance;
                parent[v] = u;
                index++;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    int current = dest;
    index = 0;
    while (current != -1) {
        path[index] = current;
        index++;
        current = parent[current];
    }
    *k = index;
    freeMinHeap(minHeap);
    return distances[dest];
}

// Ia indexul Corabiei
int getIndexSrc(Graph *graph) {
    int i;
    for (i = 0; i < graph->num_vertices; i++) {
        if (!strcmp(graph->node_names[i], "Corabie")) {
            return i;
        }
    }
    printf("Nu s-a gasit corabia\n");
    return -1;
}

// Ia indexul Insulei
int getIndexDest(Graph *graph) {
    int i;
    for (i = 0; i < graph->num_vertices; i++) {
        if (!strcmp(graph->node_names[i], "Insula")) {
            return i;
        }
    }
    printf("Nu s-a gasit insula\n");
    return -1;
}

// Functie dezalocare graf
void freeGraph(Graph *graph) {
    if (graph == NULL) {
        return;
    }

    int i;
    for (i = 0; i < graph->num_vertices; ++i) {
        AdjListNode *currentNode = graph->array[i].head;
        while (currentNode != NULL) {
            AdjListNode *nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
        free(graph->node_names[i]);
    }
    free(graph->component);
    free(graph->array);
    free(graph->node_names);
    free(graph);
}

// Functie dezalocare MinHeap
void freeMinHeap(MinHeap *minHeap) {
    int i;
    if (minHeap == NULL) {
        return;
    }

    // Eliberarea memoriei pentru array
    for (i = 0; i < minHeap->size; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);

    // Eliberarea memoriei pentru pos
    free(minHeap->pos);

    // Eliberarea memoriei pentru minHeap
    free(minHeap);
}
