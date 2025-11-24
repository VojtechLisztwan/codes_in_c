#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
const int MAX_SCORE = 100;

int sqr(int x) {
    return x*x;
}
int parabola(int x, int a, int b){
    return a*sqr(x)+b;
}

// *a -veme hodnotu z mista a
// &a vlozi misto hodnoty a
// int *a = je to promenna na misto
void swap(double * a, double * b){
    double c = *a;
    *a = *b;
    *b = c;
}

int main() {
    /*
    int x = 20;
    x = sqr(x);
    printf("Druha mocnina je %d\n\n", x);
    */
    
    /*
    int a=2, b=10;
    int range = 20;
    for (int i = -1*range; i <= range; i++)
    {
        printf("point [%d x, %d y]\n",i, parabola(i, a, b));
    }    
    */  
    /*
    double i = 2.5, ii = 8.6;

    printf("Promenna i = %lf, promenna ii = %lf\n\n", i, ii);
    swap(&i, &ii);
    printf("Promenna i = %lf, promenna ii = %lf\n\n", i, ii);
    */

    // 85 65 50 4 mensi nez 50
    
    
    // vyhodnocovani znamky
    int input=0;
    int rate=0;
    int n=0;
    do
    {
        printf("Zadejte skore\n");
        scanf(" %d", &input);
        if(input<0 || input>MAX_SCORE)break;
        rate +=input;
        n++;
        if (input>85)printf("Znamka 1\n");
        else if (input>65)printf("Znamka 2\n");
        else if (input>50)printf("Znamka 3\n");
        else if (input>0)printf("Znamka 4\n");
        else printf("Znamka 5\n");

    } while (input>=0);
    
    printf("Prumer je %lf\n\n", (double)((double)rate/(double)n));
    
    
    /*
    int n = 10;
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result*=i;
    }
    printf("Vysledek je: %d\n\n", result);
    */







    return 0;
}
