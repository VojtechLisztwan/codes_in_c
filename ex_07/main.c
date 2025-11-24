#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51

int max(int pole[],char *znaky, int n){
    int max_index = 0;
    int i;
    for (i = 0; i < n; i++){
        
        if(pole[i]>pole[max_index])max_index = i;
        if(pole[i]==pole[max_index]){
            //if(*(znaky+i)<*(znaky+max_index))max_index = i;
            
        }
    }
    return max_index;
}

int main() {
    int n;
    char buff[MAX];
    int counter[10];
    char *znaky;
    for(int i =0; i<10; i++){
        counter[i]=0;
    }
    int res_index;
    fgets(buff, MAX, stdin);
    if(!strcmp(strtok(buff, " "),"most-common")==0){
        return 0;
        
    }
    znaky = strtok(NULL, "\n");
    

    fgets(buff, MAX, stdin);
    n = atoi(buff);
    for (int i = 0; i < n; i++){
        fgets(buff, MAX, stdin);
        for(int j =0; buff[j]!='\0'&&buff[j]!='\n'; j++){
            for(int k =0; znaky[k]!='\0'&&znaky[k]!='\n'; k++){
                if(buff[j]==znaky[k])counter[k]++;
            }
        }
    }

   // printf("%s znaky", znaky);
    res_index = max(counter,znaky, 10);
    if(counter[res_index]==0){
        printf("(empty)\n");
        return 0;
    }
   
    printf("%c (%d)\n", znaky[res_index], counter[res_index]);

    
    return 0;
}

