//
//  Execution.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "Execution.h"

void Execution::update() {
    if (stall) return;
    switch (T) {
        case InsT::U : return Execution::TypeU();
        case InsT::R : return Execution::TypeR();
        case InsT::S : return Execution::TypeS();
        case InsT::I : return Execution::TypeI();
        case InsT::B : return Execution::TypeB();
        case InsT::J : return Execution::TypeJ();
        default:
            break;
    }
}

void Execution::TypeU(){
    if (opcode == 0b0110111) {
        exe_val = imm;
    } else {
        exe_val = imm + PC;
//        pip->ID->i = pip->mem.fetch_instruction(pip->ID->PC);
    }
}

void Execution::TypeR() {
    switch (funct3) {
        case 0b000:
            if (funct7 == 0b0000000)
                exe_val = v1 + v2;  //ADD
            else exe_val = v1 - v2; //SUB
            return;
        case 0b001:
            exe_val = v1 << v2;  //SLL
            return;
        case 0b010:
            exe_val = (v1 < v2); //SLT
            return;
        case 0b011:
            exe_val = ( (unsigned)v1 < (unsigned)v2 );  //SLTU
            return;
        case 0b100:
            exe_val = v1 ^ v2;  //XOR
            return;
        case 0b101:
            if (funct7 == 0b0000000)
                exe_val = (int)( (unsigned)v1 >> v2 );
            else
                exe_val = v1 >> v2;
            return;
        case 0b110:
            exe_val = v1 | v2;
            return;
        case 0b111:
            exe_val = v1 & v2;
            return;
        default:
            break;
    }
}

void Execution::TypeI() {
    switch (opcode) {
        case 0b1100111:  //JALR
            exe_val = PC + 4;
//            pip->ID->i = pip->mem.fetch_instruction(pip->ID->PC);
            return;
        case 0b0000011:  //L*
            exe_val = v1 + imm;
            return;
        case 0b0010011:  //***I
            switch (funct3) {
                case 0b000:
                    exe_val = v1 + imm;
                    break;
                case 0b001:
                    exe_val = v1 << imm;
                    break;
                case 0b010:
                    exe_val = (v1 < (int)imm);
                    break;
                case 0b011:
                    exe_val = (unsigned(v1) < imm);
                    break;
                case 0b100:
                    exe_val = v1 ^ imm;
                    break;
                case 0b101:
//                    if (imm & 0b10000) imm = 0;
                    if (funct7 == 0b0000000)
                        exe_val = (unsigned)v1 >> imm;
                    else exe_val = v1 >> imm;
                    break;
                case 0b110:
                    exe_val = v1 | imm;
                    break;
                case 0b111:
                    exe_val = v1 & imm;
                    break;
                default:
                    break;
            }
            return;
        default:
            break;
    }
}

void Execution::TypeS() {
    exe_val = v1 + imm;
}

void Execution::TypeB() {
    switch (funct3) {
        case 0b000:
            exe_val = (v1 == v2);
            solve_branch();
            break;
        case 0b001:
            exe_val = !(v1 == v2);
            solve_branch();
            break;
        case 0b100:
            exe_val = (v1 < v2);
            solve_branch();
            break;
        case 0b101:
            exe_val = !(v1 < v2);
            solve_branch();
            break;
        case 0b110:
            exe_val = ( (unsigned)v1 < v2);
            solve_branch();
            break;
        case 0b111:
            exe_val = !( (unsigned)v1 < v2);
            solve_branch();
            break;
        default:
            break;
    }
}

void Execution::TypeJ() {
    exe_val = PC + 4;
//    pip->ID->i = pip->mem.fetch_instruction(pip->ID->PC);
}

void Execution::solve_branch() {
    if (exe_val) {
        if (pip->ID->PC == PC + imm) {
            pip->pred.modify(PC, 1, 1);
        } else {
            pip->IF->nextPC = PC + imm;
            pip->pred.modify(PC, 0, 1, PC + imm);
            pip->ID->stall = 1;
        }
    } else {
        if (pip->ID->PC == PC + 4) {
            pip->pred.modify(PC, 1, 0);
        } else {
            pip->IF->nextPC = PC + 4;
            pip->pred.modify(PC, 0, 0, PC + 4);
            pip->ID->stall = 1;
        }
    }
}

void Execution::pass() {
    if (stall) {
        --stall; ++pip->MEM->stall;
//        printf("EXE is stall\n");
        return;
    }
    pip->MEM->PC = PC;
    pip->MEM->mem_val = exe_val;
    pip->MEM->funct3 = funct3;
    pip->MEM->funct7 = funct7;
    pip->MEM->rs1 = rs1;
    pip->MEM->rs2 = rs2;
    pip->MEM->v1 = v1;
    pip->MEM->v2 = v2;
    pip->MEM->opcode = opcode;
    pip->MEM->rd = rd;
    pip->MEM->T = (MemoryAccess::InsT)T;
    pip->MEM->i = i;
    pip->MEM->imm = imm;
}

void Execution::debug() {
    printf("EXE Debugging\n");
    printf("EXE PC: ");
    printf("%04X\n", PC);
    printf("EXE Instruction:");
    printf("%08X\n", i);
//    printf("funct3: %d\tfunct7: %d\n", funct3, funct7);
//    printf("rs1: %d\trs2: %d\trd: %d\n", rs1, rs2, rd);
//    printf("v1: %d\tv2: %d\n", v1, v2);
    printf("IMM: %d\n", imm);
    printf("exe_val:\t%d\n", exe_val);
    printf("-----------------\n");
}

