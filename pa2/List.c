/***
* Adrian Olmos
* amolmos
* 2024 Winter CSE101 PA2
* List.c
* Implements a doubly linked list ADT with operations to manipulate the list.
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "List.h"
// structs ---------------------------------------------------------------------
typedef struct NodeObj *Node;

typedef struct NodeObj
{
    ListElement data;
    struct NodeObj *next;
    struct NodeObj *previous;
} NodeObj;

typedef struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// Creates and returns a new empty Node.
Node newNode(ListElement data)
{
    // Creates Node and ensures it is made with assert
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);

    // Initalizes the node
    N->data = data;
    N->next = NULL;
    N->previous = NULL;

    return (N);
}

// Frees node
void freeNode(Node *pN)
{
    // Frees node then sets pointer to NULL
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void)
{
    // Creates list and asserts to ensure its allocated succesfully
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);

    // Initalizes the list
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;

    return (L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL. *******************************
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (!(length(*pL) == 0))
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling length() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling index() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling front() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0)
    {
        return L->front->data;
    }

    return 0;
}

// Returns back element of L. Pre: length()>0
int back(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling back() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0)
    {
        return L->back->data;
    }

    return 0;
}

// Returns cursor element of L. Pre: length()>0, index()>=0 *************************************
int get(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling get() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "List Error: calling get() with a NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0 && index(L) >= 0)
    {
        return L->cursor->data;
    }

    return 0;
}

// Returns true iff Lists A and B contain the same sequence of elements, returns false otherwise.
bool equals(List A, List B)
{
    if (A == NULL && B == NULL)
    {
        return true;
    }
    else if (A == NULL || B == NULL)
    {
        return false;
    }

    // Check if lengths are different
    if (A->length != B->length)
    {
        return false;
    }

    // Traverse both lists and compare elements
    Node current1 = A->front;
    Node current2 = B->front;

    while (current1 != NULL)
    {
        // Compare elements
        if (current1->data != current2->data)
        {
            return false;
        }

        // Move to the next nodes
        current1 = current1->next;
        current2 = current2->next;
    }

    // If both lists are traversed completely, they are equal
    return true;
}

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    while (length(L) != 0)
    {
        deleteFront(L);
    }
    L->cursor = NULL;
    L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling set() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) > -1)
    {
        L->cursor->data = x;
    }
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
    if (L->length != 0)
        L->index = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveBack()) on NULL list\n");
        exit(EXIT_FAILURE);
    }

    L->cursor = L->back;
    L->index = (L->length - 1);
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL)
    {
        L->cursor = L->cursor->previous;
        L->index--;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined, do nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveNext() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL)
    {
        L->cursor = L->cursor->next;
        if (L->cursor != NULL)
            L->index++;
        else
            L->index = -1;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x)
{
    Node N = newNode(x);
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0)
    {
        L->front = L->back = N;
        L->length++;
    }
    else
    {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        if (L->cursor != NULL)
            L->index++;
        L->length++;
    }
}

// Insert new element into L. If L is non-empty,insertion takes place after back element.
void append(List L, int x)
{
    Node N = newNode(x);
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0)
    {
        L->front = L->back = N;
        L->length++;
    }
    else
    {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
        L->length++;
    }
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "List Error: calling insertBefore() with a NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->cursor == L->front)
    {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        L->index++;
        L->length++;
    }
    else
    {
        N->previous = L->cursor->previous;
        N->next = L->cursor;
        L->cursor->previous->next = N;
        L->cursor->previous = N;
        L->index++;
        L->length++;
    }
}

// Insert new element after cursor.Pre: length()>0, index()>=0
void insertAfter(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertAfter() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL)
   {
      fprintf(stderr,"List Error: calling insertAfter() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
    Node N=newNode(x);
    if(L->cursor == L->back)
   {
      N->previous = L->back;
      L->back->next = N;
      L->back = N;
      L->length++;
   }
   else
   {
      N->next = L->cursor->next;
      N->previous = L->cursor;
      L->cursor->next->previous = N;
      L->cursor->next = N;
      L->length++;
   }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling deleteFront() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->front==NULL)
    {
        fprintf(stderr, "List Error: calling deleteFront() on empty list\n");
        exit(EXIT_FAILURE);
    }
    Node N=NULL;
    if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else
   {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->previous = NULL;
      if(L->index == 0)
         L->cursor = NULL;
      L->index--;
      L->length--;
   }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling deleteBack() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->back==NULL)
    {
        fprintf(stderr, "List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
    Node N=NULL;
    if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else
   {
      N = L->back;
      if(L->cursor == N)
      {
         L->cursor = NULL;
         L->index = -1;
      }
      L->back = L->back->previous;
      freeNode(&N);
      L->back->next = NULL;
      L->length--;
   }
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling delete() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL)
   {
      fprintf(stderr,"List Error: calling delete() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
   Node N=NULL;
    N = L->cursor;
   L->cursor = NULL;
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = NULL;
   }
   else if(L->front == N)
   {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->previous = NULL;
   }
   else if(L->back == N)
   {
      N = L->back;
      L->back = L->back->previous;
      freeNode(&N);
      L->back->next = NULL;
   }
   else
   {
      N->previous->next = N->next;
      N->next->previous = N->previous;
      freeNode(&N);
   }
   L->length--;
   L->index = -1;
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L)
{
    if (out == NULL)
    {
        fprintf(stderr, "File Error: Unable to open the file for printing\n");
        exit(EXIT_FAILURE);
    }
    if (L == NULL)
    {
        fprintf(stderr, "Error printing NULL list");
        exit(EXIT_FAILURE);
    }

    for (Node N = L->front; N != NULL; N = N->next)
    {
        fprintf(out, "%d ", N->data);
    }
}

// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state of L is unchanged
List copyList(List L)
{
    List Copy = newList();
   Node N = NULL;
   if( L==NULL )
   {
      fprintf(stderr,"List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   N = L->front;
   while(N != NULL)
   {
      append(Copy, N->data);
      N = N->next;
   }
   return(Copy);
}
