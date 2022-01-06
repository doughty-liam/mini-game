#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ROWS 40
#define COLUMNS 95


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

int drawMaze( char playBoard[ROWS][COLUMNS], int currPos[2] ) {

    /* previousMove 1 = down, 2 = forward, 3 = up */
    int i, j;
    int nextPos[2];
    int atEnd = 0;
    int moveDir = 1;
    srand(time(0));
    int previousMove;


    i = 0;

    /* currPosition initially set to the starting point of the maze */

    while( atEnd == 0 ) {

        playBoard[currPos[0]][currPos[1]] = 32;

        if( currPos[1] == (COLUMNS - 1) ) {
            atEnd = 1;  /* terminate maze drawing if the final column is reached */
        }

        /* checking if the current position is near top or bottom edge */
        if( currPos[0] < 2 ) {

            nextPos[0] = currPos[0] + 1;
            nextPos[1] = currPos[1];
            previousMove = 1;
        } else if (currPos[0] > 37) {

            nextPos[0] = currPos[0] - 1;
            nextPos[1] = currPos[1];
            previousMove = 3;
        } else {

            /* Any move direction is possible. up, down, or forwards. */
            moveDir = ( (rand())%6 ) + 1;

            if( moveDir == 1 ) {
                nextPos[0] = currPos[0] + 1;
                nextPos[1] = currPos[1];
                previousMove = 2;
            } else if( moveDir == 2 ) {
                nextPos[0] = currPos[0];
                nextPos[1] = currPos[1] + 1;
                previousMove = 3;
            } else if( moveDir == 3 ) {
                nextPos[0] = currPos[0] - 1;
                nextPos[1] = currPos[1];
                previousMove = 1;
            } else if( (moveDir == 4) && (currPos[0] >= 3) && (currPos[1] <= 90) ) { /* upwards U shape */ 

                nextPos[1] = currPos[1];
                nextPos[0] = nextPos[0] - 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';

                nextPos[0] = nextPos[0] - 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';

                nextPos[1] = nextPos[1] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';

                nextPos[1] = nextPos[1] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';
                
                nextPos[1] = nextPos[1] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';
                
                nextPos[1] = nextPos[1] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';
                
                nextPos[0] = nextPos[0] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';

                nextPos[0] = nextPos[0] + 1;
                nextPos[1] = nextPos[1];                

            } else if ( (moveDir == 5) && (currPos[1] <= 90) ) { /* straight forward 3 units */
                
                nextPos[1] = currPos[1];
                for( i = 0; i < 2; ++ i ) {
                    nextPos[1] = nextPos[1] + 1;
                    playBoard[nextPos[0]][nextPos[1]] = ' '; 
                }
                nextPos[0] = currPos[0];
                nextPos[1] = nextPos[1] + 1;
            
            } else if ( (moveDir == 6) && (currPos[0] <= 90) && (currPos[1] >= 35 ) ) { /* Downwards L shape */  
                
                nextPos[0] = currPos[0];
                nextPos[1] = currPos[1];
                for( i = 0; i < 4; ++i ) {
                    nextPos[0] = nextPos[0] + 1;
                    playBoard[nextPos[0]][nextPos[1]] = ' ';
                }

                nextPos[1] = nextPos[1] + 1;
                playBoard[nextPos[0]][nextPos[1]] = ' ';
                
                nextPos[1] = nextPos[1] + 1;

            }

        }

        currPos[0] = nextPos[0];
        currPos[1] = nextPos[1];

    }

    /* INITIAL MAZE DRAWN, NOW NEED TO MAKE IT MORE COMPLICATED... */
    /* RUNNING ALGORITHM MULTIPLE TIMES */

    /* Set start position of near top border */
    currPos[0] = 1;
    currPos[1] = 5;
    atEnd = 0;

    while( atEnd == 0 ) {

        playBoard[currPos[0]][currPos[1]] = 32;


        /* checking if the current position is near top or bottom edge */
        if( currPos[0] < 2 ) {

            nextPos[0] = currPos[0] + 1;
            nextPos[1] = currPos[1];
            previousMove = 1;

        } else if (currPos[0] > 37) {

            nextPos[0] = currPos[0] - 1;
            nextPos[1] = currPos[1];
            previousMove = 3;

        }else if ( (currPos[1] > 92) || (currPos[1] < 2) || (currPos[0] > 37) ) {

            /* at the RHS or LHS, ENDING */
            atEnd = 1;

        } else {

            /* Any move direction is possible. up, down, or forwards. */
            moveDir = ( (rand())%(3-1+1) ) + 1;

            if( moveDir == 1 ) {
                nextPos[0] = currPos[0] + 1;
                nextPos[1] = currPos[1];
                previousMove = 2;
            } else if( moveDir == 2 ) {
                nextPos[0] = currPos[0];
                nextPos[1] = currPos[1] + 1;
                previousMove = 3;
            } else if( moveDir == 3 ) {
                nextPos[0] = currPos[0] - 1;
                nextPos[1] = currPos[1];
                previousMove = 1;
            }
        }

        currPos[0] = nextPos[0];
        currPos[1] = nextPos[1];

    }

    return 0;
}