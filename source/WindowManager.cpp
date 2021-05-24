//
// Created by mikhail on 5/20/21.
//

#include "../include/WindowManager.h"
#include <SDL2/SDL.h>

WindowManager::WindowManager(const std::string& windowName, type::Vector2i p_size, type::Vector2i p_pos, Uint32 p_flag) {
    SDL_Log("Created Window");

    m_window = SDL_CreateWindow(windowName.c_str(), p_pos.x, p_pos.y, p_size.x, p_size.y, p_flag);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_window == nullptr){
        SDL_Log("Error! Window is null");
    }
}

bool WindowManager::hasQuit(){
    while(SDL_PollEvent(&m_event)){
        if (m_event.type == SDL_QUIT) {

            return true;

        }
        if(m_event.type == SDL_KEYDOWN){
            if(m_event.key.keysym.sym == SDLK_ESCAPE){
                return true;
            }
        }
    }
    return false;
}

bool WindowManager::update(){
    SDL_RenderPresent(m_renderer);
    return hasQuit();
}

type::Vector2i WindowManager::getMonitorSize(){
    SDL_DisplayMode t_dm;
    SDL_GetCurrentDisplayMode(0, &t_dm);
    return {t_dm.w, t_dm.h};
}
