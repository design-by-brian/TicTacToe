#ifndef TICTACTOE_H
#define TICTACTOE_H

#define TRUE 1
#define FALSE 0

/*FUNCTIONS*/
void getSettings(FILE*, int*, int*);

/* TYPEDEF: logEntry
 * FIELDS: gameNum - keeps track of what number game that log is in,
 * turn - turn of the specific game, player - X/O, x - x position, 
 * y - y position on board.
 * ASSERTION: keeps a log of a players move, storing the key infromation
 * that needs to be displayed in the game logs.
 */
typedef struct { 
   int gameNum;
   int turn;
   char player;
   int x;
   int y; 
} logEntry;

#endif
