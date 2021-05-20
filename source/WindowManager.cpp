//
// Created by mikhail on 5/20/21.
//

#include "WindowManager.h"
#include <SDL2/SDL.h>

WindowManager::WindowManager(std::string windowName, type::Vector2i p_size, type::Vector2i p_pos, Uint32 p_flag) {
    m_window = SDL_CreateWindow(windowName.c_str(), p_pos.x, p_pos.y, p_size.x, p_size.y, p_flag);
}
