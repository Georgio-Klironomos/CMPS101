//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

/*WORKS CITED
https://classes.soe.ucsc.edu/cmps101/Fall18/Examples/C/Queue/Queue.c
https://stackoverflow.com/questions/10668504/segmentation-fault-c
https://en.cppreference.com/w/cpp/language/operator_incdec
https://stackoverflow.com/questions/2612447/pinpointing-conditional-jump-or-move-depends-on-uninitialized-values-valgrin
*/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev,  and data fields.
// Private.
Node newNode(int data, Node prev, Node next){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = prev;
   N->next = next;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
       Node current1 = (*pL)->front;
      while(current1 != NULL) { 
        Node current2 = current1;
        current1 = current1->next;
        freeNode(&current2);
        current2 = NULL;
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

int index(List L) {
    return(L->index);
}

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( (L==NULL) || (L->length < 1) ){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
   }
   return(L->front->data);
}

int back(List L){
   if( (L==NULL) || (L->length < 1) ){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
   }
   return(L->back->data);
}

int get(List L) {
   if((L == NULL) || (L->index < 0) || (L->length < 1)) {
      printf("List Error: calling get() on NULL List or NULL cursor\n");
      exit(1);
   }
   return(L->cursor->data);
}

int equals(List A, List B) {
    int same = 0;
   Node N = NULL;
   Node M = NULL;
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   same = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( same && N!=NULL){
      same = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return same;
}

void clear(List L) {
    Node current1 = L->front; 
    while(current1 != NULL) {
      Node current2 = current1;
      current1 = current1->next;
      freeNode(&current2);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

void moveFront(List L) {
  if(L->length > 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}
void moveBack(List L) {
  if(L->length > 0) {
    L->cursor = L->back;
    L->index = L->length-1;
  }
}
void movePrev(List L) {
  if(L->cursor != NULL){
            L->cursor = L->cursor->prev;
            L->index--;
        }
}
void moveNext(List L) {
  if(L->cursor != NULL){
            L->cursor = L->cursor->next;
            if(L->index == (L->length-1)) {L->index = -1;}
            else{L->index++;}
        }
}
void prepend(List L, int data) {
  Node new_node = newNode(data, NULL, L->front);
		if(L->length > 0){
			L->front->prev = new_node;
		}
		if(L->length == 0){
	    	L->back = new_node;
		}
    L->front = new_node;  
    L->length++;
    if(L->cursor != NULL){
      L->index++;//NEW!
    }
}

void append(List L, int data) {
  Node new_node = newNode(data, NULL, NULL);		
        if(L->length > 0){	
            L->back->next = new_node;
            new_node->prev = L->back;										
        }   
        if(L->length == 0){
            L->front = new_node;
        }
        L->back = new_node;
        L->length++;
}

void insertBefore(List L, int data) {
  if(L->length > 0 && L->index >= 0) {
            Node new_node = newNode(data, L->cursor->prev, L->cursor);
            if(L->cursor->prev != NULL) {
                L->cursor->prev->next = new_node;
            }
            L->cursor->prev = new_node;
            if(L->cursor == L->front){
                L->front = new_node;
            }
            L->length++;
            L->index++;
        }
}

void insertAfter(List L, int data) {
  if(L->length > 0 && L->index >= 0) {
            Node new_node = newNode(data, L->cursor, L->cursor->next);
            if(L->cursor->next != NULL) {
                L->cursor->next->prev = new_node;
            }
            L->cursor->next = new_node;
            if(L->cursor == L->back){
                L->back = new_node;
            }
            L->length++;
        }
}

void deleteFront(List L) {
  if (L->length <= 0 || L->front == NULL){
            return;
        }
        if (L->front->next!=NULL){
            L->front->next->prev = NULL;
        }
        if(L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
        else {
            L->index--;
        }
        free(L->front);
        L->front = L->front->next;
        L->length--;
}

void deleteBack(List L) {
  if (L->length <= 0 || L->back == NULL){
            return;
        }
        if (L->back->prev!=NULL){
            L->back->prev->next = NULL;
        }
        if(L->cursor == L->back){
            L->cursor = NULL;
            L->index = -1;
        }
        free(L->back);
        L->back = L->back->prev;
        L->length--;
}

void delete(List L) {
  if (L->length <= 0 || L->length <0 || L->cursor == NULL) {
            return;
        }
        if(L->cursor->prev!=NULL) {
            L->cursor->prev->next = L->cursor->next;
            if(L->back == L->cursor){
                L->back = L->cursor->prev;
            }
        }
        if(L->cursor->next!=NULL){
            L->cursor->next->prev = L->cursor->prev;
             if(L->front == L->cursor){
                L->front = L->cursor->next;
            }
        }
        free(L->cursor);
        L->cursor = NULL;
        L->index = -1;
        L->length--;
}

void printList(FILE* out, List L) {
  Node current = L->front;
  while(current != NULL){
    fprintf(out, "%d ",current->data); 
    current = current->next;   
  }
  free(current);  
}

List copyList(List L) {
    List newbie = newList();
    if (L->length > 0 && L->front != NULL) {
        Node current = L->front;
        while(current != NULL) {
            append(newbie, current->data);
            current = current->next;
        }
    }
    
    return newbie;
}