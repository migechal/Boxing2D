#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
using namespace std;

extern Mix_Music *music;
extern SDL_Surface *screen;
extern SDL_Surface *background;
extern SDL_Surface *player1F1;
extern SDL_Surface *player1F2;
extern SDL_Surface *player1F3;
extern SDL_Surface *player2F1;
extern SDL_Surface *player2F2;
extern SDL_Surface *player2F3;
extern vector<SDL_Surface *> KOP1;
extern vector<SDL_Surface *> KOP2;
extern int leftpos;
extern int rightpos;
extern int leftpos2;
extern int rightpos2;
extern int player1hp;
extern int player2hp;
extern bool leftBut;
extern bool rightBut;
extern bool downBut;
extern bool leftBut2;
extern bool rightBut2;
extern bool downBut2;
extern int Player1Multiplier;
extern int Player2Multiplier;
extern SDL_Rect Player1pos;
extern SDL_Rect Player2pos;
extern int p1action;
extern int p2action;
extern time_t punchclock1;
extern time_t punchclock2;
extern time_t blockclock1;
extern time_t blockclock2;

struct Point2D {
  int x, y;
};
void createrect(SDL_Rect &Player1pos, SDL_Rect &Player2pos);
void getSettings(Point2D &windowsize, string path);
SDL_Surface *BMPloader(string file);
Mix_Music *loadMusic(string file);
int mainmenu(SDL_Window *window, SDL_Surface *screen, string path);
int settings(SDL_Window *window, SDL_Surface *screen, string path);
void ClearScreen();