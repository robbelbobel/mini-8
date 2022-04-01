#ifndef CHIP_H
#define CHIP_H

#include <stdlib.h>

#include "instructions.h"

#define PROGRAM_LOCATION 0x0200
#define CHARACTER_LOCATION 0x0000

#define DISPLAY_WIDTH   64
#define DISPLAY_HEIGHT  32
#define DISPLAY_BUFFER_SIZE (DISPLAY_WIDTH / 8) * DISPLAY_HEIGHT // 1 Bit Per Pixel

struct chip_s{
    __uint8_t memory[4096];
    __uint16_t stack[16];

    __uint16_t pc;
    __uint8_t sp;

    __uint8_t v[16];
    __uint16_t i;

    __uint8_t dt;
    __uint8_t st;

    __uint8_t* display;

} typedef chip_t;

chip_t* create_chip(const char* program, const size_t length);

void tick_chip(chip_t* chip);

void __execute(chip_t* chip);

#endif
