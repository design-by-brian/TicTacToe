/***********************************************
 * AUTHOR: BRIAN SMITH
 * FILE_NAME: "TicTacToe.c"
 * DATE_CREATED: 01/10/2019
 * DATE_LAST_EDITED: 16/09/2019
 * PURPOSE: A game of m-n-k tic-tac-toe. UserInterface  
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "UserInterface.h"
#include "BoardDisplay.h"
#include "LinkedList.h"
#include "TicTacToe.h"

/*MACROS*/
#ifdef EDITOR
   #define START_GAME 1
   #define CHANGE_SETTINGS 2
   #define VIEW_SETTINGS 3
   #define VIEW_LOGS 4
   #define SAVE_LOGS 5
   #define EXIT 6
#else
   #define START_GAME 1
   #define VIEW_SETTINGS 2
   #define VIEW_LOGS 3
   #define SAVE_LOGS 4
   #define EXIT 5
#endif

/*BOOLEAN*/
#define TRUE 1
#define FALSE 0

/* FUNCTION: mainMenu 
 * IMPORTS: none
 * EXPORTS: none
 * PURPOSE: Main user interface for the tic tac toe game, continually runnning
 * throughout TicTacToe program.
 * LINKS: Called by the main in TicTacToe.c. Calls every other function from
 * BoarDisplay.c, some from LinkedList.c and uses all the other functions
 * defined in this c file.
 */
void mainMenu(int* settings) {
   int selection; char error[50]; 
  
   LinkedList* logList; /*LinkedLists for storing,
                                 displaying and writing all gameLogs*/
  
   /*-------- CREATE LINKED LIST TO STORE LOG GAME LOGS--------*/
   logList = createLinkedList();

   /*--------- WHILE !EXIT_CONDITION (5) ---------*/
   do { 
      #ifndef EDITOR
      printf(" -----------------------------\n"); 
      printf("|       TIC-TAC-TOE MENU      |\n"); 
      printf(" -----------------------------\n");
      printf("|   1. START NEW GAME         |\n"); 
      printf("|   2. VIEW GAME SETTINGS     |\n");
      printf("|   3. VIEW CURRENT LOGS      |\n");
      printf("|   4. SAVE LOGS TO A FILE    |\n");
      printf("|   5. EXIT                   |\n");
      printf(" -----------------------------\n\n"); 
      #else
      printf(" -----------------------------\n"); 
      printf("|       TIC-TAC-TOE MENU      |\n"); 
      printf(" -----------------------------\n");
      printf("|   1. START NEW GAME         |\n"); 
      printf("|   2. CHANGE GAME SETTINGS   |\n"); 
      printf("|   3. VIEW GAME SETTINGS     |\n");
      printf("|   4. VIEW CURRENT LOGS      |\n");
      printf("|   5. SAVE LOGS TO A FILE    |\n");
      printf("|   6. EXIT                   |\n");
      printf(" -----------------------------\n\n"); 
      #endif

      sprintf(error, "INVALID ENTRY: POSITVE INTEGER FROM 1-%d ONLY", EXIT);
      selection = inputInt("SELECTION: ", error, 1);
 
      printf("\n"); 
      switch(selection) {
         case START_GAME:
            enterGame(settings, logList);
         break;
         #ifdef EDITOR
         case CHANGE_SETTINGS:
            changeSettings(settings);
         break;
         #endif
         case VIEW_SETTINGS:
            printSettings(settings);
         break;
         case VIEW_LOGS:
            printf(" --------------\n");
            printf("| CURRENT LOGS |\n");
            printf(" --------------\n");
            printf("\n");
            printLinkedList(logList, printGameLog); 
            break;
         case SAVE_LOGS:
         #ifndef SECRET
            saveLogs(settings, logList);
         #else
            printf("SECRET MODE SELECTED - LOGS CANNOT BE SAVED\n");
         #endif
         break;
         case EXIT:
            printf(" -----------------\n");
            printf("| EXITING PROGRAM |\n");
            printf(" -----------------\n"); 
         break;
         default:
            printf("INCORRECT ENTRY - OUT OF BOUNDS\n"); 
         break;
      }      
   } while (selection != EXIT);
   
   freeLinkedList(logList, freeGameLog); 
}


/*---------------------------------------------------------------------------*/
               /*FUNCTIONS FOR MENU OPTIONS AND USER INPUT*/
/*---------------------------------------------------------------------------*/


/* FUNCTION: printSettings 
 * IMPORTS: int* settings
 * EXPORTS: none
 * PURPOSE: prints the current settings to the terminal. Uses the import of
 * the settings array. 
 * LINKS: Called by mainMenu only.
 */
void printSettings(int* settings) { 
   printf(" ---------------\n");
   printf("| GAME SETTINGS |\n");
   printf(" ---------------\n");
   printf("\n");
   printf("    BOARD WIDTH = %d\n", settings[0]);
   printf("    BOARD HEIGHT = %d\n", settings[1]);
   printf("    NUMBER OF TILES TO WIN = %d\n", settings[2]);
   printf("\n");
}
 
           
/* FUNCTION: enterGame 
 * IMPORTS: int* settings, LinkedList* logList
 * EXPORTS: none
 * PURPOSE: Function for running an individual MNK game. Creates a new linked 
 * list that stores the game data. Uses settings and passes this to the board
 * display fucntions. 
 * LINKS: Called by mainMenu only.
 */
