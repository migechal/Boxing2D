//
// Created by mikhail on 5/20/21.
//

#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(){
    SDL_Window* window = SDL_CreateWindow("Hello", 100, 100, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN);
    std::cout << "Hello World!" << std::endl;
    return 0;
}