#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <time.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#include "Cust_func/header.h"
#define IMGUI_IMPLEMENTATION
#include "imgui/imgui.h"
#include "imgui/imgui_sdl.h"

#ifdef IMGUI_IMPLEMENTATION
#include <iterator>

#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_widgets.cpp"
#endif

using namespace std;
#define PUNCHFRAME 60
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
      exit(-2);                                                             \
    }                                                                       \
  }

//
int main(int argc, char *argv[]) {
  bool debug = false;
  cout << argc << endl;
  if (argc > 1) {
    char ask = ' ';
    cout << "Welcome To Boxing2D, Created By Mikhail Chalakov. You're Running "
            "This In Debug Mode, This Could Lead To A Bit Of Performance "
            "Issues, Are You Sure (y,n):   "
         << flush;
    cin >> ask;
    debug = ask == 'y' ? true : false;
    ClearScreen();
  }
  string pathtoassets;
  string pathtosettings = pathtoassets = argv[0];
  for (size_t i = pathtosettings.size() - 1; pathtosettings[i] != '/'; i--) {
    pathtosettings.pop_back();
  }
  pathtoassets += ".runfiles/__main__/main/";
  //* Init
  // CHECK_RESULT(!Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096));
  createrect(Player1pos, Player2pos);
  Point2D window_size;
  getSettings(window_size, pathtoassets + "settings/config.json");
  SDL_Window *window = SDL_CreateWindow("Boxing Game", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, window_size.x,
                                        window_size.y, SDL_WINDOW_SHOWN);
  // load_files(pathtoassets);
  screen = SDL_GetWindowSurface(window);

  //* Load Images
  background = BMPloader(pathtoassets + "assets/Ring.bmp");
  player1F1 = BMPloader(pathtoassets + "assets/BLUE/Idle/Blue_Idle.bmp");
  player1F2 =
      BMPloader(pathtoassets + "assets/BLUE/PunchRight/Blue-Punch-Right-4.bmp");
  player1F3 = BMPloader(pathtoassets + "assets/BLUE/Blocking/Blocking.bmp");
  player2F1 = BMPloader(pathtoassets + "assets/RED/Idle/Red_Idle.bmp");
  player2F2 = BMPloader(pathtoassets + "assets/RED/PunchRight/Punch-4.bmp");
  player2F3 = BMPloader(pathtoassets + "assets/RED/Blocking/Blocking-0.bmp");
  const int SecondsBetweenPunch = 1;
  const Uint32 MaxFPS = 60;
  const Uint32 FrameTime = (1000.0 / MaxFPS);
  //!
  //!
  //!
  //* Game Loop
  //!
  //!
  //!
  long pc1 = time(&punchclock1);
  long pc2 = time(&punchclock2);
  long pb1 = time(&blockclock1);
  long pb2 = time(&blockclock2);
  SDL_Event e;
  bool gameLoop = true;
  while (gameLoop) {
    auto startFrameTime = SDL_GetTicks();  //* Update the window
    SDL_UpdateWindowSurface(window);
    //* Check if the close button is pressed
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        SDL_Quit();
        gameLoop = false;
      }
    }
    //* Movement
    const Uint8 *KeyboardState = SDL_GetKeyboardState(NULL);
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
    if (leftBut || rightBut) {
      p1action = 0;
    }
    if (leftBut2 || rightBut2) {
      p2action = 0;
    }
    //* Update the positions of the players
    //
    //* Player one:
    Player1pos.x += rightpos - leftpos;
    leftpos = 0;
    rightpos = 0;
    if (rightBut) {
      if (Player1pos.x + movment < Player2pos.x - dist) {
        rightpos += movment;
      }
    }
    if (leftBut) {
      if (Player1pos.x - movment >= -100) {
        leftpos += movment;
      }
    }
    //* Player two:
    Player2pos.x += leftpos2 - rightpos2;
    leftpos2 = 0;
    rightpos2 = 0;
    if (leftBut2) {
      if (Player2pos.x - movment > Player1pos.x + dist) {
        leftpos2 -= movment;
      }
    }
    if (rightBut2) {
      if (Player2pos.x - movment < 1920) {
        rightpos2 -= movment;
      }
    }
    //* Check the players health
    if (player1hp <= 0) {
      p1action = 3;
    }
    if (player2hp <= 0) {
      p2action = 3;
    }
    //
    // Clear Game Screen
    //
    SDL_BlitSurface(background, NULL, screen, NULL);
    //
    // Clear Game Screen END PLAYER DRAW START
    //
    if (debug) {
      cout << "\033[1;31m[+]   \033[0m Time Between Player One Punch Is:  "
           << time(&punchclock1) - pc1 << endl;
    }

    switch (p1action) {
      case 0:
        // Player One Normal
        CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
        break;
      case 1:
        // Player One Punching
        if (time(&punchclock1) - pc1 >= SecondsBetweenPunch) {
          CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
          pc1 = time(&punchclock1);
          if (Player1pos.x + dist + 10 >= Player2pos.x) {
            player2hp -= hd;
            if (debug) {
              cout << "\033[1;31m[+]   \033[0m Player Two Health Is:  "
                   << player2hp << endl;
            }
          }
        }
        break;
      case 2:
        // Player One blocking
        CHECK_RESULT(!SDL_BlitSurface(player1F3, NULL, screen, &Player1pos));
        break;
      case 3:
        // Player One KO
        for (int i = 0; i != 9; i++) {
          CHECK_RESULT(!SDL_BlitSurface(KOP1[i], NULL, screen, &Player1pos));
          CHECK_RESULT(!SDL_BlitSurface(player2F1, NULL, screen, &Player2pos));
          CHECK_RESULT(!SDL_UpdateWindowSurface(window));
          SDL_Delay(60);
        }
        SDL_Delay(1000);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                 "Red Is The Winner", window);
        // TODO: CHANGE THIS TO GOTO TITLE SCREEN
      default:;
    }
    //
    //
    //
    //
    //
    //
    if (debug) {
      cout << "\033[1;31m[+]   \033[0m Time Between Player Two Punch Is:  "
           << time(&punchclock2) - pc2 << endl;
    }
    switch (p2action) {
      case 0:
        CHECK_RESULT(!SDL_BlitSurface(player2F1, NULL, screen, &Player2pos));
        break;
      case 1:
        if (time(&punchclock2) - pc2 >= SecondsBetweenPunch) {
          CHECK_RESULT(!SDL_BlitSurface(player2F2, NULL, screen, &Player2pos));
          if (Player2pos.x + dist + 10 >= Player2pos.x) {
            player2hp -= hd;
            if (debug) {
              cout << "\033[1;31m[+]   \033[0m Player One Health Is:  "
                   << player1hp << endl;
            }
          }
          pc2 = time(&punchclock2);
        }
        break;
      case 2:
        CHECK_RESULT(!SDL_BlitSurface(player2F3, NULL, screen, &Player2pos));
        break;
      case 3:
        for (int i = 0; i != 9; i++) {
          CHECK_RESULT(!SDL_BlitSurface(KOP2[i], NULL, screen, &Player2pos));
          CHECK_RESULT(!SDL_BlitSurface(player1F1, NULL, screen, &Player1pos));
          CHECK_RESULT(!SDL_UpdateWindowSurface(window));
          SDL_Delay(60);
        }
        SDL_Delay(1000);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Winner",
                                 "Red Is The Winner", window);
        // TODO: CHANGE THIS TO GOTO TITLE SCREEN
    }
    //* Clean up the frame
    if (p1action == 2 && p2action == 1) {
      Player1Multiplier *= 2;
    }
    auto frameDuration = (SDL_GetTicks() - startFrameTime);
    if (frameDuration < FrameTime) {
      SDL_Delay(FrameTime - frameDuration);
    }
  }
  //
  //
  // GAME LOOP END
  //
  //
}
