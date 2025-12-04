#include "cpu.hpp"

int cpu::load_rom(const std::string& file_path, int size){
    std::ifstream file(file_path, std::ios::binary);

    if (!file){
        std::cout << "could not open file";
        return -1;
    }
    if (size > (4096 - 0x200)){
        std::cout << "program is too large for chip8";
        return -1;
    }

    file.read(reinterpret_cast<char*>(&memory[0x200]), size);
    printf("%02X\n",((memory[0x228] << 8) | memory[0x229]));

    return 1;

}

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

//    std::cout << std::hex << op.nib_1 << " "; 
    printf("%02X\n", op.full_op);
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
    V[op.nib_2] += op.sec_byte;
}

void cpu::op_set(){
    V[op.nib_2] = op.sec_byte;
}

void cpu::op_setI(){
    I = op.addr;
}

void cpu::op_clear(){
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 64; j ++){
            display[i][j] = 0;
        }
    }
    draw(win, winSurface, display);
}

void cpu::op_jump(){
    pc = op.addr;
    printf("%02X\n", op.addr);
}

void cpu::op_display(){
    uint8_t x = V[op.nib_2];
    uint8_t y = V[op.nib_3];

    for (int i = 0; i < op.nib_4; i++) {
        uint8_t temp = memory[I + i];
        for (int c = 0; c < 8; c ++){
            uint8_t val = (temp >> (7 - c)) & 1;
            display[(y + i) % 32][(x + c) % 64] ^= val;
        } 
    }

    draw(win, winSurface, display);  

}

void cpu::print(){
    for (int i = 0; i < 132; i++){
        uint16_t opcode = (memory[0x200 +i] << 8) | memory[0x201 + i];
        printf("%02X\n", opcode);
        i++;
    }
}

