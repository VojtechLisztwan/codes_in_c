#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROW_MAX 51


void normalize(char *row);
bool containsUpper(char *word);
void normalizeWord(char *word);
void toLower(char *word);
char charToLower(char c);
void toUpper(char *word);
char charToUpper(char c);
int countUpper(char *word);
int countLower(char *word);
int countChar(char *word, char c);
void controllDoubles(char *word);

int my_strlen(char *word){
    int i;
    for (i = 0; word[i]!='\0'; i++){
    }
    return i;
    
}

void my_strcpy(char* dst, char* src){
    int i = 0;
    while(1){
        dst[i]=src[i];
        if(src[i]=='\0')break;
        i++;
    }
    
}

int my_atoi(char *src){
    int i, a=0;
    for (i = 0; src[i]<'0'||src[i]>'9'; i++);
    for (int j = i; src[i]>='0'&&src[i]<='9'; i++){
        a *=10;
        a+=src[i]-'0';
    }
    return a;
    
}

int my_strcmp(char *s1, char* s2){
    int i;
    for (i = 0; s1[i]!='\0'; i++){
        if(s1[i]!=s2[i]){
            if(s1[i]>s2[i])return 1;
            else return -1;
        }
        
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;
    } else if (s1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}
void my_strcat(char *dst, char *src){
    int i;
    for (i = 0; dst[i]!='\0'; i++);

    int j;
    for (j = 0; src[j]!='\0'; j++){
        dst[i+j] = src[j];
    }
    dst[i+j]='\0';
    
}


char* my_strtok(char **str, char del) {
    if (*str == NULL) return NULL;

    while (**str == del) {
        (*str)++;
    }

    if (**str == '\0') return NULL;

    char *start = *str;
    while (**str != '\0' && **str != del) {
        (*str)++;
    }
    if (**str == del) {
        **str = '\0';
        (*str)++;
    }
    return start;
}



int main() {
    char buff[51];
    int n =0;
    fgets(buff, ROW_MAX, stdin);
    n = my_atoi(buff);
    for (int i = 0; i < n; i++) {
        fgets(buff, ROW_MAX, stdin);
        normalize(buff);
        if(i<n-1)printf("\n");
    }
    

    


    return 0;
}


void controllDoubles(char *word){
    char buff[ROW_MAX];
    int counter=0;
    for (int i = 0; i < (int)my_strlen(word); i++){
        if(word[i]!=word[i+1]){
            buff[counter]=word[i];
            counter++;
        }
    }
    buff[counter]='\0';
    my_strcpy(word, buff);

}

void normalize(char *row){
    char cpy[ROW_MAX];
    my_strcpy(cpy, row);
    char *word;
    char newRow[ROW_MAX];
    int counter = 0;
    char buf[ROW_MAX];
    newRow[0]='\0';
    while (1){
        //if(counter)word = strtok(NULL, " ");
        //else word = strtok(row, " ");
        //if(word == NULL)break;
        word = my_strtok(&row, ' ');
        if(word==NULL)break;
        my_strcpy(buf, word);
        normalizeWord(buf);
        if(counter!=0&&(my_strcmp(buf, "\n")!=0))my_strcat(newRow, " ");
        my_strcat(newRow, buf);
        counter++;
    }
    controllDoubles(newRow);
    printf("%s", newRow);
    printf("lowercase: %d -> %d\n", countLower(cpy),countLower(newRow));
    printf("uppercase: %d -> %d\n", countUpper(cpy),countUpper(newRow));
    printf("spaces: %d -> %d\n", countChar(cpy,' '),countChar(newRow,' '));
    
}

void normalizeWord(char *word){
    
    if(containsUpper(word)){
        toLower(word);
        word[0] = charToUpper(word[0]);
        //printf("Obsahuje velke\n");
    }else{
        toUpper(word);
    }

}




bool containsUpper(char *word){
    for (int i = 0; i < (int)my_strlen(word); i++){
        if(word[i]>='A'&&word[i]<='Z')return true;
    }
    return false;
}
 


int countUpper(char *word){
    int tmp=0;
    for (int i = 0; i < (int)my_strlen(word); i++){
        if(word[i]>='A'&&word[i]<='Z')tmp ++;
    }
    return tmp;
}

int countLower(char *word){
    int tmp=0;
    for (int i = 0; i < (int)my_strlen(word); i++){
        if(word[i]>='a'&&word[i]<='z')tmp ++;
    }
    return tmp;
}
int countChar(char *word, char c){
    int tmp=0;
    for (int i = 0; i < (int)my_strlen(word); i++){
        if(word[i]==c)tmp ++;
    }
    return tmp;
}

void toLower(char *word){
    for (int i = 0; i < (int)my_strlen(word); i++){
        word[i] = charToLower(word[i]);
    }
}

void toUpper(char *word){
    for (int i = 0; i < (int)my_strlen(word); i++){
        word[i] = charToUpper(word[i]);
    }
}

char charToLower(char c){
    if(c>='A'&&c<='Z')return c-('A'-'a');
    else return c;
}
char charToUpper(char c){
    if(c>='a'&&c<='z')return c+('A'-'a');
    else return c;
}