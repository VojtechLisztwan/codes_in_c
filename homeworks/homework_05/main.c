#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Pro bonusovou ulohu 1
#define BONUS 1

typedef struct{
    int direction;
    int row;
    int col;
}Tturtle;

int * allocate(int size){
    int *memory = (int *) malloc(size*sizeof(int));
    return memory;
}

int index2dto1d(int row,int col, int cols){
    return row*cols + col;
}

void init(int *field, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int a = index2dto1d(i, j, cols);
            field[a] = (int)'.';
        }   
    }
    
}

void printField(int *field, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int a = index2dto1d(i,j, cols);
            printf("%c", (char)field[a]);
        }
        printf("\n");
    }
}

void makeBariers(int *field, int rows, int cols){
    for(int i = 0; i<3; i++){
        int a = rand()%(rows*cols-1);
        a++;
        field[a] = '#';
    }
}

void printWithTurtles(int *field, int rows, int cols, Tturtle tur[], int counter){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int a = index2dto1d(i,j, cols);
            char tmp = (char)field[a];
            if(tmp =='.') tmp = ' ';
            for (int k = 0; k < counter; k++){
                if(i==tur[k].row && j==tur[k].col) tmp = 'z';
            }
            printf("%c", tmp);
        }
        printf("\n");
    }
}


void initTurtle(Tturtle turtles[], int size){
    for(int i = 0; i < size; i++){
        turtles[i].direction = 0;
        turtles[i].row = 0;
        turtles[i].col = 0;
    }
}



int main() {
    int cas = (int) time(NULL);
    srand(cas);

    char ch;
    int rows, cols;
    int counter = 1;
    Tturtle tur[3];
    initTurtle(tur,3);

    scanf("%d %d", &rows, &cols);
    int* field = allocate(rows*cols);
    init(field, rows, cols);

    if(BONUS)makeBariers(field, rows, cols);
    
    while(1){
        scanf("%c ", &ch);
        if(ch=='x')break;
        switch (ch){
            case 'o':
                for(int i = 0; i<counter; i++){
                    int a = index2dto1d(tur[i].row, tur[i].col, cols);
                    if(((char)field[a])=='o')field[a]=(int)'.';
                    else field[a]=(int)'o';
                }
                break;
            case 'm':
                for(int i = 0; i<counter; i++){
                    int prev_row = tur[i].row;
                    int prev_col = tur[i].col;
                    switch (tur[i].direction){
                        case 0:
                            tur[i].col++;
                            if(tur[i].col>=cols)tur[i].col = 0;
                            break;
                        case 1:
                            tur[i].row++;
                            if(tur[i].row>=rows)tur[i].row = 0;
                            break;
                        case 2:
                            tur[i].col--;
                            if(tur[i].col<0)tur[i].col = cols-1;
                            break;
                        case 3:
                            tur[i].row--;
                            if(tur[i].row<0)tur[i].row = rows-1;
                            break;

                        default:
                            break;
                    }
                    int temp = index2dto1d(tur[i].row,tur[i].col,cols);
                    if(field[temp]=='#'){
                        tur[i].row = prev_row;
                        tur[i].col = prev_col;
                    }
                }
                break;
            case 'r':
                for(int i = 0; i<counter; i++){
                    tur[i].direction++;
                    if(tur[i].direction>3)tur[i].direction=0;
                }
                break;
            case 'l':
                for(int i = 0; i<counter; i++){
                    tur[i].direction--;
                    if(tur[i].direction<0)tur[i].direction=3;
                }
                break;
            case 'f':
                counter ++;
                if(counter>3)counter = 3;
                break;
            
            default:
                break;
        }
        if(BONUS){
            printf("\x1b[?25l");
            fflush(stdout);
            usleep(1000 * 100);
            system("clear");
            printf("\x1b[2J\x1b[1;1H");
            printWithTurtles(field, rows, cols, tur, counter);    
        }
        
    }
    
    
    printField(field, rows, cols);
    
    free(field);
    return 0;
}
