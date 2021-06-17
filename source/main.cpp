//
// Created by mikhail on 5/20/21.
//
#include "../include/ResourceLoader.h"
#include "../include/Game.h"
#include "../include/WindowManager.h"
#include "../include/Types.h"
#include "../include/Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_JPG);

    WindowManager window("Boxing", type::Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), SDL_WINDOW_SHOWN);
    window.setBackground(
            ResourceLoader::getInstance()->loadTexture(std::string("../assets/Ring.jpg"), window.getRenderer()));

    auto *Blue = new Player("blue", &window);
    auto *Red = new Player("red", &window);

    bool done = false;

    while (!done) {
        if (window.update()) {
            done = true;
        }
        Blue->update();
        Red->update();
    }

    return 0;
}
