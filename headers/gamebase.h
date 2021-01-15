#pragma once
#include "player.h"
#include <SDL2/SDL.h>
class GameBase
{
    const int hight = 10;
    int defHp;
    Player KOer;
    bool checkBlock(Player &player);

    void updateWindow();
    void printKO(Player KOd, Player KOer);
    SDL_Surface* background_, *screen_;
    SDL_Window* window;
public:
    GameBase(SDL_Surface* background, SDL_Surface* screen, SDL_Window* Window, int DefaultHP);
    void clearTerm(int lines);
    void drawHPBar(char direction, int x, int y, int hp, Uint8 r, Uint8 g, Uint8 b, int scaleBar);

    void clearScreen();
    void updateScreen();

    void PrintPlayer(Player player, int F);
    int decreaseHP(Player &playerHit, Player &playerHitting);
    void changeKOer(Player player);
};