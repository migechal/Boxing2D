#define IMGUI_IMPLEMENTATION
#include "imgui/imgui.h"

#include "imgui/imgui_impl_sdl.h"

#ifdef IMGUI_IMPLEMENTATION

#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"
#endif

#include "headers/menu.h"
#include "headers/loading.h"
#include <iostream>
#include <string>

#define CHECK_RESULT(fnc)                                                   \
  {                                                                         \
    auto res = fnc;                                                         \
    if (!res)                                                               \
    {                                                                       \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                << std::endl;                                               \
      exit(-2);                                                             \
    }                                                                       \
  }


int MainMenu::printMenu(std::string menuSurfaceLocation)
{
    menuSurface = loading::BMPloader(menuSurfaceLocation);
    CHECK_RESULT(menuSurface);
    int ret = SDL_BlitSurface(menuSurface, NULL, screen, NULL);
    SDL_FreeSurface(menuSurface);
    return ret;
}

void SettingsMenu::menuAction(SDL_Window* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForD3D(window);
    bool running = true;
    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT || (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window)))
            {
                running = false;
            }
        }
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        ImGui::Begin("Settings");
        ImGui::SliderFloat3("FPS(Frames Per Second)", &this->sliderSpeed, 0.0F, 20.0F);
        ImGui::End();
        ImGui::Render();
    }
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

Click::Click(SDL_Event &event)
{
    e = event;
}

void Click::getClick()
{
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&this->clickDst.x, &this->clickDst.y);
        }
    }
}

SDL_Rect Click::getClickPos()
{
    getClick();
    return clickDst;
}

void Quit::menuAction(SDL_Window* window)
{
    SDL_Quit();
    SDL_DestroyWindow(window);
}

void Play::menuAction(bool &playing)
{
    playing = true;
}