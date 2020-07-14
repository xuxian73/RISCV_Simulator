//
//  WriteBack.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef WriteBack_h
#define WriteBack_h

#include "Pipeline.h"
class WriteBack {
public:
    Pipeline* pip;
    enum InsT {
        R, I, S, B, U, J
    } T;
    unsigned rd;
    int32_t wb_val;
    int32_t i;
    int32_t PC;
    int stall;
    
    WriteBack(Pipeline* p): pip(p), stall(1) {}
    
    void update();
    
    void debug();
};

#endif /* WriteBack_h */
