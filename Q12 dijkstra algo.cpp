#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;  
};
 
struct Graph
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 	for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->weight = weight;
    newNode->dest = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    newNode =  (struct AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->weight = weight;
    newNode->dest = src;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct MinHeapNode
{
    int  v;
    int dist;
};

struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int* pos;      // This is needed for decreaseKey()
    struct MinHeapNode** array;
};

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2*idx + 1;
    right = 2*idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
       	MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        struct MinHeapNode* t = minHeap->array[smallest];
        minHeap->array[smallest] = minHeap->array[idx];
        minHeap->array[idx] = t;
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (minHeap->size <= 0)
        return NULL;
    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = (minHeap->size)-1;
    minHeap->pos[lastNode->v] = 0;
    --(minHeap->size);
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i != 0 && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        struct MinHeapNode* t = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i-1)/2];
        minHeap->array[(i-1)/2] = t;
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
void printArr(int dist[], int n, int pred[])
{
    printf("Vertex   Distance from Source\t    Predecessor\n");
    for (int i = 0; i < n; ++i)
    	if(pred[i] == -1)
        printf("%d \t\t %d\t\t\tNULL\n", i, dist[i]);
        else
        printf("%d \t\t %d\t\t\t%d\n", i, dist[i], pred[i]);
}

void dijkstra(struct Graph* graph, int src)
{
    int V = graph->V;     // Get the number of vertices in graph
    int dist[V];          // dist values used to pick minimum weight edge in cut
    int pred[V];
    struct MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
    	pred[v] = -1;
        dist[v] = INT_MAX;
        minHeap->array[v] = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
        minHeap->array[v]->v = v;
        minHeap->array[v]->dist = dist[v];
        minHeap->pos[v] = v;
    }
    minHeap->array[src] =  (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeap->array[src]->v = src;
    minHeap->array[src]->dist = dist[src];
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (minHeap->size > 0)
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;      // Store the extracted vertex number
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && pCrawl->weight + dist[u] < dist[v])
            {
            	pred[v] = u;
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    printArr(dist, V, pred);
}
 
int main()
{
    int V = 9;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
    dijkstra(graph, 0);
    return 0;
}

