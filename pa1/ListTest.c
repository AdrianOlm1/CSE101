/***
* Adrian Olmos
* amolmos
* 2024 Winter CSE101 PA1
* ListTest.c
* Contains tests for all ADT operations of the List.
***/

#include<stdio.h>

#include "List.h"

void printingList(List list) {
    moveFront(list);
    if(length(list)==0) {
        printf("Empty List\n");
        return;
    }    
    for(int i=0;i<length(list);++i) {
        printf("%d: %d\n", index(list), get(list));
        moveNext(list);
    }
}

int main() {
    List l1 = newList();
    List l2 = newList();
    List l3 = newList();

    // Testing list insert functions
    prepend(l1,1);
    prepend(l1,2);
    append(l1,3);

    printf("Printing list 2\n");
    prepend(l2,4);    
    printingList(l2);
    
    printf("\nTesting insertBefore() on List 2\n");
    moveFront(l2);
    insertBefore(l2,5);
    printingList(l2);
    
    printf("\nTesting insertAfter() on List 2\n");
    moveFront(l2);
    insertAfter(l2,6);
    printingList(l2);

    // Testing remove functions
    printf("\nTesting deleteFront()[cursor]\n");
    moveFront(l2);
    printf("Pre delete index: %d\n", index(l2));
    deleteFront(l2);
    printf("Post delete index: %d\n",index(l2));    
    printingList(l2);
   
    printf("\nTesting deleteBack()\n");
    deleteBack(l2);
    printingList(l2);


    printf("\nTesting delete()\n");
    delete(l2);
    printingList(l2);

    //printf("\nTesting delete() on empty list\n");
    //delete(l3);

    // Testing moving cursor
    printf("\nTesting moveFront()\n");
    moveFront(l1);
    printf("Index: %d\n",index(l1));

    printf("\nTesting moveBack()\n");
    moveBack(l1);
    printf("Index: %d\n",index(l1));

    printf("\nTesting movePrev()\n");
    movePrev(l1);
    printf("Index: %d\n",index(l1));

    printf("\nTesting moveNext()\n");
    moveNext(l1);
    printf("Index: %d\n",index(l1));

    printf("\nTesting moveNext() onto outside of list\n");
    moveNext(l1);
    printf("Index: %d\n",index(l1));
    
    // Testing set()
    printf("\nTesting set()\n");
    moveBack(l1);
    printf("Pre set cursor value: %d\n",get(l1));
    set(l1,-3);
    printf("Post set cursor value: %d\n", get(l1));

    // Testing equal and copyList;
    printf("\nTesting equal() and copyList()\n");
    l3 = copyList(l1);
    printf("l1=l3(true): %s\n", equals(l1,l3) ? "true" : "false");
    printf("l1=l2(false): %s\n", equals(l1,l2) ? "true" : "false");

    // Testing length, front, and back
    printf("\nTesting length, front, and back\n");
    printf("Length: %d\nFront: %d\nBack: %d\n",length(l1),front(l1),back(l1));
    
    freeList(&l1);
    freeList(&l2);
    freeList(&l3);
}