void enterGame(int* settings, LinkedList* logList) {
   int ii; int jj; /*counters - used for all for loops*/   
   int gameState;
   char** positions; /*2d array for holding player moves (X/O)*/  
   
   LinkedList* gameLog;  
   
   /*initialise new gameLog for start of new game*/    
   gameLog = createLinkedList();
  
   /*-------- MALLOC 2D ARRAY OF X/O POSITIONS ---------*/
   positions = (char**)malloc(settings[1] * sizeof(char*));
   for(ii = 0;ii < settings[1];ii++) {
      positions[ii] = (char*)malloc(settings[0] * sizeof(char));
   }
   
   /*-------- SET ALL POSITIONS TO ' ' (UNUSED) ---------*/
   for(jj = 0;jj < settings[1];jj++) {
      for(ii = 0;ii < settings[0];ii++) {
         positions[jj][ii] = ' ';
      }
   } 
    
   printf("\n");
   printf("-----------------------------------------------\n"); 
   printf("STARTING NEW GAME\n");
   printf("PLAYER O STARTS\n");
   printf("ENTER '0' AT ANY TIME TO EXIT TO THE MAIN MENU.\n");
   printf("-----------------------------------------------\n");
   printf("\n");
   
   printBoard(settings[0], settings[1], positions); 
  
   gameState = 0; 
   while(gameState == 0) { /*no one has won or wants to quit*/
      gameState = playerMove(settings, gameLog, positions, 'O');
      if(gameState == 0) {
         gameState = playerMove(settings, gameLog, positions, 'X');
      }
   }
   printf("THANKS FOR PLAYING!\n");        
   if(gameState == 2) { /*player O has won*/
      printf("PLAYER 'O' IS THE WINNER!\n");
   }
   else if(gameState == 3) { /*player X has won*/
      printf("PLAYER 'X' IS THE WINNER!\n");
   }
   else { /*gameState = 1 player wants to quit or no moves left*/
      printf("DRAW!\n");
   }
   insertLast(logList, gameLog);
   
   for(ii = 0;ii < settings[1];ii++) {
      free(positions[ii]);
   }
   free(positions);  
}
/*---------------------------------------------------------------------------*/

/* FUNCTION: saveLogs 
 * IMPORTS: int* settings, LinkedList** logList
 * EXPORTS: none
 * PURPOSE: Function for writing the game logs to a file. Takens in settings
 * to write these at the start of the file. Uses the time.h library and time
 * struct to determine the current time/date. writeLinkedList used to write 
 * out all gameLogs.
 * Time struct code obtained and adapted from: https://www.techiedelight.com/
                                             print-current-date-and-time-in-c/ 
 */
