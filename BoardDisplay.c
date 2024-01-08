/***********************************************
 * AUTHOR: BRIAN SMITH
 * FILE_NAME: "BoardDisplay.c"
 * DATE_CREATED: 01/10/2019
 * DATE_LAST_EDITED: 19/10/2019
 * PURPOSE: c file for managing the board display to the terminal. Prints
 * the board, Checks if a winner is found and prints player moves to the
 * board. Function for prompting to quit is also included.
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoardDisplay.h"
#include "LinkedList.h"
#include "TicTacToe.h"
#include "UserInterface.h"

/* FUNCTION: printBoard 
 * IMPORTS: Integer height, Integer width, char** positions
 * EXPORTS: none
 * PURPOSE: Uses a height by width matrix called positions which tracks
 * which tiles (X, O) have been placed. Prints the current board to the
 * terminal. If a tile is unsed x,y coordinates are displayed to help users
 * palce tiles.
 */
void printBoard(int width, int height, char** positions) {
   int ii;
   int jj;
   
   for(jj = 0; jj < height;jj++) { /*loops through rows*/ 
      for(ii = 0; ii < width;ii++) { /*loops through cols*/
         printf(" -----  ");
      }
      printf("\n");
      for(ii = 0; ii < width;ii++) {
         if(positions[jj][ii] == 'O') {
            printf("|  O  | "); 
         }
         else if(positions[jj][ii] == 'X') {
            printf("|  X  | "); 
         }
         else {
            printf("| %d,%d | ", ii, jj); 
         }       
      }
      printf("\n");
      for(ii = 0; ii < width;ii++) {
         printf(" -----  ");
      }
      printf("\n");
   }
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: checkWinner 
 * IMPORTS: char** positions, Integer x, Integer y, int* settings 
 * EXPORTS: int
 * PURPOSE: Checks if there is a winner by looping through, rows, columns, 
 * diagonals and anti-diagonals. If no winner is found returns 0, keepgoing.
 * returns 1 for quit.
 * If 'O' wins returns 2
 * If 'X' wins returns 3
 */
int checkWinner(char** positions, int x, int y, int* settings) {
   int ii; int giveUp;
   int rowFound; int colFound; int diagFound; int aDiagFound;
   int width; int height; int n; /*n is number of tiles to win*/
   int winner; char compare; 
   
   winner = 0; compare = positions[y][x]; /*compare is the tile just placed*/
   width = settings[0]; height = settings[1]; n = settings[2];

   /*logic used to search rows is the same for all cols/diagonals, look at
      line comments below to calrify*/
   /*------------------ROWS------------------*/
   ii = 1; /*starts at one, no point at looking at the curent tile 
                  look adjacent*/
   giveUp = 0;
   rowFound = 0;
   /*while ii < number of tiles to win and in range of matrix */
   while((ii < n || giveUp == 0) && ((x-ii) >= 0) && ((x-ii) < width)){
      if(compare != positions[y][x-ii]) { /*if tile checked is not same as
                                             placed give up - not consecutive*/
         giveUp = 1;
      }
      else { /*else a consectuive tile found increment found*/
         rowFound++;
      }
      ii++; /*used to make sure number checked is less than n (number to win)
                  and used to find a tile in positions*/
   }
   
   ii = 1;
   giveUp = 0;
   while((ii < n || giveUp == 0) && ((x+ii) >= 0) && ((x+ii) < width)){ 
      if(compare != positions[y][x+ii]) {
         giveUp = 1;
      }
      else {
         rowFound++;
      }
      ii++;
   }
   
   if(rowFound == n-1) {
      winner = 1;
   }
   
   /*------------------COLUMNS------------------*/  
   if (winner == 0) { 
      ii = 1;
      giveUp = 0;
      colFound = 0;
      while((ii < n || giveUp == 0) && ((y-ii) >= 0) && ((y-ii) < height)){
         if(compare != positions[y-ii][x]) {
            giveUp = 1;
         }
         else {
            colFound++;
         }
         ii++;
      }
      
      ii = 1;
      giveUp = 0;
      while((ii < n || giveUp == 0) && ((y+ii) >= 0) && ((y+ii) < height)){ 
         if(compare != positions[y+ii][x]) {
            giveUp = 1;
         }
         else {
            colFound++;
         }
         ii++;
      }
      
      if(colFound == n-1) {
         winner = 1;
      }
   } 

   /*------------------DIAGONAL------------------*/
   if (winner == 0) { 
      ii = 1;
      giveUp = 0;
      diagFound = 0;
      while((ii < n || giveUp == 0) && ((x-ii) >= 0) && ((x-ii) < width) 
                                    && ((y-ii) >= 0) && ((y-ii) < height)){
         if(compare != positions[y-ii][x-ii]) {
            giveUp = 1;
         }
         else { 
            diagFound++;
         }
         ii++;
      }
      
      ii = 1;
      giveUp = 0;
      while((ii < n || giveUp == 0) && ((x+ii) >= 0) && ((x+ii) < width) 
                                    && ((y+ii) >= 0) && ((y+ii) < height)){
         if(compare != positions[y+ii][x+ii]) {
            giveUp = 1;
         }
         else {
            diagFound++;
         }
         ii++;
      }
      
      if(diagFound == n-1) {
         winner = 1;
      }
   } 

   /*------------------ANTI_DIAGONAL------------------*/
   if (winner == 0) { 
      ii = 1;
      giveUp = 0;
      aDiagFound = 0;
      while((ii < n || giveUp == 0) && ((x-ii) >= 0) && ((x-ii) < width) 
                                    && ((y+ii) >= 0) && ((y+ii) < height)){ 
         if(compare != positions[y+ii][x-ii]) {
            giveUp = 1;
         }
         else {
            aDiagFound++;
         }
         ii++;
      }
      
      ii = 1;
      giveUp = 0;
      while((ii < n || giveUp == 0) && (((x+ii) >= 0) && ((x+ii) < width)) 
                                    && (((y-ii) >= 0) && ((y-ii) < height))){
         if(compare != positions[y-ii][x+ii]) {
            giveUp = 1;
         }
         else { 
            aDiagFound++;
         }
         ii++;
      }
      
      if(aDiagFound == n-1) {
         winner = 1;
      }
   } 
   
   if(winner == 1) {
      if (positions[y][x] == 'O') {
         winner = 2;
      }
      else {
         winner = 3;
      }
   }
   return winner; 
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: playerMove 
 * IMPORTS: int** settings, LinkedList* gameLog, logEntry* entry, char** position
 * EXPORTS: int
 * PURPOSE: determines if a valid coordinate is enterter by the user. If not
 * it asks if the player wants to quit using the quitGame function. If the
 * coordinate is valid it places the correct char 'O' or 'X' and then uses
 * the checkWinner function to see if that was a winning move or not. 
 */

int playerMove(int* settings, LinkedList* gameLog, char** positions, char player) {
   int x; int y;
   int moveSuccessful; int decision; 
   int width; int height;
   int numRead;
   logEntry* entry;
   char buffer;

   static int gameNum = 1;
   static int turn = 1;

   moveSuccessful = FALSE;
   width = settings[0]; height = settings[1];
   numRead = 0; decision = 0; x = -1; y = -1;
   
   /*VARIABLE: decision 
    * 0 -> keep going
    * 1 -> quit
    * 2 -> player O wins
    * 3 -> player X wins
    */

   while(moveSuccessful == FALSE && decision == 0) { /*while incorrect 
                     coordinate and player doesnt want to quit.*/
      printf("PLAYER (%c)\n", player);
      printf("ENTER COORDINATES x,y --> ");
      numRead = scanf("%d,%d", &x, &y);
      if((numRead == 2) && !((x < 0 || x > width - 1) || 
                                       (y < 0 || y > height - 1))) { 
         if (positions[y][x] == ' ') { /*if tile is empty*/                              
            positions[y][x] = player;
            entry = (logEntry*)malloc(sizeof(logEntry));  
            entry->gameNum = gameNum; 
            entry->turn = turn;
            entry->player = player;
            entry->x = x;
            entry->y = y;      
            
            insertLast(gameLog, entry);  
            printBoard(settings[0], settings[1], positions); 
            printf("\n");
            moveSuccessful = TRUE;
            turn++;
            decision = checkWinner(positions, x, y, settings); 
         }
         else {
            printf("TILE NOT EMPTY! CHOOSE ANOTHER...\n");
         }
      }
      else { 
         if (x == 0){ /*input to quit*/
            decision = quitGame();
         }
         else {
            printf("INCORRECT ENTRY\n");
         } 
      }
      do { /*entry is probably something weird - clear the buffer*/
         buffer = getchar();
      } while (buffer != '\n');   
   }
   if(turn == (width*height + 1)) { /*all tiles placed and no winner*/
      decision = 1; /*quit*/
   }
   
   if(decision > 0 && turn > 1) { /*game over and tile has been placed*/
      gameNum++;
   }

   if(decision > 1) { /*game not over but tile placed*/
      turn = 1; 
   }
 
   return decision;
}

/*---------------------------------------------------------------------------*/

/* FUNCTION: quitGame 
 * IMPORTS: none
 * EXPORTS: none
 * PURPOSE: Allows the user to select quit or continue playing. Returns 0 for
 * continue and 1 for quit 
 * LINKS: Called by playerMove in BoardDisplay.
 */
int quitGame() {
   int quit;
   char decision;

   quit = 0; 
   
   do {
      decision = getchar();
   } while (decision != '\n');

   do { 
      printf("WOULD YOU LIKE TO QUIT TO THE MAIN MENU? (y/n): "); 
      decision = getchar();
   
      if (decision != 'y' && decision != 'n') {
         printf("INVALID ENTRY\n");
         do {
            decision = getchar();
         } while (decision != '\n');
         decision = 0;  
      }
   } while(decision == 0);
   if(decision == 'y') {
      printf("RETURNING TO MAIN MENU\n");
      quit = 1;
   }     

   return quit;    
}



