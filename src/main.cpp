#include <iostream>
#include <SDL.h>

#include "GameOfLifeMap.h"

const int WINDOW_WIDTH = 512; 
const int WINDOW_HEIGHT = 512;
const int PIXEL_SIZE = 16;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Point mouse_pos;
bool mouseDown = false;
bool running = true;

void inputHandling() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym  != SDLK_ESCAPE) break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                mouse_pos.x = event.motion.x;
                mouse_pos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown = event.button.button == SDL_BUTTON_LEFT;
            break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                }
            break;
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    case SDL_WINDOWEVENT_LEAVE:
                        mouse_pos.x = mouse_pos.y = -1;
                        break;
                }
                break;
        }
    }
}

void renderMap(GameOfLifeMap &map) {
    SDL_Rect rect;
    rect.h = PIXEL_SIZE;
    rect.w = PIXEL_SIZE;

    for (auto y = 0; y < map.height(); y++) {
        for (auto x = 0; x < map.width(); x++)  {
            rect.x = x * PIXEL_SIZE;
            rect.y = y * PIXEL_SIZE;

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if (map.getFieldState(x, y) == FIELD_STATE_ALIVE) {
                SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 255);
            }
            SDL_RenderFillRect(renderer, &rect);

            if (SDL_PointInRect(&mouse_pos, &rect)) {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 128);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void mainLoop() {
    mouse_pos.x = mouse_pos.y = -1;
    GameOfLifeMap map(WINDOW_WIDTH/PIXEL_SIZE, WINDOW_HEIGHT/PIXEL_SIZE);
    while(running) {
       
        inputHandling();

        if (mouseDown && mouse_pos.x != -1 && mouse_pos.y != -1) {
            map.setFieldState(mouse_pos.x / PIXEL_SIZE, mouse_pos.y / PIXEL_SIZE, FIELD_STATE_ALIVE);
        }

        renderMap(map);
        
        if (!mouseDown) {

            if(! map.nextSimulationStep()) {
                map.generate();
            }
            SDL_Delay(50);
        } 
    }
}

int main(int argc, char**argv) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Video init failed" << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "GameOfLive V1.0",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_ClearError();
        SDL_Quit();
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_ClearError();
        SDL_Quit();
        return 1;
    }

    mainLoop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}