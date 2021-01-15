#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
struct Player
{
  std::string color;
  int HP = 100;
  int CTMG = 1;
  int PT;
  int BT;
  SDL_Surface *F1;
  SDL_Surface *F2;
  SDL_Surface *F3;
  bool ableToDoDamage;
  bool punch;
  bool block;
  SDL_Rect pos;
  std::vector<SDL_Surface *> KOP;
};