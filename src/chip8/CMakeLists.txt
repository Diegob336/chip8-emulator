add_library(chip8-core 
    src/cpu.cpp
)

target_include_directories(chip8-core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
