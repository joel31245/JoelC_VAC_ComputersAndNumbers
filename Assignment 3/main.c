#include <stdio.h>
#include <stdlib.h>

// RUNTIME ERROR FIBONNACCI

double smallNumbers( int arr[10000] );

int main()
{
    int a=0;
    printf("Please Enter a: ");
    scanf("%d", &a);

    int b=0;
    printf("Please Enter b: ");
    scanf("%d", &b);

    int arr[10000];
    FILE *file;

    file = fopen("10000.dat","r");

    int counts=0; int sum=0;
    while(!feof(file)){
        fscanf(file,"%d",&arr[counts++]);
    }
    for( counts=0; counts<10000; counts++ ){
        arr[counts] = arr[counts]*a+b;
        sum+=arr[counts];
    }
    printf("The sum is: %d\n", sum);

    // Fibbonacci
    long long fib1 = 0, fib2=0, fib3=0; int index=0;
    int n=0; // loop var
    printf("Input an Index to start the sum of the fibonnaci sequence within the 10,000 numbers:\n");
    scanf("%d",&index);

    sum=0;
    fib1 = arr[index];
    fib2 = arr[index+1];
    fib3 = fib1+fib2;
    for( n=3; n<=50; n++ ){
        // runs 49 times after the 2 first ones
        fib3 = fib1+fib2;
        fib1 = fib2;
        fib2 = fib3;
    }
    printf("50th Fibonnaci number: %lli\nNumber chosen is: %d\n", fib3, arr[index] );

    unsigned long fac=1;
    int i=0;
    for( i=1; i<=15; i++ ){
        fac*=i;
    }
    printf("15!: %ld\n\n", fac);

    printf("\nAssignment 3.2:\n Sum 1/(n^2) using Kahan's summation Algorithm: %.20lf\n\n", smallNumbers(arr) );

    return 0;
}

double smallNumbers( int arr[10000] ){
    double error = 0;
    double sum = 0;
    double ctr=0;
    for (ctr=1; ctr<=10000; ctr++){
        double tmp = sum; // error suppression helper
        double y = ctr + error; // error suppression determinate
        sum = tmp + 1/(ctr*ctr); // Actual addition
        error = (tmp - sum) + y; // error suppression
    }
    return sum;
}
