//
//  MemoryAccess.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef MemoryAccess_h
#define MemoryAccess_h

#include "Pipeline.h"
#include "BitOperation.h"
class Pipeline;
class MemoryAccess {
    friend class Pipeline;
public:
    Pipeline* pip;
    enum InsT {
        R, I, S, B, U, J
    } T;
    unsigned rs1, rs2, rd, funct3, funct7, opcode;
    int32_t v1, v2, mem_val;
    int32_t i;
    int32_t PC;
    Immediate imm;
    int stall;
    
    MemoryAccess(Pipeline* p): pip(p), stall(1) {}
    
    void update();
    
    void load();
    
    void store();
    
    void pass();
    
    void debug();
};

#endif /* MemoryAccess_h */
