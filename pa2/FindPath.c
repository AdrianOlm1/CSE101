#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
    if(argc!=3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialization
    int num = 0;
    int vA = 0;
    int vB = 0;
    int src = 0;
    int end = 0;

    // Opening files and ensuring their open
    FILE *in = fopen(argv[1],"r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(argv[2],"w");
    if (out == NULL) {
        printf("Unable to open file %s for reading\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Creating graph using first line
    fscanf(in, "%d", &num);
    Graph g = newGraph(num);

    // Get vertices and insert into graph
    while (fgetc(in) != EOF){
        fscanf(in, "%d", &vA);
        fscanf(in, "%d", &vB);

        if (vA == 0 && vB == 0) 
            break;
        else 
            addEdge(g, vA, vB);
    }

    printGraph(out, g);
    fprintf(out, "\n");

    // Do BFS
    while (fgetc(in) != EOF){
        fscanf(in, "%d", &src);
        fscanf(in, "%d", &end);

        // Trival path
        if (src == 0 && end == 0)
        break;

        List l = newList();
        BFS(g, src);
        getPath(l, g, end);
        int dist = getDist(g, end);

        // If path doesn't exist
        if(dist == -2){
            fprintf(out, "The distance from %d to %d is infinity\n", src, end);
            fprintf(out, "No %d-%d path exists\n", src, end);
        }
        // Outputting
        else {
            fprintf(out, "The distance from %d to %d is %d\n", src, end, length(l) - 1);
            fprintf(out, "A shortest %d-%d path is: ", src, end);
            printList(out, l);
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
        freeList(&l);
    }

    // Clean memory and close files
    freeGraph(&g);
    fclose(in);
    fclose(out);
    
    return(0);
    }