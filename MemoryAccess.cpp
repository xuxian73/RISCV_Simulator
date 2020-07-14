//
//  MemoryAccess.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "MemoryAccess.h"

void MemoryAccess::update() {
    if (stall) return;
    switch (opcode) {
        case 0b0100011:
            store();
            return;
        case 0b0000011:
            load();
            return;
        default:
            break;
    }
}

void MemoryAccess::store() {
    switch (funct3) {
        case 0b000:
            pip->mem.write_short(mem_val, v2 & 0xff);
//            printf("write byte %d to Mem[%d]\n", v2 & 0xff, mem_val);
            break;
        case 0b001:
            pip->mem.write_short(mem_val, v2 & 0xffff);
//            printf("write short %d to Mem[%d]\n", v2 & 0xffff, mem_val);
            break;
        case 0b010:
            pip->mem.write_word(mem_val, v2);
//            printf("write word %d to Mem[%d]\n", v2, mem_val);
            break;
        default:
            break;
    }
}

void MemoryAccess::load() {
    switch (funct3) {
        case 0b000:
            mem_val = pip->mem.load_byte(mem_val);
            mem_val = signed_extend(mem_val, 8);
//            printf("load byte %d from Mem\n", mem_val);
            break;
        case 0b001:
            mem_val = pip->mem.load_short(mem_val);
            mem_val = signed_extend(mem_val, 16);
//            printf("load short %d from Mem\n", mem_val);
            break;
        case 0b010:
            mem_val = pip->mem.load_word(mem_val);
//            printf("load word %d from Mem\n", mem_val);
            break;
        case 0b100:
            mem_val = pip->mem.load_byte(mem_val);
//            printf("load unsigned byte %d from Mem\n", mem_val);
            break;
        case 0b101:
            mem_val = pip->mem.load_short(mem_val);
//            printf("load upsigned short %d from Mem\n", mem_val);
            break;
        default:
            break;
    }
    
    if (rd == 0) return;
    if (pip->EXE->T == Execution::InsT::I and pip->EXE->rs1 == rd)
    {
        pip->EXE->v1 = mem_val;
        return;
    }
    if (pip->EXE->rs1 == rd and
        (pip->EXE->T == Execution::InsT::R
         or pip->EXE->T == Execution::InsT::B
         or pip->EXE->T == Execution::InsT::S) ) {
        pip->EXE->v1 = mem_val;
    }
    if (pip->EXE->rs2 == rd and
        (pip->EXE->T == Execution::InsT::R
         or pip->EXE->T == Execution::InsT::B
         or pip->EXE->T == Execution::InsT::S) ) {
        pip->EXE->v2 = mem_val;
    }
}

void MemoryAccess::pass() {
    if (stall) {
        --stall; ++pip->WB->stall;
//        printf("MEM is stall\n");
        return;
    }
//    pip->WB->opcode = opcode;
    pip->WB->PC = PC;
    pip->WB->wb_val = mem_val;
    pip->WB->T = (WriteBack::InsT)T;
//    pip->WB->rs1 = rs1;
//    pip->WB->rs2 = rs2;
    pip->WB->rd = rd;
    pip->WB->i = i;
//    pip->WB->funct3 = funct3;
//    pip->WB->funct7 = funct7;
}

void MemoryAccess::debug(){
    printf("MEM Debugging\n");
    printf("MEM PC: ");
    printf("%04X\n", PC);
    printf("MEM Instruction:");
    printf("%08X\n", i);
//    printf("funct3: %d\tfunct7: %d\n", funct3, funct7);
//    printf("rs1: %d\trs2: %d\trd: %d\n", rs1, rs2, rd);
//    printf("v1: %d\tv2: %d\n", v1, v2);
    printf("IMM: %d\n", imm);
    printf("mem_val:\t%d\n", mem_val);
    printf("-----------------\n");
}

