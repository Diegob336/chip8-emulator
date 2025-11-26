#include <stdint.h>
#include <stack>
#include "opcodes.hpp"
#include "graphics.hpp"

constexpr int GRID_SIZE = 64 * 32;

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
    void decode();
    void op_add();
    void op_set();
    void op_setI();
    void op_clear();
    void op_jump();
    void op_display();
private:
    uint8_t memory[4096];
    std::stack<uint16_t> stack;
    uint16_t pc;
    uint16_t I;
    uint8_t V[16];
    opcode op;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[GRID_SIZE];
};


