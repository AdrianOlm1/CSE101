#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
    int lineCount = 0;
    FILE *in, *out;
    char line[MAX_LEN];

    // Check to see if the correct number of arguments is given
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open input file and ensure the file is able to be read
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    // Count the number of lines in the file
    while (fgets(line, sizeof(line), in) != NULL) {
        lineCount++;
    }

    char **wordArray=malloc(lineCount * sizeof(char *));
    if(wordArray==NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
    }

    rewind(in);

    // Populate the array with strings
    int temp = 0;
    while (fgets(line, MAX_LEN, in) != NULL && temp < lineCount) {
    // Allocate memory for the current line in wordArray
    wordArray[temp] = malloc((strlen(line) + 1) * sizeof(char));

    // Check if memory allocation was successful
    if (wordArray[temp] == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the line into wordArray
    strcpy(wordArray[temp], line);

    temp++;
}

    fclose(in);
    
    // Open the output file
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    // List Sort
    int location;
    List L = newList();
    for(int i=0;i<lineCount;++i) {
        append(L,-2);
    }
    for(int i=0;i<lineCount;++i) {
        location=0;
        for(int j=0;j<lineCount;++j) {
            if(strcmp(wordArray[j],wordArray[i])<0) {
                location++;
            }

        }
        moveFront(L);    

        while(index(L)!=location) {
            moveNext(L);
        }
        set(L,i);
    }


    // Call/Print the strings
    moveFront(L);
    for(int i=0;i<length(L);++i){
        fprintf(out, "%s", wordArray[get(L)]);
        moveNext(L);
    }

    fclose(out);

    freeList(&L);
    for (int i = 0; i < lineCount; i++) {
        free(wordArray[i]);
    }
    free(wordArray);

    return 0;  // Exit successfully
}
