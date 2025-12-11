#include <SDL2/SDL.h>
#include <iostream>

void createWindow(SDL_Window *&win, SDL_Surface *&winSurface);
void draw(SDL_Window *win, SDL_Surface *winSurface, uint8_t display[32][64]); 