void saveLogs(int* settings, LinkedList* logList) {   
   time_t now; int hour; int min; int month; int day; struct tm *local; 
   char fileName[50];
   FILE* logFile;
 
   /*gets the current time as of log save selected*/     
   time(&now); 
   /*converts to calender time and returns pointer to tm struct*/
   local = localtime(&now);
   hour = local->tm_hour;
   min = local->tm_min;
   day = local->tm_mday;
   month = local->tm_mon + 1;
              
   sprintf(fileName, "MNK_%d-%d-%d_%d-%d_%d-%d.log", settings[0], 
                     settings[1], settings[2], hour, min, day, month);   
   
   logFile = fopen(fileName, "w");
  
   if(logFile != NULL) { 
      printf("SAVING LOGS...\n"); 
      printf("%s\n", fileName);
 
      fprintf(logFile, " ---------------\n");
      fprintf(logFile, "| GAME SETTINGS |\n");
      fprintf(logFile, " ---------------\n");
      fprintf(logFile, "\n");
      fprintf(logFile, "    BOARD WIDTH = %d\n", settings[0]);
      fprintf(logFile, "    BOARD HEIGHT = %d\n", settings[1]);
      fprintf(logFile, "    NUMBER OF TILES TO WIN = %d\n", settings[2]);
      fprintf(logFile, "\n");
   
      writeLinkedList(logList, writeGameLog, logFile);              
   }
   else {
      printf("ERROR: Could not open file.\n");
   }
   fclose(logFile);    
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: changeSettings 
 * IMPORTS: array of ints
 * EXPORTS: none
 * PURPOSE: function for changing the settings in editor mode
 * Prompts user to select which setttings they would like to change.
 * Passes this by reference to the array of settings. Only compiled in editor
 * mode
 */
#ifdef EDITOR
void changeSettings(int* settings) {
   int selection; 
   
   do { 
      printf(" ---------------------------\n"); 
      printf("|       CHANGE SETTINGS     |\n"); 
      printf(" ---------------------------\n");
      printf("|   1. CHANGE WIDTH         |\n"); 
      printf("|   2. CHANGE HEIGHT        |\n");
      printf("|   3. CHANGE TILES TO WIN  |\n"); 
      printf("|   4. BACK TO MAIN-MENU    |\n");
      printf(" ---------------------------\n\n"); 
      
      selection = inputInt("SELECTION: ", 
                                 "INAVLID ENTRY: INTEGER BETWEEN 1-4 ONLY", 1); 
      switch(selection) {
         case 1:
            settings[0] = inputInt("WIDTH: ", 
                                    "INVALID ENTRY: POSTIVE INTEGER ONLY", 1); 
         break;
         case 2: 
            settings[1] = inputInt("HEIGHT: ", 
                                    "INVALID ENTRY: POSTIVE INTEGER ONLY", 1); 
         break;
         case 3:
            settings[2] = inputInt("TILES TO WIN: ", 
                                    "INVALID ENTRY: POSTIVE INTEGER ONLY", 1); 
         break;
         case 4:
            printf(" ------------------------\n");
            printf("| RETURNING TO MAIN_MENU |\n");
            printf(" ------------------------\n"); 
            break;
         default:
            printf("INCORRECT ENTRY - OUT OF BOUNDS\n");
      }
   } while (selection != 4);
}
#endif

/* FUNCTION: inputInt
 * IMPORTS: const char* prompt, const char* error, int min
 * EXPORTS: int
 * PURPOSE: A generic integer input from the terminal. Good for code reuse 
 * as this functionality is needed quite a few times througout. Deals with
 * unexpected inputs by using numREad and a do-while getchar to clear buffer. 
 */
int inputInt(const char* prompt,const char* error, int min) {
   int input; int numRead;
   do {
      printf("%s", prompt);
      numRead = scanf("%d", &input);
    
      if ((numRead != 1) || (input < min)) { /* if not a single int and less 
                                                   than min.*/
         do {
            input = getchar();
         } while (input != '\n'); /*clears buffer waiting for newline*/
         printf("%s\n", error);
         input = -1;
      }
   } while (input == -1);
   return input;
}                  


/*---------------------------------------------------------------------------*/
         /*LINKEDLIST HELPER FUNCTIONS - logList, gameLogm, logEntry*/
/*---------------------------------------------------------------------------*/


/* FUNCTION: printGameLog 
 * IMPORTS: void* data
 * EXPORTS: none
 * PURPOSE: helper function for printing a linkedlist of GameLogs. Directly
 * prints the gameNum using the fist logEntry of gameLog.
 */
void printGameLog(void* data) {
   LinkedList* gameLog;
   gameLog = (LinkedList*)(data);
   if (gameLog->numElements > 0) {
      printf("GAME: %d\n", ((logEntry*)(gameLog->head->data))->gameNum); 
      printLinkedList(gameLog, printLogEntry);       
   }
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: printLogEntry
 * IMPORTS: void* data
 * EXPORTS: none
 * PURPOSE: function to help print the data in the gameLog LinkedList. Prints 
 * logEntry data to the terminal
 */
void printLogEntry(void* data) {
   printf("    TURN: %d\n", ((logEntry*)data)->turn);
   printf("    PLAYER: %c\n", ((logEntry*)data)->player);
   printf("    LOCATION: %d,%d\n", ((logEntry*)data)->x, ((logEntry*)data)->y); 
   printf("\n");
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: writeLogEntry 
 * IMPORTS: void* data, FILE* file
 * EXPORTS: none
 * PURPOSE: function to help write data in the gameLog LinkedList. Writes logEntry
 * data to a file. 
 */
void writeLogEntry(void* data, FILE* file) {
   fprintf(file, "    TURN: %d\n", ((logEntry*)data)->turn);
   fprintf(file, "    PLAYER: %c\n", ((logEntry*)data)->player);
   fprintf(file, "    LOCATION: %d,%d\n", ((logEntry*)data)->x, ((logEntry*)data)->y); 
   fprintf(file, "\n");
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: freeGameLog 
 * IMPORTS: void* data
 * EXPORTS: none
 * PURPOSE: helps freeLinkedList to free data of logList (GameLogs)
 */
void freeGameLog(void* data) {
   LinkedList* gameLog;
   gameLog = (LinkedList*)data;
   freeLinkedList(gameLog, freeLogEntry);
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: freeLogEntry 
 * IMPORTS: void* data
 * EXPORTS: none
 * PURPOSE: helps freeLinkedList to free data of logEntry 
 */
void freeLogEntry(void* data) {
   free(data);
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: writeGameLog 
 * IMPORTS: void* data, FILE* file 
 * EXPORTS: none
 * PURPOSE: function for helping writeLinkedList to write GameLogs 
 */
void writeGameLog(void* data, FILE* file) {
   LinkedList* gameLog;
   gameLog = (LinkedList*)data;
   fprintf(file, "GAME: %d\n", ((logEntry*)(gameLog->head->data))->gameNum); 
   writeLinkedList(gameLog, writeLogEntry, file);
} 
