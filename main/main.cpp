#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#define TPP 0.
using namespace std;
#define movment 10
#define playerw
#define CHECK_RESULT(fnc)                                                   \
  {                                                                         \
    auto res = fnc;                                                         \
    if (!res) {                                                             \
      std::cout << "ERR: " << __FILE__ << "(" << __LINE__ << ") SDL_Error(" \
                << SDL_GetError() << ")  err: " << res << " in " << #fnc    \
                << std::endl;                                               \
      exit(res);                                                            \
    }                                                                       \
  }
struct Point2D {
  int x;
  int y;
};
const Uint32 MaxFPS = 60;
const Uint32 FrameTime = (1000.0 / MaxFPS);
bool leftBut = false;
bool rightBut = false;
int p1action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
int p2action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
SDL_Rect Player1pos;
SDL_Rect Player2pos;
time_t timerS;
time_t p1p;
void starttimeSD() { timerS = 0; }
int gettimeSD() { return time(&timerS); }
void createrect() {
  // Player 1 position
  Player1pos.x = 0;
  Player1pos.y = 600;
  // Player 2 position
  Player2pos.x = 1400;
  Player2pos.y = 600;
}
void getSettings(Point2D &windowsize) {
  namespace pt = boost::property_tree;
  pt::ptree loadPtreeRoot;
  pt::read_json("settings/config.json", loadPtreeRoot);
  pt::ptree temp;
  pt::ptree tsizex;
  pt::ptree tsizey;
  pt::ptree ttype;
  string type;
  // Get child of file
  temp = loadPtreeRoot.get_child("Screen");
  tsizex = temp.get_child("Resolution x");
  tsizey = temp.get_child("Resolution y");
  ttype = temp.get_child("Type");
  windowsize.x = tsizex.get_value<int>();
  windowsize.y = tsizey.get_value<int>();
  type = ttype.get_value<string>();
}
SDL_Surface *BMPloader(string file) {
  cout << file << endl;
  return SDL_LoadBMP(file.c_str());
}
int main() {
  int right = 0;
  int left = 0;
  Point2D windowSize;
  getSettings(windowSize);
  CHECK_RESULT(!SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window = nullptr;
  window = SDL_CreateWindow("GG Boxing", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y,
                            SDL_WINDOW_SHOWN);
  CHECK_RESULT(window != nullptr);

  SDL_Surface *screen = SDL_GetWindowSurface(window);
  SDL_Surface *background = BMPloader("assets/Ring.bmp");
  SDL_Surface *player1F1 = BMPloader("assets/BLUE/Idle/Blue_Idle-0.bmp");
  SDL_Surface *player1F2 =
      BMPloader("assets/BLUE/PunchRight/Blue-Punch-Right-3.bmp");
  SDL_Surface *player1F3 = BMPloader("assets/BLUE/");
  SDL_Surface *player1F4 = BMPloader("assets/BLUE/");
  SDL_Surface *player1KO = BMPloader("assets/BLUE/");
  SDL_Surface *player2F1 = BMPloader("assets/RED/Idle/Red_Idle-0.bmp");
  SDL_Surface *player2F2 =
      BMPloader("assets/RED/PunchRight/Red_Blocking-3.bmp");
  SDL_Surface *player2F3 = BMPloader("assets/RED");
  SDL_Surface *player2F4 = BMPloader("assets/RED");
  SDL_Surface *player2KO = BMPloader("assets/RED");
  bool running = true;
  createrect();
  while (running) {
    SDL_Event e;
    auto startFrameTime = SDL_GetTicks();
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
        starttimeSD();
        break;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_LEFT:
            leftBut = true;
            break;
          case SDL_SCANCODE_RIGHT:
            rightBut = true;
            break;
          case SDL_SCANCODE_RCTRL:
            p1action = 1;
            p1p = 0;
            break;
        }
      }
      // Player 1
      switch (e.key.keysym.scancode) {
        // Player 1
        case SDL_SCANCODE_LEFT:
          leftBut = false;
          break;
        case SDL_SCANCODE_RIGHT:
          rightBut = false;
          break;
          //
          // Player 2
      }
    }
    //
    // UPDATE PLAYER 1 POS
    //
    if (rightBut) {
      if (Player1pos.x + movment < Player2pos.x) {
        right += movment;
      }
    }
    if (leftBut) {
      if (Player1pos.x - movment >= 50) {
        left += movment;
      }
    }
    Player1pos.x += right - left;
    left = 0;
    right = 0;
    //
    // DRAW
    //
    CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
    switch (p1action) {
      case 0:
        CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
        break;
      case 1:
        CHECK_RESULT(!SDL_BlitSurface(player1F2, NULL, screen, &Player1pos));
        break;
    }
    CHECK_RESULT(!SDL_UpdateWindowSurface(window));
    // Check for player state
    if (p1p = 50000000) {
      p1action = 0;
    }
    // End Frame Delay
    auto frameDuration = (SDL_GetTicks() - startFrameTime);
    if (frameDuration < FrameTime) {
      cout << FrameTime - frameDuration << endl;
      SDL_Delay(FrameTime - frameDuration);
    }
  }
}
std::cout << "Out of Game Loop" << std::endl;
std::cout << gettimeSD() / 100000000 << " millisecond shutdown" << std::endl;
}