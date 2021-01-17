#include <SDL2/SDL.h>
#include <string>
struct Button{
    int startx, starty, endx, endy;
};

class MainMenu{
    SDL_Surface* menuSurface;
    SDL_Surface* screen;
public:
    MainMenu(std::string menuSurfaceLocation, SDL_Window* window, SDL_Surface* screen);
    virtual ~MainMenu();
    int printMenu();
    virtual void menuAction() const = 0;
protected:
    float sliderSpeed = 1.00;
    SDL_Window* window;
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
    virtual void menuAction();
};

class Quit : public MainMenu{
public:
    virtual void menuAction();
};