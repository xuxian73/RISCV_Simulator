//
//  Register.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef Register_h
#define Register_h

#include <cassert>
class Register {
public:
    int32_t reg[32];
    bool modify[32];
    Register() {
        reg[0] = 0;
        for (int i = 0; i < 32; ++i)
            modify[i] = false;
    }
    
    int32_t & operator[](size_t ind) {
        return reg[ind];
    }
    
};
#endif /* Register_h */
