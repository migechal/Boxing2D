#include "headers/gamebase.h"
#include "headers/debugmodule.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

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

GameBase::GameBase(SDL_Surface *background, SDL_Surface *screen, SDL_Window *Window, int DefaultHP)
{
    background_ = background;
    screen_ = screen;
    defHp = DefaultHP;
    window = Window;
}
bool GameBase::checkBlock(Player &player)
{
    std::cout << player.color << " block  " << player.block << std::endl;
    return player.block;
}
void GameBase::updateWindow()
{
    CHECK_RESULT(!SDL_UpdateWindowSurface(window));
}
void GameBase::printKO(Player KOd, Player KOer)
{
    for (int i = 0; i != 9; i++)
    {
        updateWindow();
        clearScreen();
        PrintPlayer(KOer, 1);
        CHECK_RESULT(!SDL_BlitSurface(KOd.KOP[i], NULL, screen_, &KOd.pos));
        SDL_Delay(60);
    }
}

void GameBase::clearTerm(int lines)
{
    for (int i = 0; i < lines; i++)
    {
        std::cout << std::endl;
    }
}
void GameBase::drawHPBar(char direction, int x, int y, int hp, Uint8 r, Uint8 g, Uint8 b, int scaleBar)
{
    SDL_Rect HealthBar;
    SDL_Rect bgrd;
    SDL_Surface *HP = SDL_CreateRGBSurface(0, hp * scaleBar, hight, 32, 0, 0, 0, 0);
    SDL_Surface *Outline = SDL_CreateRGBSurface(0, defHp * scaleBar + 10, hight + 10, 32, 0, 0, 0, 0);
    CHECK_RESULT(HP);
    CHECK_RESULT(Outline);
    int offset = 0;
    switch (direction)
    {
    case 'R':
        offset = (defHp - hp) * scaleBar;
        break;
    case 'L':
        offset = 0;
        break;
    default:
        break;
    }
    bgrd.x = x - 5;
    bgrd.y = y - 5;
    HealthBar.x = x - 5 + offset;
    HealthBar.y = y;
    SDL_FillRect(HP, NULL, SDL_MapRGB(HP->format, r, g, b));
    CHECK_RESULT(!SDL_BlitSurface(Outline, NULL, screen_, &bgrd));
    CHECK_RESULT(!SDL_BlitSurface(HP, NULL, screen_, &HealthBar));
}
void GameBase::clearScreen()
{
    CHECK_RESULT(!SDL_BlitSurface(background_, NULL, screen_, NULL));
}
void GameBase::updateScreen() { updateWindow(); }
void GameBase::PrintPlayer(Player player, int F)
{
    DebugMode DBM;
    switch (F)
    {
    case 1:
        SDL_BlitSurface(player.F1, NULL, screen_, &player.pos);
        break;
    case 2:
        SDL_BlitSurface(player.F2, NULL, screen_, &player.pos);
        break;
    case 3:
        SDL_BlitSurface(player.F3, NULL, screen_, &player.pos);
        break;
    case 4:
        printKO(player, KOer);
        break;
    default:
        DBM.printMSG("Invalid case");
    }
}
int GameBase::decreaseHP(Player &playerHit, Player &playerHitting)
{
    if (checkBlock(playerHit))
    {
        playerHit.CTMG = 10;
    }
    else
    {
        playerHit.HP -= playerHitting.CTMG;
    }
    return playerHit.HP;
}

void GameBase::changeKOer(Player player) { KOer = player; }