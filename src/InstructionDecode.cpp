//
//  InstructionDecode.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "InstructionDecode.h"

void InstructionDecode::update() {
    if (stall) return;
    opcode = get_digit_from(i, 6, 0);
    switch (opcode) {
        case 0b0110111: TypeU(); return;
        case 0b0010111: TypeU(); pip->IF->nextPC = PC + imm; return;
        case 0b1101111: TypeJ(); return;
        case 0b1100111: TypeI(); solveI(); pip->IF->nextPC = v1 + imm; return;
        case 0b0000011: TypeI(); solveI(); return;
        case 0b0010011: TypeI(); solveI(); return;
        case 0b1100011: TypeB(); solveBRS(); return;
        case 0b0100011: TypeS(); solveBRS(); return;
        case 0b0110011: TypeR(); solveBRS(); return;
        default:
            break;
    }
}

void InstructionDecode::TypeU() {
    rd = get_digit_from(i, 11, 7);
    imm = get_digit_from(i, 31, 12);
    imm <<= 12;
    
    T = InsT::U;
}

void InstructionDecode::TypeJ() {
    rd = get_digit_from(i, 11, 7);
    imm = get_digit_from(i, 30, 21) << 1;
    imm += get_digit_from(i, 19, 12) << 12;
    imm += get_digit_from(i, 20, 20) << 11;
    imm += get_digit_from(i, 31, 31) << 20;
    T = InsT::J;
    imm = signed_extend(imm, 21);
    imm -= imm & 1;
    pip->IF->nextPC = PC + imm;
}

void InstructionDecode::TypeI() {
    rd = get_digit_from(i, 11, 7);
    imm = get_digit_from(i, 31, 20);
    rs1 = get_digit_from(i, 19, 15);
    funct3 = get_digit_from(i, 14, 12);
    T = InsT::I;
    v1 = pip->reg[rs1];
    imm = signed_extend(imm, 12);
    
}

void InstructionDecode::TypeB() {
    funct3 = get_digit_from(i, 14, 12);
    rs1 = get_digit_from(i, 19, 15);
    rs2 = get_digit_from(i, 24, 20);
    imm = get_digit_from(i, 11, 8) << 1;
    imm += get_digit_from(i, 7, 7) << 11;
    imm += get_digit_from(i, 30, 25) << 5;
    imm += get_digit_from(i, 31, 31) << 12;
    imm -= imm & 1;
    imm = signed_extend(imm, 13);
    T = InsT::B;
    v1 = pip->reg[rs1];
    v2 = pip->reg[rs2];
}

void InstructionDecode::TypeS() {
    funct3 = get_digit_from(i, 14, 12);
    rs1 = get_digit_from(i, 19, 15);
    rs2 = get_digit_from(i, 24, 20);
    imm = get_digit_from(i, 11, 7);
    imm += get_digit_from(i, 31, 25) << 5;
    T = InsT::S;
    v1 = pip->reg[rs1];
    v2 = pip->reg[rs2];
    imm = signed_extend(imm, 12);
}

void InstructionDecode::TypeR() {
    funct3 = get_digit_from(i, 14, 12);
    funct7 = get_digit_from(i, 31, 25);
    rd = get_digit_from(i, 11, 7);
    rs1 = get_digit_from(i, 19, 15);
    rs2 = get_digit_from(i, 24, 20);
    T = InsT::R;
    v1 = pip->reg[rs1];
    v2 = pip->reg[rs2];
    
}

void InstructionDecode::solve_hazard() {
    switch (T) {
        case InsT::I: return solveI();
        case InsT::B:
        case InsT::S:
        case InsT::R: return solveBRS();
        default:
            break;
    }
}

void InstructionDecode::solveI() {
    if (rs1 == 0) return;
    if (rs1 == pip->EXE->rd and pip->EXE->opcode != 0b1100011 and pip->EXE->opcode != 0b0100011) {
        if (pip->EXE->opcode != 0b0000011) {
            v1 = pip->EXE->exe_val;
        }
        return;
    }
    if (rs1 == pip->MEM->rd and pip->MEM->opcode != 0b1100011 and pip->MEM->opcode != 0b0100011) {
        v1 = pip->MEM->mem_val;
    }
}

void InstructionDecode::solveBRS() {
    if (rs1 != 0) {
        if (rs1 == pip->EXE->rd and pip->EXE->opcode != 0b1100011 and pip->EXE->opcode != 0b0100011) {
            if (pip->EXE->opcode != 0b0000011) {
                v1 = pip->EXE->exe_val;
            }
        } else if(rs1 == pip->MEM->rd and pip->MEM->opcode != 0b1100011 and pip->MEM->opcode != 0b0100011) {
            v1 = pip->MEM->mem_val;
        }
    }
    if (rs2 != 0) {
        if (rs2 == pip->EXE->rd and pip->EXE->opcode != 0b1100011 and pip->EXE->opcode != 0b0100011) {
            if (pip->EXE->opcode != 0b0000011) {
                v2 = pip->EXE->exe_val;
            }
        } else if(rs2 == pip->MEM->rd and pip->MEM->opcode != 0b1100011 and pip->MEM->opcode != 0b0100011) {
            v2 = pip->MEM->mem_val;
        }
    }
}

void InstructionDecode::pass() {
    if (stall) {
        --stall; ++pip->EXE->stall;
//        printf("ID is stall\n");
        return;
    }
    pip->EXE->rs1 = rs1;
    pip->EXE->rs2 = rs2;
    pip->EXE->funct7 = funct7;
    pip->EXE->funct3 = funct3;
    pip->EXE->rd = rd;
    pip->EXE->imm = imm;
    pip->EXE->T = (Execution::InsT)T;
    pip->EXE->opcode = opcode;
    pip->EXE->v1 = v1;
    pip->EXE->v2 = v2;
    pip->EXE->i = i;
    pip->EXE->PC = PC;
}

void InstructionDecode::debug() {
    printf("ID Debugging\n");
    printf("ID PC: ");
    printf("%04X", PC);
    printf("\tType: %d\n", T);
    printf("ID Instruction:");
    printf("%08X\n", i);
    printf("funct3: %d\tfunct7: %d\n", funct3, funct7);
    printf("rs1: %d\trs2: %d\trd: %d\n", rs1, rs2, rd);
    printf("v1: %d\tv2: %d\n", v1, v2);
    printf("IMM: %d\n", imm);
    printf("-------------------\n");
}
