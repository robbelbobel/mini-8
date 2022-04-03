#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "core/chip.h"

void render(chip_t* chip, SDL_Renderer* renderer);

#endif