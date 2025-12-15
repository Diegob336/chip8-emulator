#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL2/SDL.h>
#include <iostream>

inline uint8_t keys[16];
void handleKeyDown(SDL_KeyboardEvent& key);
void handleKeyUp(SDL_KeyboardEvent& key);

#endif

