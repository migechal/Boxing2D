#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#define CHECK_RESULT(fnc)                                                   \
  {                                                                         \
    auto res = fnc;                                                         \
    if (!res) {                                                             \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                << std::endl;                                               \
      exit(-1);                                                             \
    }                                                                       \
  }

using namespace std;
struct Point2D {
  int x;
  int y;
};
void createrect(SDL_Rect &Player1pos, SDL_Rect &Player2pos) {
  //! Player 1 position
  Player1pos.x = 0;
  Player1pos.y = 600;
  //! Player 2 position
  Player2pos.x = 1400;
  Player2pos.y = 600;
}
void getSettings(Point2D &windowsize, string path) {
  namespace pt = boost::property_tree;
  pt::ptree loadPtreeRoot;
  pt::read_json(path, loadPtreeRoot);
  pt::ptree temp;
  pt::ptree tsizex;
  pt::ptree tsizey;
  pt::ptree ttype;
  string type;
  //! Get child of file
  temp = loadPtreeRoot.get_child("Screen");
  tsizex = temp.get_child("Resolution x");
  tsizey = temp.get_child("Resolution y");
  ttype = temp.get_child("Type");
  windowsize.x = tsizex.get_value<int>();
  windowsize.y = tsizey.get_value<int>();
  type = ttype.get_value<string>();
}
SDL_Surface *BMPloader(string file) {
  // SDL_Log(file.c_str(), " Has been loaded successfullys.");
  SDL_Surface *bp = SDL_LoadBMP(file.c_str());
  CHECK_RESULT(bp);
  return bp;
}
// Mix_Music *loadMusic(string file) {
//   // Load Music
//   Mix_Music *lm = Mix_LoadMUS(file.c_str());
//   CHECK_RESULT(lm);
//   return lm;
// }
int mainmenu(SDL_Window *window, SDL_Surface *screen, string path) {
  bool running = true;
  SDL_Surface *MM = BMPloader(path + "assets/MainMenu.bmp");
  SDL_Event e;
  CHECK_RESULT(!SDL_BlitSurface(MM, NULL, screen, NULL));
  CHECK_RESULT(!SDL_UpdateWindowSurface(window));
  int x, y;
  while (running) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        exit(0);
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&x, &y);
        // cout << "x:  " << x << "   y:  " << y << endl;
        if (x > 502 && x < 1436 && y > 168 && y < 284) {
          return 0;
        } else if (x < 1439 && x > 500 && y < 437 && y > 317) {
          return 1;
        }
      }
    }
  }
  return -1;
}
int settings(SDL_Window *window, SDL_Surface *screen, string path) {
  bool running = true;
  SDL_Event e;
  SDL_Surface *SM = BMPloader(path + "assets/Settings.bmp");
  Point2D mouse;
  SDL_BlitSurface(SM, NULL, screen, NULL);
  SDL_UpdateWindowSurface(window);
  while (running) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        exit(0);
      }

      if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        // cout << "x:  " << mouse.x << "   y:  " << mouse.y << endl;
      }
    }
  }
  return 0;
}