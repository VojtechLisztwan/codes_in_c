#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// If you don't your program runs in external console,
// set "externalConsole" to false to prevent this.
// However, in external console, you should be able to see
// AddressSanitizer output


int main() {
    printf( "Hello, World!\n" );
    double a=2, b=10, c=1;
    double d=0;
    double x1 =1, x2=100;
    bool hasTwoDifferentRoots = false;

    printf("\nEnter a: ");
    scanf("%lf", &a);

    printf("\nEnter b: ");
    scanf("%lf", &b);

    printf("\nEnter c: ");
    scanf("%lf", &c);


    d = b*b - (4*a*c);
    hasTwoDifferentRoots = d>0?true:false;
    printf("Discriminant %f\n\n", d);
    if(hasTwoDifferentRoots)printf("Given equation has two different roots\n\n");
    if(d<0){
        printf("Without result\n");
        return 0;
    }
    if (d==0){
        printf("Result is\n");
        return 0;
    }
    if (d>0){
        x1 = (sqrt(d)-b)/(2*a);
        x2 = (-sqrt(d)-b)/(2*a);
        printf("Results are %f and %f\n", x1, x2);
        return 0;
    }


    return 0;
}
