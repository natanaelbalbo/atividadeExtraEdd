#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    int V;
    AdjList* array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

Node* newNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* node = newNode(dest);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    node = newNode(src);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

void removeEdge(Graph* graph, int src, int dest) {
    Node* temp = graph->array[src].head;
    Node* prev = NULL;

    while (temp != NULL && temp->dest != dest) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (prev != NULL)
        prev->next = temp->next;
    else
        graph->array[src].head = temp->next;

    free(temp);

    // Remover a aresta para grafos não direcionados
    temp = graph->array[dest].head;
    prev = NULL;

    while (temp != NULL && temp->dest != src) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (prev != NULL)
        prev->next = temp->next;
    else
        graph->array[dest].head = temp->next;

    free(temp);
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        Node* temp = graph->array[v].head;
        printf("\n Lista de adjacência do vértice %d\n cabeça ", v);
        while (temp) {
            printf("-> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    printf("\nRemovendo aresta 1-4\n");
    removeEdge(graph, 1, 4);
    printGraph(graph);

    return 0;
}
