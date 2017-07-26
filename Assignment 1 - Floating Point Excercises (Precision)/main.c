#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void roundoff( double input, int nDecimalPlaces ){

    int i=0;
    int j10s = 1;
    for (i=0; i<nDecimalPlaces; i++)
        j10s*=10;

    input = input*j10s;
    double rounded = 0.0;
    double error = 0.0;

    if( ((int)(input*10)%10) != 5){         rounded = roundf(input);  }
    else if(  (((int)input%10)%2) == 0){    rounded = floorf(input);  }
    else                                    rounded = ceilf(input);

    if( rounded>input ) error = rounded-input;
    else                               error = input-rounded;

    printf(" Original %lf\n Rounded %lf\n Error %lf\n Relative Error %lf\n", input/j10s, rounded/j10s, error/j10s, error/input);


}

int main()
{

    int n=0;
    // Number of decimal place
    printf("Input the number of decimal places to round to: \n");
    scanf(" %d", &n);
    // Does the work
    double a = .1036; double b = .2122; double c = .7381;
    double A = .2081; double B = .4247; double C = .9327;
    printf("System of Equations:\n\t0.1036x+0.2122y=0.7381\n\t0.2081x+0.4247y=0.9327");

    double x = ( C- B*c/b )/( A - B/b*a);
    double y = ( c - a*x )/b;

    printf("Unrounded \nx=%lf\t y=%lf\n", x,y);
    printf("\nRounded X:\n\t");
    roundoff(x,n);
    printf("\nRounded Y:\n\t");
    roundoff(y,n);
    return 0;
}
