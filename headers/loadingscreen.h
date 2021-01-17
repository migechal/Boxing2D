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
        int windowWidth;
        int windowHight;
        int scale;
        SDL_Surface* screen_;
        SDL_Surface* file;
        SDL_Rect pos;
        bool isMax();
        void drawText(int fontSize, std::string text, SDL_Color color);
        void drawBar();
        

    public:
        SplashScreen(SDL_Surface* screen, int maximum, int width, int hight, SDL_Surface* SplashScreenFile);
        ~SplashScreen();
        void drawSplash (std::string message, SDL_Color messageColor);
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