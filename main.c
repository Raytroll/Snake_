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
    srand(time(NULL));   // Initialization, should only be called once.
    POS* SNAKE_PATH = init_snake_path();
    int* SNAKE_LENGTH = 3;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        printf("error initializing SDL: %s\n", SDL_GetError());
    SDL_Window* win = SDL_CreateWindow("GAME", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    
    int running = 1;
    vec2 SNAKE_POS = {.x = SCREEN_WIDTH/2, .y = SCREEN_HEIGHT / 2};
    vec2 SNAKE_VEL = {.x = 10, .y = 0};
    update_tile(SNAKE_PATH, SNAKE_POS);
    vec2 ORB_POS = spawn_orb(SNAKE_PATH);
    printf("%d %d\n", ORB_POS.x, ORB_POS.y);
    int _;

    while (running == 1) {
        SDL_RenderClear(rend);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    SNAKE_VEL.y = -10;
                    SNAKE_VEL.x = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    SNAKE_VEL.x = -10;
                    SNAKE_VEL.y = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    SNAKE_VEL.y = 10;
                    SNAKE_VEL.x = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    SNAKE_VEL.x = 10;
                    SNAKE_VEL.y = 0;
                    break;
                default:
                    break;
                }
            }
        }


        draw_tiles(SNAKE_PATH, rend);
        
        
        
        _ = move_snake(SNAKE_PATH, (vec2) {SNAKE_VEL.x, SNAKE_VEL.y}, &SNAKE_POS, &SNAKE_LENGTH);
        if (_ != 1)
            return 0;
        

        
        SDL_Rect rect;
        rect.x = ORB_POS.x;
        rect.y = ORB_POS.y;
        rect.w = 10;
        rect.h = 10;
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderDrawRect(rend, &rect);
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        SDL_RenderPresent(rend);
        // calculates to 60 fps
        SDL_Delay(1000 / 10);
    }
 

 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}