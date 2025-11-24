#include <stdio.h>

int main() {
    
    int obrazec = 0;
    int a = 0;
    int b = 0;
    int counter = 0;
    char ch = ' ';
    scanf("%d%d%d", &obrazec, &a, &b);

    switch (obrazec){
    case 0:
    case 1:
    case 2:
        counter = 0;
        for (int i = 0; i < b; i++) {
            for (int j = 0; j < a; j++) {
                if (obrazec==0) {
                    ch='x';
                }else if(obrazec==1){
                    ch = 'x';
                    if((i>0&&i<(b-1))&&(j>0&&j<(a-1)))ch = ' ';
                }else{
                    ch = 'x';
                    if((i>0&&i<(b-1))&&(j>0&&j<(a-1))){
                        ch = (char)(counter + '0');
                        counter++;
                        counter = counter%10;
                    }
                }
                
                printf("%c", ch);
            }
            printf("\n");
            
        }
        break;
    case 3:
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < a; j++) {
                ch = ' ';
                if(j==i)ch = 'x';
                printf("%c", ch);
                if(ch=='x')break;;
            }
            printf("\n");
        }
        break;
    case 4:
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < a; j++) {
                ch = ' ';
                if(((a-1)-j)==i)ch = 'x';
                printf("%c", ch);
            }
            printf("\n");
        }
        break;
    case 5:
        a--;
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= 2*a; j++) {
                ch = ' ';
                if((j==(a-i))||(j==(a+i)))ch = 'x';
                if(i==a)ch = 'x';
                printf("%c", ch);
            }
            printf("\n");
        }
        break;
    case 6:
        for (int j = 0; j < a; j++) {
            ch = 'x';
            printf("%c", ch);
        }
        printf("\n");
        for (int j = 0; j < (b-1); j++) {
            for (int i = 0; i < a; i++) {
                ch = ' ';
                if(((a-1)/2)==i)ch = 'x';
                printf("%c", ch);
                if(((a-1)/2)==i)break;
            }
            printf("\n");
        }
        
        break;
    
    case 7:
        for (int j = 0; j < b; j++) {
            for (int i = 0; i < a; i++) {
                ch = ' ';
                if(j==0||j==((b-1)/2))ch='x';
                if((j<(b/2))&&((i==0)||(i==(a-1))))ch='x';
                if(i==0)ch='x';
                printf("%c", ch);
            }
            printf("\n");
        }
        
        break;
    case 9:
        counter = 1;
        int c = b-2;
        for (int i = 0; i < b; i++) {
            for (int j = 0; j < a; j++) {
                ch = 'x';
                if((i>0&&i<(b-1))&&(j>0&&j<(a-1))){
                    ch = (char)(i+(j-1)*c -1);
                    ch = ch%10;
                    ch+='0';        
                }
                
                printf("%c", ch);
            }
            
            printf("\n");
            
        }
        
        break;
    default:
        printf("Neznamy obrazec\n");
        break;
    }
    
    return 0;
}