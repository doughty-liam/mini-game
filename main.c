#include "miniGame.h"

/************************************************************************************************
 *  Liam Doughty
 *  December 2021
 *  Version 0.01 - Under Development
 *  
 *  Developing maze-type game functionality.
 * 
 *  Compilation: gcc -ansi -o miniGame main.c
 *  Running: ./miniGame
 *  Controls: w - up
 *            s - down
 *            a - left
 *            d - right
 *            q - quit game, stop execution
 * 
 * **********************************************************************************************/

/* Need to develop algorithms to create random path to other end of the playboard. Then, another
   algorithm that will create all of the "fake" paths along the way to make it more difficult */



int main( int argc, char *argv[] ) {

    char playBoard[ROWS][COLUMNS];
    int inputRet = 0;
    int i;
    int j;
    int currRow = 1;
    int currColumn = 1;
    int startPosition[2];

    startPosition[0] = 12;
    startPosition[1] = 0;

    system( "./removeEcho.sh" );

    char *nextMove = malloc( sizeof(char) );

    for( i = 0; i < ROWS; ++i ) {
        for( j = 0; j < COLUMNS; ++j ) {
            playBoard[i][j] = 'X';
        }
    }

    system( "clear" );


    drawMaze( playBoard, startPosition );
    printBoard( playBoard, currColumn, currRow );


    for( i = 0; i < 30; ++i ) {

        inputRet = getMove( &currRow, &currColumn, nextMove );

        if( inputRet == 1 ) {
            printf( "Thanks for playing!\n" );
            system( "stty echo" );
            free(nextMove);
            return 0;
        }
        system( "clear ");
        printBoard( playBoard, currRow, currColumn );

    }

    free( nextMove );

    system( "stty echo" );
    system( "rm move.txt" ); /* removing temp file */

    return 0;
}