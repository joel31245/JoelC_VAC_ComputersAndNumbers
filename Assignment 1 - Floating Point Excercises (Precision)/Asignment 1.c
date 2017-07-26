#include <stdio.h>
#include <stdlib.h>

int main()
{
    float sum32=0.0;
    double sum64=0.0;

    int i=1;
    for( i=1; i<=10000; i++ ){
        sum32+=1.0/(float)(i*i);
        sum64+=(double)1.0/(i*i);
    }
    printf(" Sum with float 1-10,000: %.17f\t Sum with double 1-10,000: %.16lf\n", sum32, sum64);

    sum32=0; sum64=0;
    for( i=10000; i>0; i--){
        sum32+=(float)1.0/(i*i);
        sum64+=(double)1.0/(i*i);
    }
    printf(" Sum with float 1-10,000: %.17f\t Sum with double 10,000-1: %.16lf", sum32, sum64);
    return 0;
}
