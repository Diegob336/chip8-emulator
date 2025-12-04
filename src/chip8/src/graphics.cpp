#include "graphics.hpp"

void createWindow(SDL_Window *&win, SDL_Surface *&winSurface){

    win = SDL_CreateWindow("Window", 100, 100, 64, 32, SDL_WINDOW_RESIZABLE);
    if (!win){
        std::cout << "failed to create window: " << SDL_GetError() << std::endl; 
    }

    winSurface = SDL_GetWindowSurface(win);

}

void draw(SDL_Window *win, SDL_Surface *winSurface, uint8_t display[32][64]){ 
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 64; j++){
            if (display[i][j] == 1) {
                SDL_Rect rect;
                rect.x = j;
                rect.y = i;
                rect.h = 1;
                rect.w = 1;
                SDL_FillRect(winSurface, &rect, SDL_MapRGB(winSurface->format, 255,255, 255));
            }
        }
    }
    SDL_UpdateWindowSurface(win);
}
