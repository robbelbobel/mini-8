#include "chip.h"

#include "instructions.h"

chip_t* create_chip(const char* program, const size_t length){
    // Create CHIP
    chip_t* chip = (chip_t*) malloc(sizeof(chip_t));

    // Create Display Buffer
    chip -> display = (uint8_t*) malloc(sizeof(uint8_t) * DISPLAY_BUFFER_SIZE);

    // Copy Program Into Memory
    for(size_t i = 0; i < length; i++) chip -> memory[PROGRAM_LOCATION + i] = program[i];

    // Initialize Registers
    chip -> pc = PROGRAM_LOCATION; 
    chip -> sp = 0;
    chip -> dt = 0;
    chip -> st = 0;

    // Initialize Character Sprites
    __uint8_t digitSprites[16][5] = {   {0xF0, 0x90, 0x90, 0x90, 0xF0},     // 0
                                        {0x20, 0x60, 0x20, 0x20, 0x70},     // 1
                                        {0xF0, 0x10, 0xF0, 0x80, 0xF0},     // 2
                                        {0xF0, 0x10, 0xF0, 0x10, 0xF0},     // 3
                                        {0x90, 0x90, 0xF0, 0x10, 0x10},     // 4
                                        {0xF0, 0x80, 0xF0, 0x10, 0xF0},     // 5
                                        {0xF0, 0x10, 0x20, 0x40, 0x40},     // 7
                                        {0xF0, 0x90, 0xF0, 0x90, 0xF0},     // 8
                                        {0xF0, 0x80, 0xF0, 0x90, 0xF0},     // 6
                                        {0xF0, 0x90, 0xF0, 0x10, 0xF0},     // 9
                                        {0xF0, 0x90, 0xF0, 0x90, 0x90},     // A
                                        {0xE0, 0x90, 0xE0, 0x90, 0xE0},     // B
                                        {0xF0, 0x80, 0x80, 0x80, 0xF0},     // C
                                        {0xE0, 0x90, 0x90, 0x90, 0xE0},     // D
                                        {0xF0, 0x80, 0xF0, 0x80, 0xF0},     // E
                                        {0xF0, 0x80, 0xF0, 0x80, 0x80}};    // F

    // Copy digitSprites To Memory
    for(__uint8_t i = 0; i < 16; i++) for(__uint8_t j = 0; j < 5; j++) chip -> memory[CHARACTER_LOCATION + i * 5 + j] = digitSprites[i][j];

    return chip;
}

void tick_chip(chip_t* chip){
    __execute(chip);
}
