#include "instructions.h"

void __execute(chip_t* chip){
    // Fetch Instruction
    const uint16_t instr = ((uint16_t) chip -> memory[chip -> pc] << 8) + chip -> memory[chip -> pc + 1];

    // Update Program Counter
    chip -> pc += 2;

    // printf("instruction: %x\n", instr);

    // Execute Instruction
    switch((instr & 0xF000) >> 12){
        case 0x0:
            if(instr == 0xE0) __cls(chip);
            else if(instr == 0xEE) __ret(chip);
            break; 

        case 0x1:
            __jp(chip, instr);
            break;

        case 0x2:
            __call(chip, instr);
            break;
        
        case 0x3:
            __se_v_byte(chip, instr);
            break;

        case 0x4:
            __sne_v_byte(chip, instr);
            break;

        case 0x5:
            __se_v_v(chip, instr);
            break;
        
        case 0x6:
            __ld_v_byte(chip, instr);
            break;
        
        case 0x7:
            __add_v_byte(chip, instr);
            break;
        
        case 0x8:
            switch(instr & 0xF){
                case 0x0:
                    __ld_v_v(chip, instr);
                    break;
                
                case 0x1:
                    __or(chip, instr);
                    break;

                case 0x2:
                    __and(chip, instr);
                    break;
                
                case 0x3:
                    __xor(chip, instr);
                    break;

                case 0x4:
                    __add_v_v(chip, instr);
                    break;
                
                case 0x5:
                    __sub(chip, instr);
                    break;
                
                case 0x6:
                    __shr(chip, instr);
                    break;

                case 0x7:
                    __subn(chip, instr);
                    break;

                case 0xE:
                    __shl(chip, instr);
                    break;
            }
            break;
        
        case 0x9:
            __sne_v_v(chip, instr);
            break;
        
        case 0xA:
            __ld_i_addr(chip, instr);
            break;
        
        case 0xB:
            __jp_v(chip, instr);
            break;
        
        case 0xC:
            __rnd(chip, instr);
            break;
        
        case 0xD:
            __drw(chip, instr);
            break;
        
        case 0xE:
            if((instr & 0x00FF) == 0x9E) __skp(chip, instr);
            else if((instr & 0x00FF) == 0xA1) __sknp(chip, instr);
            break;
        
        case 0xF:
            switch(instr & 0x00FF){
                case 0x07:
                    __ld_v_dt(chip, instr);
                    break;
                
                case 0x0A:
                    __ld_v_k(chip, instr);
                    break;
            
                case 0x15:
                    __ld_dt_v(chip, instr);
                    break;
                
                case 0x18:
                    __ld_st_v(chip, instr);
                    break;

                case 0x1E:
                    __add_i_v(chip, instr);
                    break;

                case 0x29:
                    __ld_f_v(chip, instr);
                    break;

                case 0x33:
                    __ld_b_v(chip, instr);
                    break;
                
                case 0x55:
                    __ld_i_v(chip, instr);
                    break;
                
                case 0x65:
                    __ld_v_i(chip, instr);
                    break;
                
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

/** CLS RET **/
void __cls(chip_t* chip){
    for(uint16_t i = 0; i < DISPLAY_HEIGHT; i++) for(uint16_t j = 0; j < DISPLAY_WIDTH; j++) chip -> display[i][j] = 0x00;
}

void __ret(chip_t* chip){
    chip -> pc = chip -> stack[chip -> sp--];
}

/** JP CALL **/
void __jp(chip_t* chip, const uint16_t instr){
    chip -> pc = instr & 0x0FFF; 
}

void __jp_v(chip_t* chip, const uint16_t instr){
    chip -> pc = (instr & 0x0FFF) + chip -> v[0];
}

void __call(chip_t* chip, const uint16_t instr){
    chip -> stack[++chip -> sp] = chip -> pc;
    __jp(chip, instr);
}

/** SE **/
void __se_v_byte(chip_t* chip, const uint16_t instr){
    if(chip -> v[(instr & 0x0F00) >> 8] == (instr & 0xFF)) chip -> pc += 2;
}

void __se_v_v(chip_t* chip, const uint16_t instr){
    if(chip -> v[(instr & 0x0F00) >> 8] == chip -> v[(instr & 0x00F0) >> 4]) chip -> pc += 2;
}

void __sne_v_byte(chip_t* chip, const uint16_t instr){
    if(chip -> v[(instr & 0x0F00) >> 8] != (instr & 0xFF)) chip -> pc += 2;
}

void __sne_v_v(chip_t* chip, const uint16_t instr){
    if(chip -> v[(instr & 0x0F00) >> 8] != chip -> v[(instr & 0x00F0) >> 4]) chip -> pc += 2;
}

/** LD **/
void __ld_v_byte(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] = (instr & 0xFF);
}

void __ld_v_v(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] = chip -> v[(instr & 0x00F0) >> 4];
}

void __ld_i_addr(chip_t* chip, const uint16_t instr){
    chip -> i = instr & 0xFFF;
}

void __ld_v_dt(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] = chip -> dt;
}

