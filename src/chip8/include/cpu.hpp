#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>
#include <stack>
#include <fstream>
#include <filesystem>
#include "opcodes.hpp"
#include "graphics.hpp"
#include <chrono>
#include <thread>
#include "keyboard.hpp"

constexpr int GRID_SIZE = 64 * 32;
constexpr int FONT_SIZE = 80;
constexpr int FONT_ADDR = 0x50;

inline const uint8_t Fonts[FONT_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F

};

class cpu {

public:
    cpu(): memory{},
        stack{},
        pc(0x200),
        sp{},
        I{},
        V{}, 
        op{},
        delay_timer{},
        sound_timer{},
        display{}
    {
        load_fonts();
        SDL_Init(SDL_INIT_EVERYTHING);
        createWindow(win, winSurface);
    }

    int load_rom(const std::string& file_path, int size);
    void load_fonts();
    void cycle();
    void decode();
    void reset();
    void op_add();
    void op_set();
    void op_setI();
    void op_clear();
    void op_jump();
    void op_display();
    void op_sub_return();
    void op_sub_call();
    void timer();
    void print();
private:
    uint8_t memory[4096];
    uint16_t stack[8];
    uint8_t sp;
    uint16_t pc;
    uint16_t I;
    uint8_t V[16];
    opcode op;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[32][64];
    SDL_Window *win;
    SDL_Surface *winSurface;
};

#endif
