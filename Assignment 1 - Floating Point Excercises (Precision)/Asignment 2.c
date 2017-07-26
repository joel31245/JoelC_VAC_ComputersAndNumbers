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
    double money=0.0;
    int n=0;
    // Number of decimal place
    printf("Input the number of decimal places to round to: ");
    scanf("%d", &n);
    // Amount of money
    printf("Input the money amount to be rounded.\n");
    scanf("%lf", &money);

    // Does the work
    roundoff(money, n);



    return 0;
}
