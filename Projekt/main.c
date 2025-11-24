#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define P_WIDTH 20
#define P_HEIGHT 20


#define MAP_ROWS 21
#define MAP_COLS 19

int map[MAP_ROWS][MAP_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
    {1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1},
    {1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};




void printMap(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // modré zdi

    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            if (map[row][col] == 1) {
                SDL_Rect cell = { col * P_WIDTH, row * P_HEIGHT, P_WIDTH, P_HEIGHT };
                SDL_RenderDrawRect(renderer, &cell); // kreslí jen obvod
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("PACMAN - ultra game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int line_x = 150;

    SDL_Event event;
    int running = 1;

    SDL_Texture* pac = IMG_LoadTexture(renderer, "./../pacman.png");
    if (!pac) {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", IMG_GetError());
        // Možná cesta není správná
    }

    SDL_Rect pac_pos = {
        .x = 0,
        .y = 0,
        .w = P_WIDTH,
        .h = P_HEIGHT
    };

    Uint8* key_state;
    



    while (running == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        key_state = SDL_GetKeyboardState(NULL);
        if (key_state[SDL_SCANCODE_RIGHT]) {
            pac_pos.x ++;

        }
        if (key_state[SDL_SCANCODE_LEFT]) {
            pac_pos.x --;

        }
        if (key_state[SDL_SCANCODE_UP]) {
            pac_pos.y --;

        }
        if (key_state[SDL_SCANCODE_DOWN]) {
            pac_pos.y ++;

        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nastavení barvy na černou
        SDL_RenderClear(renderer);
        printMap(renderer);
        SDL_RenderCopy(renderer, pac, NULL, &pac_pos);
        SDL_RenderPresent(renderer);  // Prezentace kreslítka
        

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
