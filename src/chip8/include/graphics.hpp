#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>

void createWindow(SDL_Window *&win, SDL_Surface *&winSurface);
void draw(SDL_Window *win, SDL_Surface *winSurface, uint8_t display[64][32]); 
