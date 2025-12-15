#include "keyboard.hpp"

void handleKeyDown(SDL_KeyboardEvent& key){
//    std::cout << "keyboard stroke detected: " << SDL_GetKeyName(key.keysym.sym);
    switch(key.keysym.scancode){
        case SDL_SCANCODE_1: // 1
            
            keys[0x1] = 1;
            break;
        case SDL_SCANCODE_2: // 2
            
            keys[0x2] = 1;
            break;
        case SDL_SCANCODE_3:
            keys[0x3] = 1;

            break;
        case SDL_SCANCODE_4:
            keys[0xC] = 1;

            break;
        case SDL_SCANCODE_Q:
            keys[0x4] = 1;

            break;

        case SDL_SCANCODE_W:
            keys[0x5] = 1;

            break;

        case SDL_SCANCODE_E:
            keys[0x6] = 1;

            break;
        case SDL_SCANCODE_R:
            keys[0xD] = 1;

            break;

        case SDL_SCANCODE_A:
            keys[0x7] = 1;

            break;
        case SDL_SCANCODE_S:

            keys[0x8] = 1;
            break;

        case SDL_SCANCODE_D:
            keys[0x9] = 1;

            break;
        case SDL_SCANCODE_F:
            keys[0xE] = 1;

            break;

        case SDL_SCANCODE_Z:
            keys[0xA] = 1;

            break;
        case SDL_SCANCODE_X:
            keys[0x0] = 1;

            break;
        case SDL_SCANCODE_C:
            keys[0xB] = 1;

            break;
        case SDL_SCANCODE_V:
            keys[0xF] = 1;

            break;
    }
}

void handleKeyUp(SDL_KeyboardEvent& key){
//    std::cout << "keyboard stroke detected: " << SDL_GetKeyName(key.keysym.sym);
    switch(key.keysym.scancode){


        case SDL_SCANCODE_1: // 1

            keys[0x1] = 0;
            break;
        case SDL_SCANCODE_2: // 2

            keys[0x2] = 0;
            break;
        case SDL_SCANCODE_3:
            keys[0x3] = 0;

            break;
        case SDL_SCANCODE_4:
            keys[0xC] = 0;

            break;
        case SDL_SCANCODE_Q:
            keys[0x4] = 0;

            break;

        case SDL_SCANCODE_W:
            keys[0x5] = 0;

            break;

        case SDL_SCANCODE_E:
            keys[0x6] = 0;

            break;
        case SDL_SCANCODE_R:
            keys[0xD] = 0;

            break;

        case SDL_SCANCODE_A:
            keys[0x7] = 0;

            break;
        case SDL_SCANCODE_S:

            keys[0x8] = 0;
            break;

        case SDL_SCANCODE_D:
            keys[0x9] = 0;

            break;
        case SDL_SCANCODE_F:
            keys[0xE] = 0;

            break;

        case SDL_SCANCODE_Z:
            keys[0xA] = 0;

            break;
        case SDL_SCANCODE_X:
            keys[0x0] = 0;

            break;
        case SDL_SCANCODE_C:
            keys[0xB] = 0;

            break;
        case SDL_SCANCODE_V:
            keys[0xF] = 0;

            break;
    }
}
