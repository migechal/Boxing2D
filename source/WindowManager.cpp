//
// Created by mikhail on 5/20/21.
//

#include "../include/WindowManager.h"
#include "../include/Types.h"
#include <SDL2/SDL.h>
#include <iostream>
WindowManager::WindowManager(const std::string& windowName, type::Vector2i p_pos, Uint32 p_flag) :
    m_bkg(nullptr), m_size(type::Vector2i(1920, 1080))
{
    SDL_Log("Created Window");
    m_window = SDL_CreateWindow(windowName.c_str(), p_pos.x, p_pos.y, m_size.x, m_size.y, p_flag);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_window == nullptr){
        SDL_Log("Error! Window is null");
    }
}

type::Vector2i WindowManager::getSize(){
    return m_size;
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

int WindowManager::draw(SDL_Texture* txt, const SDL_Rect* src, const SDL_Rect* dst){
    return SDL_RenderCopy(m_renderer, txt, src, dst);
}

bool WindowManager::update(){
    SDL_RenderPresent(m_renderer);
    if(m_bkg != nullptr){
        if(draw(m_bkg, NULL, NULL) != 0){
            std::cout << SDL_GetError() << std::endl;
        }
    }
    return hasQuit();
}

type::Vector2i WindowManager::getMonitorSize(){
    SDL_DisplayMode t_dm;
    SDL_GetCurrentDisplayMode(0, &t_dm);
    return {t_dm.w, t_dm.h};
}

void WindowManager::setBackground(SDL_Texture* background){
    m_bkg = background;
}

SDL_Renderer* WindowManager::getRenderer(){
    return m_renderer;
}
