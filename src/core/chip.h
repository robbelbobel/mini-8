#ifndef CHIP_H
#define CHIP_H

#include <stdint.h>
#include <stdio.h> // DEBUG

#include "instructions.h"

#define PROGRAM_LOCATION 0x0200
#define CHARACTER_LOCATION 0x0000

#define DISPLAY_WIDTH   64
#define DISPLAY_HEIGHT  32
#define DISPLAY_BUFFER_SIZE (DISPLAY_WIDTH / 8) * DISPLAY_HEIGHT // 1 Bit Per Pixel

struct chip_s{
    uint8_t memory[4096];
    uint16_t stack[16];

    uint8_t* display;
    uint16_t keyStates;

    uint16_t pc;
    uint8_t sp;

    uint8_t v[16];
    uint16_t i;

    uint8_t dt;
    uint8_t st;

    uint8_t (*rnd_fun_ptr)();

} typedef chip_t;

chip_t* create_chip(const char* program, const uint16_t length, void* (*malloc_fun_ptr)(unsigned long), uint8_t (*rnd_fun_ptr)());

void decrement_timers(chip_t* chip);
void tick_chip(chip_t* chip);

#endif
