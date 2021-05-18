//
// Created by brant on 5/15/21.
//

#ifndef SAP_1_PROCESSOR_H
#define SAP_1_PROCESSOR_H

#include <stdint.h>
#define LDA 0b0000
#define ADD 0b0001
#define SUB 0b0010
#define OUT 0b1110
#define HLT 0b1111
#define LDA_T 0b00000000
#define ADD_T 0b00010000
#define SUB_T 0b00100000
#define OUT_T 0b11100000
#define HLT_T 0b11110000

typedef uint8_t byte;

void initialize();
void loadRAM(byte bin[]);
void reset();
char* run();
#endif //SAP_1_PROCESSOR_H
