//
//  Execution.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef Execution_h
#define Execution_h

#include "Pipeline.h"

class Pipeline;
class Execution {
    friend class Pipeline;
public:
    Pipeline* pip;
    enum InsT {
        R, I, S, B, U, J
    } T;
    unsigned rs1, rs2, rd, funct3, funct7, opcode;
    int32_t v1, v2, exe_val;
    int32_t i;
    int32_t PC;
    Immediate imm;
    int stall;
    
    Execution(Pipeline* p) : pip(p), stall(1) {}
    
    void update();
    
    void TypeR();
    
    void TypeI();
    
    void TypeS();
    
    void TypeB();
    
    void TypeU();
    
    void TypeJ();
    
    inline void solve_branch();
    
    void pass();
    
    void debug();
};

#endif /* Execution_h */
