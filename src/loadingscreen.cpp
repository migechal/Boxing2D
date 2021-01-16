#include "headers/loadingscreen.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

loading::SplashScreen::SplashScreen(SDL_Surface* screen, int maximum){
    max = maximum;
    screen_ = screen;
    progress = -1;
}

loading::SplashScreen::~SplashScreen(){
    SDL_FreeSurface(screen_);
}


bool loading::SplashScreen::isMax(){
    return progress == max;
}

void loading::SplashScreen::drawText(int fontSize, std::string text, SDL_Color color){
    pos.x = 0;
    pos.h = fontSize;
    pos.y = 1920 - (fontSize + 20);
    pos.w = 100;
    Font font("Sans.ttf", fontSize);
    font.renderText(text, color, screen_, &pos);
}

void loading::SplashScreen::drawSplash(SDL_Surface* file, std::string message, SDL_Color messageColor){
    SDL_BlitSurface(file, NULL, screen_, NULL);
    drawText(28, message, messageColor);
    drawBar();
}

void loading::SplashScreen::drawBar(){

/// TOMORROW


}



loading::Font::Font(std::string fontName, int fontSize){
    font = TTF_OpenFont(fontName.c_str(), fontSize);
}

loading::Font::~Font(){
    free(font);
}

SDL_Surface* loading::Font::loadText(std::string text, SDL_Color textColor){
    return TTF_RenderText_Solid(font, text.c_str(), textColor);
}

void loading::Font::renderText(std::string text, SDL_Color textColor, SDL_Surface* screen, SDL_Rect* pos){
    SDL_BlitSurface(loadText(text, textColor), NULL, screen, pos);
}