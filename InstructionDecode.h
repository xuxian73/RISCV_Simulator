//
//  InstructionDecode.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef InstructionDecode_h
#define InstructionDecode_h

#include "Pipeline.h"

class Pipeline;
class InstructionDecode {
    friend class Pipeline;
public:
    Pipeline* pip;
    enum InsT {
        R, I, S, B, U, J
    } T;
    unsigned rs1, rs2, rd, funct3, funct7, opcode;
    int32_t v1, v2;
    int32_t i;
    int32_t PC;
    Immediate imm;
    int stall;
    
    InstructionDecode(Pipeline* p):pip(p), rs1(0), rs2(0), rd(0),
    funct3(0), funct7(0), opcode(0), stall(1) {}
    
    void update();
    
    void TypeR();
    
    void TypeI();
    
    void TypeS();
    
    void TypeB();
    
    void TypeU();
    
    void TypeJ();
    
    void solve_hazard();

    void solveI();
    
    void solveBRS();
    
    void pass();
    
    void debug();
};

#endif /* InstructionDecode_h */
