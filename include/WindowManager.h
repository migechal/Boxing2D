//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_WINDOWMANAGER_H
#define BOXING2D_2_WINDOWMANAGER_H
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include "Types.h"

class WindowManager {
    std::unique_ptr<SDL_Window> m_window;
    std::unique_ptr<SDL_Renderer> m_renderer;
    std::unique_ptr<SDL_Texture> m_bkg;

    SDL_Event m_event{};
    type::Vector2i m_size;

    bool hasQuit();


    type::Vector2i getMonitorSize();

public:

    SDL_Renderer* getRenderer();

    type::Vector2i getSize();
    void setBackground(SDL_Texture* background);
    int draw(SDL_Texture* txt, const SDL_Rect* src, const SDL_Rect* dst);
    bool update();
    WindowManager(const std::string& windowName, type::Vector2i p_pos, Uint32 p_flag);

};


#endif //BOXING2D_2_WINDOWMANAGER_H
