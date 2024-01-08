/***********************************************
 * AUTHOR: BRIAN SMITH
 * FILE_NAME: "TicTacToe.c"
 * DATE_CREATED: 01/10/2019
 * DATE_LAST_EDITED: 16/09/2019
 * PURPOSE: A game of m-n-k tic-tac-toe.  
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TicTacToe.h"
#include "UserInterface.h"
#include "BoardDisplay.h"

/*BOOLEAN*/
#define TRUE 1
#define FALSE 0

int main(int argc, char const *argv[]) {
   if(argc > 2 || argc < 2) {
      printf("ERROR: Enter the name of one file only.\n");
   }
   else {
      FILE *settingsFile = fopen(argv[1], "r"); /*open file for reading*/
      if(settingsFile == NULL) { /*if file could not be opened*/
         printf("ERROR: Could not open settings file.\n");
      }
      else {
         int settings[3] = {-1,-1,-1}; /*stores settings read from file*/
         int* error = NULL; /*used to check for any errors in settings*/ 
         
         /*malloc error, one int*/
         error = (int*)malloc(sizeof(int));
         *error = FALSE;

         getSettings(settingsFile, settings, error);
         getSettings(settingsFile, settings, error);
         getSettings(settingsFile, settings, error);
         
         if(*error != TRUE) {
            mainMenu(settings);
         }
         else {
            printf("ERROR: Incorrect settings file format.\n");
         }

         free(error); 
         fclose(settingsFile);
      }
   }
   return 0;
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: getSettings
 * IMPORTS: FILE*, int**, int* 
 * EXPORTS: none
 * PURPOSE: reads in three settings from a settings file. width, height and 
 * number of tiles. An array of int* is used to store the settings and is 
 * passed in by reference to this function. If any of the settings are wrong 
 * the int* error is changed to TRUE (1). Check that all input settings are 
 * valid. E.g. non duplicates, greater than zero, M,N or K used.
 */
void getSettings(FILE* settingsFile, int* settings, int* error) { 
   int numRead; int tempInt;
   char tempChar;
   
   numRead = fscanf(settingsFile, "%c=%d\n", &tempChar, &tempInt);
   if(numRead != 2) {
      *error = TRUE; 
   }
   else { 
      if ((tempChar == 'M' || tempChar == 'm') && (tempInt > 0)
                                       && (settings[0] < 0)) {
         settings[0] = tempInt;
      }
      else if ((tempChar == 'N' || tempChar == 'n') && (tempInt > 0)
                                       && (settings[1] < 0)) {
         settings[1] = tempInt;   
      }  
      else if ((tempChar == 'K' || tempChar == 'k') && (tempInt > 0)
                                       && (settings[2] < 0)) {
         settings[2] = tempInt; 
      }
      else { 
         *error = TRUE;
      }
   }
}
