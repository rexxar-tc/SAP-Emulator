//
// Created by brant on 5/15/21.
//


#include <stdio.h>
#include <stdlib.h>
#include "processor.h"


uint8_t memory[16];
byte regc;
byte rega;
byte regb;
byte mar;
byte inr;
byte pc;
byte or;
byte display[16];
int didx;

int tick();

void initialize() {
    for (int i = 0; i < 16; i++)
        memory[i] = 0;
    rega = 0;
    regb = 0;
    reset();
}

void reset() {
    pc = 0;
    mar = 0;
    inr = 0;
    didx = 0;
    for (int i = 0; i < 16; i++)
        display[i] = 0;
}

void loadRAM(byte bin[]) {
    printf("loading memory: 0x");
    for (int i = 0; i < 16; i++) {
        memory[i] = bin[i];
        printf("%.2x", bin[i]);
    }
    printf("\n");
}

const char * hex = "0123456789ABCDEF";

char *run() {
    reset();
    int r;
    do{
        r = tick();
    }
    while (r == 1);

    char *ret = malloc(33);
    int i =0;
    while(i<32){
        byte d = display[i];
        ret[i]=hex[d>>4];
        i++;
        ret[i]=hex[d&0xf];
        i++;
    }
    ret[32] = 0;

    return ret;
}

int tick() {
    //t1
    mar = pc;
    //t2
    pc++;
    //t3
    inr = memory[mar];

    byte op = inr >> 4;
    byte ov = inr & 0x0f;

    switch (op) {
        case LDA:
            rega = memory[ov];
            break;
        case ADD:
            rega = rega + memory[ov];
            break;
        case SUB:
            rega = rega - memory[ov];
            break;
        case OUT:
            or = rega;
            display[didx] = or;
            didx++;
            break;
        case HLT:
            return 0;
        default:
            printf("Invalid opcode: 0x%x\n", inr);
            return 0;
    }

    return 1;
}
