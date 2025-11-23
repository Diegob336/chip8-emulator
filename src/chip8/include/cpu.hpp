#include <stdint.h>
#include <stack>
#include "opcodes.hpp"
class cpu {

public:
    cpu(): memory{},
        stack{},
        pc(0x200),
        I{},
        V{}, 
        op{},
        delay_timer{},
        sound_timer{},
        display{}
    {
    }
    void cycle();
private:
    uint8_t memory[4096];
    std::stack<uint16_t> stack;
    uint16_t pc;
    uint16_t I;
    uint8_t V[16];
    opcode op;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[64 * 32];
};


