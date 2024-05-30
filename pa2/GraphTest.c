/***
* Adrian Olmos
* amolmos
* 2024 Winter CSE101 PA2
* GraphTest.c
* Tests the Graph ADT for correctness.
***/
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main() {
    Graph g = newGraph(6);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,4);
    addEdge(g,2,5);
    addEdge(g,2,6);
    addEdge(g,3,4);
    addEdge(g,5,4);
    addEdge(g,6,5);

    printGraph(stdout,g);

    BFS(g,4);
    List p=newList();
    getPath(p,g,1);
    
    printf("\nSource: %d\n",getSource(g));
    printf("Order:% d\n",getOrder(g));
    printf("Size: %d\n",getSize(g)); 
    printf("Distance from %d to %d is %d\n",getSource(g), 1, getDist(g,1));

    makeNull(g);
    printf("\nG after makeNull():\n");
    printGraph(stdout, g);

    g = newGraph(4);
    addArc(g,1,2);
    addArc(g,1,3);
    addArc(g,2,4);
    addArc(g,4,1);
    addArc(g,3,2);

    BFS(g,3);

    printf("\nNew graph: \n");
    printGraph(stdout, g);
    printf("\nSource: %d\n", getSource(g));
    printf("Order: %d\n", getOrder(g));
    printf("Size: %d\n", getSize(g));

    printf("Distance from %d to %d is %d\n",getSource(g),1,getDist(g,1));
    
    freeList(&p);
    freeGraph(&g);
    return (0);
}

