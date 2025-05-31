# DFS and BFS Implementation in C

## Description

This repository contains the implementation of **Depth-First Search (DFS)** and **Breadth-First Search (BFS)** in the C programming language. These fundamental graph traversal algorithms are essential for understanding more complex graph-related problems and are commonly used in a wide range of applications, including network analysis, pathfinding, and solving puzzles.

---

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Usage](#usage)
- [Code](#code)
  - [DFS Implementation](#dfs-implementation)
  - [BFS Implementation](#bfs-implementation)
- [Author](#author)
- [References](#references)
- [License](#license)

---

## Features

✅ **Implements DFS with:**

- Edge classification
- DFS discovery and completion times
- Component detection

✅ **Implements BFS with:**

- Level-based traversal
- Shortest distance calculation from the source

✅ **Supports:**

- Directed and undirected graphs
- Dynamic input of vertices and edges

---

## Usage

1. Compile the C code using a C compiler, e.g.:
   ```
   gcc dfs.c -o dfs
   ```
2. Run the executable:
   ```
   ./dfs.exe
   ```
3. Input the number of vertices and the adjacency matrix as prompted.
4. Provide the starting node and the algorithm will give it's desired result.
5. The compilation and execution process of DFS is shown. The process is same for BFS.

---

## Code

### DFS Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// macro and global variables

# define MAX 30

int ds = 0; // dfs start time
int dc = 0; // dfs completion time
int dfsIdx = 0; // dfs array index

/*
++++++++++++++++++++++++++++++++ Graph Structure ++++++++++++++++++++++++++++++++
*/

typedef struct Graph{
	int vertices; // total number of vertices
	int visited[MAX]; // visited verices
	int adjM[MAX][MAX]; // adjacency matrix
	int dfsNo[MAX]; // dfs number array
	int dfsCompNo[MAX]; // dfs completion number array
}Graph;

/*
++++++++++++++++++++++++++++++++ DFS function and Edge Classification ++++++++++++++++++++++++++++++++
*/

void edgeClassification(Graph *g, int v1, int v2){

	if(!g->visited[v2]){
		printf("Tree Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] > g->dfsNo[v2] && g->dfsCompNo[v2] == 0){
		printf("Back Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] < g->dfsNo[v2] && g->dfsCompNo[v2] != 0){
		printf("Forward Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] > g->dfsNo[v2] && g->dfsCompNo[v2] != 0){
		printf("Cross Edge: (%d ---> %d)\n", v1, v2);
	}
}

void dfs(Graph *g, int start, int *arr){
	int i;

	arr[dfsIdx] = start;
	dfsIdx++;
	g->visited[start] = 1;
	g->dfsNo[start] = ++ds;

	for(i = 0; i< g->vertices; i++){
		if(g->adjM[start][i] == 1){
			// edge exists

			edgeClassification(g, start, i); // edge classification

			if(!g->visited[i]){
				// not visited i

				dfs(g, i, arr); // recursive call
			}
		}
	}
	g->dfsCompNo[start] = ++dc;
}
```

### BFS Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 50

typedef struct Queue {
    int data[MAX];
    int front;
    int rear;
} Queue;

/*
++++++++++++++++++++++++++++++++ Graph Structure ++++++++++++++++++++++++++++++++
*/


typedef struct Graph {
    int vertices;
    int adjM[MAX][MAX];
    int visited[MAX];
    int dist[MAX];
} Graph;

/*
++++++++++++++++++++++++++++++++ BFS and shortest distance for an unweighted graph ++++++++++++++++++++++++++++++++
*/


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
```

---

## Author

**Priyam Bhattacharya**  
M.Sc. in Computer Science, University of Calcutta  
GitHub: [itspriyambhattacharya](https://github.com/itspriyambhattacharya)  
Email: itspriyambhattacharya@gmail.com

---

## References

- Cormen, Thomas H., et al. _Introduction to Algorithms_, 3rd Edition, MIT Press.
- Sedgewick, Robert, and Kevin Wayne. _Algorithms_, 4th Edition, Addison-Wesley.
- GeeksforGeeks. [Depth First Search (DFS) for a Graph](https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/)
- GeeksforGeeks. [Breadth First Search (BFS) for a Graph](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
