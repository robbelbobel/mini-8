#ifndef CHIP_H
#define CHIP_H

#include <stdlib.h>

#include "instructions.h"

#define PROGRAM_LOCATION 0x0200
#define CHARACTER_LOCATION 0x0000

#define DISPLAY_BUFFER_SIZE (64 / 8) * 32 // 1 Bit Per Pixel

struct chip_s{
    __uint8_t memory[4096];
    __uint16_t stack[16];

    __uint16_t pc;
    __uint8_t sp;

    __uint8_t v[16];
    __uint16_t i;

    __uint8_t dt;
    __uint8_t st;

    __uint8_t display[DISPLAY_BUFFER_SIZE];

} typedef chip_t;

chip_t* create_chip(const char* program);

void tick_chip(chip_t* chip);

void __execute(chip_t* chip);

#endif
