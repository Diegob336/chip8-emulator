#include <stdint.h>
#include "cpu.hpp"

using namespace std::chrono;

int main(int argc, char* argv[]){

    std::string file_path = "../chip8-programs/2-ibm-logo.ch8";
    int size = std::filesystem::file_size(file_path);
    std::cout << size << std::endl;
    cpu chip8;

    double cycleDelay = 0.30;


    int res = chip8.load_rom(file_path, size);
    if (res < 0){
        return -1;

    }
    //chip8.print();
    auto prev = steady_clock::now();
    steady_clock::time_point curr;
    duration<double> time_elapsed;
    int instructions;
    int decrement_amount;

    while(1){
        curr = steady_clock::now();
        time_elapsed = curr - prev;
        if (time_elapsed.count() > cycleDelay){
            instructions = time_elapsed.count() * 700;
            std::cout << "time elapsed: " << time_elapsed.count() << std::endl; 
            std::cout << "instructions: " << instructions << std::endl;
            for (int i = 0; i < instructions; i++){
                chip8.cycle();

            }
            curr = steady_clock::now();
            time_elapsed = curr - prev;
            decrement_amount = time_elapsed.count() * 60.0;
            std::cout << "decrement count by: " << decrement_amount << std::endl;
            for (int i = 0; i < decrement_amount; i++){
                chip8.timer();
            }

            prev = curr;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

