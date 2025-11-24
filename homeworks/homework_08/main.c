#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#define BONUS 0

void strtlw(char *str){
    for(int i=0; i<(int)strlen(str);i++){
        str[i] = (char)tolower(str[i]);
    }
}

void flush() {
  fflush(stdout);
}

void reset_color() {
  printf("\x1b[0m");
  flush();
}

void set_red_color() {
  printf("\x1b[41;1m");
  flush();
}


int main(int argc, char *argv[]) {
    char *input = malloc(100*sizeof(char));
    char *output = malloc(100*sizeof(char));
    char *target =  malloc(100*sizeof(char));
    strcpy(input, "");
    strcpy(output, "");
    strcpy(target, "");
   
    bool output_param = false;
    bool next_output=false;
    bool case_sensitive = true;

    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0){
            if(case_sensitive){
                case_sensitive = false;
                continue;
            }else{
                printf("Parameter -i provided multiple times\n");
                return 1;
            }
            
        }

        if(strcmp(argv[i], "-o") == 0){
            if(output_param){
                printf("Parameter -o provided multiple times\n");
                return 1;
            }
            output_param = true;
            next_output = true;
            continue;
        }
        if(next_output){
            strcpy(output, argv[i]);
            next_output = false;
            continue;
        }
        if(strcmp(input, "")==0){
            strcpy(input, argv[i]);
            continue;
        }
        if(strcmp(target, "")==0){
            strcpy(target, argv[i]);
            continue;
        }
        printf("Too many parameters provided\n");
        return 1;
    }

    if(strcmp(input, "")==0){
        printf("Input path not provided\n");
        return 1;
    }
    if(strcmp(target, "")==0){
        printf("Needle not provided\n");
        return 1;
    }
    if(output_param && strcmp(output, "")==0){
        printf("Missing output path\n");
        return 1;
    }


    FILE *fp = fopen(input, "r");
    FILE *fo;
    if(output_param){
        fo = fopen(output, "w");
    }
    char *buff=  malloc(100*sizeof(char));
    char *cpy=  malloc(100*sizeof(char));
    bool this = false;
    for(int i=0; fgets(buff, 100, fp)!=NULL;i++){
        strcpy(cpy, buff);
        if (!case_sensitive){
            strtlw(buff);
            strtlw(target);
        }
        //Verze standartni
        if(strstr(buff, target)!=NULL){
            this = true;
            if(output_param){
                if(!BONUS)fprintf(fo, "%s", cpy);
            }else{
                if(!BONUS)printf("%s", cpy);
            }
        }else{
            this = false;
        }
        
        if(BONUS&&this){
            //zvyrazneni casti kde je target
            int next_few = 0;
            int j;
            bool found = false;
            for (int i = 0; i < strlen(buff); i++){
                for (j = 0; j < strlen(target); j++){
                    if(buff[i+j]==target[j]){
                        found = true;
                    }else{
                        found = false;
                        break;
                    }
                }
                if(found)next_few = j;
                if (found||next_few>0){
                    set_red_color();
                    printf("%c", buff[i]);
                    reset_color();
                    next_few--;
                }else{
                    printf("%c", buff[i]);
                }
            }
        
        }
        
    }

    fclose(fp);
    if(output_param)fclose(fo);
    free(input);
    free(output);
    free(target);
    free(buff);
    return 0;
}
  