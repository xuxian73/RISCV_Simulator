//
//  Memory.h
//  RISC-V pipeline
//
//  Created by 许贤 on 2020/7/12.
//  Copyright © 2020 许贤. All rights reserved.
//

#ifndef Memory_h
#define Memory_h

#include <fstream>
#include <cstdio>
#include <memory.h>
typedef unsigned Immediate;
class Memory {
    int32_t hex(char& ch) {
        if (ch >= '0' and ch <= '9') return ch - '0';
        else return ch - 'A' + 10;
    }
public:
    char Mem[0x400000];
    
    Memory() {
        memset(Mem, 0, 0x400000);
    }
    
/*    void init(const char *path) {   //read from file
        unsigned cur = 0;
        std::fstream in(path);
        while ( in ) {
            std::string s;
            std::getline(in, s);
            if (s[0] == '@') {
                cur = 0;
                for (int i = 1; i < 9; ++i) {
                    cur += hex(s[i]) << ( (8 - i) << 2);
                }
            }
            else {
                int tmp = 0;
                if (s.length() == 0) break;
                while (tmp < s.length() - 1) {
                    for (int i = 0; i <= 3; ++i) {
                        Mem[cur + i] += hex(s[tmp]) << 4; ++tmp;
                        Mem[cur + i] += hex(s[tmp]); ++tmp;
                        ++tmp;
                    }
                    cur += 4;
                }
            }
        }
    }
*/
    void init() {   //read from console
        unsigned cur = 0;
        char s[16];
        while (scanf("%s", s) != EOF) {
            if (s[0] == '@') {
                cur = 0;
                for (int i = 1; i < 9; ++i) {
                    cur += hex(s[i]) << ( (8 - i) << 2);
                }
            }
            else {
                sscanf(s, "%x", &Mem[cur++]);
                scanf("%x", &Mem[cur++]);
                scanf("%x", &Mem[cur++]);
                scanf("%x", &Mem[cur++]);
            }
        }
    }
    
    char &operator[](size_t ind) {
        return Mem[ind];
    }
    
    int32_t fetch_instruction(size_t ind) {
        return *( (int32_t*)( Mem + ind ) );
    }
    
    unsigned load_word(size_t ind) {
        return *( (int32_t*)(Mem + ind) );
    }
    
    void write_word(size_t ind, Immediate imm) {
        *(Immediate *)(Mem + ind) = imm;
    }
    
    unsigned short load_short(size_t ind){
        return *(short *)( Mem + ind );
    }
    
    void write_short(size_t ind, unsigned short x) {
        *(unsigned short *)(Mem + ind) = x;
    }
    
    int8_t load_byte(size_t ind) {
        return *(int8_t*)( Mem + ind );
    }
    
    void write_byte(size_t ind, int8_t x) {
        *(int8_t*)(Mem + ind) = x;
    }
};

#endif /* Memory_h */
