#include <stdio.h>

#include "loader.h"
#include "core/chip.h"

#define EMULATION_SPEED 500

int main(int argc, char** argv){
    char* program = loadFile(argv[1]);

    if(program == NULL){
        printf("Failed to load file!");
        return -1;
    }

    chip_t* chip = create_chip(program);
    free(program);

    while(1){
        tick_chip(chip);
    }

    return 0;
}