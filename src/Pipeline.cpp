//
//  Pipeline.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "Pipeline.h"

Pipeline::Pipeline() {
    IF = new InstructionFetch(this);
    ID = new InstructionDecode(this);
    EXE = new Execution(this);
    MEM = new MemoryAccess(this);
    WB = new WriteBack(this);
}
