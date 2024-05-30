#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
    FILE* in, * out;
    Graph g,t;
    List l=newList(), *strongCon;
    int num,u,v,x,compNum=0;
    
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((in = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((out = fopen(argv[2], "w")) == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    fscanf(in," %d",&num);
    g=newGraph(num);
    while (fscanf(in," %d %d",&u,&v)==2&&u!=0&&v!=0) {
        addArc(g,u,v);
    }

    fprintf(out,"Adjacency list representation of G:\n");
    printGraph(out,g);
    fprintf(out,"\n");
    t = transpose(g);

    for (int i=1;i<=num;i++) {
        append(l,i);
    }

    DFS(g, l);
    DFS(t, l);
    for (int i = 1; i <= num; i++) {
        if (getParent(t, i) == NIL) {
            x++;
        }
    }

    strongCon = calloc(x, sizeof(List));
    for (int i=0;i<x;i++) {
        strongCon[i] = newList();
    }

    for(moveBack(l);index(l)!=-1;movePrev(l)) {
        int y = get(l);
        prepend(strongCon[compNum], y);
        if (getParent(t, y) == NIL) {
            compNum++;
        }
    }

    fprintf(out, "G contains %d strongly connected components:\n", x);
    for (int i=0;i<x;i++) {
        fprintf(out,"Component %d: ", i + 1);
        printList(out,strongCon[i]);
        fprintf(out,"\n");
        freeList(&strongCon[i]);
    }

    freeGraph(&g);
    freeGraph(&t);
    freeList(&l);
    free(strongCon);
    fclose(in);
    fclose(out);
    return 0;
}