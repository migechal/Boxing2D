#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
using namespace std;
struct Point2D {
  int x, y;
};
void createrect(SDL_Rect &Player1pos, SDL_Rect &Player2pos);
void getSettings(Point2D &windowsize, string path);
SDL_Surface *BMPloader(string file);
Mix_Music *loadMusic(string file);
int mainmenu(SDL_Window *window, SDL_Surface *screen, string path);
int settings(SDL_Window *window, SDL_Surface *screen, string path);