#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void printHorizontal(int *histogram, int offset);
void printVertical(int *histogram, int offset);
void countHistogram(int *histogram, int offset, int n);
bool isInRange(int a, int min, int max){
    if(a>=min&&a<=max)return true;
    return false;
}
int max(int *pole, int lenght){
    int max = pole[0];
    for (int i = 1; i < lenght; i++){
        if(pole[i]>pole[i-1])max = pole[i];
    }
    return max;
}

void initialize(int *pole, int lenght);


int main() {
    char ch;
    int n, offset;
    int histogram[10];

    scanf("%c", &ch);
    if(ch!='v'&&ch!='h'){
        printf("Neplatny mod vykresleni\n");
        return 1;
    }
    scanf("%d %d", &n, &offset);
    countHistogram(histogram, offset, n);
    if(ch=='h')printHorizontal(histogram, offset);
    else printVertical(histogram, offset);
  return 0;
}


void printHorizontal(int *histogram, int offset){
    char buffer[50];
    sprintf(buffer, "%d", offset+8);
    int delka = (int)strlen(buffer);

    for(int i=0;i<9;i++){
        printf("%*d",delka, i+offset);
        if(histogram[i]>0)printf(" ");//vypis mezery pokud bylo cislo pritomne
        for(int j=0;j<histogram[i];j++){
            printf("#");
        }
        printf("\n");
    }
    if(histogram[9]>0){
        printf("invalid: ");
        for(int j=0;j<histogram[9];j++){
            printf("#");
        }
        printf("\n");
    }
    
}

void printVertical(int *histogram, int offset){
    for (int i = max(histogram, 10)-1; i >= 0; i--){
        if(histogram[9]>i)printf("#");
        else printf(" ");
        for(int j=0;j<9;j++){
            if(histogram[j]>i)printf("#");
            else printf(" ");
        }   
        printf("\n"); 
    }
    printf("i");
    for(int j=offset;j<offset+9;j++){
        printf("%d", j);
    }   
    printf("\n");
}
    


void countHistogram(int *histogram, int offset, int n){
    int tmp=0;
    initialize(histogram, 10);
    for (int i = 0; i < n; i++){
        scanf("%d", &tmp);
        if(isInRange(tmp, offset, offset+8))histogram[tmp-offset]++;
        else histogram[9]++;
    }
}
void initialize(int *pole, int lenght){
    for (int i = 0; i < lenght; i++){
        pole[i]=0;
    }
    
}