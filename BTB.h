//
//  BTB.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/13.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef BTB_h
#define BTB_h

#include <map>
#include <utility>

struct info {
    int target;
    int bit;
    
    info(int t, int b):target(t), bit(b) {}
};

class BTB {
    int TOTAL_PRED;
    int SUCCESS;
    std::map<int, info> predictor;
    // map<Instruction_Addr, info(Target_Addr, Prediction_Bit > Predictor
public:
    BTB():TOTAL_PRED(0), SUCCESS(0) {}
    
    void insert(std::pair<int, info>);
    
    void modify(int32_t inst, bool successful, bool jump, int new_target = 0);
    
    int32_t fetch_addr(int32_t inst);
    
    void print_success_rate();
};

#endif /* BTB_h */
