#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

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

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;
typedef struct{
    int height;
    int width;
    TGAHeader header;
    Pixel *pixels;
}TGA_Image;
typedef struct{
    int x;//width/col
    int y;//height/row
}Pos;


Pixel* load_pixels(TGAHeader header, FILE* file) {
    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    assert(fread(pixels, sizeof(Pixel) * width * height, 1, file) == 1);
    return pixels;
}



TGAHeader load_header(FILE* file) {
    TGAHeader header = {};
    assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);
    return header;
}
TGA_Image loadImage(FILE* file){
    TGA_Image tmp = {};
    tmp.height = 0;
    tmp.width = 0;
    tmp.header = load_header(file);
    tmp.pixels = load_pixels(tmp.header, file);
    
    memcpy(&tmp.width, tmp.header.width, 2);
    memcpy(&tmp.height, tmp.header.height, 2);
    
    return tmp;
}

void drawRect(TGA_Image *img, Pos begin, Pos end){
    for (int i = 0; i < img->width; i++){
        for (int j = 0; j < img->height; j++){
            if(begin.x<=j&&end.x>=j){
                if(begin.y<=i&&end.y>=i){
                    Pixel* pixel = img->pixels+(i*img->width+j);
                    pixel->blue=204;
                    pixel->green=56;
                    pixel->red=17;
                }   
            }
        }
    }
}

void saveTGA(TGA_Image *img, FILE *out){
    assert(fwrite(&((*img).header),sizeof(TGAHeader),1, out)==1);
    assert(fwrite((*img).pixels,sizeof(Pixel)*img->width*img->height,1, out)==1);

}





int main(int argc, char *argv[]) {
        
    FILE* file = fopen("carmack.tga", "rb");
    FILE* out = fopen("output.tga", "wb");
    assert(file);
    Pos begin, end;
    

    if(argc == 5){
        begin.x = atoi(argv[1]);
        begin.y = atoi(argv[2]);
        end.x = atoi(argv[3]);
        end.y = atoi(argv[4]);
    }else{
        begin.x = 100;
        begin.y = 100;
        end.x = 180;
        end.y = 180;
    }

    TGA_Image img1 = {};
    img1 = loadImage(file);
    
    

    printf("Image type: %d, pixel depth: %d, rozmery %dx%d\n", img1.header.image_type, img1.header.depth, img1.height, img1.width);
    
    drawRect(&img1,begin, end);
    saveTGA(&img1, out);
    fclose(file);
    fclose(out);
    return 0;
}
