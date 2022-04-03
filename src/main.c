#include <stdio.h>

#include "random.h"
#include "renderer.h"
#include "loader.h"
#include "core/chip.h"

#define EMULATION_SPEED 500

uint8_t handleInput(SDL_Window* window);

int main(int argc, char** argv){
    /** INITIALIZE RANDOM **/
    srand(time(NULL));

    /** INITIALIZE CHIP **/
    size_t length;
    char* program = loadFile(argv[1], &length);

    if(program == NULL){
        printf("Failed to load file!");
        return -1;
    }

    chip_t* chip = create_chip(program, length, malloc, getRandom_8);
    free(program);

    /** INITIALIZE SDL **/
    // Window
    SDL_Window* window = SDL_CreateWindow("MINI-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 4 * DISPLAY_WIDTH, 4 * DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL){ 
        printf("Failed to create SDL window!");
        SDL_Quit();
        return -2;
    }
    
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(renderer == NULL){
        printf("Failed to create renderer!");
        SDL_Quit();
        return -3;
    }

    /** MAIN LOOP **/
    while(handleInput(window)){
        tick_chip(chip);
        render(chip, renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

uint8_t handleInput(SDL_Window* window){
    SDL_Event ev;

    while(SDL_PollEvent(&ev)){
        switch(ev.type){
            case SDL_QUIT:
                return 0;

            default:
                break;
        }
    }

    return 1;
}