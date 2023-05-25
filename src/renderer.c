#include "renderer.h"

void render(chip_t* chip, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    SDL_Rect px;
    px.w = 4;
    px.h = 4;

    for(uint8_t y = 0; y < DISPLAY_HEIGHT; y++){
        px.y = y * px.h;
        for(uint8_t x = 0; x < DISPLAY_WIDTH; x++){
            px.x = x * px.w;

            // if((chip -> display[y * (DISPLAY_WIDTH / 8) + (x / 8)] >> (7 - (x % 8))) & 0b1) 
            //     SDL_RenderFillRect(renderer, &px);
        }
    }

    SDL_RenderPresent(renderer);
}