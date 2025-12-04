#include <stdint.h>
#include "cpu.hpp"

int main(int argc, char* argv[]){

    std::string file_path = "../chip8-programs/2-ibm-logo.ch8";
    int size = std::filesystem::file_size(file_path);
    std::cout << size << std::endl;
    cpu chip8;

    int res = chip8.load_rom(file_path, size);
    if (res < 0){
        return -1;

    }
    //chip8.print();

    for (int i = 0; i < size; i++){
        chip8.cycle();

    }
    sleep(10);
}

