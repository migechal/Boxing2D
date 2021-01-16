#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
namespace loading
{
    class SplashScreen
    {
        static int progress;
        int max;
        SDL_Surface* screen_;
        SDL_Rect pos;
        bool isMax();
        void drawText(int fontSize, std::string text, SDL_Color color);
        void drawBar();

    public:
        SplashScreen(SDL_Surface* screen, int maximum);
        ~SplashScreen();
        void drawSplash(SDL_Surface* file, std::string message, SDL_Color messageColor);
    };



    class Font
    {
        TTF_Font *font;
        SDL_Surface* loadText(std::string text, SDL_Color textColor);
    public:
        Font(std::string fontName, int fontSize);
        ~Font();
        void renderText(std::string text, SDL_Color textColor, SDL_Surface* screen, SDL_Rect* pos);
    };
}