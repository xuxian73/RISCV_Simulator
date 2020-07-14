//
//  InstructionFetch.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//
#ifndef InstructionFetch_h
#define InstructionFetch_h

#include "Pipeline.h"
#include "Memory.h"
typedef int32_t Instruction;
class Pipeline;
class InstructionFetch {
    friend class Pipeline;
public:
    Instruction i;
    Pipeline* pip;
    int32_t PC, nextPC;
    int stall;
    
    InstructionFetch(Pipeline* p): pip(p), PC(0), nextPC(0), stall(0) {}
    
    void update();
    
    void pass();
    
    void debug();

};

#endif /* InstructionFetch_h */
