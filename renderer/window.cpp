#include <iostream>
#include <SDL2/SDL.h>

int main(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout << "Failed to init SDL2 lib\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);

    if(!window){
        std::cout << "Failed to create window";
        return -1;
    }

    SDL_Surface *window_Surface = SDL_GetWindowSurface(window);

    if(!window_Surface){
        std::cout << "Failed to get window surface";
        return -1;
    }

    SDL_Surface *image = SDL_LoadBMP("RAY.BMP");

    if(!image){
        std::cout << "Image couldn't be opened";
        return -1;
    }

    bool keep_window_open = true;

    while (keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e)>0){
            switch (e.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            
            default:
                break;
            }

            SDL_BlitSurface(image, NULL, window_Surface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }
    

}