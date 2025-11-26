#include "cpu.hpp"

void cpu:: cycle(){

    op.full_op = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
    decode(); 
}

void cpu:: decode(){
// TODO: implement decode funciton
    op.nib_1 = op.full_op >> 12;
    op.nib_2 = (op.full_op >> 8) & 0x0F;
    op.nib_3 = (op.full_op >> 4) & 0x0F;
    op.nib_4 = op.full_op & 0xF;
    op.sec_byte = op.full_op & 0x00FF;
    op.addr = op.full_op & 0x0FFF;

    switch(op.nib_1){
        case 0x0:
            op_clear();
            break;
        case 0x1:
            op_jump();
            break;
        case 0x6:
            op_set();
            break;
        case 0x7:
             op_add();
            break;
        case 0xA:
            op_setI();
            break;
        case 0xD:
            op_display();
            break;
        default:
        std::cout << "received unimplemented opcode: " << op.nib_1 << '\n';  

    }
}
void cpu::op_add(){
    uint8_t prev = op.nib_2;
    V[op.nib_2] += V[op.nib_3];
    if(V[op.nib_2] < prev) {
        V[15] = 1;
    }
    else {
        V[15] = 0;
    }
}

void cpu::op_set(){
    V[op.nib_2] = op.sec_byte;
}

void cpu::op_setI(){
    I = op.addr;
}

void cpu::op_clear(){
    for (int i =0; i < GRID_SIZE; i++) {
        display[i] = 0;
    }
}

void cpu::op_jump(){
    pc = op.addr;
}

void cpu::op_display(){
    createWindow();
}
