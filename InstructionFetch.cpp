//
//  InstructionFetch.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "InstructionFetch.h"
#include "InstructionDecode.h"
void InstructionFetch::update() {
    PC = nextPC;
    i = pip->mem.fetch_instruction(PC);
}

void InstructionFetch::pass() {
    pip->ID->i = i;
    pip->ID->PC = PC;
    if ((i & 0x7f) == 0b1100011)
        nextPC = pip->pred.fetch_addr(PC);
    else nextPC = PC + 4;
}

void InstructionFetch::debug(){
    printf("IF Debugging...\n");
    printf("IF PC: ");
    printf("%04X\n", PC);
    printf("IF Instruction: ");
    printf("%08X\n", i);
    printf("-----------------\n");
}
