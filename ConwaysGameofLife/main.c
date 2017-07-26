#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* Conway's Game of Life
    Use 2D grid randomly filled
    RULES:
     - Any cell with fewer than 2 neighbors alive dies (underpopulation)
     - Any cell with more than 3 neighbors alive dies (overpopulation)
    Use old values to determine the matrix

    NOTE: Any variable with "index" starts counting at 0, R and C are sizes and start counting from 1
*/

// Global Variables to Define grid size.
int R;
int C;
char fileName[100];
// GENERAL FUNCTIONS Make and Run Game
void createRandGrid( int[R][C], int , int );
void displayGrid( int[R][C], int , int );
void copyGrid( int full[R][C], int empty[R][C], int rows, int cols, int topIndex, int leftIndex );
// GAME RUNNING FUNCTIONS
void scanGrid( int grid[R][C], int rows, int cols );


int main()
{
    /* STEP 1: CREATE RANDOM GRID */
    printf("Please Enter Board size ( r   c ): ");
    scanf("%d", &R); scanf("%d", &C);
    int board[R][C];
    createRandGrid( board, R, C );

    printf("How many generations do you want? ");
    int gens = 0;
    scanf("%d", &gens);
    system("cls");
    printf("\nThe initial board is: \n");
    displayGrid( board, R, C );

    int count=0;

    /* STEP 2: */
    while (count<gens){
        if( R<10 || gens>10) Sleep(200);
        else Sleep(1000);
        system("cls");
        count++;
        printf("\n GENERATION: %d/%d\n", count,gens);


        scanGrid(board, R,C);
        displayGrid( board, R, C );

    }

    /* DISPLAYING THE BOARD */

    return 0;
}


// GENERAL PURPOSE FUNCTIONS
void createRandGrid( int grid[R][C], int rows, int cols ){
    time_t t;
    srand( (unsigned) time(&t) );

    int r, c;
    double random;
    for( r=0; r<rows; r++ ){
        for( c=0; c<cols; c++){
            random = (((double)rand() / RAND_MAX));
            if ( random >= 0.5 ) grid[r][c] = 1;
            else               grid[r][c] = 0;
        }
    }
}
void displayGrid( int grid[R][C], int rows, int cols ){
    // FUNCTION SHOULD ALSO PRINT TO FILE EVENTUALLY
    int r, c;

    for( r=0; r<rows; r++ ){
        // Boundary's
        if ( r==0 ){
            for( c=0; c<cols+2; c++ )
                printf("_");
            printf("\n");
        }
        printf("|");

        // Actual Board
        for( c=0; c<cols; c++ ){
            if( grid[r][c] == 0 ) printf(" ");
            else                  printf("1");
        }

        // Boundary's
        printf("|\n");
        if ( r==rows-1 )
            for( c=0; c<cols+2; c++ )
                printf("_");
    }
}
void copyGrid( int full[R][C], int empty[R][C], int rows, int cols, int topIndex, int leftIndex ){
    int r,c;
    for( r=topIndex; r<rows+topIndex; r++ )
        for( c=leftIndex; c<cols+leftIndex; c++ )
            empty[r][c] = full[r][c];
}


// COMPARE & OPERATOR FUNCTIONS
int checkRules( int temp[R][C], int row, int col ){
    int countAlive=0;
    // CHECK CORNERS
        // Top Left
    if ( row==0 && col==0){
        if( temp[row+1][col] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
        if( temp[row+1][col+1] == 1) countAlive++;
    }
        // Top Right
    else if ( row==0 && col==C-1){
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row+1][col-1] == 1) countAlive++;
        if( temp[row+1][col] == 1) countAlive++;
    }
        // Bottom Left
    else if ( row==R-1 && col ==0){
        if( temp[row-1][col] == 1) countAlive++;
        if( temp[row-1][col+1] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
    }
        // Bottom Right
    else if ( row==R-1 && col==C-1){
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row-1][col-1] == 1) countAlive++;
        if( temp[row-1][col] == 1) countAlive++;
    }
    // CHECK EDGES
        // Top Edge
    else if ( row==0 && col>0 && col<C-1 ){
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
        if( temp[row+1][col-1] == 1) countAlive++;
        if( temp[row+1][col] == 1) countAlive++;
        if( temp[row+1][col+1] == 1) countAlive++;
    }
        // Bottom Edge
    else if ( row==R-1 && col>0 && col<C-1 ){
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
        if( temp[row-1][col-1] == 1) countAlive++;
        if( temp[row-1][col] == 1) countAlive++;
        if( temp[row-1][col+1] == 1) countAlive++;
    }
        // Left Edge
    else if ( col==0 && row>0 && row<R-1 ){
        if( temp[row-1][col] == 1) countAlive++;
        if( temp[row-1][col+1] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
        if( temp[row+1][col+1] == 1) countAlive++;
        if( temp[row+1][col] == 1) countAlive++;
    }
        // Right Edge
    else if ( col==C-1 && row>0 && row<R-1 ){
        if( temp[row-1][col] == 1) countAlive++;
        if( temp[row-1][col-1] == 1) countAlive++;
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row+1][col-1] == 1) countAlive++;
        if( temp[row+1][col] == 1) countAlive++;
    }
    else
    {
        if( temp[row-1][col-1] == 1) countAlive++;
        if( temp[row-1][col] == 1) countAlive++;
        if( temp[row-1][col+1] == 1) countAlive++;
        if( temp[row][col-1] == 1) countAlive++;
        if( temp[row][col+1] == 1) countAlive++;
        if( temp[row+1][col-1] == 1) countAlive++;
        if( temp[row+1][col] == 1) countAlive++;
        if( temp[row+1][col+1] == 1) countAlive++;
    }

    // RULES Checking
    if( temp[row][col]== 1){
        if (countAlive<2 || countAlive>3){ return 0; }
        else{ return 1; }
    }
    else{
        if (countAlive==3){ return 1; }
        else{ return 0; }
    }
}

void scanGrid( int grid[R][C], int rows, int cols ){
    int r,c;
    int temp[R][C];
    copyGrid(grid, temp, R,C, 0,0);

    for( r=0; r<rows; r++ ){
        for( c=0; c<cols; c++ ){
            grid[r][c] = checkRules(temp, r,c);
        }
    }
}
