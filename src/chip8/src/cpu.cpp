#include "cpu.hpp"

void cpu:: cycle(){

    op.full_op = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
    op.decode(); 
}
