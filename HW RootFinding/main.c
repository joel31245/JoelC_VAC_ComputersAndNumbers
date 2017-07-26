#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program finds the maximum deflection on a beam which follows the curve
    2.31e-14 ( -x^5 + 2L^2 x^2 - L^4 x )
    REASSIGNMENT: e^-x -x, Ans = .567

    Use one of the bracketing methods, and one open method and compare rate of convergence, time, convergence itself...
*/
/* Board spans a length of 600 cm */


#define L 1
#define tolerance .00001

// Prototypes functions
double  f( double );
double df( double );
double bisectionRoot( double , double , double );
double newtonRaphson( double , double );

int main()
{
    printf("Program finds the zero for the curve:\n\n");

    double root = bisectionRoot(0,L, tolerance);
    printf("Bisection Method: Root: %lf", root );
    // Checks to see if the root is a valid input
//    if( root >= 0 && root <= 1 )
//        printf("Bisection Method: Root: %lf\n", root );
//    else
//        printf("  Program Terminating. Have a good day!\n");


    printf("\n");
    root = newtonRaphson(0, tolerance); // Newton-Raphson Method
    printf("\nNewtonRaphson: Root: %lf\n", root);

    return 0;
}




// EQUARTIONS
double f( double x ){
    // FORMULA: 2.31e-14 ( -x^5 + 2L^2 x^2 - L^4 x )
    return 2.31*pow(10,-14) * ( -pow(x,5) + 2*L*L*x*x - L*L*L*L*x );
}
double df( double x ){
    return exp(-x) - x;
}
double ddf( double x ){
    return -exp(-x) - 1;
}


double bisectionRoot( double xL, double xR, double tol){

    // Check to see if the signs on either boundary are different
    // NOTE: Only df is being used in this function because we are looking for when the beam curves back which is when df = 0.
    // NOTE: df is the derivitive of f(x) OR f'(x)

    if( df(xL)*df(xR)>0 ){
        // If signs are not different exit function
        printf(" Bisection Method. NO REAL ROOT\n");
        return -1.0;
    }


    double xOld = 0.0;
    double error = 1.0;
    double xNew = 0.0;

    // Things to compare the effectiveness of this against the other methods
    int loopIterationsCounter = 0;

    while(error > tol){

        xNew = (xL+xR)/2;                  // Sets new x to the middle of the interval
        if( df(xNew)*df(xL) < 0 ){ xR = xNew; }     // Checks the left half to see a sign flip. If so, then reset right boundary to the new x
        else if( df(xNew)*df(xL) > 0 ){ xL = xNew; } // Checks the right half to see a sign flip. If so, then reset left boundary to the new x
        else{ return xNew; }                        // Checks if the new x is the root
        error = (double) fabs((df(xNew)-df(xOld))/(df(xNew)))*100;
        // Manual Absolute Value
        //if (error<0){ error*=-1; }

        // reseting Old x to the new one for the next iteration
        xOld = xNew;

        // Things to compare the effectiveness of this against the other methods
        loopIterationsCounter++;
    }

    printf("Bisection: LoopCounter: %d\n", loopIterationsCounter);

    return xNew;
}



double newtonRaphson( double xI, double tol ){

    double error = 1.0;
    double xNew = 0.0;
    double xOld = xI;

    int loopIterationsCounter = 0;

    while (error>tol){
        xNew = xOld - ( df(xOld) )/( ddf(xOld) );
        error = (xNew-xOld)/xNew*100;
        // Setting vars for next iteration
        xOld = xNew;

        loopIterationsCounter++;
    }

    printf("NewtonRaphson: LoopCounter: %d\n", loopIterationsCounter);

    return xNew;
}
