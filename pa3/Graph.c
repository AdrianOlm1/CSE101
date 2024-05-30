#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

typedef struct GraphObj {
    List* adj;
    int *color;
    int *parent;
    int *finish;
    int *discover; 
    int order;
    int size;
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n) {
    Graph G = malloc(sizeof(struct GraphObj));
    G->adj = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->discover = malloc((n+1) * sizeof(int));
    G->finish = malloc((n+1) * sizeof(int));  

    for(int i=1;i<=n;++i) {
        G->adj[i]=newList();
        G->color[i]=WHITE;;
        G->parent[i]=NIL;
        G->finish[i]=UNDEF;
        G->discover[i]=UNDEF;
    }
    G->size=0;
    G->order=n;
    return G;
}

void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) {
        for(int i=1;i<=(*pG)->order;++i) {
            freeList(&((*pG)->adj[i]));
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->finish);
        free((*pG)->discover);
        free(*pG);
        *pG=NULL;
    }
}

// Access functions
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "getOrder() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "getSize() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// Pre: 1<=u<=n=getOrder(G) 
int getParent(Graph G, int u){
    if (G == NULL) {
        printf("Error: cannot perform getParent() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u<1 || u>getOrder(G)) {
        printf("Error: Cannot perform getParent on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
 
// Pre: 1<=u<=n=getOrder(G) 
int getDiscover(Graph G, int u) {
    if(u<1 || u>getOrder(G)) {
        printf("Error: Cannot perform getDiscover() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
    if(u<1 || u>getOrder(G)) {
        printf("Error: Cannot perform getFinish on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation procedures
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v) {
    if (v > getOrder(G) || u > getOrder(G) || v < 1 || u < 1) {
        printf("addArc(): invalid vertex index\n");
        exit(1);
    }
    List L = G->adj[u];
    if (length(L) == 0) {
        append(L, v);
    } else {
        for (moveFront(L); index(L) >= 0; moveNext(L)) {
            if (v < get(L)) {
                insertBefore(L, v);
                break;
            } else if (v == get(L)) {
                // Arc already exists, do nothing
                return;
            }
        }
        if (index(L) < 0) {
            append(L, v);
        }
    }

    G->size++;
}

// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v) {
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S){
    for(int i = 0; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    List temp = copyList(S);
    clear(S);
    moveFront(temp);
    while(index(temp) >= 0){
        int vertex = get(temp);
        if(G->color[vertex] == WHITE){
            visit(G, vertex, &time, S);
        }
        moveNext(temp);
    }
    freeList(&temp);
} 

void visit(Graph G, int x, int *time, List S){
    G->discover[x] = ++(*time);
    G->color[x] = GRAY;
    List L = G->adj[x];
    moveFront(L);
    while (index(L) >= 0) {
        int y = get(L);
        if(G->color[y] == WHITE){
            G->parent[y] = x;
            visit(G, y, time, S);
        }
        moveNext(L);
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(*time);
    prepend(S, x);
}

// Other Functions
Graph transpose(Graph G){
    int n = getOrder(G);
    Graph T = newGraph(n);
    for (int u = 1; u <= n; u++) {
        List adj = G->adj[u];
        for(moveFront(adj);index(adj)!=-1;moveNext(adj)) {
            int v = get(adj);
            addArc(T, v, u);
        }
    }
    return T;
}

Graph copyGraph(Graph G){
    int n = getOrder(G);
    Graph C = newGraph(n);
    for (int u = 1; u <= n; u++) {
        List adj = G->adj[u];
        for(moveFront(adj);index(adj)!=-1;moveNext(adj)) {
            int v = get(adj);
            addArc(C, u, v);
        }
    }
    return C;
}

void printGraph(FILE* out , Graph G){
    for(int i=1;i<=getOrder(G);++i) {
        List l=G->adj[i];
        fprintf(out,"%d: ",i);
        for(moveFront(l);index(l)!=-1;moveNext(l)) {
            fprintf(out,"%d ",get(l));
        }
        fprintf(out,"\n");
    }
}
