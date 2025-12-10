#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define P_WIDTH 40
#define P_HEIGHT 40


#define MAP_ROWS 20
#define MAP_COLS 20

typedef enum{
    RIGHT,
    DOWN,
    LEFT,
    UP
}Direction;

typedef struct{
    SDL_Texture *texture;
    SDL_Rect rect;
    Direction direction;
    Direction nextDirection;
    int speed;
}Entity;

typedef struct{
    int index;
    SDL_Rect rect;
    char *name;
}Menu_item;

SDL_Rect map_border = {
    .x = 10,
    .y = 10,
    .w = MAP_COLS*P_WIDTH,
    .h = MAP_ROWS*P_HEIGHT
};

typedef enum{
    FIELD_WALL,
    FIELD_EMPTY,
    FIELD_GHOST_SPAWN,
    FIELD_PLAYER_SPAWN,
    FIELD_FOOD,
    FIELD_BOOSTER
}Field_type;

typedef struct{
    Field_type fields[MAP_ROWS][MAP_COLS];
}Map;
int speed = 1;


int load_map(const char *filename, Map *map) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open map file!\n");
        return 0;
    }

    char line[MAP_COLS + 5];

    for (int r = 0; r < MAP_ROWS; r++) {
        if (!fgets(line, sizeof(line), f)) {
            printf("Invalid map size!\n");
            fclose(f);
            return 0;
        }

        for (int c = 0; c < MAP_COLS; c++) {
            char ch = line[c];
            switch (ch) {
                case '#': map->fields[r][c] = FIELD_WALL; break;
                case '.': map->fields[r][c] = FIELD_EMPTY; break;
                case 'o': map->fields[r][c] = FIELD_FOOD; break;
                case 'P': map->fields[r][c] = FIELD_PLAYER_SPAWN; break;
                case 'G': map->fields[r][c] = FIELD_GHOST_SPAWN; break;
                case 'B': map->fields[r][c] = FIELD_BOOSTER; break;
                default:
                    map->fields[r][c] = FIELD_EMPTY;
                    break;
            }
        }
    }

    fclose(f);
    return 1;
}
SDL_Rect getPlayerSpawn(Map *map){
    SDL_Rect tmp; 
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            if (map->fields[r][c] == FIELD_PLAYER_SPAWN) {
                tmp = (SDL_Rect){
                    .x = c*P_WIDTH+map_border.x,
                    .y = r*P_HEIGHT+map_border.y,
                    .w = P_WIDTH,
                    .h = P_HEIGHT
                };
                return tmp;
            }
        }
    }
    return tmp;
}

Field_type get_field(Map *map, int x, int y) {
    int col = (x - map_border.x) / P_WIDTH;
    int row = (y - map_border.y) / P_HEIGHT;

    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
        return FIELD_WALL;

    return map->fields[row][col];
}

int can_move(Map *map, SDL_Rect *rect, Direction dir) {
    int px = rect->x;
    int py = rect->y;

    switch(dir) {
        case UP:    py -= speed; break;
        case DOWN:  py += speed; break;
        case LEFT:  px -= speed; break;
        case RIGHT: px += speed; break;
    }

    // střed pacmana + offset aby nekolidoval hranou textury
    int check_x = px + rect->w / 2;
    int check_y = py + rect->h / 2;

    return get_field(map, check_x, check_y) != FIELD_WALL;
}


void printMap(SDL_Renderer *renderer, Map *map, SDL_Texture *beer, SDL_Texture *booster) {
   
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {

            SDL_Rect fieldRect = {
                .x = c * P_WIDTH+map_border.x,
                .y = r * P_HEIGHT+map_border.y,
                .w = P_WIDTH,
                .h = P_HEIGHT
            };

            switch (map->fields[r][c]) {
                case FIELD_WALL:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &fieldRect);
                    break;

                case FIELD_FOOD:
                    SDL_RenderCopy(renderer, beer, NULL, &fieldRect);
                    break;

                case FIELD_BOOSTER:
                    SDL_RenderCopy(renderer, booster, NULL, &fieldRect);
                    break;

                default:
                    break;
            }
        }
    }    

    SDL_RenderDrawRect(renderer, &map_border);

}


