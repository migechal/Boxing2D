//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_WINDOWMANAGER_H
#define BOXING2D_2_WINDOWMANAGER_H
#include <SDL2/SDL.h>
#include <string>
#include "Types.h"

class WindowManager {
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
public:
    int update();
    WindowManager(std::string windowName, type::Vector2i p_size, type::Vector2i p_pos, Uint32 p_flag);
};


#endif //BOXING2D_2_WINDOWMANAGER_H
