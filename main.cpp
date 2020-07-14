//
//  main.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//


#include <cstdio>
#include "Register.h"
#include "Memory.h"
#include "BTB.h"
#include "Pipeline.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"
#include "Execution.h"
#include "MemoryAccess.h"
#include "WriteBack.h"

Pipeline pip;
/* void runtest(const char* path) {
    pip.mem.init(path);
    while (true) {
        pip.WB->update();
//      pip.WB->debug();
//      printf("%d\n", pip.WB->PC);
        if (pip.MEM->i == 0x0ff00513) break;
        
        pip.MEM->update();
//      pip.MEM->debug();
        
        pip.EXE->update();
//      pip.EXE->debug();

        pip.ID->update();
//      pip.ID->debug();
        
        pip.IF->update();
//      pip.IF->debug();
        
        pip.MEM->pass();
        pip.EXE->pass();
        pip.ID->pass();
        pip.IF->pass();
    }
    printf("%d\n",((unsigned int)pip.reg[pip.MEM->rd]) & 255u);
//  pip.pred.print_success_rate();
}
*/
void runtest() {
    pip.mem.init();
    
    while (true) {
        pip.WB->update();
        if (pip.MEM->i == 0x0ff00513) break;
        pip.MEM->update();
        pip.EXE->update();
        pip.ID->update();
        pip.IF->update();
    
        pip.MEM->pass();
        pip.EXE->pass();
        pip.ID->pass();
        pip.IF->pass();
    }
    printf("%d\n",((unsigned int)pip.reg[pip.MEM->rd]) & 255u);
    //  pip.pred.print_success_rate();
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    runtest("/Users/xuxian/Desktop/RISCV Reference/riscv-testcases/testcases/qsort.data");
    runtest();
    return 0;
}
