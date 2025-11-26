#include "graphics.hpp"
#include <unistd.h>

void createWindow(){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("Window", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
    if (!win){
        std::cout << "failed to create window: " << SDL_GetError() << std::endl; 
    }

    SDL_Surface *winSurface = SDL_GetWindowSurface(win);

    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 0, 255, 255));

    SDL_UpdateWindowSurface(win);

    sleep(10);

    SDL_DestroyWindow(win);

    win = NULL;

    winSurface = NULL; 
}
