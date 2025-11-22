#include <stdint.h>
#include <stack>

class cpu {

public:

private:
    uint8_t memory[4096];
    std::stack<uint16_t> stack;
    uint16_t PC;
    uint16_t I;
    uint8_t registers[16];
    uint8_t delay_timer;
    uint8_t sound_timer;
};