int game(SDL_Renderer *renderer, Map *map){
    SDL_Event event;
    int running = 1;
    SDL_Texture *beer = IMG_LoadTexture(renderer, "./beer.png");
    SDL_Texture *booster = IMG_LoadTexture(renderer, "./madmong.png");

    Entity pacman;
    pacman.texture = IMG_LoadTexture(renderer, "./pacman.png");
    pacman.rect = getPlayerSpawn(map);
    pacman.direction = 0;
    pacman.nextDirection = 0;
    pacman.speed = 1;

    Uint8* key_state;
    while (running == 1){

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
                return 0;
            }
        }
        
        key_state = SDL_GetKeyboardState(NULL);
        if (key_state[SDL_SCANCODE_RIGHT]) {
            pacman.direction = RIGHT;

        }
        if (key_state[SDL_SCANCODE_LEFT]) {
            pacman.direction = LEFT;
        }
        if (key_state[SDL_SCANCODE_UP]) {
            pacman.direction = UP;

        }
        if (key_state[SDL_SCANCODE_DOWN]) {
            pacman.direction = DOWN;
        }
        

        switch (pacman.direction){
            case UP:
                if(pacman.rect.y > map_border.y){
                    pacman.rect.y -= speed*pacman.speed;
                }
                break;
            case DOWN:
                if((pacman.rect.y + pacman.rect.h) < map_border.y + map_border.h){
                    pacman.rect.y += speed*pacman.speed;
                }   
                break;
            case LEFT:
                if(pacman.rect.x > map_border.x){
                    pacman.rect.x -= speed*pacman.speed;
                }    
                break;
            case RIGHT:
                if((pacman.rect.x + pacman.rect.w) < map_border.x + map_border.w){
                    pacman.rect.x += speed*pacman.speed;
                }
                break;
            default:
                break;
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        printMap(renderer,map, beer, booster);

        
        SDL_RenderCopyEx(renderer, pacman.texture, NULL, &(pacman.rect), pacman.direction==2 ? 0:pacman.direction*90, NULL, pacman.direction==2 ? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
        
        SDL_RenderPresent(renderer);
    }
}

void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text){
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &location);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void menu(SDL_Renderer *renderer){
    int fontsize = 20;
    TTF_Font* font = TTF_OpenFont("Arial.ttf", fontsize);
    if (!font) {
        printf("Font error: %s\n", TTF_GetError());
    }
    Entity beerman;
    beerman.texture = IMG_LoadTexture(renderer, "./beerman.png");
    beerman.rect.x = (WINDOW_WIDTH/8)*4;
    beerman.rect.y = (WINDOW_HEIGHT/8)*2;
    beerman.rect.w = 300;
    beerman.rect.h = 200;
    beerman.direction = 0;
    beerman.nextDirection = 0;
    beerman.speed = 1;

    Menu_item items[3];
    int n = 3;
    int choosed=0;
    items[0].name = "Play";
    items[1].name = "Hall of Fame";
    items[2].name = "Exit";

    for (int i = 0; i < n; i++){
        items[i].index = i;
        SDL_Rect tmp;
        tmp.x = WINDOW_WIDTH/8;
        tmp.y = i*fontsize*1.5+50;
        tmp.w = fontsize*strlen(items[i].name)*0.7;
        tmp.h = fontsize;
        items[i].rect = tmp;
    }
    


    int running = 1;
    SDL_Event event;
    Uint8* key_state;
    while(running ==1){
        
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        key_state = SDL_GetKeyboardState(NULL);
        
        if (key_state[SDL_SCANCODE_UP]) {
            if(choosed>0)choosed--;
            if(choosed<0)choosed=n-1;
            SDL_Delay(100);
        }
        if (key_state[SDL_SCANCODE_DOWN]) {
            if(choosed<n-1)choosed++;
            if(choosed==n)choosed=0;
            SDL_Delay(100);
        }
        if(key_state[SDL_SCANCODE_RETURN]){
            switch (choosed)
            {
            case 0:
                Map map;
                load_map("map.txt", &map);
                if(game(renderer,&map)==0)running = 0;
                break;
            case 1:
                break;
            case 2:
                running = 0;
                break;
            default:
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 23, 3, 26, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < n; i++){
            SDL_Color tmp;
            if(choosed==i){
                tmp.r = 255;
                tmp.g = 0;
                tmp.b = 0;
                tmp.a = 255;
            }else{
                tmp.r = 255;
                tmp.g = 255;
                tmp.b = 255;
                tmp.a = 255;
            }
            SDL_RenderCopyEx(renderer, beerman.texture, NULL, &(beerman.rect), 0, NULL, SDL_FLIP_NONE);
            sdl_draw_text(renderer, font, tmp, items[i].rect, items[i].name);

        }

        SDL_RenderPresent(renderer);
        
    }
    TTF_CloseFont(font);
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
    TTF_Init();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


    menu(renderer);





    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
