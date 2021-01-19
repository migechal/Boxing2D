#pragma once
#include <SDL2/SDL.h>
#include <string>
struct Button{
    int startx, starty, endx, endy;
};

class MainMenu{
public:
    MainMenu(SDL_Window* window, SDL_Surface* screen, std::string menuLocation, bool& playing);
    virtual ~MainMenu();
    virtual void menuAction() = 0;
protected:
    float sliderSpeed = 1.00;
    SDL_Window* window;
    SDL_Surface* screen;
    
    SDL_Surface* menu;
    
    bool playing;
};

class Click{
    SDL_Event e;
    SDL_Rect clickDst;
    void getClick();
public:
    Click(SDL_Event& event);
    SDL_Rect getClickPos();
};

class SettingsMenu : public MainMenu{
public:
    SettingsMenu();
    virtual void menuAction();
};

class Quit : public MainMenu{
public:
    virtual void menuAction();
};

class Play : public MainMenu{
public:
    virtual void menuAction() override;
};

class PrintMenu : public MainMenu{
public:
    virtual void menuAction() override;
};
