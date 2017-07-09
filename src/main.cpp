#include <iostream>
#include <SDL.h>

#include "GameOfLifeMap.h"

const int WINDOW_WIDTH = 512; 
const int WINDOW_HEIGHT = 512;
const int PIXEL_SIZE = 8;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


int main(int argc, char**argv) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Video init failed" << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "GameOfLive V1.0",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_INPUT_FOCUS
    );

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_ClearError();
        SDL_Quit();
        return 1;
    }

    GameOfLifeMap map(WINDOW_WIDTH/PIXEL_SIZE, WINDOW_HEIGHT/PIXEL_SIZE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_Rect rect;
        
        for (int y = 0; y < map.height(); y++) {
            for (int x = 0; x < map.width(); x++)  {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                if (map.getFieldState(x, y) == FIELD_STATE_ALIVE) {
                    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 255);
                }

                rect.x = x * PIXEL_SIZE;
                rect.y = y * PIXEL_SIZE;
                rect.h = PIXEL_SIZE;
                rect.w = PIXEL_SIZE;

                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        map.nextSimulationStep();
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}