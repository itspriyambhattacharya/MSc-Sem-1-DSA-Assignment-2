#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 50

typedef struct Queue {
    int data[MAX];
    int front;
    int rear;
} Queue;

typedef struct Graph {
    int vertices;
    int adjM[MAX][MAX];
    int visited[MAX];
    int dist[MAX];
} Graph;

// Queue Functions
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}

void enqueue(Queue *q, int elem) {
    if ((q->rear + 1) % MAX == q->front) {
        printf("Queue is full! Cannot enqueue %d\n", elem);
        return;
    }
    if (q->front == -1) {
        q->front = 0; // Reset front if queue was empty
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = elem;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    int x = q->data[q->front];

    if (q->front == q->rear) {
        initializeQueue(q);
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return x;
}

// Graph Functions
void initializeGraph(Graph *g, int v) {
    g->vertices = v;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            g->adjM[i][j] = 0;
        }
        g->visited[i] = 0;
        g->dist[i] = INT_MAX;
    }
}

void addEdge(Graph *g, int src, int dest, int dOrUd) {
    g->adjM[src][dest] = 1;
    if(dOrUd == 2){
    	g->adjM[dest][src] = 1;
	}
}

void display(Graph *g) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%d ", g->adjM[i][j]);
        }
        printf("\n");
    }
}

void bfs(Graph *g, int start) {
    Queue q;
    initializeQueue(&q);
    
    printf("BFS Traversal:\n");
    enqueue(&q, start);
    g->visited[start] = 1; // Mark as visited when enqueued
    g->dist[start] = 0;

    while (!isEmpty(&q)) {
        int x = dequeue(&q);
        printf("%d ", x);

        for (int i = 0; i < g->vertices; i++) {
            if (g->adjM[x][i] == 1 && !g->visited[i]) {
                enqueue(&q, i);
                g->visited[i] = 1; // Mark as visited when enqueued
                g->dist[i] = g->dist[x] + 1;
            }
        }
    }
    printf("\n");
}

// Main Function
int main(void) {
    Graph g;
    int v, e, start, destination;
    int i; // loop
    int dOrUd; // directed graph or undirected graph

    printf("\nEnter number of vertices: ");
    scanf("%d", &v);

    printf("\nEnter number of edges: ");
    scanf("%d", &e);
    
    printf("\nEnter \"1\" for directed graph and \"2\" for undirected graph:\t");
	scanf("%d", &dOrUd);

    initializeGraph(&g, v);

    for (int i = 0; i < e; i++) {
        int src, dest;
        printf("\nEnter source and destination vertices: ");
        scanf("%d %d", &src, &dest);
        addEdge(&g, src, dest, dOrUd);
    }

    display(&g);

    printf("\nEnter the start vertex: ");
    scanf("%d", &start);
    
    printf("\nEnter the destination vertex: ");
    scanf("%d", &destination);

    if (start < 0 || start >= v) {
        printf("Invalid start vertex.\n");
        return 1;
    }
    
    if (destination < 0 || destination >= v) {
        printf("Invalid destination vertex.\n");
        return 1;
    }

    bfs(&g, start);
    for(i = 0; i< v; i++){
    	if(!g.visited[i]){
    		bfs(&g, i);
		}
	}
    
    printf("\nThe distance array is:");
    for(i=0; i< v; i++){
    	printf("%d\t", g.dist[i]);
	}
	
	printf("\nThe distance from %d to %d is %d\n", start, destination, g.dist[destination]);

    return 0;
}
