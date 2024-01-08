/*Reused from practical 7. Code made by me (Brian Smith) and is reused here
 * for the pusposes of the final UCP assignment.*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

/* TYPEDEF: LinkedListNode
 * FIELDS: data - stores a any data needed, next - points to teh next node,
 * prev - points to the previous node
 * ASSERTION: Node for storing data and pointers in the LinkedList
 */
typedef struct LinkedListNode {
   void* data;
   struct LinkedListNode* next;
   struct LinkedListNode* prev;
} LinkedListNode;

/* TYPEDEF: LinkedList
 * FIELDS: numElements - stores the num elements in the list, head - points
 * to the start of the list, tail - points to the last element in the last 
 * ASSERTION: Overall list struct for managing the list. 
 */
typedef struct {
   int numElements;
   LinkedListNode* head;
   LinkedListNode* tail;
} LinkedList;

LinkedList* createLinkedList(void);
void insertStart(LinkedList* list, void* data);
void* removeStart(LinkedList* list);
void insertLast(LinkedList* list, void* data);
void* removeLast(LinkedList* list);
typedef void (*structHelp)(void*);
typedef void (*fileHelp)(void*, FILE*);
void writeLinkedList(LinkedList*, fileHelp, FILE*);
void printLinkedList(LinkedList* list, structHelp printList);
void freeLinkedList(LinkedList* list, structHelp freeList);

#endif
