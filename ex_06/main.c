#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>



int my_strlen(const char* str){
    int i=0;
    while (str[i]!=0){
        i++;
    }
    return i;
    
}

void my_strcat(char* dst, const char* src){
    int len_dst = my_strlen(dst);
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src; i++){
        dst[i+len_dst] = src[i];
    }
}

void remove_end_of_line(char *str){
    int len = strlen(str);
    if(str[len-1]=='\n')str[len-1] = 0;
}

void print_splitted_string(char *str, const char* delimiter){
    char *nxt_token;
    char *substring = strtok_r(str, delimiter,&nxt_token);
    while (substring!=NULL){
        printf("%s\n", substring);
        substring = strtok(NULL, delimiter);
    }
    
}

void to_upper(char *str){
    for (int i = 0; str[i]!=0; i++){
        str[i] = toupper(str[i]);
    }
    printf("%s\n", str);
}
char* my_dynamic_strcat(const char* s1, const char* s2){
    char *result = malloc(my_strlen(s1)+my_strlen(s2)+1);
    char *ptr = result;
    for (int i = 0; s1 != 0; i++){
        *ptr = s1[i];
        ptr++;
    }
    for (int i = 0; s1 != 0; i++){
        *ptr = s1[i];
        ptr++;
    }
    return ptr;
}

int main() {
    
    char *s1 = "Hello world";
    printf("%s\n", s1);
    printf("Lenght of string is %d\n", my_strlen(s1));
    s1 = "AHOOJ"; 
    


    
    char *s2 = "world";
    char buffer[80] = "Hello ";
    char *buff;
    buff = my_dynamic_strcat(s1, s2);
    printf("Output of concatation is %s\n", buff);
    
    if(strcmp(s1, buffer)==0)printf("String are the same\n\n");
    
    while (fgets(buffer, 80, stdin)!=NULL){
        remove_end_of_line(buffer);
        printf("Readed line %s\n", buffer);
        to_upper(buffer);
        print_splitted_string(buffer, ";");
    }
    return 0;
}
