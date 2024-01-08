#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "LinkedList.h"

/*------ MAIN USER INTERFACE METHODS/OPTIONS ------*/
void mainMenu(int*);
void enterGame(int*, LinkedList*);
void printSettings(int*);
void saveLogs(int*, LinkedList*); 
void changeSettings(int*);
int inputInt(const char*, const char*, int);

/*------ LINKED LIST HELP FUNCTIONS -----*/
void writeGameLog(void*, FILE*);
void writeLogEntry(void*, FILE*);
void printGameLog(void*);
void printLogEntry(void*);
void freeGameLog(void*);
void freeLogEntry(void*);

#endif
