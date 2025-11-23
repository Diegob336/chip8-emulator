#include "opcodes.hpp"

void opcode::decode(){
// TODO: implement decode funciton
    this->nib_1 = this->full_op & 0xF000;
    nib_2 = full_op & 0x0F00;
    nib_3 = full_op & 0x00F0;
    nib_4 = full_op & 0x000F;
    sec_byte = full_op & 0x00FF;
    addr = full_op & 0x0FFF;

    switch(nib_1){
        case 0x0:
            clear();
            break;
        case 0x1:
            jump();
            break;
        case 0x6:
            set();
            break;
        case 0x7:
             add();
            break;
        case 0xA:
            setI();
            break;
        case 0xD:
            display();
            break;
        default:
        std::cout << "received unimplemented opcode: " << nib_1 << '\n';  

    }
}
void opcode::add(){

}

void opcode::set(){

}

void opcode::clear(){

}

void opcode::jump(){

}
void opcode::display(){

}
