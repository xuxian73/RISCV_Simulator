//
//  Pipeline.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef Pipeline_h
#define Pipeline_h

#include "Register.h"
#include "Memory.h"
#include "BTB.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"
#include "Execution.h"
#include "MemoryAccess.h"
#include "WriteBack.h"

typedef int32_t Instruction;
typedef unsigned Immediate;
class InstructionFetch;
class InstructionDecode;
class Execution;
class MemoryAccess;
class WriteBack;

class Pipeline {
    
public:
    Memory mem;
    Register reg;
    BTB pred;
    InstructionFetch* IF;
    InstructionDecode* ID;
    Execution* EXE;
    MemoryAccess* MEM;
    WriteBack* WB;
    
    Pipeline();
};

#endif /* Pipeline_h */
