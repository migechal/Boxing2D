#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#define IMGUI_IMPLEMENTATION
#include "src/imgui.h"

#ifdef IMGUI_IMPLEMENTATION
#include "src/imgui.cpp"
#include "src/imgui_demo.cpp"
#include "src/imgui_draw.cpp"
#include "src/imgui_widgets.cpp"
#endif

using namespace std;

#define movment 10
#define dist 360
#define hd 5
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
//*
time_t punchclock1;
time_t blockclock1;
time_t punchclock2;
time_t blockclock2;
//*
const Uint32 MaxFPS = 60;
const Uint32 FrameTime = (1000.0 / MaxFPS);
int p2d = hd;
int p1d = hd;
bool leftBut = false;
bool rightBut = false;
bool downBut = false;
int p1action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
int p2action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
SDL_Rect Player1pos;
SDL_Rect Player2pos;
time_t timerS;
void starttimeSD() { timerS = 0; }
int gettimeSD() { return time(&timerS); }
void createrect() {
  //! Player 1 position
  Player1pos.x = 0;
  Player1pos.y = 600;
  //! Player 2 position
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
  cout << file << endl;
  return SDL_LoadBMP(file.c_str());
}
int mainmenu(SDL_Window *window, SDL_Surface *screen) {
  bool running = true;
  SDL_Event e;
  SDL_Surface *MM = BMPloader("assets/MainMenu.bmp");
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
        cout << "x:  " << x << "   y:  " << y << endl;
      }
    }
  }
  return -1;
}
void settings(SDL_Window *window, SDL_Surface *screen) {
  bool running = true;
  SDL_Event e;
  SDL_Surface *SM = BMPloader("assets/Settings.bmp");
  Point2D mouse;
  while (running) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        exit(0);
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        cout << "x:  " << mouse.x << "   y:  " << mouse.y << endl;
      }
    }
  }
}
//*
//*
//*
//*
//*
int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    cout << argv[i] << endl;
  }
  Point2D windowSize;
  getSettings(windowSize);
  CHECK_RESULT(!SDL_Init(SDL_INIT_VIDEO));
  SDL_Window *window = nullptr;
  window = SDL_CreateWindow("GG Boxing", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y,
                            SDL_WINDOW_SHOWN);
  CHECK_RESULT(window != nullptr);
  SDL_Surface *screen = SDL_GetWindowSurface(window);

  if (string(argv[1]) == "menu") {
    cout << "first" << endl;
    if (mainmenu(window, screen) == 0) {
      ;
    } else if (mainmenu(window, screen) == 1) {
    }
    //! Play button -> x:  502   y:  168 ->> x:  1436   y:  284
    //! Quit button -> x:  1439   y:  437 ->> x:  500   y:  317
    //! Settings button -> x:  503   y:  442 ->> x:  576   y:  498
  }
  SDL_Delay(10000);
  int player1hp = 100;
  int player2hp = 100;
  int right = 0;
  int left = 0;
  int right2 = 0;
  int left2 = 0;

  SDL_Surface *background = BMPloader("assets/Ring.bmp");
  SDL_Surface *player1F1 = BMPloader("assets/BLUE/Idle/Blue_Idle-0.bmp");
  SDL_Surface *player1F2 =
      BMPloader("assets/BLUE/PunchRight/Blue-Punch-Right-3.bmp");
  SDL_Surface *player1F3 = BMPloader("assets/BLUE/Blocking/Blocking.bmp");
  int f = 0;
  vector<SDL_Surface *> KOP1;
  for (; f != 9; f++) {
    string file = "assets/BLUE/KO/KO-" + to_string(f);
    KOP1.push_back(BMPloader(file + ".bmp"));
  }
  SDL_Surface *player2F1 = BMPloader("assets/RED/Idle/Red_Idle-0.bmp");
  SDL_Surface *player2F2 = BMPloader("assets/RED/PunchRight/Punch-3.bmp");
  SDL_Surface *player2F3 = BMPloader("assets/RED/Blocking/Blocking-3.bmp");
  f = 0;
  vector<SDL_Surface *> KOP2;
  for (; f != 9; f++) {
    string file = "assets/RED/KO/KO-" + to_string(f);
    KOP2.push_back(BMPloader(file + ".bmp"));
  }
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
      //
      // !player 1 animations and stuff
      //
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_LEFT:
            leftBut = true;
            break;
          case SDL_SCANCODE_RIGHT:
            rightBut = true;
            break;
          case SDL_SCANCODE_RCTRL:
            punchclock1 = 0;
            p1action = 1;
            break;
          case SDL_SCANCODE_DOWN:
            blockclock1 = 0;
            downBut = true;
            p1action = 2;
            break;
          default:
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
          case SDL_SCANCODE_DOWN:
            downBut = false;
            p1action = 0;
            break;
          default:
            break;
        }
      }
      //
      // !UPDATE PLAYER 1 POS
      //
      Player1pos.x += right - left;
      left = 0;
      right = 0;
      if (rightBut) {
        if (Player1pos.x + movment < Player2pos.x - dist) {
          right += movment;
        }
      }
      if (leftBut) {
        if (Player1pos.x - movment >= -100) {
          left += movment;
        }
      }
      // !Player 2 animations and stuff
      //
      bool leftBut2 = false;
      bool rightBut2 = false;
      bool downBut2 = false;

      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_A:
            leftBut2 = true;
            break;
          case SDL_SCANCODE_D:
            rightBut2 = true;
            break;
          case SDL_SCANCODE_LCTRL:
            p2action = 1;
            break;
          case SDL_SCANCODE_S:
            downBut2 = true;
            p2action = 2;
            break;
          default:
            break;
        }
      }
      if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_LEFT:
            leftBut2 = false;
            break;
          case SDL_SCANCODE_RIGHT:
            rightBut2 = false;
            break;
          case SDL_SCANCODE_DOWN:
            downBut2 = false;
            p2action = 0;
            break;
          default:
            break;
        }
      }
      //
      // !UPDATE PLAYER 2 POS
      //

      Player2pos.x += left2 - right2;
      left2 = 0;
      right2 = 0;
      if (leftBut2) {
        if (Player2pos.x - movment > Player1pos.x + dist) {
          left2 -= movment;
        }
      }
      if (rightBut2) {
        if (Player2pos.x - movment < 1920) {
          right2 -= movment;
        }
      }
      //
      //! Check hp
      //
      if (player1hp <= 0) {
        p1action = 3;
      }
      if (player2hp <= 0) {
        p2action = 3;
      }
      //
      // !DRAW
      //

      CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
      switch (p1action) {
        case 0:
          CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
          break;
        case 1:
          CHECK_RESULT(!SDL_BlitSurface(player1F2, NULL, screen, &Player1pos));
          if (Player1pos.x + dist + 10 >= Player2pos.x) {
            player2hp -= hd;
          }
          break;
        case 2:
          CHECK_RESULT(!SDL_BlitSurface(player1F3, NULL, screen, &Player1pos));
          break;
        case 3:
          for (int i = 0; i != 9; i++) {
            CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
            CHECK_RESULT(!SDL_BlitSurface(KOP1[i], NULL, screen, &Player1pos));
            CHECK_RESULT(
                !SDL_BlitSurface(player2F1, NULL, screen, &Player2pos));
            CHECK_RESULT(!SDL_UpdateWindowSurface(window));
            SDL_Delay(60);
          }
          SDL_Delay(1000);
          SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                   "Red Is The Winner", window);
          //
          //
          // TODO: CHANGE THIS TO GOTO TITLE SCREEN
          //
          //
          starttimeSD();
          SDL_Quit();
          exit(1);
          break;

        default:
          break;
      }

      //
      //! Draw
      //
      switch (p2action) {
        case 0:
          CHECK_RESULT(!SDL_BlitSurface(player2F1, NULL, screen, &Player2pos));
          break;
        case 1:
          CHECK_RESULT(!SDL_BlitSurface(player2F2, NULL, screen, &Player2pos));
          if (Player2pos.x - dist - 10 == Player1pos.x) {
            player1hp -= hd;
          }
          break;
        case 2:
          CHECK_RESULT(!SDL_BlitSurface(player2F3, NULL, screen, &Player2pos));
          break;
        case 3:
          for (int i = 0; i != 9; i++) {
            CHECK_RESULT(!SDL_BlitSurface(background, NULL, screen, NULL));
            CHECK_RESULT(!SDL_BlitSurface(KOP2[i], NULL, screen, &Player2pos));
            CHECK_RESULT(
                !SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
            CHECK_RESULT(!SDL_UpdateWindowSurface(window));
            SDL_Delay(60);
          }
          SDL_Delay(1000);
          SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                   "Blue Is The Winner", window);
          //
          //
          // TODO: CHANGE THIS TO GOTO TITLE SCREEN
          //
          //
          starttimeSD();
          SDL_Quit();
          exit(1);
          break;

          break;
        default:
          break;
      }
      if (p1action == 2 && p2action == 1) {
        p1d *= 2;
      }

      //
      // !Update Window Surface:
      CHECK_RESULT(!SDL_UpdateWindowSurface(window));

      // End Frame Delay
      auto frameDuration = (SDL_GetTicks() - startFrameTime);
      if (frameDuration < FrameTime) {
        // cout << FrameTime - frameDuration << endl;
        SDL_Delay(FrameTime - frameDuration);
      }
      // cout << "Player 1 hp:  " << player1hp << endl;
      // cout << "Player 2 hp:  " << player2hp << endl;
    }

    // Player 1 action
    p2action = 0;
    p1action = 0;
  }
  std::cout << "Out of Game Loop" << std::endl;
  std::cout << gettimeSD() / 100000000 << " millisecond shutdown" << std::endl;
}