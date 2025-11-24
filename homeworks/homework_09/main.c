#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define BETWEEN_LETTERS 1.1
#define ON_SPACE 0.9
#define SPACE_ON_START 10
#define UNDERLINE 1

typedef unsigned char byte;

#pragma pack(push, 1)
typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;
#pragma pack(pop)

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

typedef struct{
    char letter;
    TGAHeader header;
    Pixel* pixels;
    int width;
    int height;
}TGA_Letter;

typedef struct{
    byte red;
    byte green;
    byte blue;
}Color;

typedef enum{
    RED,
    GREEN,
    BLUE,
    PINK,
    YELLOW,
    ORANGE,
    PURPLE,
    WHITE,
    GRAY,
    BROWN,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_PINK,
    LIGHT_YELLOW,
    LIGHT_ORANGE,
    LIGHT_PURPLE,
    LIGHT_WHITE,
    LIGHT_GRAY,
    LIGHT_BROWN
}Colorname;

Color colors[] = {
    [RED] = {255, 0, 0},
    [GREEN] = {0, 255, 0},
    [BLUE] = {0, 0, 255},
    [PINK] = {255, 192, 203},
    [YELLOW] = {255, 255, 0},
    [ORANGE] = {255, 165, 0},
    [PURPLE] = {128, 0, 128},
    [WHITE] = {255, 255, 255},
    [GRAY] = {128, 128, 128},
    [BROWN] = {165, 42, 42},
    
    [LIGHT_BLUE] = {173, 216, 230},
    [LIGHT_GREEN] = {144, 238, 144},
    [LIGHT_PINK] = {255, 182, 193},
    [LIGHT_YELLOW] = {255, 255, 224},
    [LIGHT_ORANGE] = {255, 204, 153},
    [LIGHT_PURPLE] = {221, 160, 221},
    [LIGHT_WHITE] = {245, 245, 245},
    [LIGHT_GRAY] = {211, 211, 211},
    [LIGHT_BROWN] = {210, 180, 140}
};


TGA_Letter* letters;
int width;
int height;
Pixel* pixels;



Pixel* load_pixels(TGAHeader header, FILE* file) {
    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    Pixel* pixels = (Pixel*) malloc((int)sizeof(Pixel) * width * height);
    assert(pixels);

    assert(fread(pixels, (int)sizeof(Pixel) * width * height, 1, file) == 1);
    return pixels;
}


void save_tga(FILE* out, TGAHeader* header, Pixel* pixels) {
    assert(out);

    assert(fwrite(header, (int)sizeof(TGAHeader), 1, out) == 1);

    int width = 0;
    int height = 0;
    memcpy(&width, header->width, 2);
    memcpy(&height, header->height, 2);

    assert(fwrite(pixels, (int)sizeof(Pixel) * width * height, 1, out) == 1);

    fclose(out);
}

TGA_Letter* load_letters(char* fonts_folder){
    TGA_Letter* letters = (TGA_Letter*)malloc((int)sizeof(TGA_Letter)*('Z'-'A'+1));
    char filename[100];
    FILE* file;
    for (int i = 'A'; i <= 'Z'; i++){
        snprintf(filename, (int)sizeof(filename), "%s/%c.tga", fonts_folder, i);

        file = fopen(filename, "rb");
        assert(file);

        int tmpx = fread(&letters[i-'A'].header, (int)sizeof(TGAHeader), 1, file);
        assert(tmpx == 1);
        letters[i-'A'].pixels = load_pixels(letters[i-'A'].header, file);
        letters[i-'A'].letter = (char)i;
        letters[i-'A'].width = 0;
        letters[i-'A'].height = 0;
        memcpy(&letters[i-'A'].width, letters[i-'A'].header.width, 2);
        memcpy(&letters[i-'A'].height, letters[i-'A'].header.height, 2);
        fclose(file);
        file = NULL;
    }
    return letters;
}