void __ld_v_k(chip_t* chip, const uint16_t instr){
    for(uint8_t i = 0; i < 16; i++){
        if((chip -> keyStates >> i) & 0b1){
            chip -> v[(instr & 0x0F00) >> 8] = i;
            return;
        }
    }

    chip -> pc -= 2;
}

void __ld_dt_v(chip_t* chip, const uint16_t instr){
    chip -> dt = chip -> v[(instr & 0x0F00) >> 8];
}

void __ld_st_v(chip_t* chip, const uint16_t instr){
    chip -> st = chip -> v[(instr & 0x0F00) >> 8];
}

void __ld_f_v(chip_t* chip, const uint16_t instr){
    chip -> i = CHARACTER_LOCATION + chip -> v[(instr & 0x0F00) >> 8] * 5;
}   

void __ld_b_v(chip_t* chip, const uint16_t instr){
    uint8_t n = chip -> v[(instr & 0x0F00) >> 8];

    chip -> memory[chip -> i] = n / 100;
    chip -> memory[chip -> i + 1] = (n / 10) % 10;
    chip -> memory[chip -> i + 2] = n % 10;
}

void __ld_i_v(chip_t* chip, const uint16_t instr){
    for(uint8_t n = 0; n <= ((instr & 0x0F00) >> 8); n++) chip -> memory[chip -> i + n] = chip -> v[n];
}

void __ld_v_i(chip_t* chip, const uint16_t instr){
    for(uint8_t n = 0; n <= ((instr & 0x0F00) >> 8); n++) chip -> v[n] = chip -> memory[chip -> i + n];
}

/** ADD **/
void __add_v_byte(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] += instr & 0xFF;
}

void __add_v_v(chip_t* chip, const uint16_t instr){
    uint16_t res = (uint16_t) chip -> v[(instr & 0x0F00) >> 8] + chip -> v[(instr & 0x00F0) >> 4];

    chip -> v[0xF] = res >> 8 ? 1 : 0;

    chip -> v[(instr & 0x0F00) >> 8] = res;
}

void __add_i_v(chip_t* chip, const uint16_t instr){
    chip -> i += chip -> v[(instr & 0x0F00) >> 8];
}

/** BIT OPERATIONS **/
void __or(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] |= chip -> v[(instr & 0x00F0) >> 4];
}

void __and(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] &= chip -> v[(instr & 0x00F0) >> 4];
}

void __xor(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] ^= chip -> v[(instr & 0x00F0) >> 4];
}

/** SUB **/
void __sub(chip_t* chip, const uint16_t instr){
    chip -> v[0xF] = chip -> v[(instr & 0x0F00) >> 8] > chip -> v[(instr & 0x00F0) >> 4];

    chip -> v[(instr & 0x0F00) >> 8] -= chip -> v[(instr & 0x00F0) >> 4];
}

void __subn(chip_t* chip, const uint16_t instr){
    chip -> v[0xF] = chip -> v[(instr & 0x0F00) >> 8] < chip -> v[(instr & 0x00F0) >> 4];

    chip -> v[(instr & 0x0F00) >> 8] = chip -> v[(instr & 0x00F0) >> 4] - chip -> v[(instr & 0x0F00) >> 8];
}

/** SHIFT **/
void __shr(chip_t* chip, const uint16_t instr){
    chip -> v[0xF] = chip -> v[(instr & 0x0F00) >> 8] & 0b1;

    chip -> v[(instr & 0x0F00) >> 8] >>= 1;
}

void __shl(chip_t* chip, const uint16_t instr){
    chip -> v[0xF] = chip -> v[(instr & 0x0F00) >> 8] >> 7;

    chip -> v[(instr & 0x0F00) >> 8] <<= 1;
}

/** SKIP **/
void __skp(chip_t* chip, const uint16_t instr){
    if(chip -> keyStates >> chip -> v[(instr & 0x0F00) >> 8]) chip -> pc += 2;
}

void __sknp(chip_t* chip, const uint16_t instr){
    if(!chip -> keyStates >> chip -> v[(instr & 0x0F00) >> 8]) chip -> pc += 2;
}

/** MISC **/
void __rnd(chip_t* chip, const uint16_t instr){
    chip -> v[(instr & 0x0F00) >> 8] = (*chip -> rnd_fun_ptr)() & (instr & 0x00FF);
}

void __drw(chip_t* chip, const uint16_t instr){
    // Initialize Collision Flag
    chip -> v[0xF] = 0;

    for(uint8_t i = 0; i < (instr & 0x000F); i++){
        uint8_t y = chip -> v[(instr & 0x00F0) >> 4] + i;

        // Draw Each Pixel
        for(uint8_t j = 0; j < 8; j++){
            uint8_t x  = chip -> v[(instr & 0x0F00) >> 8] + j;
            uint8_t px = (chip -> memory[chip -> i + i] >> (7 - j)) & 0b1;

            if(px && chip -> display[y][x]) chip -> v[0xF] = 1;
            
            chip -> display[y][x] ^= px;
        }
    }
}