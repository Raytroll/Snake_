#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT)
#include "snake.c"
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    POS* MAP = init_MAP();
    int* SNAKE_LENGTH = 3;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        printf("error initializing SDL: %s\n", SDL_GetError());
    SDL_Window* win = SDL_CreateWindow("GAME", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    int* running = 1;
    vec2 SNAKE_POS = {.x = SCREEN_WIDTH/2, .y = SCREEN_HEIGHT / 2};
    vec2 SNAKE_VEL = {.x = 10, .y = 0};
    update_tile(MAP, SNAKE_POS);
    vec2 ORB_POS = spawn_orb(MAP);
    while (running == 1) {
        SDL_RenderClear(rend);
        handle_events(&running, &SNAKE_VEL);
        draw_tiles(MAP, rend);
        int _=move_snake(MAP, (vec2){SNAKE_VEL.x,SNAKE_VEL.y},&SNAKE_POS,&SNAKE_LENGTH);
        if (_ != 1) return 0;
        SDL_Rect rect = {ORB_POS.x, ORB_POS.y, 10, 10};
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderDrawRect(rend, &rect);
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 10);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void handle_events(int* running, vec2* SNAKE_VEL) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        SNAKE_VEL->y = -10;
                        SNAKE_VEL->x = 0;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        SNAKE_VEL->x = -10;
                        SNAKE_VEL->y = 0;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        SNAKE_VEL->y = 10;
                        SNAKE_VEL->x = 0;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        SNAKE_VEL->x = 10;
                        SNAKE_VEL->y = 0;
                        break;
                }
        }
    }
}
