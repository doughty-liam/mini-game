#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ROWS 35
#define COLUMNS 80


int printBoard( char playBoard[ROWS][COLUMNS], int playerRow, int playerCol ) {

    int i, j;

    for( i = 0; i < ROWS; ++i ) {
        for( j = 0; j < COLUMNS; ++j ) {
            if( (playerRow == i) && (playerCol == j) ) {
                printf( "\033[0;31m" );
            } else {
                printf( "\033[0;37m" );
            }
            printf( "%c", playBoard[i][j] );
        }
        printf( "\n" );
    }

    printf( "\033[0;37m" );

    return 0;
}


int getMove( int *currRow, int *currCol, char *nextMove ) { /* gets user input, returns 1 if quit key is pressed */

    FILE *fp;
    system( "./getMove.sh" );
    fp = fopen( "move.txt", "r" );
    fscanf( fp, "%c", nextMove );

    /* fscanf( stdin, "%c", nextMove ); getting next move from stdin
    getc( stdin ); */

    if( *nextMove == 'w' ) {
        (*currRow) = (*currRow) - 1;
    } else if( *nextMove == 's' ) {
        (*currRow) = (*currRow) + 1;
    } else if( *nextMove == 'a' ) {
        (*currCol) = (*currCol) - 1;
    } else if( *nextMove == 'd' ) {
        (*currCol) = (*currCol) + 1;
    } else if( *nextMove == 'q' ) {
        return 1;
    }

    fclose( fp );
    return 0;
}
