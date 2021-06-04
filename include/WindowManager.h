//
// Created by mikhail on 5/20/21.
//

#ifndef BOXING2D_2_WINDOWMANAGER_H
#define BOXING2D_2_WINDOWMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <memory>
#include "Types.h"
struct SDLWindowDestroyer
{
    void operator()(SDL_Window *w) const
    {
        SDL_DestroyWindow(w);
    }
};
struct SDLRendererDestroyer
{
    void operator()(SDL_Renderer *w) const
    {
        SDL_DestroyRenderer(w);
    }
};

struct SDLTextureDestroyer
{
    void operator()(SDL_Texture *w) const
    {
        SDL_DestroyTexture(w);
    }
};

class WindowManager
{
    std::unique_ptr<SDL_Window, SDLWindowDestroyer> m_window;
    std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> m_renderer;
    std::unique_ptr<SDL_Texture, SDLTextureDestroyer> m_bkg;

    SDL_Event m_event{};
    type::Vector2i m_size;

    bool hasQuit();

    type::Vector2i getMonitorSize();

public:
    SDL_Renderer *getRenderer();

    type::Vector2i getSize();
    void setBackground(SDL_Texture *background);
    int draw(SDL_Texture *txt, const SDL_Rect *src, const SDL_Rect *dst);
    bool update();
    WindowManager(std::string windowName, type::Vector2i p_pos, Uint32 p_flag);
};

#endif //BOXING2D_2_WINDOWMANAGER_H
