#include "structs.h"

int main(int argc, char const *argv[]) {
    Graph *graph;
    if (argc < 2) {
        printf("Nu s-au specificat toate argumentele necesare");
        return 1;
    }
    if (strstr(argv[1], "1")) { // Cerinta 1
        graph = Citire();
        int i, j, num = 0;
        int *subgraphStart = (int *)malloc(graph->num_vertices * sizeof(int));
        FILE *out = fopen("tema3.out", "w");
        assignComponents(graph);
        Graph **subgraphs =
            (Graph **)malloc(graph->num_components * sizeof(Graph *));
        fprintf(out, "%d\n", graph->num_components);
        if (graph->num_components > 1) {
            int *costs = (int *)malloc(graph->num_components * sizeof(int));
            for (i = 0; i < graph->num_components; i++) {
                for (j = 0; j < graph->num_vertices; j++) {
                    if (graph->component[j] == i + 1) {
                        num++;
                    }
                }
                subgraphs[i] = createSubgraph(graph, i + 1, num);
                num = 0;
            }
            for (i = 0; i < graph->num_components; i++) {
                costs[i] = primMST(out, subgraphs[i]);
            }
            qsort(costs, graph->num_components, sizeof(int), cmpfunc);
            for (i = 0; i < graph->num_components; i++) {
                fprintf(out, "%d\n", costs[i]);
            }
            for (i = 0; i < graph->num_components; i++) {
                freeGraph(subgraphs[i]);
            }
            free(costs);
            free(subgraphs);
            free(subgraphStart);
        } else {
            int cost = 0;
            cost = primMST(out, graph);
            fprintf(out, "%d\n", cost);
            free(subgraphs);
            free(subgraphStart);
        }
        fclose(out);
    } else { // Cerinta 2
        graph = Citire2();
        int i;
        int indexDest = getIndexSrc(graph); // Corabia
        int indexSrc = getIndexDest(graph); // Insula
        bool visited[graph->num_vertices];
        FILE *out = fopen("tema3.out", "w");
        for (i = 0; i < graph->num_vertices; i++) {
            visited[i] = 0;
        }
        if (isPathExists(graph, indexDest, indexSrc, visited)) {
            for (i = 0; i < graph->num_vertices; i++) {
                visited[i] = 0;
            }
            if (isPathExists(graph, indexSrc, indexDest, visited)) {
                for (i = 0; i < graph->num_vertices; i++) {
                    AdjListNode *pCrawl = graph->array[i].head;
                    while (pCrawl) {
                        pCrawl->scor = (float)pCrawl->distance /
                                       (float)graph->array[pCrawl->dest].depth;
                        pCrawl = pCrawl->next;
                    }
                }
                int path[graph->num_vertices], k = 0, distFinal, MinDepth,
                                               drumuri = 0;
                distFinal = dijkstra(graph, indexSrc, indexDest, path, &k);
                MinDepth = graph->array[path[k - 2]].depth;
                for (i = k - 1; i >= 0; i--) {
                    fprintf(out, "%s ", graph->node_names[path[i]]);
                    if (graph->array[path[i]].depth < MinDepth && i != k - 1 &&
                        i != 0) {
                        MinDepth = graph->array[path[i]].depth;
                    }
                }
                fprintf(out, "\n");
                fprintf(out, "%d\n", distFinal);
                fprintf(out, "%d\n", MinDepth);
                drumuri = graph->comoara / MinDepth;
                if (drumuri * MinDepth != graph->comoara) {
                    drumuri++;
                }
                fprintf(out, "%d\n", drumuri);

            } else {
                fprintf(
                    out,
                    "Echipajul nu poate transporta comoara inapoi la corabie");
            }
        } else {
            fprintf(out, "Echipajul nu poate ajunge la insula");
        }
        fclose(out);
    }
    freeGraph(graph);
    return 0;
}