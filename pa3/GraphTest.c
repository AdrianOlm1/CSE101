#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main() {
    List p=newList();
    Graph g = newGraph(6);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,4);
    addEdge(g,2,5);
    addEdge(g,2,6);
    addEdge(g,3,4);
    addEdge(g,5,4);
    addEdge(g,6,5);

    for(int i=1;i<=6;++i) {
        append(p,i);
    }

    printf("Printing first Graph:\n");
    printGraph(stdout,g);
    
    DFS(g,p);
    printf("\n");
    for(int i=1;i<=6;++i) {
        printf("Vertex: %d, Discovery: %d, Finish: %d, Parent: %d\n",i,getDiscover(g,i),getFinish(g,i),getParent(g,i));
    }

    Graph c = copyGraph(g);

    printf("\nTesting copy Graph\n");
    printGraph(stdout,c);

    Graph a = newGraph(6);
    addArc(a,1,2);
    addArc(a,1,3);
    addArc(a,2,4);
    addArc(a,2,5);
    addArc(a,2,6);
    addArc(a,3,4);
    addArc(a,5,4);
    addArc(a,6,5);

    printf("\nPrinting arc graph to test transpose\n");
    printGraph(stdout,a);

    printf("\nTranspose graph test:\n");
    Graph h = transpose(a);
    printGraph(stdout,h);   
    
    freeGraph(&h);
    freeGraph(&c);
    freeList(&p);
    freeGraph(&g);
    return (0);
}