void draw_line(const char *line, int start_x, int start_y){
    int x = start_x;
    int y = start_y;
    int inside_letter_x = 0;
    int inside_letter_y = 0;
    int r=0;
    for (int j = 0; j < (int)strlen(line); j++){
        Pixel* tmp2;
        if(line[j]==' '){
            x+=(int)((float)letters[0].width*ON_SPACE);
            continue;
        }
        if(line[j]=='\0'||line[j]=='\n')return;

        TGA_Letter letter = letters[toupper(line[j])-'A'];
        r = rand()%(sizeof(colors)/sizeof(Color));
        for (inside_letter_y = 0; inside_letter_y < letter.height; inside_letter_y++){
            for(inside_letter_x = 0; inside_letter_x < letter.width; inside_letter_x++){
                tmp2=&letter.pixels[inside_letter_y*letter.width+inside_letter_x];
                if(tmp2->blue<250 || tmp2->green<250 || tmp2->red<250)continue;
                if(inside_letter_y+y>=height || inside_letter_x+x>=width)continue;
                
                pixels[(inside_letter_y+y)*width+(inside_letter_x+x)].blue=colors[r].blue;
                pixels[(inside_letter_y+y)*width+(inside_letter_x+x)].green=colors[r].green;
                pixels[(inside_letter_y+y)*width+(inside_letter_x+x)].red=colors[r].red;
                
            }
        }
        x+=(int)((float)letter.width*BETWEEN_LETTERS);
    }
    if(UNDERLINE){
        for (int j = 0; j < 3; j++){
            for(int i = start_x; i<x; i++){
                if(i>=width)continue;
                pixels[(start_y+33+j)*width+(i)].blue=colors[r].blue;
                pixels[(start_y+33+j)*width+(i)].green=colors[r].green;
                pixels[(start_y+33+j)*width+(i)].red=colors[r].red;    
            }    
        }        
    }
}

int calculate_center(const char *line){
    int x = 0;
    for (int i = 0; i < ((int)strlen(line)); i++){
        
        if(line[i]==' '){
            x+=(int)(ON_SPACE*letters[0].width);
            continue;
        }
        if(line[i]=='\0'||line[i]=='\n')break;
        x+=(int)(letters[toupper(line[i])-'A'].width*BETWEEN_LETTERS);    
    }
    return (width-x)/2;
    
}


int main(int argc, char *argv[]) {
    if(argc!=4){
        printf("Wrong parameters\n");
        return 1;
    }
    char *input_filename = strdup(argv[1]);
    char *output_filename = strdup(argv[2]);
    char *fonts = strdup(argv[3]);

    srand((unsigned int)time(NULL));

    width = 0;
    height = 0;

    FILE* file = fopen(input_filename, "rb");
    FILE* out = fopen(output_filename, "wb");
    if(file==NULL){
        printf("Could not load image\n");
        free(input_filename);
        free(output_filename);
        free(fonts);
        if(out) fclose(out);
        return 1;
    }

    TGAHeader header = {};
    assert(fread(&header, (int)sizeof(TGAHeader), 1, file) == 1);

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    pixels = load_pixels(header, file);
    fclose(file);
    letters = load_letters(fonts);
    char tmp[100];
    int top=0;
    int bottom=0;
    fgets(tmp, 100, stdin);
    top = atoi(strtok(tmp, " "));
    bottom = atoi(strtok(NULL, " "));

    char** top_s;
    char** bottom_s;
    top_s = (char**)malloc((int)sizeof(char*)*top);
    bottom_s = (char**)malloc((int)sizeof(char*)*bottom);
    for(int i=0; i<top; i++){
        top_s[i] = (char*)malloc((int)sizeof(char)*100);
    }
    for(int i=0; i<bottom; i++){
        bottom_s[i] = (char*)malloc((int)sizeof(char)*100);
    }

    int outside_letter_y = SPACE_ON_START;

    for(int i=0; i<top; i++){
        fgets(top_s[i], 100, stdin);
        top_s[i][(int)strlen(top_s[i])-1] = '\0';
        draw_line(top_s[i], calculate_center(top_s[i]), outside_letter_y);
        outside_letter_y+=40;
    }
    
    outside_letter_y = height-(bottom*40)-SPACE_ON_START;
    

    for(int i=0; i<bottom; i++){
        fgets(bottom_s[i], 100, stdin);
        bottom_s[i][(int)strlen(bottom_s[i])-1] = '\0';
        draw_line(bottom_s[i], calculate_center(bottom_s[i]), outside_letter_y);
        outside_letter_y+=40;        
    }
    

    save_tga(out, &header, pixels);


    free(pixels);
    for (int i = 0; i <= 'Z' - 'A'; i++) {
        free(letters[i].pixels);
    }
    free(letters);
    for(int i=0; i<top; i++){
        free(top_s[i]);
    }
    free(top_s);
    for(int i=0; i<bottom; i++){
        free(bottom_s[i]);
    }
    free(bottom_s);
    free(input_filename);
    free(output_filename);
    free(fonts);

    return 0;
}