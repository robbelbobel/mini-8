#include <stdio.h>

#include "loader.h"
#include "core/chip.h"

#define EMULATION_SPEED 500

int main(int argc, char** argv){
    size_t length;
    char* program = loadFile(argv[1], &length);

    if(program == NULL){
        printf("Failed to load file!");
        return -1;
    }

    chip_t* chip = create_chip(program, length);
    free(program);

    uint32_t cycles = 0;

    while(cycles++ < 10000){
        tick_chip(chip);
    }

    return 0;
}