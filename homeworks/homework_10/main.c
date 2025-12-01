#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynamic_array.h"
#include "sdl.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct{
    SDL_Rect rect;
    int speed;
    int angle;
    int dir;
}Tvlocka;

typedef struct{
    SDL_Rect rect;
    int RGBA[4];
}Particles;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    SDL_Context ctx = sdl_context_init("snowflakes", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Texture* image = IMG_LoadTexture(ctx.renderer, "snowflake.svg");
    
    dynarray array;
    dynarray_init(&array, 10);
    dynarray particles;
    dynarray_init(&particles, 10);

    Tvlocka *tmp_vlocka = (Tvlocka*) malloc(sizeof(Tvlocka));
    SDL_Rect rect_tmp = {
        .x = 100,
        .y = 100,
        .w = 400,
        .h = 400
    };
    int size;
    SDL_Event event;
    int counter = 0;


    Uint64 last = SDL_GetPerformanceCounter();
    int running = 1;
    while (running == 1) {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if(event.type == SDL_MOUSEMOTION){
                counter++;
                if(counter%10 == 0){
                    int x = 0;
                    int y = 0;
                    SDL_GetMouseState(&x, &y);
                    rect_tmp.x = x;
                    rect_tmp.y = y;
                    size = (rand()%160)+10;
                    rect_tmp.w = size;
                    rect_tmp.h = size;
                    tmp_vlocka->rect = rect_tmp;
                    tmp_vlocka->speed = rand()%200+200;
                    tmp_vlocka->angle = rand()%360;
                    tmp_vlocka->dir = rand()%3-1;
                    Tvlocka *vlocka = (Tvlocka*) malloc(sizeof(Tvlocka));
                    *vlocka = *tmp_vlocka;
                    dynarray_push(&array, vlocka);
                }
                
                
            }
        }
        SDL_RenderClear(ctx.renderer);
        for (int i = array.size-1; i >=0; i--){//iteruje pozpatku kvuli moznosti smazani prvku
            Tvlocka *vlocka = (Tvlocka*) array.items[i];
            Particles *tmp;
            SDL_Rect *rect = &(vlocka->rect);
            SDL_RenderCopyEx(ctx.renderer, image, NULL, rect, vlocka->angle*vlocka->dir, NULL, SDL_FLIP_NONE);
            int speed = vlocka->speed;
            rect->y += speed*deltaTime;
            vlocka->angle += speed*deltaTime;
            tmp = (Particles*) malloc(sizeof(Particles));
            tmp->rect.x = rect->x+rand()%rect->w;
            tmp->rect.y = rect->y;
            tmp->rect.w = 3;
            tmp->rect.h = 3;
            tmp->RGBA[0] = rand()%255;
            tmp->RGBA[1] = rand()%255;
            tmp->RGBA[2] = rand()%255;
            tmp->RGBA[3] = 255;
            dynarray_push(&particles, tmp);
            
            if(rect->y > WINDOW_HEIGHT){
                dynarray_remove(&array, rect);
            }
        }
        for(int i = 0; i < particles.size; i++){
            Particles *particle = (Particles*) particles.items[i];
            SDL_SetRenderDrawColor(ctx.renderer, particle->RGBA[0], particle->RGBA[1], particle->RGBA[2], particle->RGBA[3]);
            SDL_SetRenderDrawBlendMode(ctx.renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(ctx.renderer, &(particle->rect));
            particle->RGBA[3] -= 1;
            if(particle->RGBA[3] <= 5){
                dynarray_remove(&particles, particle);
            }
        }

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
        SDL_Delay(16);

        SDL_RenderPresent(ctx.renderer);
        last = now;
    }
    
    free(tmp_vlocka);
    dynarray_free(&particles);
    dynarray_free(&array);    
    SDL_DestroyTexture(image);
    sdl_context_free(&ctx);
    return 0;
}
