#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#include "src/header.h"

#define IMGUI_IMPLEMENTATION
#include "imgui/imgui.h"
#include "imgui/imgui_sdl.h"

#ifdef IMGUI_IMPLEMENTATION
#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"
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
      exit(-1);                                                             \
    }                                                                       \
  }

//*
time_t punchclock1;
time_t blockclock1;
time_t punchclock2;
time_t blockclock2;
//*
bool running = true;

const Uint32 MaxFPS = 60;
const Uint32 FrameTime = (1000.0 / MaxFPS);
int p2d = hd;
int p1d = hd;
bool leftBut = false;
bool rightBut = false;
bool downBut = false;
bool leftBut2 = false;
bool rightBut2 = false;
bool downBut2 = false;
SDL_Rect Player1pos;
SDL_Rect Player2pos;
time_t timerS;

//*
//*
//*
//*
//*

// /home/m/.cache/bazel/_bazel_m/e203261d3dae0136730cffdcc1787516/execroot/__main__/bazel-out/k8-fastbuild/bin/main/game.runfiles/__main__/main/settings/config.json
// /home/m/.cache/bazel/_bazel_m/e203261d3dae0136730cffdcc1787516/execroot/__main__/bazel-out/k8-fastbuild/bin/main/game.runfiles/__main4__/main/settings/config.json
int main(int argc, char *argv[]) {
  // for (int i = 0; i < argc; i++) {
  //   cout << argv[i] << endl;
  // }
  string pathtosettings = argv[0];
  for (size_t i = pathtosettings.size() - 1; pathtosettings[i] != '/'; i--) {
    pathtosettings.pop_back();
  }
  string pathtoassets = pathtosettings;
  pathtosettings += "game.runfiles/__main__/main/settings/config.json";
  pathtoassets += "game.runfiles/__main__/main/";
  // cout << pathtosettings << endl;
  Point2D windowSize;

  getSettings(windowSize, pathtosettings);
  CHECK_RESULT(!SDL_Init(SDL_INIT_EVERYTHING));
  CHECK_RESULT(!Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))

  // cout << pathtoassets << endl;
  SDL_Window *window = nullptr;
  Mix_Music *music = nullptr;
  music = loadMusic(pathtoassets + "assets/Music/Music1.mp3");
  if (Mix_PlayingMusic() == 0) {
    CHECK_RESULT(!Mix_PlayMusic(music, -1));
  }
  window = SDL_CreateWindow("GG Boxing", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y,
                            SDL_WINDOW_SHOWN);
  CHECK_RESULT(window != nullptr);
  SDL_Surface *screen = SDL_GetWindowSurface(window);
  //
  //*Audio
  //
  //!
  //
  //
  if (argc > 0) {
    SDL_Log("argc is greater then 0");
    if (string(argv[1]) == "menu") {
    TOP:
      int resp = mainmenu(window, screen, pathtoassets);
      if (resp == 0) {
        SDL_Log("starting \n");
      } else if (resp == 1) {
        SDL_Log("quiting \n");
        running = false;
      } else if (resp == 2) {
        if (settings(window, screen, pathtoassets) == 0) {
          ;
        }

        //! Play button -> x:  502   y:  168 ->> x:  1436   y:  284
        //! Quit button -> x:  1439   y:  437 ->> x:  500   y:  317
        //! Settings button -> x:  503   y:  442 ->> x:  576   y:  498
      }
    }
  }

  int right = 0;
  int left = 0;
  int right2 = 0;
  int left2 = 0;
  // cout << pathtoassets << "assets/Ring.bmp" << endl;
  SDL_Surface *background = BMPloader(pathtoassets + "assets/Ring.bmp");
  SDL_Surface *player1F1 =
      BMPloader(pathtoassets + "assets/BLUE/Idle/Blue_Idle-0.bmp");
  SDL_Surface *player1F2 =
      BMPloader(pathtoassets + "assets/BLUE/PunchRight/Blue-Punch-Right-3.bmp");
  SDL_Surface *player1F3 =
      BMPloader(pathtoassets + "assets/BLUE/Blocking/Blocking.bmp");

  vector<SDL_Surface *> KOP1;
  for (int f = 0; f != 9; f++) {
    string file = pathtoassets + "assets/BLUE/KO/KO-" + to_string(f);
    KOP1.push_back(BMPloader(file + ".bmp"));
  }
  SDL_Surface *player2F1 =
      BMPloader(pathtoassets + "assets/RED/Idle/Red_Idle-0.bmp");
  SDL_Surface *player2F2 =
      BMPloader(pathtoassets + "assets/RED/PunchRight/Punch-3.bmp");
  SDL_Surface *player2F3 =
      BMPloader(pathtoassets + "assets/RED/Blocking/Blocking-3.bmp");

  vector<SDL_Surface *> KOP2;
  for (int f = 0; f != 9; f++) {
    string file = pathtoassets + "assets/RED/KO/KO-" + to_string(f);
    KOP2.push_back(BMPloader(file + ".bmp"));
  }
  createrect();
  int player1hp = 100;
  int player2hp = 100;
  int p1action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
  int p2action = 0;  // 0 = normal, 1 = hitting, 2 = block, 3 = KO
  while (running) {
    SDL_Event e;
    auto startFrameTime = SDL_GetTicks();
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
        starttimeSD();
        break;
      }
    }
    //
    // !player 1 animations and stuff
    //
    SDL_Log("running");
    const Uint8 *KeyboardState = SDL_GetKeyboardState(NULL);
    //* Movement
    leftBut = KeyboardState[SDL_SCANCODE_A];
    rightBut = KeyboardState[SDL_SCANCODE_D];
    rightBut2 = KeyboardState[SDL_SCANCODE_RIGHT];
    leftBut2 = KeyboardState[SDL_SCANCODE_LEFT];
    //* Combat
    if (KeyboardState[SDL_SCANCODE_LCTRL]) {
      punchclock1 = 0;
      p1action = 1;
    }
    if (KeyboardState[SDL_SCANCODE_S]) {
      blockclock1 = 0;
      downBut = true;
      p1action = 2;
    }
    if (KeyboardState[SDL_SCANCODE_RCTRL]) {
      punchclock2 = 0;
      p2action = 1;
    }
    if (KeyboardState[SDL_SCANCODE_DOWN]) {
      blockclock2 = 0;
      downBut2 = true;
      p2action = 2;
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
    //*
    //*
    //*
    //*
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
    SDL_Log("Drawing");
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
          CHECK_RESULT(!SDL_BlitSurface(player2F1, NULL, screen, &Player2pos));
          CHECK_RESULT(!SDL_UpdateWindowSurface(window));
          SDL_Delay(60);
        }
        SDL_Delay(1000);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                 "Red Is The Winner", window);
        goto TOP;
        //
        //
        // TODO: CHANGE THIS TO GOTO TITLE SCREEN
        //
        //
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
          CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
          CHECK_RESULT(!SDL_UpdateWindowSurface(window));
          SDL_Delay(60);
        }
        SDL_Delay(1000);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                 "Blue Is The Winner", window);
        //
        //
        // TODO: CHANGE THIS TO GOTO TITLE SCREEN
        goto TOP;
        //
        //
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

    // Player 1 action
    p2action = 0;
    p1action = 0;
  }
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}