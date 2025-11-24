#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>



int max(int a, int b){
    if(a>b)return a;
    return b;
}
int min(int a, int b){
    if(a<b)return a;
    return b;
}
int absolute(int a){
    if (a<0)return a*-1;
    return a;    
}
bool isOdd(int a){
    if(a==0)return false;
    if(a%2)return true;
    return false;
}
bool isEven(int a){
    if(a==0)return false;
    if(a%2)return false;
    return true;
}
char* printOddEven(int value){
    if(isOdd(value))return "odd";
    if (isEven(value))return "even";
    return "neutral";
}

//greatest common divisor
int gcd(int u, int w){
    int r;
    while (w!=0){
        r = u%w;
        u=w;
        w=r;
    }
    return u;
    
}

//lowest common multiple
int lcm(int a, int b){
    return max(a, b)/gcd(a, b)*min(a,b);
}

int main() {
    int a=0, b=0;
    int c;
    int d;
    printf("Enter two number\n");
    scanf("%d%d", &a, &b);
    c = max(a, b);
    d = min(a, b);
    printf("Max value is %d with absolute value %d and is %s\n\n", c, absolute(c), printOddEven(c));
    printf("Min value is %d with absolute value %d and is %s\n\n", d, absolute(d), printOddEven(d));

    if(a<=0 || b<=0){
        printf("At least one of those two numbers is zero or negative\n\n");
        return 0;
    }
    printf("Greatest common divisor of those two numbers is: %d\n\n", gcd(c,d));
    printf("Lowest common multiple: %d\n\n", lcm(c,d));


    return 0;
}
