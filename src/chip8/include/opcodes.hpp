#include <stdint.h>
#include <iostream>

typedef struct {
    uint8_t nib_1;
    uint8_t nib_2;
    uint8_t nib_3;
    uint8_t nib_4;
    uint8_t sec_byte;
    uint16_t addr;
    uint16_t full_op;
}opcode;
