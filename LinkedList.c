/***********************************************
 * AUTHOR: BRIAN SMITH
 * FILE_NAME: "LinkedList.c"
 * DATE_CREATED: 20/09/2019
 * DATE_LAST_EDITED: 18/10/2019
 * PURPOSE: c file for managing a generic linked list.
 * REFERENCE: This LinkedList.c has been created by me (Brian Smith) and
 * submitted in a previous UCP practical (Practical 7). I am reusing it
 * for the purposes of the final UCP assignment in the TicTacToe program.
 * Reference also made in the project report.
 ***********************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LinkedList.h"

/*******************************************************/
               /*LinkedList Functions*/
/*******************************************************/

/* FUNCTION: createLinkedList
 * IMPORTS: none
 * EXPORTS: pointer to a new LinkedList
 * PURPOSE: Creates a pointer to a new LinkedList struct and sets the field
 * values to default.
 */
LinkedList* createLinkedList(void) {
   LinkedList* list;
   list = (LinkedList*)malloc(sizeof(LinkedList));

   list->numElements = 0;
   list->head = NULL;
   list->tail = NULL;
   
   return list;
}

/*-----------------------------------------------------*/

/* FUNCTION: insertStart
 * IMPORTS: pointer to LinkedList, void pointer
 * EXPORTS: none
 * PURPOSE: Adds an element to the start of the LinkedList (list)
 */
void insertStart(LinkedList* list, void* data) {
   LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode)); 
 
   newNode->data = data; 
   newNode->next = NULL;
   newNode->prev = NULL;
   
   if(list->numElements == 0) {    
      list->head = newNode;
      list->tail = newNode;
      list->numElements++;
   }
   else {
      newNode->next = list->head;
      list->head->prev = newNode;
      list->head = newNode;       
      list->numElements++;
   } 
}

/*-----------------------------------------------------*/

/* FUNCTION: removeStart
 * IMPORTS: pointer to LinkedList
 * EXPORTS: a void pointer to the removed nodes data 
 * PURPOSE: Removes a node from the LinkedList (list) and returns the data
 */
void* removeStart(LinkedList* list) {   
   void* outData;
   LinkedListNode* tempNode;
   
   if(list->numElements == 0) {
      outData = NULL;  
   }
   else if(list->numElements == 1) {   
      tempNode = list->head;
      outData = list->head->data;  
      free(tempNode); 
      list->head = NULL;
      list->tail = NULL;
      list->numElements--;
   }
   else {
      tempNode = list->head;
      outData = list->head->data; 
      list->head = list->head->next;    
      list->head->prev = NULL;
      free(tempNode);
      tempNode = NULL; 
      list->numElements--; 
   }
   return outData;
}

/*-----------------------------------------------------*/

/* FUNCTION: insertLast
 * IMPORTS: pointer to LinkedList, void pointer
 * EXPORTS: none
 * PURPOSE: Inserts a new node/element to the end of the LinkedLis (list)
 */
void insertLast(LinkedList* list, void* data) {
   LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode)); 
 
   newNode->data = data; 
   newNode->next = NULL;
   newNode->prev = NULL;
   
   if(list->numElements == 0) {    
      list->head = newNode;
      list->tail = newNode;
      list->numElements++;
   }
   else {
      newNode->prev = list->tail;
      list->tail->next = newNode;
      list->tail = newNode;       
      list->numElements++;
   } 
}

/*-----------------------------------------------------*/

/* FUNCTION: removeLast 
 * IMPORTS: pointer to LinkedList
 * EXPORTS: a void pointer 
 * PURPOSE: Removes a node from the LinkedList (list) and returns a void 
 * pointer to the data 
 */
void* removeLast(LinkedList* list) {
   void* outData;
   LinkedListNode* tempNode;
   
   if(list->numElements == 0) {
      outData = NULL;  
   }
   else if(list->numElements == 1) {  
      tempNode = list->tail;
      outData = list->tail->data; 
      free(tempNode);  
      list->head = NULL;
      list->tail = NULL;
      list->numElements--;
   }
   else {
      tempNode = list->tail;
      outData = list->tail->data;  
      list->tail = list->tail->prev;  
      free(tempNode);
      list->tail->next = NULL;       
      list->numElements--; 
   }
   return outData;
}

/*-----------------------------------------------------*/

/* FUNCTION: printLinkedList 
 * IMPORTS: pointer to LinkedList, structHelp
 * EXPORTS: none 
 * PURPOSE: Traverses through the list printing the data at each node, using
 * the function pointer printData.
 */
void printLinkedList(LinkedList* list, structHelp printData) {
   LinkedListNode *node, *nextNode; 

   node = list->head; 
   while(node != NULL) {
      nextNode = node->next;
      (*printData)(node->data); 
      node = nextNode;
   }
   printf("\n"); 
}

/*-----------------------------------------------------*/

/* FUNCTION: writeLinkedList 
 * IMPORTS: pointer to LinkedList, fileHelp, pointer to a file
 * EXPORTS: none 
 * PURPOSE: Traverses through the LinkedList (list) and writes the data
 * to the file given by the FILE pointer.
 */
void writeLinkedList(LinkedList* list, fileHelp writeData, FILE* file) {
   LinkedListNode *node, *nextNode; 

   node = list->head; 
   while(node != NULL) {
      nextNode = node->next;
      (*writeData)(node->data, file); 
      node = nextNode;
   } 
}

/*-----------------------------------------------------*/

/* FUNCTION: freeLinkedList 
 * IMPORTS: pointer to LinkedList, structHelp
 * EXPORTS: none 
 * PURPOSE: Traverses through the LinkedList (list) and frees the data
 * at each node using the freeData function pointer.
 */
void freeLinkedList(LinkedList* list, structHelp freeData) {
   LinkedListNode *node, *nextNode;

   node = list->head;
   while(node != NULL) {
      nextNode = node->next;
      (*freeData)(node->data);
      free(node); 
      node = nextNode;
   }
   free(list);
}
