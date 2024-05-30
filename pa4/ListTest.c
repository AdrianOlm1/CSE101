#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   int i, u=-1, v=-2, w=-3; 
   bool equal = false;

   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
    }

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveFront(B); index(B)>=0; moveNext(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\n");

    for(moveBack(A); index(A)>=0; movePrev(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\n");

    moveFront(A);
    while( index(A)>=0 ){
        append(C, get(A));
        moveNext(A);
    }
    for(moveFront(C); index(C)>=0; moveNext(C)){
        printf("%d ", *(int*)get(C));
    }
    printf("\n");

    equal = (length(A)==length(C));
    moveFront(A);
    moveFront(C);
    while( index(A)>=0 && equal){
        equal = ( get(A)==get(C) );
        moveNext(A);
        moveNext(C);
    }
    printf("A equals C is %s\n", (equal?"true":"false") );

    moveFront(A);
    for(i=0; i<5; i++) moveNext(A);
    printf("index(A)=%d\n", index(A));
    insertBefore(A, &u);
    printf("index(A)=%d\n", index(A));
    for(i=0; i<9; i++) moveNext(A);
    printf("index(A)=%d\n", index(A));
    insertAfter(A, &v);
    printf("index(A)=%d\n", index(A));
    for(i=0; i<5; i++) movePrev(A);
    printf("index(A)=%d\n", index(A));
    delete(A);
    printf("index(A)=%d\n", index(A));
    moveBack(A);
    printf("index(A)=%d\n", index(A));
    for(i=0; i<10; i++) movePrev(A);
    printf("index(A)=%d\n", index(A));
    set(A, &w);

    for(moveFront(A); index(A)>=0; moveNext(A)){
    printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveBack(A); index(A)>=0; movePrev(A)){
    printf("%d ", *(int*)get(A));
    }
    printf("\n");
    printf("%d\n", length(A));
    clear(A);
    printf("%d\n", length(A));

    List D = newList();
    int x = 1, y = 2, z = 3, a = 5, b = 6;
    append(D, &x);
    moveFront(D);
    set(D, &y);
    moveBack(A);
    set(D, &z);
    append(D, &y);
    prepend(D, &z);
    insertBefore(D, &a);
    insertAfter(D, &b);
    printList(stdout, D);
    freeList(&D);

    List E = newList();
    for (int i = 0; i < 10; i++) {
        append(E, &i);
    }
    moveFront(E);
    for (int i = 0; i < 10; i++) {
        if (index(E) != i) {
            printf("Test Index: FAILED\n");
            break;
        }
        moveNext(E);
    }
    freeList(&E);
    printf("Test Index: PASSED\n");
    
    List F = newList();
    for (int i = 0; i < 10; i++) {
        append(F, &i);
    }
    moveFront(F);
    for (int i = 0; i < 10; i++) {
        set(F, &i);
        if (*((int *) get(F)) != i) {
            printf("Test SetGet: FAILED\n");
            break;
        }
        moveNext(F);
    }
    printf("Test SetGet: PASSED\n");

    freeList(&F);
    freeList(&A);
    freeList(&B);
    freeList(&C);
    return(0);
}
