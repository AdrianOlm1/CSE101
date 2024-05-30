#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

typedef struct GraphObj {
    List* neigh;
    int *color;
    int *parent;
    int *dist;
    int size;
    int src;
    int order;
} GraphObj;

void listIns(List l, int a) {
    if(length(l)==0) {
        append(l,a);
        return;
    }

    for(moveFront(l);index(l)!=-1;moveNext(l)) {
        if(a<get(l)) {
            insertBefore(l,a);
            break;
        }
    }

    if(index(l)==-1)
        append(l,a);
}

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(struct GraphObj));
    G->neigh = calloc(n+1, sizeof(List));
    G->color=calloc(n+1,sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->dist = calloc(n+1,sizeof(int));

    for(int i=1;i<=n;++i) {
        G->neigh[i]=newList();
        G->color[i]=WHITE;;
        G->parent[i]=NIL;
        G->dist[i]=INF;
    }
    G->size=0;
    G->src=NIL;
    G->order=n;
    return G;
}
void freeGraph(Graph* pG) {
    Graph g = *pG;
    for(int i=1;i<=getOrder(g);++i){
        freeList(&(g->neigh[i]));
    }
    free(g->color);
    free(g->parent);
    free(g->dist);
    free(g->neigh);
    free(*pG);
    *pG=NULL;
}
/*** Access functions ***/
int getOrder(Graph G) {
    return G->order;
}
int getSize(Graph G) {
    return G->size;
}
int getSource(Graph G) {
    return G->src;
}
int getParent(Graph G, int u) {
    if(u<1 && u>getOrder(G)) {
        printf("Error: Cannot perform getParent on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
int getDist(Graph G, int u) {
    if (u < 1 && u > getOrder(G)){
        printf("Error: Cannot perform getDist() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }

    if (getSource(G) == NIL) 
        return INF;
    else 
        return G->dist[u];
}
void getPath(List L, Graph G, int u) {
    if (u < 1 && u > getOrder(G)){
        printf("Error: Cannot perform getPath() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }

    int p = G->parent[u];
    int s = getSource(G);

    if(s==NIL) {
        printf("Error: Cannot perform getPath() with invalid source\n");
        exit(EXIT_FAILURE);
    }

    if(u==s)
        append(L,s);
    else if (p==NIL)
        append(L,NIL);
    else {
        getPath(L,G,p);
        append(L,u);
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G) {
    for(int i=1;i<=getOrder(G);++i) {
        clear(G->neigh[i]);
    }
    G->size=0;
}
void addEdge(Graph G, int u, int v) {
    if(((u<1&&u>(getOrder(G)))||(v<1&&v>getOrder(G)))) {
        printf("Error: cannot perform addEdge() on invalid verticies");
        exit(EXIT_FAILURE);
    }

    List A=G->neigh[u];
    List B=G->neigh[v];

    listIns(A,v);
    listIns(B,u);
    G->size++;
}
void addArc(Graph G, int u, int v) {
    if((u<1&&u>(getOrder(G)))||(v<1&&v>getOrder(G))) {
        printf("Error: cannot perform addArc() on invalid verticies");
        exit(EXIT_FAILURE);
    }

    List A=G->neigh[u];

    listIns(A,v);
    G->size++;
}
void BFS(Graph G, int s) {
    for (int i=1;i<=getOrder(G);++i){
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = WHITE;
    }

    G->color[s] = GRAY;
    G->parent[s] = NIL;
    G->src = s;
    G->dist[s] = 0;

    List l = newList();
    append(l, s);

    while (length(l) > 0){
        int a=front(l);
        deleteFront(l);
        List adjacent= G->neigh[a];

        for (moveFront(adjacent);index(adjacent)!=-1;moveNext(adjacent)){
            int y=get(adjacent);
            if (G->color[y]==WHITE){
                G->color[y]=GRAY;
                G->dist[y]=G->dist[a] + 1;
                G->parent[y]=a;
                append(l,y);
            }
        }
        G->color[a] = BLACK;
    }
    freeList(&l);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    for(int i=1;i<=getOrder(G);++i) {
        List l=G->neigh[i];
        fprintf(out,"%d: ",i);
        for(moveFront(l);index(l)!=-1;moveNext(l)) {
            fprintf(out,"%d ",get(l));
        }
        fprintf(out,"\n");
    }
}
