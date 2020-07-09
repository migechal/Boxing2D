#include <SDL2/SDL.h>
#include <bits/stdc++.h>

#include <fstream>
using namespace std;
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
  ifstream config;
  config.open("settings/config.txt");
  config >> windowsize.x >> windowsize.y;
  cout << windowsize.x << endl << windowsize.y << endl;
  config.close();
}
bool BMPloader(SDL_Surface *Image, char file[]) {
  Image = SDL_LoadBMP(file);
  if (Image = nullptr) {
    cout << "Err: '" << Image
         << "' could not be loaded. (Check if correct path)" << endl
         << "Shutdown? (y/n):   " << flush;
    char q = NULL;
    cin >> q;
    if (q == 'y') {
      cout << endl << "Bye!" << endl;
      return false;
    }
  }
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
                            SDL_WINDOW_OPENGL);
  CHECK_RESULT(window != nullptr);

  SDL_Surface *screen = SDL_GetWindowSurface(window);
  SDL_Surface *background = SDL_LoadBMP("assets/Ring.bmp");
  CHECK_RESULT(background != nullptr);
  SDL_Surface *player1F1 = SDL_LoadBMP("assets/BLUE/Idle/Blue_Idle-0.bmp");
  SDL_Surface *player1F2 =
      SDL_LoadBMP("assets/BLUE/PunchRight/Blue-Punch-Right-3.bmp");
  SDL_Surface *player1F3 = SDL_LoadBMP("assets/BLUE/");
  SDL_Surface *player1F4 = SDL_LoadBMP("assets/BLUE/");
  SDL_Surface *player1KO = SDL_LoadBMP("assets/BLUE");
  SDL_Surface *player2F1 = SDL_LoadBMP("assets/RED/Idle/Red_Idle-0.bmp");
  SDL_Surface *player2F2 =
      SDL_LoadBMP("assets/RED/PunchRight/Red_Blocking-3.bmp");
  SDL_Surface *player2F3 = SDL_LoadBMP("assets/RED");
  SDL_Surface *player2F4 = SDL_LoadBMP("assets/RED");
  SDL_Surface *player2KO = SDL_LoadBMP("assets/RED");
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
            p1action = 0;
            leftBut = true;
            break;
          case SDL_SCANCODE_RIGHT:
            p1action = 0;
            rightBut = true;
            break;
          case SDL_SCANCODE_RCTRL:
            p1action = 1;
            break;
        }
      }
      if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_LEFT:
            leftBut = false;
            break;
          case SDL_SCANCODE_RIGHT:
            rightBut = false;
            break;
        }
      }
      //
      // UPDATE PLAYER 1 POS
      //
      if (rightBut) {
        right += 10;
      }
      if (leftBut) {
        left += 10;
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
        case 1:
          CHECK_RESULT(!SDL_BlitSurface(player1F2, NULL, screen, &Player1pos));
      }
      CHECK_RESULT(!SDL_UpdateWindowSurface(window));
    }
  }
}