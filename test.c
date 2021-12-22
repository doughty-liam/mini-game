#include "miniGame.h"

int main( int argc, char *argv[] ) {

    char **playBoardHeap = NULL;
    char playBoardStack[ROWS][COLUMNS];
    int i;
    int j;
    int currRow = 1;
    int currColumn = 1;
    int playerRow = 25;
    int playerCol = 25;

    clock_t before, after;
    double differenceHeap, differenceStack;

    char *nextMove = malloc( sizeof(char) );
    
    playBoardHeap = malloc( ROWS*sizeof(char *) ); /* Declaring 35 double char pointers for board rows  */

    for( i = 0; i < ROWS; ++i ) {

        playBoardHeap[i] = (char*)malloc( COLUMNS*sizeof(char *) ); /* Setting each row to have 80 characters across for columns */

    }

    for( i = 0; i < ROWS; ++i ) {
        for( j = 0; j < COLUMNS; ++j ) {
            playBoardHeap[i][j] = 'X';
            playBoardStack[i][j] = 'X';
        }
    }

    before = clock();

    /* Insert timed process */
    printBoard( playBoardHeap, 25, 25 );

    after = clock();
    differenceHeap = ((double)(after - before))/(CLOCKS_PER_SEC);

    before = clock();

    /* Insert timed process */
    for( i = 0; i < ROWS; ++i ) {
        for( j = 0; j < COLUMNS; ++j ) {
            if( (playerRow == i) && (playerCol == j) ) {
                printf( "\033[0;31m" );
            } else {
                printf( "\033[0;37m" );
            }
            printf( "%c", playBoardStack[i][j] );
        }
        printf( "\n" );
    }

    printf( "\033[0;37m" );

    after = clock();
    differenceStack = ((double)(after - before))/(CLOCKS_PER_SEC);


    printf( "Heap print time: %f\n", differenceHeap );
    printf( "Stack print time: %f\n", differenceStack );

    for( i = 0; i < ROWS; ++ i ) {
            free( playBoardHeap[i] );
    }


   return 0;
}