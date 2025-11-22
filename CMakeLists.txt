cmake_minimum_required(VERSION 3.16)

project(chip8-emulator LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/chip8)

add_executable(chip8 
    src/main.cpp
)

target_link_libraries(chip8 PRIVATE chip8-core)



