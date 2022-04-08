#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip.h"

struct chip_s typedef chip_t;

void __execute(chip_t* chip);

void __cls(chip_t* chip);
void __ret(chip_t* chip);

void __jp(chip_t* chip, const uint16_t instr);
void __jp_v(chip_t* chip, const uint16_t instr);
void __call(chip_t* chip, const uint16_t instr);

void __se_v_byte(chip_t* chip, const uint16_t instr);
void __se_v_v(chip_t* chip, const uint16_t instr);
void __sne_v_byte(chip_t* chip, const uint16_t instr);
void __sne_v_v(chip_t* chip, const uint16_t instr);

void __ld_v_byte(chip_t* chip, const uint16_t instr);
void __ld_v_v(chip_t* chip, const uint16_t instr);
void __ld_i_addr(chip_t* chip, const uint16_t instr);
void __ld_v_dt(chip_t* chip, const uint16_t instr);
void __ld_v_k(chip_t* chip, const uint16_t instr);
void __ld_dt_v(chip_t* chip, const uint16_t instr);
void __ld_st_v(chip_t* chip, const uint16_t instr);
void __ld_f_v(chip_t* chip, const uint16_t instr);
void __ld_b_v(chip_t* chip, const uint16_t instr);
void __ld_i_v(chip_t* chip, const uint16_t instr);
void __ld_v_i(chip_t* chip, const uint16_t instr);

void __add_v_byte(chip_t* chip, const uint16_t instr);
void __add_v_v(chip_t* chip, const uint16_t instr);
void __add_i_v(chip_t* chip, const uint16_t instr);

void __or(chip_t* chip, const uint16_t instr);
void __and(chip_t* chip, const uint16_t instr);
void __xor(chip_t* chip, const uint16_t instr);

void __sub(chip_t* chip, const uint16_t instr);
void __subn(chip_t* chip, const uint16_t instr);

void __shr(chip_t* chip, const uint16_t instr);
void __shl(chip_t* chip, const uint16_t instr);

void __skp(chip_t* chip, const uint16_t instr);
void __sknp(chip_t* chip, const uint16_t instr);

void __rnd(chip_t* chip, const uint16_t instr);
void __drw(chip_t* chip, const uint16_t instr);

#endif