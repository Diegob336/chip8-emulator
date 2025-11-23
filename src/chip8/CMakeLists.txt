add_library(chip8-core 
    src/cpu.cpp
    src/opcodes.cpp
)

target_include_directories(chip8-core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
