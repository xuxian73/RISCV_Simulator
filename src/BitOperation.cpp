//
//  BitOperation.cpp
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#include "BitOperation.h"

unsigned get_digit_from(unsigned n, int hi, int lo) {
    return (n >> lo) & ((1 << (hi - lo + 1)) - 1);
}

unsigned signed_extend(unsigned n, int cnt) {
    if (0xffffffff << ( cnt - 1 ) & n)
        return (0xffffffff << cnt | n);
    else return ( (1 << cnt) - 1) & n;
}
