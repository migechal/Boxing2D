#pragma once
#include <SDL2/SDL.h>
#include <string>
struct Button{
    int startx, starty, endx, endy;
};

class MainMenu{
    SDL_Surface* menuSurface;
    SDL_Surface* screen;
public:
    MainMenu();
    virtual ~MainMenu();
    virtual int printMenu(std::string menuSurfaceLocation) = 0;
    virtual void menuAction() = 0;
protected:
    float sliderSpeed = 1.00;
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
    int printMenu(std::string menuSurfaceLocation) override;
};

