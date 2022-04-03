#include <stdio.h>

#include "random.h"
#include "renderer.h"
#include "loader.h"
#include "core/chip.h"

#define EMULATION_SPEED 500

uint8_t handleInput(SDL_Window* window, chip_t* chip);

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
    while(handleInput(window, chip)){
        printf("keystates: %x\n", chip -> keyStates);

        tick_chip(chip);
        render(chip, renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

uint8_t handleInput(SDL_Window* window, chip_t* chip){
    SDL_Event ev;

    while(SDL_PollEvent(&ev)){
        switch(ev.type){
            case SDL_QUIT:
                return 0;

            case SDL_KEYDOWN:
                switch(ev.key.keysym.sym){
                    case SDLK_1:
                        chip -> keyStates |= (0x0001 << 0x1);
                        break;

                    case SDLK_2:
                        chip -> keyStates |= (0x0001 << 0x2);
                        break;

                    case SDLK_3:
                        chip -> keyStates |= (0x0001 << 0x3);
                        break;

                    case SDLK_4:
                        chip -> keyStates |= (0x0001 << 0xC);
                        break;

                    case SDLK_a:
                        chip -> keyStates |= (0x0001 << 0x4);
                        break;

                    case SDLK_z:
                        chip -> keyStates |= (0x0001 << 0x5);
                        break;

                    case SDLK_e:
                        chip -> keyStates |= (0x0001 << 0x6);
                        break;

                    case SDLK_r:
                        chip -> keyStates |= (0x0001 << 0xd);
                        break;

                    case SDLK_q:
                        chip -> keyStates |= (0x0001 << 0x7);
                        break;

                    case SDLK_s:
                        chip -> keyStates |= (0x0001 << 0x8);
                        break;

                    case SDLK_d:
                        chip -> keyStates |= (0x0001 << 0x9);
                        break;

                    case SDLK_f:
                        chip -> keyStates |= (0x0001 << 0xE);
                        break;

                    case SDLK_w:
                        chip -> keyStates |= (0x0001 << 0xA);
                        break;

                    case SDLK_x:
                        chip -> keyStates |= (0x0001 << 0x0);
                        break;

                    case SDLK_c:
                        chip -> keyStates |= (0x0001 << 0xB);
                        break;

                    case SDLK_v:
                        chip -> keyStates |= (0x0001 << 0xF);
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(ev.key.keysym.sym){
                    case SDLK_1:
                        chip -> keyStates &= ~(0x0001 << 0x1);
                        break;

                    case SDLK_2:
                        chip -> keyStates &= ~(0x0001 << 0x2);
                        break;

                    case SDLK_3:
                        chip -> keyStates &= ~(0x0001 << 0x3);
                        break;

                    case SDLK_4:
                        chip -> keyStates &= ~(0x0001 << 0xC);
                        break;

                    case SDLK_a:
                        chip -> keyStates &= ~(0x0001 << 0x4);
                        break;

                    case SDLK_z:
                        chip -> keyStates &= ~(0x0001 << 0x5);
                        break;

                    case SDLK_e:
                        chip -> keyStates &= ~(0x0001 << 0x6);
                        break;

                    case SDLK_r:
                        chip -> keyStates &= ~(0x0001 << 0xd);
                        break;

                    case SDLK_q:
                        chip -> keyStates &= ~(0x0001 << 0x7);
                        break;

                    case SDLK_s:
                        chip -> keyStates &= ~(0x0001 << 0x8);
                        break;

                    case SDLK_d:
                        chip -> keyStates &= ~(0x0001 << 0x9);
                        break;

                    case SDLK_f:
                        chip -> keyStates &= ~(0x0001 << 0xE);
                        break;

                    case SDLK_w:
                        chip -> keyStates &= ~(0x0001 << 0xA);
                        break;

                    case SDLK_x:
                        chip -> keyStates &= ~(0x0001 << 0x0);
                        break;

                    case SDLK_c:
                        chip -> keyStates &= ~(0x0001 << 0xB);
                        break;

                    case SDLK_v:
                        chip -> keyStates &= ~(0x0001 << 0xF);
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

    return 1;
}