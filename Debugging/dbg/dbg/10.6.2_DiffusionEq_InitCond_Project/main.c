#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
    PROGRAM DISPLAYS THE DIFFUSION EQUATION FOR ENERGY? IN A BEAM THROUGH TIME
    _____EXPLICIT_METHOD__________IMPLICIT_METHOD__________CRANK-NICOLSON_METHOD_________JACOBI_METHOD____
    Users Can Change the:
     - initializer multiple (n)     [defined]
     - density coefficient  (D)     [defined]
     - when time stops      (tEND)  [defined]               Meaning for calculation. Program does not help with midlife crises.
     - length of the board  (xEND)  [defined]
     - time step            (dt)    [defined]
     - position step        (dx)    [defined]
*/

// These are equation/situation specific definitions
#define n 1
#define D 1.0
#define tEND 10.0
#define xEND M_PI

#define lam .4
#define dx (M_PI/10)
#define dt (lam/D*dx*dx)
int xSize = (double)xEND/dx +1;
int tSize = (double)tEND/dt +1;

char fileName[100];
char fileNameTimeSepCSV[100];
char fileNameBlockCSV[100];
char fileNameBlockActualCSV[100];
char errorFile[101];
char continu = 'y';
char whichMethod = '1';


/*
   x : 0->PI
   t : 0->1
*/


// MINI FUNCTION SET TO 0 BY DEFAULT CONDITIONS defined by problem
double F( double t, double x ){ return 0; }
// STEPWISE COMPUTATIONAL FUNCTIONS
void initializeU( double u[xSize][tSize] );
void boundaryConditions( double u[tSize][xSize], int tRow );
void ExplicitfillRow( double[tSize][xSize], int );
void implicitNOTESfillRow( double[tSize][xSize], int );
//void CNfillRow( double[tSize][xSize], int );
// DISPLAY FUNCTION
void printAll( double u[tSize][xSize] );
// EXACT FUNCTION
double exact( double t, double x ){ return exp(-pow((n-.5),2)*t) * cos((n-.5)*x); }

int main()
{
    double U[tSize][xSize];

    while (continu == 'y'){

        printf("Please Enter which method to compute the Diffusion Equation:\n(1 - Explicit)\t(2 - Implicit)\t(3 - Crank-Nicolson)\t(4 - Jacobi):\t");
        scanf(" %c", &whichMethod);

        printf("Please Enter the file name in which these values will be stored: \n");
        scanf(" %s", fileName);
        strcpy(fileNameBlockCSV, fileName);
        strcpy(errorFile, fileName);
        strcpy(fileNameBlockActualCSV, fileName);
        strcat(fileNameBlockCSV, "BLOCK.csv");
        strcat(errorFile, "ERROR.csv");
        strcat(fileNameBlockActualCSV, "BLOCKACTUAL.csv");

        /* STEP 1: Set the initial U at t=0 for the length of the beam x: 0->PI */
        initializeU( U );

        int i; // goes through all the time steps
        for( i=1; i<tSize; i++ ){
        /* STEP 2: Boundary Conditions for Next time Step */
            boundaryConditions( U, i );
        /* STEP 3: Filling in the rest of the current time Step */
            if( whichMethod == '1' ) ExplicitfillRow( U, i ); // Explicit
            else if( whichMethod == '2' ) implicitNOTESfillRow( U, i );// Implicit
            else if( whichMethod == '3' ) printf("Method under construction.");// CN
            else if( whichMethod == '4' ) printf("Method under construction.");// Jacobi
        }


        /* STEP 4: Displaying the Results */
        printAll( U );

        printf("\n\nLambda Marker to compare to Explicit:\n %lf\n\n", lam);

        printf("\nWould you like to continue again? (y/n) ");
        scanf(" %c", &continu);
    }


    return 0;
}

// PRINTING FUNCTION
void printAll( double u[tSize][xSize] ){
    int i, j; double error;

    FILE *ef = fopen(errorFile, "w");
    FILE *bf = fopen(fileNameBlockCSV, "w");
    FILE *abf = fopen(fileNameBlockActualCSV, "w");

    for( i=0; i<tSize; i++ ){
        for( j=0; j<xSize; j++ ){
            if( j==0 )printf("ESTIMATE:\t");
            printf("%lf\t", u[i][j] );
            fprintf(bf,"%lf,", u[i][j]);
        }
        fprintf(bf,"\n");

        for( j=0; j<xSize; j++ ){
            if( j==0 )printf("\nACTUAL:\t\t");
            printf("%lf\t", exact(i*dt, j*dx) );
            fprintf(abf, "%lf,", exact(i*dt, j*dx) );
        }
        fprintf(abf, "\n" );

        for( j=0; j<xSize; j++ ){
            if( j==0 )printf("\nERROR:\t\t");
            error = fabs(exact(i*dt, j*dx)-u[i][j])/exact(i*dt, j*dx) *100;
            if( u[i][j] == 0 && ( j==0 || j==xSize-1) ) error = 0.0;
            printf("%lf\t", error );
            fprintf(ef, "%lf,", error );
        }
        fprintf(ef, "\n");

        printf("\n\n\n\n");
    }

    fclose(ef);
    fclose(abf);
    fclose(bf);

}


void initializeU( double u[tSize][xSize] ){
    int i;
    for( i=0; i<xSize; i++ ){
        u[0][i] = cos((n-.5)*i*dx);
    }
}
void boundaryConditions( double u[tSize][xSize], int t ){
    u[t][0] = 0;

    u[t][xSize-1] = 0;
}

void ExplicitfillRow( double u[tSize][xSize], int t){
    int i=0;
    // Initial Column becuase of ghost node
    u[t][i] = u[t-1][i] + lam*( u[t-1][i+1] - 2*u[t-1][i] + u[t-1][i+1] ) + dt*F(i*dt, i*dx);
    // Normal Operating Explicit Method
    for( i=1; i<xSize-1; i++ ){
        u[t][i] = u[t-1][i] + lam*( u[t-1][i-1] - 2*u[t-1][i] + u[t-1][i+1] ) + dt*F(i*dt, i*dx);
    }

}

void implicitNOTESfillRow( double u[tSize][xSize], int t){
    /* STEP A: SETTING UP THE Tridiagonal */
    int N = xSize-1;
    double alpha[N], a=1+2*lam, b=-lam, c=-lam, g[N]; int j=0;


    /* STEP B: FORWARD THROUGH THE alpha's AND g's */
    alpha[0] = a;
    g[0] = u[t-1][0];

    for( j=1; j<N; j++ ){
        alpha[j] = a - (b*c)/alpha[j-1];
        g[j] =  u[t-1][j] - (b/alpha[j-1])*g[j-1];
    }

    /* STEP C: BACKWARD THROUGH u[t][j] */
    // Starting 1 below max because the end is set to 0 by "boundaryConditions" as it should be
    u[t][xSize-2] = g[N-1]/alpha[N-1];
    //printf("g[Size] = %lf\n\n", g[xSize-2]);
    for( j=N-2; j>0; j-- ){
        u[t][j] = ( g[j] - c*u[t][j+1] )/alpha[j];
    }

    // Initial Column for Row since boundary no longer determines it. BUT does not get used until next time step becuase of how the implicit method works
    u[t][0] = ( g[0] - 2*c*u[t][1] )/alpha[0];
}
