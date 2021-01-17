#include "headers/loading.h"
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
#define CHECK_RESULT(fnc)                                                         \
    {                                                                             \
        auto res = fnc;                                                           \
        if (!res)                                                                 \
        {                                                                         \
            std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                      << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                      << std::endl;                                               \
            exit(-2);                                                             \
        }                                                                         \
    }

std::string loading::GetResourcePath(std::string applicationPath)
{
    auto envResourcePath = getenv("PATH_TO_BOXING2D_RESOURCES");
    std::cout << "envResourcePath:  " << (envResourcePath ? envResourcePath : "NULL")
              << std::endl;
    if (envResourcePath != nullptr)
    {
        applicationPath.assign(envResourcePath);
        if (applicationPath.back() != '/')
        {
            applicationPath += "/";
        }
    }
    else
    {
        while (applicationPath.back() != '/')
        {
            applicationPath.pop_back();
        }
    }
    return applicationPath + "";
}

loading::SplashScreen::SplashScreen(SDL_Surface *screen, int maximum, int width, int hight, SDL_Surface *SplashScreenFile)
{
    max = maximum;
    screen_ = screen;
    progress = -1;
    windowHight = hight;
    windowWidth = width;
    scale = windowWidth / max;
    file = SplashScreenFile;
}

loading::SplashScreen::~SplashScreen()
{
    SDL_FreeSurface(screen_);
}

bool loading::SplashScreen::isMax()
{
    return progress == max;
}
SDL_Surface *loading::BMPloader(std::string file)
{
    SDL_Log(file.c_str(), " Has been loaded successfullys.");
    SDL_Surface *bp = SDL_LoadBMP(file.c_str());
    CHECK_RESULT(bp);
    return bp;
}

void loading::SplashScreen::drawText(int fontSize, std::string text, SDL_Color color)
{
    pos.x = 0;
    pos.h = fontSize;
    pos.y = windowWidth - (fontSize + 20);
    pos.w = 100;
    Font font("Sans.ttf", fontSize);
    font.renderText(text, color, screen_, &pos);
}

void loading::SplashScreen::drawSplash(std::string message, SDL_Color messageColor)
{
    SDL_BlitSurface(file, NULL, screen_, NULL);
    drawText(28, message, messageColor);
    drawBar();
}

void loading::SplashScreen::drawBar()
{
    SDL_Surface *loading = SDL_CreateRGBSurface(0, ++progress * scale, 25, 32, 0, 11, 172, 0);
    SDL_Rect pos;
    pos.x = 0;
    pos.y = windowHight - 25;
    SDL_BlitSurface(loading, NULL, screen_, &pos);
}

loading::Font::Font(std::string fontName, int fontSize)
{
    font = TTF_OpenFont(fontName.c_str(), fontSize);
}

loading::Font::~Font()
{
    free(font);
}

SDL_Surface *loading::Font::loadText(std::string text, SDL_Color textColor)
{
    return TTF_RenderText_Solid(font, text.c_str(), textColor);
}

void loading::Font::renderText(std::string text, SDL_Color textColor, SDL_Surface *screen, SDL_Rect *pos)
{
    SDL_BlitSurface(loadText(text, textColor), NULL, screen, pos);
}