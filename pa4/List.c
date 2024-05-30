#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "List.h"

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
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);

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
        clear(*pL);
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
ListElement front(List L)
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
ListElement back(List L)
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
ListElement get(List L)
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

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    Node current = L->front;
    while (current != NULL)
    {
        Node temp = current->next;
        freeNode(&current);
        current = temp;
    }
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, ListElement x)
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
    if (L->length != 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling moveBack()) on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0)
    {
        L->cursor = L->back;
        L->index = (L->length - 1);
    }
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
        if (L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else
        {
            L->cursor = L->cursor->previous;
            L->index--;
        }
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
        if (L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else
        {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, ListElement x)
{
    Node N = newNode(x);
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0)
    {
        L->front = N;
        L->back = N;
        L->cursor = N;
        L->index = 0;
    }
    else
    {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        L->index++;
    }
    L->length++;
}

// Insert new element into L. If L is non-empty,insertion takes place after back element.
void append(List L, ListElement x)
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
    }
    else
    {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x)
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
    if (index(L) == 0)
    {
        L->front->previous = N;
        N->next = L->front;
        L->front = N;
    }
    else
    {
        N->previous = L->cursor->previous;
        L->cursor->previous->next = N;
        N->next = L->cursor;
        L->cursor->previous = N;
    }
    L->index++;
    L->length++;
}

// Insert new element after cursor.Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertAfter() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "List Error: calling insertAfter() with a NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->cursor == L->back)
    {
        L->back->next = N;
        N->previous = L->back;
        L->back = N;
    }
    else
    {
        N->next = L->cursor->next;
        L->cursor->next->previous = N;
        N->previous = L->cursor;
        L->cursor->next = N;
    }
    L->length++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling deleteFront() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->front == NULL)
    {
        fprintf(stderr, "List Error: calling deleteFront() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0)
    {
        Node n = L->front;
        if (L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        if (L->length > 1)
        {
            L->front = L->front->next;
            L->front->previous = NULL;
            if (L->index != -1)
            {
                L->index--;
            }
        }
        else
        {
            L->front = L->back = NULL;
            if (L->index != -1)
            {
                L->index--;
            }
        }
        L->length--;
        freeNode(&n);
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
    if (L->back == NULL)
    {
        fprintf(stderr, "List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->back;
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    if (length(L) == 1) {
        L->front = NULL;
        L->back = NULL;
        L->length = 0;
        freeNode(&temp);
    } else {
        L->back = temp->previous;
        L->back->next = NULL;
        L->length--;
        freeNode(&temp);
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
    if (L->cursor == NULL)
    {
        fprintf(stderr, "List Error: calling delete() with a NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->cursor;
    if (temp == L->front) {
        L->front = temp->next;
        if (L->front != NULL) {
            L->front->previous = NULL;
        }
    } else if (temp == L->back) {
        L->back = temp->previous;
        if (L->back != NULL) {
            L->back->next = NULL;
        }
    } else {
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
    }
    L->cursor = NULL;
    L->index = -1;
    L->length--;
    freeNode(&temp);
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    for (moveFront(L); index(L) >= 0; moveNext(L)) {
        fprintf(out, "%d ", *((int*) get(L)));
    }

    fprintf(out, "\n");
}