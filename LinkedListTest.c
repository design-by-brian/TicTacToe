/* 
 * File: LinkedListTest.c
 * File created: Friday, 6th September 2019 11:40:35 am
 * Author: Jonathon Winter
 * -----
 * Last Modified: Tuesday, 24th September 2019 2:29:59 pm
 * Modified By: Jonathon Winter
 * -----
 * Purpose: Semi complete Test harness for a Generic Linked List in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

void printString(void* data);
void freeString(void* data);

int main(int argc, char const *argv[])
{
   LinkedList* list = NULL;
   char* data;
   char* input1 = (char*)malloc(sizeof(char)*6);
   char* input2 = (char*)malloc(sizeof(char)*4);
   char* input3 = (char*)malloc(sizeof(char)*4);
   char* input4 = (char*)malloc(sizeof(char)*7);

   strncpy(input1,"hello",6);
   strncpy(input2,"bye",4);
   strncpy(input3,"hey",4);
   strncpy(input4,"see-ya",7);

   /*CREATING*/
   printf("Creating List: ");
   list = createLinkedList();
   if(list == NULL || list->head != NULL)
   {
      printf("FAILED\n");
   }
   else
   {
      printf("PASSED\n");
   }

   /*INSERTING FIRST*/
   printf("Inserting First: ");
   insertStart(list,input1);
   if(list->head == NULL)
   {
      printf("FAILED\n");
   }
   else if(strncmp((char*)list->head->data, input1, strlen(input1)+1)==0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }

   printf("Inserting First (2): ");
   insertStart(list,input2);
   if(list->head == NULL)
   {
      printf("FAILED\n");
   }
   else if(strncmp((char*)list->head->data, input2, strlen(input2)+1)==0 && 
            strncmp((char*)list->tail->data, input1, strlen(input1)+1)==0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }

   /*INSERTING LAST*/
   printf("Inserting Last: ");
   insertLast(list,input3);
   if(list->head == NULL)
   {
      printf("FAILED\n");
   }
   else if(strncmp((char*)list->head->data, input2, strlen(input2)+1)==0 && 
            strncmp((char*)list->tail->data, input3, strlen(input3)+1)==0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }

   printf("Inserting Last (2): ");
   insertLast(list,input4);
   if(list->head == NULL)
   {
      printf("FAILED\n");
   }
   else if(strncmp((char*)list->head->data, input2, strlen(input2)+1)==0 && 
            strncmp((char*)list->tail->data, input4, strlen(input1)+1)==0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }
   
   /*PRINTING*/
   printf("----------Printing----------\n");
   printf("Expecting: bye hello hey see-ya\n");
   printf("Actual: ");
   printLinkedList(list, printString);

   /*REMOVING FIRST*/
   printf("Remove First: ");
   data = (char*)removeStart(list);

   if(strncmp(data, input2, strlen(input2)+1) == 0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }
   free(data);
   data = NULL;

   /*REMOVING LAST*/
   printf("Remove Last: ");
   data = (char*)removeLast(list);

   if(strncmp(data, input4, strlen(input4)+1) == 0)
   {
      printf("PASSED\n");
   }
   else
   {
      printf("FAILED\n");
   }
   free(data);
   data = NULL;

   /*FREEING*/
      freeLinkedList(list, freeString);      
   /* ANY OTHER TESTS YOU WANT TO DO*/

   return 0;
}

void printString(void* data) {
   printf("%s ", (char*)data);
}

void freeString(void* data) {
   free(data);
}
