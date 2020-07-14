//
//  BTB.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/13.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "BTB.h"

void BTB::insert(std::pair<int32_t, info > p) {
    predictor.insert(p);
}

void BTB::modify(int32_t inst, bool successful, bool jump, int new_target) {
    std::map<int32_t, info>::iterator p = predictor.find(inst);
    ++TOTAL_PRED;
    if (successful) {
        if (jump and p->second.bit != 3) ++p->second.bit;
        if (!jump and p->second.bit != 0) --p->second.bit;
        ++SUCCESS;
    } else {
        if (jump)  {
            ++p->second.bit;
            if (p->second.bit & 0b10) p->second.target = new_target;
        }
        else {
            --p->second.bit;
            if (p->second.bit < 2) p->second.target = new_target;
        }
    }
}

int BTB::fetch_addr(int inst) {
    std::map<int32_t, info >::iterator p = predictor.find(inst);
    if (p == predictor.end())
    {
        predictor.insert(std::pair<int, info>(inst, info(inst + 4, 0b01)));
        p = predictor.find(inst);
    }
    return p->second.target;
}

void BTB::print_success_rate() {
    printf("TOTAL: %d\n", TOTAL_PRED);
    printf("SUCCESS: %d\n", SUCCESS);
    printf("SUCCESS_RATE: %.2f", (double)SUCCESS / TOTAL_PRED * 100);
    putchar('%'); putchar('\n');
}
