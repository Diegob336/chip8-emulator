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

void cpu::load_fonts(){
    for (int i = 0 ; i < FONT_SIZE; i++){
        memory[FONT_ADDR + i] = Fonts[i];
    }
}

void cpu:: cycle(){

    op.full_op = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
    decode(); 
}

void cpu:: decode(){

    op.nib_1 = op.full_op >> 12;
    op.nib_2 = (op.full_op >> 8) & 0x0F;
    op.nib_3 = (op.full_op >> 4) & 0x0F;
    op.nib_4 = op.full_op & 0xF;
    op.sec_byte = op.full_op & 0x00FF;
    op.addr = op.full_op & 0x0FFF;

//    std::cout << std::hex << op.nib_1 << " "; 
//    printf("%02X\n", op.full_op);
    switch(op.nib_1){
        case 0x0:
            if (op.nib_4){
                op_sub_return();
            } else {
                op_clear();
            }
            break;
        case 0x1:
            op_jump();
            break;
        case 0x2:
            op_sub_call();
            break;
        case 0x3:
            if (V[op.nib_2] == op.sec_byte){
                pc += 2;
            }
            break;
        case 0x4:
            if (V[op.nib_2] != op.sec_byte){
                pc += 2;
            }
            break;
        case 0x5:
            if (op.nib_4 != 0){
                std::cout << "invalid opcode, last nibble is: " << op.nib_4 << '\n';
            }
            if (V[op.nib_2] == V[op.nib_3]){
                pc += 2;
            }
            break;
        case 0x6:
            op_set();
            break;
        case 0x7:
             op_add();
            break;
        case 0x8:
            switch(op.nib_4){
                case 0x0:
                    V[op.nib_2] = V[op.nib_3];
                    break;
                case 0x1: 
                    V[op.nib_2] |= V[op.nib_3];
                    break;
                case 0x2:
                    V[op.nib_2] &= V[op.nib_3];
                    break;
                case 0x3:
                    V[op.nib_2] ^= V[op.nib_3];
                    break;
                case 0x4:{
                    uint8_t temp = V[op.nib_2];
                    V[op.nib_2] += V[op.nib_3];
                    if(V[op.nib_2] < temp){
                        V[0xF] = 1;
                    }
                    else {
                        V[0xF] = 0;
                    }
                    break;
                }
                case 0x5:{

                    if (V[op.nib_2] >= V[op.nib_3]){
                        V[0xF] = 1;
                    }
                    else {
                        V[0xF] = 0;
                    }
                    V[op.nib_2] -= V[op.nib_3];
                    break;
                }
                case 0x6:
                    V[0xF] = V[op.nib_2] & 1;
                    V[op.nib_2] >>= 1;
                    break;
                case 0x7:
                    if (V[op.nib_3] >= V[op.nib_2]){
                        V[0xF] = 1;
                    }
                    else {
                        V[0xF] = 0;
                    }
                    V[op.nib_2] = V[op.nib_3] - V[op.nib_2];
                    break;
                case 0xE:
                    if ((V[op.nib_2] >> 7) & 1){
                        V[0xF] = 1;
                    }
                    else {
                        V[0xF] = 0;
                    }
                    V[op.nib_2] <<= 1;
                    break;
                default:
                    std::cout << "recevied invlaid command, fourth nibble is: " << op.nib_4;

            }

            break;
        case 0x9:
            if (op.nib_4 != 0){
                std::cout << "invalid opcode, last nibble is: " << op.nib_4 << '\n';
            }

            if (V[op.nib_2] != V[op.nib_3]){
                pc +=2;
            }

            break;
        case 0xA:
            op_setI();
            break;
        case 0xB:
            pc = V[0] + op.addr;
            break;
        case 0xC:
            V[op.nib_2] = rand() & op.sec_byte;
            break;
        case 0xD:
            op_display();
            break;
        case 0xE:
            if (op.nib_3 == 0x9 && op.nib_4 == 0xE){
                if (V[op.nib_2] < 16){
                    if (keys[V[op.nib_2]]){
                        pc += 2;
                    }

                }
                else {
                    std::cout << "Vx is too large ";
                }
            }
            else if (op.nib_3 == 0xA && op.nib_4 == 0x1){
                if (V[op.nib_2] < 16){
                    if (!keys[V[op.nib_2]]){
                        pc += 2;
                    }

                }
                else {
                    std::cout << "Vx is too large ";
                }
            }
            break;
        case 0xF:
            switch(op.nib_4){
                case 0x3:{

                    uint8_t temp = V[op.nib_2];
                    for (int i = 2; i >= 0; i--){
                        memory[I + i] = temp % 10; 
                        temp /= 10;
                    }

                    break;
                }
                case 0x5: 
                    switch(op.nib_3){

                        case 0x1:
                            delay_timer = V[op.nib_2];
                            break;
                        case 0x5:
                            for (int i = 0; i <= op.nib_2; i++){
                                memory[I + i] = V[i];
                            }
                            break;
                        case 0x6:
                            for (int i = 0; i <= op.nib_2; i++){
                                V[i] = memory[I + i];
                            }
                    }

                    break;
                case 0x7: 
                    V[op.nib_2] = delay_timer;
                    break;
                case 0x8:
                    sound_timer = V[op.nib_2];
                    break;
                case 0x9:
                    I = FONT_ADDR + (V[op.nib_2] * 5);
                    break;
                case 0xA: {
                    uint8_t pressed{};
                    for (int i = 0; i < 16; i ++){
                        if (keys[i]){
                            pressed = 1;
                            V[op.nib_2] = i;
                        }
                    }
                    if (!pressed){
                        pc -= 2;
                    }
                    break;

                }
                case 0xE:
                    I += V[op.nib_2];
                    break;
            }
            break;

        default:
            std::cout << "received invalid opcode: " << op.nib_1 << '\n';  
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
}

void cpu::op_display(){
    uint8_t x = V[op.nib_2];
    uint8_t y = V[op.nib_3];
    V[0xF] = 0;

    for (int i = 0; i < op.nib_4; i++) {
        uint8_t temp = memory[I + i];
        for (int c = 0; c < 8; c ++){
            uint8_t prev = display[(y + i) % 32][(x + c) % 64]; 
            uint8_t val = (temp >> (7 - c)) & 1;
            display[(y + i) % 32][(x + c) % 64] ^= val;
            if (prev == 1 && val == 1){
                V[0xF] = 1;
            }
        } 
    }

    draw(win, winSurface, display);  

}

void cpu::op_sub_call(){

    if (sp >= 16){
        std::cout << "stack overflow";
        return;
    }
    stack[sp] = pc;
    pc = op.addr;
    sp ++;
}

void cpu::op_sub_return(){
    if (sp <= 0){
        std::cout << "nothing in stack";
        return;
    }
    pc = stack[sp - 1];
    sp --;
}


void cpu::timer(){
    if (delay_timer > 0){

        delay_timer--;
    }
    if (sound_timer > 0){

        sound_timer--; 

    }
}


void cpu::print(){
    for (int i = 0; i < 132; i++){
        uint16_t opcode = (memory[0x200 +i] << 8) | memory[0x201 + i];
        printf("%02X\n", opcode);
        i++;
    }
}

