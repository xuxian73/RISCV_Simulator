//
//  WriteBack.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "WriteBack.h"

void WriteBack::update() {
    if (stall) { --stall;
//        printf("WB is stall\n");
        return; } 
    if (rd == 0) return;
    if (T == InsT::B or T == InsT::S) return;
    pip->reg[rd] = wb_val;
//    printf("Write reg[%d] to %d\n", rd, wb_val);
}

void WriteBack::debug() {
    printf("WB Debugging\n");
    printf("WB PC: ");
    printf("%04X\n", PC);
    printf("WB Instruction:");
    printf("%08X\n", i);
    printf("rd: %d\n", rd);
    printf("wb_val:\t%d\n", wb_val);
    printf("-----------------\n");
}
